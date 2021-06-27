#include "chartpane.h"
#include "ui_chartpane.h"
#include "qwdialogpen.h"

ChartPane::ChartPane(QWidget *parent)
	: QWidget(parent)
{
	ui = new Ui::ChartPane();
	ui->setupUi(this);

	init();
}

ChartPane::~ChartPane()
{
	delete ui;
}

void ChartPane::drawBar()
{
	if (m_labels.empty())
	{
		QStringList labels = autoGenLabels(m_barData);
		setLabels(labels);
		return drawBar();
	}

	QMap<QString, QBarSet*> barSets;
	for each (QString label in m_labels)
	{
		QBarSet* barSet = new QBarSet(label);
		barSets.insert(label, barSet);
	}

	for (int nRow = 0; nRow < m_model->rowCount(); nRow++)
	{
		for (int nCol = 0; nCol < m_model->columnCount(); nCol++)
		{
			QString label = m_labels.at(nCol);
			if (Q_NULLPTR != barSets.value(label))
			{
				barSets.value(label)->append(m_model->item(nRow, nCol)->data().toLongLong());
			}
		}
	}

	if (m_barOrientation == VERTICAL_BAR)
	{
		QBarSeries* series = new QBarSeries();
		curSeries = series;
		for each (QString setKey in barSets.keys())
		{
			series->append(barSets.value(setKey));
		}
		m_chart->addSeries(series);

		QStringList categories = m_barData.keys();

		QBarCategoryAxis *axisX = new QBarCategoryAxis();
		axisX->append(categories);
		axisX->setGridLineVisible(false);
		m_chart->setAxisX(axisX, series);
		axisX->setRange(categories.at(0), categories.at(categories.size() - 1));

		QValueAxis* axisY = new QValueAxis();
		curAxis = axisY;
		axisY->setRange(m_minValue, m_maxValue);
		axisY->setTitleText(m_label);
		axisY->setGridLineVisible(false);
		axisY->applyNiceNumbers();
		m_chart->setAxisY(axisY, series);

		m_chart->legend()->setAlignment(Qt::AlignBottom);

		series->setLabelsVisible(true);
		series->setLabelsPosition(QAbstractBarSeries::LabelsInsideEnd);
	}
	else
	{
		QHorizontalBarSeries* series = new QHorizontalBarSeries();
		curHorSeries = series;
		for each (QString setKey in barSets.keys())
		{
			series->append(barSets.value(setKey));
		}
		m_chart->addSeries(series);

		QStringList categories = m_barData.keys();

		QBarCategoryAxis *axisY = new QBarCategoryAxis();
		axisY->append(categories);
		axisY->setGridLineVisible(false);
		m_chart->setAxisY(axisY, series);
		axisY->setRange(categories.at(0), categories.at(categories.size() - 1));

		QValueAxis* axisX = new QValueAxis();
		curAxis = axisX;
		axisX->setRange(m_minValue, m_maxValue);
		axisX->setTitleText(m_label);
		axisX->setGridLineVisible(false);
		axisX->applyNiceNumbers();
		m_chart->setAxisX(axisX, series);

		m_chart->legend()->setAlignment(Qt::AlignTop);

		series->setLabelsVisible(true);
		series->setLabelsPosition(QAbstractBarSeries::LabelsInsideEnd);
	}

	m_chart->legend()->setVisible(true);
	m_chart->setTitle(m_title);

	foreach(QLegendMarker* marker, m_chart->legend()->markers()) {
		QObject::disconnect(marker, SIGNAL(clicked()), this, SLOT(on_LegendMarkerClicked()));
		QObject::connect(marker, SIGNAL(clicked()), this, SLOT(on_LegendMarkerClicked()));
	}
}

void ChartPane::setData(const QMap<QString, QMap<QString, long long>>& barData)
{
	clear();
	m_barData = barData;
	analyseData(m_barData, m_minValue, m_maxValue);
}

void ChartPane::setLabels(const QStringList& labels)
{
	m_labels = labels;

	//准备Model
	buildModel(m_barData, m_labels, m_model);
}

void ChartPane::setYLabel(const QString& yLabel)
{
	m_label = yLabel;
}

void ChartPane::setOrientation(BarOrientation orientation)
{
	m_barOrientation = orientation;
}

QT_CHARTS_NAMESPACE::QChart* ChartPane::chart()
{
	return m_chart;
}

