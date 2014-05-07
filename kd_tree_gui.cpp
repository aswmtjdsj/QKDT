#include "kd_tree_gui.h"
#include "qmessagebox.h"

#include "common.h"

KD_Tree_GUI::KD_Tree_GUI(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	/*
	in the class implementation, probably in the constructor, after the ui->setupUi(this); command you would make the connection of the button and your slot:

	connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(mySlot()));
	*/
	connect(ui.ranGenButton, SIGNAL(clicked()), this, SLOT(ranGenButtonClicked())); // rand gen data and construct tree
	connect(ui.inputNumber, SIGNAL(returnPressed()), this, SLOT(inputNumberHandle())); // catch the return 
	connect(ui.clearInputButton, SIGNAL(clicked()), ui.inputNumber, SLOT(clear())); // clear the line edit and text view
	connect(ui.clearInputButton, SIGNAL(clicked()), ui.outputWindow, SLOT(clear()));
	connect(ui.graphicsView, SIGNAL(showInfo(QString)), ui.outputWindow, SLOT(setText(QString))); // glwidget shows debug or echo info to UI
	connect(ui.showPointsButton, SIGNAL(clicked()), this, SLOT(showPointsInfo())); // show input data in text view
	connect(this, SIGNAL(tranPoints(void *)), ui.graphicsView, SLOT(updatePoints(void *)));  // 
	connect(this, SIGNAL(tranSelectedPoints(void *)), ui.graphicsView, SLOT(updateSelectedPoints(void *))); 
	connect(ui.pointSizeChanger, SIGNAL(valueChanged(int)), ui.graphicsView, SLOT(updatePointSize(int)));
	connect(ui.graphicsView, SIGNAL(giveRange(KD_Point<double>, KD_Point<double>)), this, SLOT(getRange(KD_Point<double>, KD_Point<double>)));
	connect(ui.compDivChanger, SIGNAL(valueChanged(int)), this, SLOT(setCompDiv(int)));
	connect(ui.compPerformButton, SIGNAL(clicked()), this, SLOT(runPerformTest())); // rand gen data and construct tree

	number_of_points = 0;
	comp_test_div = 10;
	kd_tree = NULL;
}

KD_Tree_GUI::~KD_Tree_GUI()
{

}

void KD_Tree_GUI::ranGenButtonClicked() {

	// for test
	number_of_points = checkStringInteger(ui.inputNumber->text(), 100000); // need modification, not fixed threshold
	if(number_of_points == -2) {
		number_of_points = 0;
		show_msg = "Invalid input!\nPlease redo.";
		ui.outputWindow->setText(show_msg);
	}
	/*else if(number_of_points == -1) {
		number_of_points = 0;
		show_msg = "Input number too large!\nPlease redo.";
		ui.outputWindow->setText(show_msg);
	}*/
	else if(number_of_points == 0) {
		show_msg = "Number is zero!\nPlease redo.";
		ui.outputWindow->setText(show_msg);
	}
	else {
		kd_tree = new KD_Tree;
		kd_tree->randomPoints(number_of_points);

		if(number_of_points > 100000) {

		}
		else {
			emit tranPoints((void *)&(kd_tree->point_set));
		}

		kd_tree->build();
		show_msg = "KD tree built.\n";
		show_msg.append("Build time: " + QString::number(kd_tree->build_time) + " ms.\n");
		/*KD_Point<double> biu = kd_tree->root->mark_point;
		show_msg.append("Root: " + QString::number(biu.x) + "," + QString::number(biu.y) + "," + QString::number(biu.index) + "\n");*/
		ui.outputWindow->setText(show_msg);
		//showPointsInfo();
	}
}

void KD_Tree_GUI::inputNumberHandle() {
	ranGenButtonClicked();
}

int KD_Tree_GUI::checkStringInteger(const QString &input, const int &max_number) {
	int len = input.size();
	if(len == 0) {
		return -2;
	}
	for(int i = 0; i < len; i++) {
		if(!isdigit(input[i].toAscii())) { // invalid
			return -2;
		}
	}
	int ret_value = input.toInt();
	/*if(ret_value > max_number) { // too large
		return -1;
	}*/
	return ret_value;
}

void KD_Tree_GUI::showPointsInfo() {
	if(number_of_points == 0) {
		show_msg = "Not prepared!\nPlease redo.\n";
	}
	else {
		show_msg = "Number: ";
		show_msg.append(QString::number(number_of_points));
		show_msg.append("\n");
		for(int i = 0; i < kd_tree->number; i++) {
			QString cur_p = "P[";
			cur_p.append(QString::number(i));
			cur_p.append("]: (");
			cur_p.append(QString::number(kd_tree->point_set[i].x));
			cur_p.append(", ");
			cur_p.append(QString::number(kd_tree->point_set[i].y));
			cur_p.append(")\n");
			show_msg.append(cur_p);
		}
	}
	ui.outputWindow->setText(show_msg);
}


void KD_Tree_GUI::getRange(KD_Point<double> a, KD_Point<double> b) {
	if(kd_tree != NULL) {
		KD_Point<double> r1, r2;
		r1.x = min(a.x, b.x);
		r1.y = min(a.y, b.y);
		r2.x = max(a.x, b.x);
		r2.y = max(a.y, b.y);

		show_msg = "";
		show_msg.append("rect p1: (" + QString::number(r1.x) + ", " + QString::number(r1.y) + ").\n");
		show_msg.append("rect p2: (" + QString::number(r2.x) + ", " + QString::number(r2.y) + ").\n");

		std::vector<KD_Point<double> > biu = kd_tree->search(r1, r2);
		show_msg.append("KD tree search done.\n");
		show_msg.append("search time: " + QString::number(kd_tree->query_time) + " ms.\n");

		show_msg.append("Number: ");
		show_msg.append(QString::number(biu.size()));
		show_msg.append("\n");
		for(int i = 0; i < biu.size(); i++) {
			QString cur_p = "P[";
			cur_p.append(QString::number(biu[i].index));
			cur_p.append("]: ");
			cur_p.append("(");
			cur_p.append(QString::number(biu[i].x));
			cur_p.append(", ");
			cur_p.append(QString::number(biu[i].y));
			cur_p.append(")\n");
			show_msg.append(cur_p);
		}
		emit tranSelectedPoints((void *)&biu);
	}
	else {
		show_msg = "Not prepared!\nPlease redo.\n";
	}
	ui.outputWindow->setText(show_msg);
}

void KD_Tree_GUI::setCompDiv(int d) {
	comp_test_div = d;
}

void KD_Tree_GUI::runPerformTest() {
	if(kd_tree != NULL) {
		std::vector<float> comp_time;
		bool test_ok = kd_tree->search_compare(comp_test_div, comp_time);
		
		show_msg = "Number of Points: " + QString::number(number_of_points) + ".\n";
		show_msg.append("Search range: [x, y] x [x+" + QString::number(1./comp_test_div) + ", y+" + QString::number(1./comp_test_div) + "].\n");
		show_msg.append("For 1000 times search->\n");
		show_msg.append("KD query time: " + QString::number(comp_time[0]) + " ms.\n");
		show_msg.append("Brute Force query time: " + QString::number(comp_time[1]) + " ms.\n");
		if(!test_ok) {
			show_msg.append("test failed!\n");
		}
		else {
			show_msg.append("test okay!\n");
		}
	}
	else {
		show_msg = "Not prepared!\nPlease redo.\n";
	}
	ui.outputWindow->setText(show_msg);
}
