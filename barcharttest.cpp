#include "barcharttest.h"

BarChartTest::BarChartTest(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	QMap<QString, QMap<QString, long long>> scores;
	QMap<QString, long long> hanmeimeiScores;
	hanmeimeiScores.insert(YUWEN, 90);
	hanmeimeiScores.insert(SHUXUE, 85);
	hanmeimeiScores.insert(YINGYU, 95);
	hanmeimeiScores.insert(WULI, 80);
	hanmeimeiScores.insert(LISHI, 98);
	scores.insert(HANMEIMEI, hanmeimeiScores);

	QMap<QString, long long> lileiScores;
	lileiScores.insert(YUWEN, 78);
	lileiScores.insert(SHUXUE, 99);
	lileiScores.insert(YINGYU, 80);
	lileiScores.insert(WULI, 92);
	lileiScores.insert(LISHI, 75);
	scores.insert(LILEI, lileiScores);

	QMap<QString, long long> polyScores;
	polyScores.insert(YUWEN, 95);
	//polyScores.insert(SHUXUE, 60);
	polyScores.insert(YINGYU, 99);
	polyScores.insert(WULI, 61);
	polyScores.insert(LISHI, 96);
	scores.insert(POLY, polyScores);

	QStringList labels;
	labels << YUWEN << SHUXUE << YINGYU << WULI << LISHI;

	ui.widget->setData(scores);
	//ui.widget->setLabels(labels);
	ui.widget->setTitle(QString::fromLocal8Bit("成绩统计图"));
	ui.widget->setYLabel(QString::fromLocal8Bit("分数"));
	ui.widget->setOrientation(ChartPane::HORIZONTAL_BAR);
	ui.widget->drawBar();
}

BarChartTest::~BarChartTest()
{
	
}