void ChartPane::init()
{
	m_chart = new QChart();
	//样式设置
	m_chart->setTheme(QChart::ChartThemeQt);
	m_chart->setMargins(QMargins(6, 6, 6, 6));
	m_chart->setAnimationOptions(QChart::SeriesAnimations);
	ui->chartViewBar->setChart(m_chart);
	ui->chartViewBar->setRenderHint(QPainter::Antialiasing);
	m_model = new QStandardItemModel(this);
	m_barOrientation = VERTICAL_BAR;

	ui->toolBox->hide();
}

void ChartPane::clear()
{
	m_barData.clear();
	clearChartUI();

	if (Q_NULLPTR != m_model)
	{
		m_model->clear();
	}

	m_label.clear();
	m_labels.clear();
	m_title.clear();
	m_minValue = 0;
	m_maxValue = 0;
}

void ChartPane::clearChartUI()
{
	if (Q_NULLPTR != m_chart)
	{
		m_chart->removeAllSeries();
		m_chart->removeAxis(m_chart->axisX());
		m_chart->removeAxis(m_chart->axisY());
	}
}

QStringList ChartPane::autoGenLabels(const QMap<QString, QMap<QString, long long>>& data)
{
	QSet<QString> labels;
	for each (QString dataKey in data.keys())
	{
		QSet<QString> curLabels = data.value(dataKey).keys().toSet();
		labels = labels + curLabels;
	}

	return labels.toList();
}

void ChartPane::analyseData(const QMap<QString, QMap<QString, long long>>& data,
	long long& minVlue, long long& maxValue)
{
	for each (QString XKey in data.keys())
	{
		for each (QString YKey in data.value(XKey).keys())
		{
			if (m_minValue > data.value(XKey).value(YKey))
			{
				m_minValue = data.value(XKey).value(YKey);
			}
			if (m_maxValue < data.value(XKey).value(YKey))
			{
				m_maxValue = data.value(XKey).value(YKey);
			}
		}
	}
}

void ChartPane::buildModel(const QMap<QString, QMap<QString, long long>>& data,
	const QStringList& labels, QStandardItemModel* model)
{
	model->setColumnCount(labels.length());
	model->setRowCount(data.size());
	model->setHorizontalHeaderLabels(labels);
	model->setVerticalHeaderLabels(data.keys());

	int nRow = 0;
	for each (QString dataKey in data.keys())
	{
		int nCol = 0;
		for each (QString label in labels)
		{
			long long value = data.value(dataKey).value(label);
			QStandardItem* aItem = new QStandardItem(value);
			aItem->setData(QVariant::fromValue(value));
			model->setItem(nRow, nCol, aItem);
			nCol++;
		}
		nRow++;
	}
}

void ChartPane::setTitle(const QString& title)
{
	m_title = title;
}

void ChartPane::on_btn_styleSet_clicked()
{
	if (ui->toolBox->isVisible())
	{
		ui->toolBox->hide();
		ui->btn_styleSet->setText(QString::fromLocal8Bit("样式设置"));
	}
	else
	{
		ui->toolBox->show();
		ui->btn_styleSet->setText(QString::fromLocal8Bit("关闭设置"));
	}
}

void ChartPane::on_LegendMarkerClicked()
{
	QLegendMarker* marker = qobject_cast<QLegendMarker*> (sender());

	switch (marker->type())
	{
	case QLegendMarker::LegendMarkerTypeBar:
	{
		marker->series()->setVisible(!marker->series()->isVisible());
		marker->setVisible(true);
		qreal alpha = 1.0;
		if (!marker->series()->isVisible())
			alpha = 0.5;

		QColor color;
		QBrush brush = marker->labelBrush();
		color = brush.color();
		color.setAlphaF(alpha);
		brush.setColor(color);
		marker->setLabelBrush(brush);

		brush = marker->brush();
		color = brush.color();
		color.setAlphaF(alpha);
		brush.setColor(color);
		marker->setBrush(brush);

		QPen pen = marker->pen();
		color = pen.color();
		color.setAlphaF(alpha);
		pen.setColor(color);
		marker->setPen(pen);
		break;
	}
	default:
		break;
	}
}

void ChartPane::on_btnSetTitle_clicked()
{
	//设置图标标题文字
	QString str = ui->editTitle->text();
	ui->chartViewBar->chart()->setTitle(str);
}

void ChartPane::on_btnSetTitleFont_clicked()
{
	//设置图标标题文字的字体
	QFont font = ui->chartViewBar->chart()->titleFont();
	bool  ok = false;
	font = QFontDialog::getFont(&ok, font);
	if (ok)
		ui->chartViewBar->chart()->setTitleFont(font);
}

