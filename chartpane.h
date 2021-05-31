#ifndef CHARTPANE_H
#define CHARTPANE_H

#include <QtCharts>
QT_CHARTS_USE_NAMESPACE

#include <QWidget>
#include <QStandardItemModel>
#include <QItemSelectionModel>

namespace Ui {class ChartPane;};

class ChartPane : public QWidget
{
	Q_OBJECT
public:
	/*
	 *	柱状图朝向
	 */
	enum BarOrientation
	{
		VERTICAL_BAR = 0,
		HORIZONTAL_BAR,
	};

	ChartPane(QWidget *parent = 0);
	~ChartPane();
	

	/*!
	*@method:		draw
	*@brief:		绘制二维柱状图
	*@return:		void
	*@accesss:		public 
	*/
	void drawBar();
	/*!
	*@method:		setData
	*@brief:		输入二维柱状图数据
	*@param[in]:	barData	二维柱状图数据  
	*@return:		void
	*@accesss:		public 
	*/
	void setData(const QMap<QString, QMap<QString, long long>>& barData);

	/*!
	*@method:		setLabels
	*@brief:		指定Label顺序
	*@param[in]:	labels  指定顺序的label字符串
	*@return:		void
	*@accesss:		public 
	*/
	void setLabels(const QStringList& labels);

	/*!
	*@method:		setTitle
	*@brief:		设置柱状图标题
	*@param[in]:	title	柱状图标题
	*@return:		void
	*@accesss:		public 
	*/
	void setTitle(const QString& title);

	/*!
	*@method:		setYLabel
	*@brief:		设置Y轴Label显示文本 
	*@param[in]:	yLabel	Y轴Label显示文本
	*@return:		void
	*@accesss:		public 
	*/
	void setYLabel(const QString& yLabel);

	/*!
	*@method:		setOrientation
	*@brief:		设置柱状图朝向属性
	*@param[out]:	orientation
	*@param[in]:	orientation  
	*@return:		void
	*@accesss:		public 
	*/
	void setOrientation(BarOrientation orientation);

	/*!
	*@method:		chart
	*@brief:		获取QChart对象，用于设置
	*@return:		QT_CHARTS_NAMESPACE::QChart*
	*@accesss:		public 
	*/
	QChart* chart();

protected:

	/*!
	*@method:		init
	*@brief:		初始化模型与界面
	*@return:		void
	*@accesss:		protected 
	*/
	void init();

	/*!
	*@method:		clear
	*@brief:		清理模型与界面
	*@return:		void
	*@accesss:		protected 
	*/
	void clear();

	/*!
	*@method:		clearChartUI
	*@brief:		界面清理
	*@return:		void
	*@accesss:		protected 
	*/
	void clearChartUI();

	/*!
	*@method:		autoGenLabels
	*@brief:		根据输入的model数据自动生成Labels
	*@param[in]:	data   
	*@return:		QStringList	Labels
	*@accesss:		protected 
	*/
	QStringList autoGenLabels(const QMap<QString,QMap<QString,long long>>& data);

	/*!
	*@method:		analyseData
	*@brief:		分析输入的数据获取最大值、最小值
	*@param[out]:	minVlue
	*@param[out]:	maxValue
	*@param[in]:	data  
	*@return:		void
	*@accesss:		protected 
	*/
	void analyseData(const QMap<QString, QMap<QString, long long>>& data,
		long long& minVlue,long long& maxValue);

	/*!
	*@method:		buildModel
	*@brief:		利用数据和Label构建Model数据
	*@param[out]:	model
	*@param[in]:	data  
	*@param[in]:	labels  
	*@return:		void
	*@accesss:		protected 
	*/
	void buildModel(const QMap<QString, QMap<QString, long long>>& data,
		const QStringList& labels,QStandardItemModel* model);
	
	/*
	 *	二维柱状图数据
	 */
	QMap<QString, QMap<QString, long long>> m_barData;
	
	QStandardItemModel* m_model;
	QChart* m_chart;
	QString m_title;
	QString m_label;
	QStringList m_labels;
	long long m_minValue;
	long long m_maxValue;
	BarOrientation m_barOrientation;

private:
	Ui::ChartPane *ui;

	/*
	 *	样式设置所需项
	 */
	QBarSeries *curSeries;				//当前序列
	QHorizontalBarSeries *curHorSeries;	//当前序列
	QValueAxis *curAxis;				//当前坐标轴

private slots:
	void on_btn_styleSet_clicked();

	void on_LegendMarkerClicked();		//图例单击

	void on_btnSetTitle_clicked();

	void on_btnSetTitleFont_clicked();

	void on_btnSetMargin_clicked();

	void on_chkBarLabelVisible_clicked(bool checked);

	void on_radioButton_middle_clicked();

	void on_radioButton_top_clicked();

	void on_radioButton_bottom_clicked();

	void on_radioButton_out_clicked();

	void on_chkLegendVisible_clicked(bool checked);

	void on_btnSetAxisRange_clicked();

	void on_spinTickCount_valueChanged(int arg1);

	void on_spinMinorTickCount_valueChanged(int arg1);

	void on_checkBox_clicked(bool checked);

	void on_chkGridLineVisible_clicked(bool checked);

	void on_chkMinorTickVisible_clicked(bool checked);

	void on_chkBoxLegendBackground_clicked(bool checked);

	void on_radioButton_clicked();

	void on_radioButton_2_clicked();

	void on_radioButton_3_clicked();

	void on_radioButton_4_clicked();

	void on_btnLegendFont_clicked();

	void on_btnLegendlabelColor_clicked();

	void on_chkBoxVisible_clicked(bool checked);

	void on_btnAxisSetTitle_clicked();

	void on_btnAxisSetTitleFont_clicked();

	void on_chkBoxAxisTitle_clicked(bool checked);

	void on_pushButton_clicked();

	void on_btnAxisLabelColor_clicked();

	void on_btnAxisLabelFont_clicked();

	void on_chkBoxLabelsVisible_clicked(bool checked);

	void on_btnGridLineColor_clicked();

	void on_pushButton_10_clicked();

	void on_chkAxisLineVisible_clicked(bool checked);

	void on_btnAxisLinePen_clicked();

	void on_btnAxisLinePenColor_clicked();

	void on_btnMinorColor_clicked();

	void on_btnMinorPen_clicked();

	void on_cBoxAnimation_currentIndexChanged(int index);

	void on_cBoxTheme_currentIndexChanged(int index);

	void on_actZoomIn_triggered();

	void on_actZoomOut_triggered();

	void on_actZoomReset_triggered();
};



#endif // CHARTPANE_H
