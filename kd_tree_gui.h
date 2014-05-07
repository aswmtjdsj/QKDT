#ifndef KD_TREE_GUI_H
#define KD_TREE_GUI_H

#include <QtGui/QMainWindow>
#include "ui_kd_tree_gui.h"

#include "kd_tree.h"

class KD_Tree_GUI : public QMainWindow
{
	Q_OBJECT

public:
	KD_Tree_GUI(QWidget *parent = 0, Qt::WFlags flags = 0);
	~KD_Tree_GUI();

	int checkStringInteger(const QString &, const int &);

signals:
	//void tranPoints(std::vector<KD_Point<double> > *);
	void tranPoints(void *);
	void tranSelectedPoints(void *);

	public slots:
		void ranGenButtonClicked(); 
		void inputNumberHandle();
		void showPointsInfo();
		void getRange(KD_Point<double>, KD_Point<double>);
		void setCompDiv(int);
		void runPerformTest();

private:
	Ui::KD_Tree_GUIClass ui;

public:
	long long number_of_points;
	KD_Tree * kd_tree;
	QString show_msg;

	int comp_test_div;
};

#endif // KD_TREE_GUI_H
