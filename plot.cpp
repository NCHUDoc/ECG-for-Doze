#include "adplot.h"
#include "ui_adplot.h"
#include <QtGui/QApplication>
#include <qapplication.h>
#include <qlayout.h>
#include <qlabel.h>
#include <qpainter.h>
#include <qwt_plot_layout.h>
#include <qwt_plot_curve.h>
#include <qwt_scale_draw.h>
#include <qwt_scale_widget.h>
#include <qwt_legend.h>
#include <qwt_legend_item.h>
#include <QTime>
#include <qtimer.h>
#include <QMessageBox>
#include <qcolor.h>
#include <qwt_plot_zoomer.h>
#include <qfile.h>
#include <qtextstream.h>

#include <stdio.h>
#include <stdlib.h>
//#include "adplot.cpp"
#include "so.cpp"



int sample_rate=255;
int cal_time=300;
int cal_point=sample_rate*cal_time;
int updata_time=20;
int updata_point=updata_time*sample_rate;
int pre=0;



class TimeScaleDraw: public QwtScaleDraw
{
public:
TimeScaleDraw(const QTime &base):
baseTime(base)
{
}

virtual QwtText label(double v) const
{
QTime upTime = baseTime.addSecs((int)v);
return upTime.toString();
}

private:
QTime baseTime;
};

//psdPlot

AdPlot::AdPlot(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdPlot)
{
    ui->setupUi(this);
    ui->qwtPlot->setAutoReplot(false);
    ui->psdPlot->setAutoReplot(false);
    QTime curTime;
    curTime = curTime.currentTime();



    QwtLegend *legend = new QwtLegend;
    //legend->setItemMode(QwtLegend::CheckableItem);
    //ui->qwtPlot->insertLegend(legend, QwtPlot::RightLegend);
    ui->qwtPlot->setAxisTitle(QwtPlot::xBottom, " System Uptime [h:m:s]");
    //ui->qwtPlot->setAxisScaleDraw(QwtPlot::xBottom,  new TimeScaleDraw(curTime));
    ui->qwtPlot->setAxisScale(QwtPlot::xBottom, 0, xMaxScale = 10);
    ui->qwtPlot->setAxisLabelAlignment(QwtPlot::xBottom, Qt::AlignLeft | Qt::AlignBottom);
    ui->qwtPlot->setAxisTitle(QwtPlot::yLeft, "V");
    ui->qwtPlot->setAxisScale(QwtPlot::yLeft, 50, 300);


    QwtScaleWidget *scaleWidget = ui->qwtPlot->axisWidget(QwtPlot::xBottom);
    const int fmh = QFontMetrics(scaleWidget->font()).height();
    scaleWidget->setMinBorderDist(0, fmh / 2);


    p_adplot = new QwtPlotCurve();
    QColor c = Qt::red;
    c.setAlpha(150);
    p_adplot->setPen(c);
    p_adplot->attach(ui->qwtPlot);
    time = 0.0;
    adPlotTimer = new QTimer();
    adPlotTimer->start(1000);
    connect(adPlotTimer, SIGNAL(timeout()),this, SLOT(plotAdCurve()));
    //connect(adPlotTimer_p, SIGNAL(timeout()),this, SLOT(plotPsdCurve()));
    //PM = new QwtPlotMagnifier(ui->qwtPlot->canvas());
  /*QwtPlotZoomer* zoomer = new QwtPlotZoomer( ui->qwtPlot->canvas() );
    zoomer->setRubberBandPen( QColor( Qt::black ) );
    zoomer->setTrackerPen( QColor( Qt::black ) );
    zoomer->setMousePattern(QwtEventPattern::MouseSelect2,Qt::RightButton, Qt::ControlModifier );
    zoomer->setMousePattern(QwtEventPattern::MouseSelect3,Qt::RightButton );
  */
/*

    ui->psdPlot->setAxisTitle(QwtPlot::yLeft, "PSD");
    ui->psdPlot->setAxisScale(QwtPlot::yLeft, 0,150);
    ui->psdPlot->setAxisTitle(QwtPlot::xBottom, " Frequency(Hz)");
    ui->psdPlot->setAxisScale(QwtPlot::xBottom, 0, 10);

    p_psdplot = new QwtPlotCurve();
    QColor b = Qt::red;
    b.setAlpha(150);
    p_psdplot->setPen(b);
    p_psdplot->attach(ui->psdPlot);

*/
  //  time = 0.0;
  //  adPlotTimer_p = new QTimer();
  // adPlotTimer_p->start(1000);
  // connect(adPlotTimer_p, SIGNAL(timeout()),this, SLOT(plotPsdCurve()));

 }



