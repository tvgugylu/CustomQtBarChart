#include "barcharttest.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	BarChartTest w;
	w.show();
	return a.exec();
}