void ChartPane::on_btnSetMargin_clicked()
{
	//设置图标的4个边距
	QMargins    mgs;
	mgs.setLeft(ui->spinMarginLeft->value());
	mgs.setRight(ui->spinMarginRight->value());
	mgs.setTop(ui->spinMarginTop->value());
	mgs.setBottom(ui->spinMarginBottom->value());
	ui->chartViewBar->chart()->setMargins(mgs);
}

void ChartPane::on_chkBarLabelVisible_clicked(bool checked)
{
	//序列的数据点标签是否可见
	if (m_barOrientation == VERTICAL_BAR)
	{
		curSeries->setLabelsVisible(checked);
	}
	else
	{
		curHorSeries->setLabelsVisible(checked);
	}
}

void ChartPane::on_radioButton_middle_clicked()
{
	if (m_barOrientation == VERTICAL_BAR)
	{
		curSeries->setLabelsPosition(QAbstractBarSeries::LabelsCenter);
	}
	else
	{
		curHorSeries->setLabelsPosition(QAbstractBarSeries::LabelsCenter);
	}
}

void ChartPane::on_radioButton_top_clicked()
{
	if (m_barOrientation == VERTICAL_BAR)
	{
		curSeries->setLabelsPosition(QAbstractBarSeries::LabelsInsideEnd);
	}
	else
	{
		curHorSeries->setLabelsPosition(QAbstractBarSeries::LabelsInsideEnd);
	}
}

void ChartPane::on_radioButton_bottom_clicked()
{
	if (m_barOrientation == VERTICAL_BAR)
	{
		curSeries->setLabelsPosition(QAbstractBarSeries::LabelsInsideBase);
	}
	else
	{
		curHorSeries->setLabelsPosition(QAbstractBarSeries::LabelsInsideBase);
	}
}

void ChartPane::on_radioButton_out_clicked()
{
	if (m_barOrientation == VERTICAL_BAR)
	{
		curSeries->setLabelsPosition(QAbstractBarSeries::LabelsOutsideEnd);
	}
	else
	{
		curHorSeries->setLabelsPosition(QAbstractBarSeries::LabelsOutsideEnd);
	}
}

void ChartPane::on_chkLegendVisible_clicked(bool checked)
{
	//图例是否可见
	ui->chartViewBar->chart()->legend()->setVisible(checked);
}

void ChartPane::on_btnSetAxisRange_clicked()
{
	//设置坐标轴的坐标范围
	curAxis->setRange(ui->spinAxisMin->value(), ui->spinAxisMax->value());
}

void ChartPane::on_spinTickCount_valueChanged(int arg1)
{
	curAxis->setTickCount(arg1);
}

void ChartPane::on_spinMinorTickCount_valueChanged(int arg1)
{
	curAxis->setMinorTickCount(arg1);
}

void ChartPane::on_checkBox_clicked(bool checked)
{
	curAxis->setLineVisible(checked);
}

void ChartPane::on_chkGridLineVisible_clicked(bool checked)
{
	//轴的网格线是否可见
	curAxis->setGridLineVisible(checked);
}

void ChartPane::on_chkMinorTickVisible_clicked(bool checked)
{
	//次级刻度是否可见
	curAxis->setMinorGridLineVisible(checked);
}

void ChartPane::on_chkBoxLegendBackground_clicked(bool checked)
{
	//图例的背景是否可见
	ui->chartViewBar->chart()->legend()->setBackgroundVisible(checked);
}

void ChartPane::on_radioButton_clicked()
{
	//图例的位置
	ui->chartViewBar->chart()->legend()->setAlignment(Qt::AlignTop);
}

void ChartPane::on_radioButton_2_clicked()
{
	//图例的位置
	ui->chartViewBar->chart()->legend()->setAlignment(Qt::AlignBottom);
}

void ChartPane::on_radioButton_3_clicked()
{
	//图例的位置
	ui->chartViewBar->chart()->legend()->setAlignment(Qt::AlignLeft);
}

void ChartPane::on_radioButton_4_clicked()
{
	//图例的位置
	ui->chartViewBar->chart()->legend()->setAlignment(Qt::AlignRight);
}

void ChartPane::on_btnLegendFont_clicked()
{
	//图例的字体设置
	QFont font = ui->chartViewBar->chart()->legend()->font();
	bool  ok = false;
	font = QFontDialog::getFont(&ok, font);
	if (ok)
		ui->chartViewBar->chart()->legend()->setFont(font);
}

