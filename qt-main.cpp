#include "kd_tree_gui.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	KD_Tree_GUI w;
	w.show();
	return a.exec();
}
