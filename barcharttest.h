#ifndef BARCHARTTEST_H
#define BARCHARTTEST_H

#include <QtWidgets/QMainWindow>
#include "ui_barcharttest.h"

#include <QString>

#define HANMEIMEI	QString::fromLocal8Bit("韩梅梅")
#define LILEI		QString::fromLocal8Bit("李雷")
#define POLY		QString::fromLocal8Bit("波利")

#define YUWEN		QString::fromLocal8Bit("语文")
#define SHUXUE		QString::fromLocal8Bit("数学")
#define YINGYU		QString::fromLocal8Bit("英语")
#define WULI		QString::fromLocal8Bit("物理")
#define LISHI		QString::fromLocal8Bit("历史")

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