void ChartPane::on_btnLegendlabelColor_clicked()
{
	//图例的文字颜色设置
	QColor  color = ui->chartViewBar->chart()->legend()->labelColor();
	color = QColorDialog::getColor(color);
	if (color.isValid())
		ui->chartViewBar->chart()->legend()->setLabelColor(color);
}

void ChartPane::on_chkBoxVisible_clicked(bool checked)
{
	//坐标轴是否可见
	curAxis->setVisible(checked);
}

void ChartPane::on_btnAxisSetTitle_clicked()
{
	//设置坐标轴的标题
	curAxis->setTitleText(ui->editAxisTitle->text());
}

void ChartPane::on_btnAxisSetTitleFont_clicked()
{
	//设置坐标轴的标题的字体
	QFont   font = curAxis->titleFont();

	bool    ok = false;
	font = QFontDialog::getFont(&ok, font);
	if (ok)
		curAxis->setTitleFont(font);
}

void ChartPane::on_chkBoxAxisTitle_clicked(bool checked)
{
	//轴标题是否可见
	curAxis->setTitleVisible(checked);
}

void ChartPane::on_pushButton_clicked()
{
	//设置坐标轴刻度标签的文字格式
	curAxis->setLabelFormat(ui->editAxisLabelFormat->text());
}

void ChartPane::on_btnAxisLabelColor_clicked()
{
	//设置坐标轴刻度标签的文字颜色
	QColor   color = curAxis->labelsColor();

	color = QColorDialog::getColor(color);
	if (color.isValid())
		curAxis->setLabelsColor(color);
}

void ChartPane::on_btnAxisLabelFont_clicked()
{
	//设置坐标轴刻度标签的文字字体
	QFont   font = curAxis->labelsFont();

	bool    ok = false;
	font = QFontDialog::getFont(&ok, font);
	if (ok)
		curAxis->setLabelsFont(font);
}

void ChartPane::on_chkBoxLabelsVisible_clicked(bool checked)
{
	//轴的刻度标签是否可见
	curAxis->setLabelsVisible(checked);
}

void ChartPane::on_btnGridLineColor_clicked()
{
	//网格线的颜色设置
	QColor   color = curAxis->gridLineColor();

	color = QColorDialog::getColor(color);
	if (color.isValid())
		curAxis->setGridLineColor(color);
}

void ChartPane::on_pushButton_10_clicked()
{
	//网格线的Pen设置
	QPen    pen;
	pen = curAxis->gridLinePen();

	bool    ok = false;
	pen = QWDialogPen::getPen(pen, ok);

	if (ok)
		curAxis->setGridLinePen(pen);
}

void ChartPane::on_chkAxisLineVisible_clicked(bool checked)
{
	//刻度是否可见
	curAxis->setLineVisible(checked);
}

void ChartPane::on_btnAxisLinePen_clicked()
{
	QPen    pen;
	pen = curAxis->linePen();

	bool    ok = false;
	pen = QWDialogPen::getPen(pen, ok);

	if (ok)
		curAxis->setLinePen(pen);
}

void ChartPane::on_btnAxisLinePenColor_clicked()
{
	QColor   color = curAxis->linePenColor();

	color = QColorDialog::getColor(color);
	if (color.isValid())
		curAxis->setLinePenColor(color);
}

void ChartPane::on_btnMinorColor_clicked()
{
	//次级刻度网格线颜色
	QColor   color = curAxis->minorGridLineColor();

	color = QColorDialog::getColor(color);
	if (color.isValid())
		curAxis->setMinorGridLineColor(color);
}

void ChartPane::on_btnMinorPen_clicked()
{
	//次级刻度线Pen设置
	QPen    pen;
	pen = curAxis->minorGridLinePen();

	bool    ok = false;
	pen = QWDialogPen::getPen(pen, ok);

	if (ok)
		curAxis->setMinorGridLinePen(pen);
}

void ChartPane::on_cBoxAnimation_currentIndexChanged(int index)
{
	//动画效果
	ui->chartViewBar->chart()->setAnimationOptions(QChart::AnimationOptions(index));
}

void ChartPane::on_cBoxTheme_currentIndexChanged(int index)
{
	//图标的主题
	ui->chartViewBar->chart()->setTheme(QChart::ChartTheme(index));
}

void ChartPane::on_actZoomIn_triggered()
{
	//放大
	ui->chartViewBar->chart()->zoom(1.2);//zoomIn();
}

void ChartPane::on_actZoomOut_triggered()
{
	//缩小
	ui->chartViewBar->chart()->zoom(0.8);//zoomOut();
}

void ChartPane::on_actZoomReset_triggered()
{
	//复位
	ui->chartViewBar->chart()->zoomReset();
}