#ifndef BARCHARTTEST_H
#define BARCHARTTEST_H

#include <QtWidgets/QMainWindow>
#include "ui_barcharttest.h"

#include <QString>

#define HANMEIMEI	QString::fromLocal8Bit("��÷÷")
#define LILEI		QString::fromLocal8Bit("����")
#define POLY		QString::fromLocal8Bit("����")

#define YUWEN		QString::fromLocal8Bit("����")
#define SHUXUE		QString::fromLocal8Bit("��ѧ")
#define YINGYU		QString::fromLocal8Bit("Ӣ��")
#define WULI		QString::fromLocal8Bit("����")
#define LISHI		QString::fromLocal8Bit("��ʷ")

class BarChartTest : public QMainWindow
{
	Q_OBJECT

public:
	BarChartTest(QWidget *parent = 0);
	~BarChartTest();

private:
	Ui::BarChartTestClass ui;
};

#endif // BARCHARTTEST_H