AdPlot::~AdPlot()
{
    delete ui;
}

 FILE *fp_t=fopen("me1109.txt","rt");

 void AdPlot::pre_load(){
    int aa=0;

        for ( int i=0;i<cal_point;i++)
        {
          fscanf(fp_t,"%d ",&aa);
          ecg_data[i]=aa;
          //printf("ecg_data = %f\n",ecg_data[i]);
          time_data[i]=time;
          time = time+1;
          //time += 0.005;//顯示時間軸大小
        }

       //printf("%d\n",pre);

}
 void AdPlot::cal()
{

    int aa=0;


       for(int i=0;i<cal_point-updata_point;i++)//移動ECG
           {
               ecg_data[i]=ecg_data[i+updata_point];
               time_data[i]=time_data[i+updata_point];

           }

        for(int i=cal_point-updata_point;i<cal_point;i++)//寫入新的ECG
           {
            fscanf(fp_t,"%d",&aa);
            ecg_data[i]=aa;

           // printf("ecg_data = %f\n",ecg_data[i]);
            time_data[i]=time;
            time = time+1;
            //time += 0.005;//顯示時間軸大小
           }
         so (ecg_data,RRI);


}

 void AdPlot::readAdData(QVector< double > &xData,  QVector<double> &yData)//(QVector<double> &xData, QVector<double> &ecg_data)
{
     xData.clear();
     yData.clear();

     for(int i=0;i<cal_point;i++)//寫入新的ECG
        {

         xData.append(time_data[i]);
         yData.append(ecg_data[i]);

         //printf("ecg_data = %f\n",yData[i]);

        }

}

//void AdPlot::so(const float RRI)0.0039







/*

void AdPlot::readPsdData(QVector<double> &xData_p, QVector<double> &yData_p)
{

    //readAdData(xData,yData);
     int psd=10;

     printf("%d\n",psd);
     yData_p.append(psd);

     xData_p.append(frq);
     frq += 1;


}

*/


void AdPlot::plotAdCurve()
{

    if(feof(fp_t))//測試是否到了檔案結束位置
    {
        while(1);
    }


    if(pre==0){
        pre_load();
        pre=1;
        readAdData(xData,yData);
    }

    printf("%d\n",pre);
    cal();
    readAdData(xData,yData);
    p_adplot->setSamples(xData,yData);

        if (!xData.empty())
        {
            if (xData.last() >= xMaxScale)
            {
            xMinScale=xMaxScale-6000;
            xMaxScale =xMaxScale+9000;
            ui->qwtPlot->setAxisScale(QwtPlot::xBottom,xMinScale,xMaxScale);

            }
        }

    p_adplot->attach(ui->qwtPlot);
    ui->qwtPlot->replot();
    adPlotTimer->start(100);//畫圖的速度
}



void AdPlot::setTimerStop()
{
adPlotTimer->stop();
}
/*
void AdPlot::plotPsdCurve()
{
    int aaa=0;
    int xxx=1;
    for(xxx=0;xxx<1000;xxx++)
    {


        aaa=xxx;
        points << QPointF( xxx, aaa );
        printf("%d\n",aaa);
        //xxx=xxx+1;


   p_psdplot->setSamples( points );
   p_psdplot->attach( ui->psdPlot );
    }
// adPlotTimer_p->start(1000);
    /*
readPsdData(xData_p,yData_p);
p_psdplot->setSamples(xData_p,yData_p);
if (!xData_p.empty())
{
ui->psdPlot->setAxisScale(QwtPlot::xBottom,0,10);
}
p_psdplot->attach(ui->psdPlot);
ui->psdPlot->replot();
adPlotTimer_p->start(1000);
}

void AdPlot::setTimerStop_p()
{
adPlotTimer_p->stop();
}


*/
