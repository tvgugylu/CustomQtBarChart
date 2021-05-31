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
	 *	��״ͼ����
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
	*@brief:		���ƶ�ά��״ͼ
	*@return:		void
	*@accesss:		public 
	*/
	void drawBar();
	/*!
	*@method:		setData
	*@brief:		�����ά��״ͼ����
	*@param[in]:	barData	��ά��״ͼ����  
	*@return:		void
	*@accesss:		public 
	*/
	void setData(const QMap<QString, QMap<QString, long long>>& barData);

	/*!
	*@method:		setLabels
	*@brief:		ָ��Label˳��
	*@param[in]:	labels  ָ��˳���label�ַ���
	*@return:		void
	*@accesss:		public 
	*/
	void setLabels(const QStringList& labels);

	/*!
	*@method:		setTitle
	*@brief:		������״ͼ����
	*@param[in]:	title	��״ͼ����
	*@return:		void
	*@accesss:		public 
	*/
	void setTitle(const QString& title);

	/*!
	*@method:		setYLabel
	*@brief:		����Y��Label��ʾ�ı� 
	*@param[in]:	yLabel	Y��Label��ʾ�ı�
	*@return:		void
	*@accesss:		public 
	*/
	void setYLabel(const QString& yLabel);

	/*!
	*@method:		setOrientation
	*@brief:		������״ͼ��������
	*@param[out]:	orientation
	*@param[in]:	orientation  
	*@return:		void
	*@accesss:		public 
	*/
	void setOrientation(BarOrientation orientation);

	/*!
	*@method:		chart
	*@brief:		��ȡQChart������������
	*@return:		QT_CHARTS_NAMESPACE::QChart*
	*@accesss:		public 
	*/
	QChart* chart();

protected:

	/*!
	*@method:		init
	*@brief:		��ʼ��ģ�������
	*@return:		void
	*@accesss:		protected 
	*/
	void init();

	/*!
	*@method:		clear
	*@brief:		����ģ�������
	*@return:		void
	*@accesss:		protected 
	*/
	void clear();

	/*!
	*@method:		clearChartUI
	*@brief:		��������
	*@return:		void
	*@accesss:		protected 
	*/
	void clearChartUI();

	/*!
	*@method:		autoGenLabels
	*@brief:		���������model�����Զ�����Labels
	*@param[in]:	data   
	*@return:		QStringList	Labels
	*@accesss:		protected 
	*/
	QStringList autoGenLabels(const QMap<QString,QMap<QString,long long>>& data);

	/*!
	*@method:		analyseData
	*@brief:		������������ݻ�ȡ���ֵ����Сֵ
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
	*@brief:		�������ݺ�Label����Model����
	*@param[out]:	model
	*@param[in]:	data  
	*@param[in]:	labels  
	*@return:		void
	*@accesss:		protected 
	*/
	void buildModel(const QMap<QString, QMap<QString, long long>>& data,
		const QStringList& labels,QStandardItemModel* model);
	
	/*
	 *	��ά��״ͼ����
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
	 *	��ʽ����������
	 */
	QBarSeries *curSeries;				//��ǰ����
	QHorizontalBarSeries *curHorSeries;	//��ǰ����
	QValueAxis *curAxis;				//��ǰ������

private slots:
	void on_btn_styleSet_clicked();

	void on_LegendMarkerClicked();		//ͼ������

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
