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
#include <qwt_plot_grid.h>
#include <QTime>
#include <qtimer.h>
#include <QMessageBox>
#include <qcolor.h>
#include <qwt_plot_zoomer.h>
#include <qfile.h>
#include <qtextstream.h>


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "so.cpp"
#include "remove.cpp"
#include "resample.cpp"
#include "RRI_mean.cpp"
#include "PSD.cpp"
#include "define.h"
#include "determine.cpp"

/*
int sample_rate=255;
int cal_time=300;

int cal_point=sample_rate*cal_time;
int updata_time=20;

int updata_point=updata_time*sample_rate;
*/
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
    //ui->qwtPlot->setAutoReplot(false);
    //ui->qwtPlot->setCanvasBackground( QColor(255,255,255));
    ui->qwtPlot->setCanvasBackground( QColor(0,0,0));
   // ui->psdPlot->setAutoReplot(false);
    ui->psdPlot->setCanvasBackground( QColor(255,255,255));
    ui->ratioPlot->setCanvasBackground( QColor(255,255,255));
    QTime curTime;
    curTime = curTime.currentTime();

   // QwtLegend *legend = new QwtLegend;
    //legend->setItemMode(QwtLegend::CheckableItem);
    //ui->qwtPlot->insertLegend(legend, QwtPlot::RightLegend);
    ///ui->qwtPlot->setAxisScaleDraw(QwtPlot::xBottom,  new TimeScaleDraw(curTime));

    //ui->qwtPlot->setAxisTitle(QwtPlot::xBottom, " Time");
    ui->qwtPlot->setAxisScale(QwtPlot::xBottom,0,5000);
    ui->qwtPlot->setAxisLabelAlignment(QwtPlot::xBottom, Qt::AlignLeft | Qt::AlignBottom);
   // ui->qwtPlot->setAxisTitle(QwtPlot::yLeft, "V");
    ui->qwtPlot->setAxisScale(QwtPlot::yLeft,0,1);
    ui->qwtPlot->setAxisMaxMinor(QwtPlot::yLeft,0.2);
    //ui->qwtPlot->setTitle("ECG Wave");

    p_adplot = new QwtPlotCurve();
    //QColor c = Qt::red;



    p_adplot->setPen(QPen(Qt::green,1,Qt::SolidLine));
    p_adplot->attach(ui->qwtPlot);
    time = 0.0;
    adPlotTimer = new QTimer();
    adPlotTimer->start(1000);
    connect(adPlotTimer, SIGNAL(timeout()),this, SLOT(plotAdCurve()));

    QwtPlotGrid *grid = new QwtPlotGrid();
    grid->setPen(QPen(Qt::gray, 0.0, Qt::DotLine));
    grid->enableX(ui->qwtPlot);
    grid->enableXMin(ui->qwtPlot);
    grid->enableY(ui->qwtPlot);
    grid->enableYMin(ui->qwtPlot);
    grid->attach(ui->qwtPlot);

    //PM = new QwtPlotMagnifier(ui->qwtPlot->canvas());
    QwtPlotZoomer* zoomer = new QwtPlotZoomer( ui->qwtPlot->canvas() );
    zoomer->setRubberBandPen( QColor( Qt::black ) );
    zoomer->setTrackerPen( QColor( Qt::black ) );
    zoomer->setMousePattern(QwtEventPattern::MouseSelect2,Qt::RightButton, Qt::ControlModifier );
    zoomer->setMousePattern(QwtEventPattern::MouseSelect3,Qt::RightButton );


//********************************** psd *****************************************
    ui->psdPlot->setAxisTitle(QwtPlot::yLeft, "PSD (normalized)");
    ui->psdPlot->setAxisScale(QwtPlot::yLeft, 0,100);
    ui->psdPlot->setAxisTitle(QwtPlot::xBottom, " Frequency(mHz)");
    ui->psdPlot->setAxisScale(QwtPlot::xBottom, 0, 500);
    ui->psdPlot->setTitle("Power Spectrum Density");

    p_psdplot = new QwtPlotCurve(); 
    p_psdplot->setPen(QPen(Qt::blue,1,Qt::SolidLine));
    p_psdplot->attach(ui->psdPlot);

    adPlotTimer_p = new QTimer();
    adPlotTimer_p->start(1000);
    connect(adPlotTimer_p, SIGNAL(timeout()),this, SLOT(plotPsdCurve()));

//********************************** ratio *****************************************
    ui->ratioPlot->setAxisTitle(QwtPlot::yLeft, "LF/HF");
    ui->ratioPlot->setAxisScale(QwtPlot::yLeft, 0,yMaxScale=3);
    ui->ratioPlot->setAxisTitle(QwtPlot::xBottom, "Time in epochs (4 sec) ");
    ui->ratioPlot->setAxisScale(QwtPlot::xBottom, 0, xMaxScale=10);
    ui->ratioPlot->setTitle("LF/HF Record");

    p_ratioplot = new QwtPlotCurve();
    p_ratioplot->setPen(QPen(Qt::blue,1,Qt::SolidLine));
    p_ratioplot->attach(ui->ratioPlot);

    adPlotTimer_r = new QTimer();
    adPlotTimer_r->start(1000);
    connect(adPlotTimer_r, SIGNAL(timeout()),this, SLOT(plotRatioCurve()));


//***************************************************************************
    movie1 = new QMovie("1110.png");
    movie2 = new QMovie("2220.png");
    movie3 = new QMovie("3330.png");
    //ui->label->setMovie(movie1);



    //time2 = 0.0;


   ui->lcd_1->setSegmentStyle(QLCDNumber::Flat);
   ui->lcd_1->display(0);

   ui->lcd_2->setSegmentStyle(QLCDNumber::Flat);
   ui->lcd_2->display(0);

   paint=new QPainter;
    LF_pre=0;


   connect(ui->Button_1,SIGNAL(clicked()), this,SLOT(close()));
   connect(ui->Button_2,SIGNAL(clicked()), this,SLOT(start()));
  // connect(ui->Button_3,SIGNAL(clicked()), this,SLOT(warm_off()));

  // page= new QWidget(parent);

 }


  int str=0;
   FILE* fp;


AdPlot::~AdPlot()
{
    delete ui;
}

 //FILE *fp_t=fopen("heng_03_14.txt","rt");
 FILE *fp_t=fopen("me0102.txt","rt");
 //FILE *fp_t=fopen("su.txt","rt");
 void AdPlot::start(){
     str=1;
     xxx=0;
     top=top;
     z=0;
     G=0;
     B=0;
     R=0;
     uptime_con1=76;

    //plotAdCurve();
 }


 void AdPlot::pre_load(){
   float  aa=0;

        for ( int i=0;i<cal_point;i++)
        {
          fscanf(fp_t,"%f ",&aa);
          ecg_data[i]=aa;

          time_data[i]=time;
          time = i;//time+1;
          //time += 0.005;//顯示時間軸大小
         // printf("%d ecg_data = %f\n",i,ecg_data[i]);
        }


       //printf("%d\n",pre);

}


 void AdPlot::cal()
{

    float aa=0;


       for(int i=0;i<cal_point-updata_point;i++){ //移動ECG
          ecg_data[i]=ecg_data[i+updata_point];
          time_data[i]=i;//time_data[i+updata_point];
          //printf("%d ecg_data = %f\n",i,ecg_data[i]);
       }

       for(int i=cal_point-updata_point;i<cal_point;i++){ //寫入新的ECG
          fscanf(fp_t,"%f",&aa);
          ecg_data[i]=aa;

          // printf("ecg_data = %f\n",ecg_data[i]);
          time_data[i]=time;
          time = i;
          //time += 0.005;//顯示時間軸大小
          // printf("%d ecg_data = %f\n",i,ecg_data[i]);
       }

       ratio_time[xxx]=xxx;
       printf("================================================\n");
       printf("uptime = %d\n",xxx);
       xxx=xxx+1;


       so ();
       remove();
       resample();
       RRI_mean();
       PSD();
       determine();
       //printf("LF/HF=%f\n",ratio)RRI[;
       ui->lcd_1->display(ratio);
       ui->lcd_2->display(HR);

       if(z==1){
           if (top ==1){
               Phonon::MediaObject *music=Phonon::createPlayer(Phonon::MusicCategory,Phonon::MediaSource("yellow.mp3"));
               music->play();

              fp = fopen("/proc/myled", "w");
               if(fp == NULL) {
                 printf("Cannot open /proc/myled for write\n");
                 return ;
               }
               fputs("0x0F\n", fp);
               fclose(fp);
               sleep(1);
           }

           if (top ==2){
               Phonon::MediaObject *music=Phonon::createPlayer(Phonon::MusicCategory,Phonon::MediaSource("red.mp3"));
               music->play();
           }
       }


}
 /*
  void AdPlot::warm_off(){
      music->stop();
  }*/

//********************************** ECG PLOT *****************************************
 void AdPlot::readAdData(QVector< double > &xData,  QVector<double> &yData){  //(QVector<double> &xData, QVector<double> &ecg_data)

     xData.clear();
     yData.clear();


     for(int i=0;i<cal_point;i++){//寫入新的ECG
         xData.append(time_data[i]);
         yData.append(0.0+(ecg_data[i]/256));
         //printf("ecg_data = %f\n",xData[i]);
     }
 }



void AdPlot::plotAdCurve(){

    if(feof(fp_t))//測試是否到了檔案結束位置
    {
        while(1);

    }

    if (str == 1){
        if(pre==0){
            pre_load();
            pre=1;
            readAdData(xData,yData);
            readPsdData(fData,powerData);
            readRatioData(uptimeData,ratioData);
    }

    //printf("%d\n",pre);
    cal();
    readPsdData(fData,powerData);
    readRatioData(uptimeData,ratioData);

    readAdData(xData,yData);
    p_adplot->setSamples(xData,yData);

    p_adplot->attach(ui->qwtPlot);
    ui->qwtPlot->replot();
    adPlotTimer->start(1000);//畫圖的速度
    }

}



void AdPlot::setTimerStop(){
    adPlotTimer->stop();
}

//********************************** PSD PLOT *****************************************
void AdPlot::readPsdData(QVector<double> &fData, QVector<double> &powerData){
    fData.clear();
    powerData.clear();

    for(int i=1;i<nfft/2;i++){//寫入新的ECG4
        fData.append(f[i-1]*0.1);
        powerData.append(pow[i]);
        //fData.append(time_data[i]);
        // powerData.append(RRI[i]*100);

        //printf("powerData = %f\n",powerData[i]);
        // printf("f = %f\n",fData[i]);
    }

}

void AdPlot::plotPsdCurve(){
    //readPsdData(fData,powerData);
    p_psdplot->setSamples(fData,powerData);

    p_psdplot->attach(ui->psdPlot);
    ui->psdPlot->replot();
    adPlotTimer_p->start(500);//畫圖的速度


}

void AdPlot::setTimerStop_p(){
    adPlotTimer_p->stop();
}


//********************************** RATIO PLOT *****************************************
void AdPlot::readRatioData(QVector<double> &uptimeData, QVector<double> &ratioData){
    uptimeData.clear();
    ratioData.clear();

    for(int i=0;i<xxx;i++){
        uptimeData.append(ratio_time[i]);
        ratioData.append(ratio_reg[i]);
       // printf("ratioData = %f\n",ratioData[i]);
    }


}

void AdPlot::plotRatioCurve(){
    p_ratioplot->setSamples(uptimeData,ratioData);
    if (!uptimeData.empty()){
        if (uptimeData.last() >= xMaxScale){
            xMaxScale =xMaxScale+10;
            ui->ratioPlot->setAxisScale(QwtPlot::xBottom, 0, xMaxScale);
        }
        if(ratioData.last() >=yMaxScale){
             yMaxScale =yMaxScale+1;
             ui->ratioPlot->setAxisScale(QwtPlot::yLeft, 0, yMaxScale);
        }
    }

    p_ratioplot->attach(ui->ratioPlot);
    ui->ratioPlot->replot();
    adPlotTimer_r->start(500);//畫圖的速度

}

void AdPlot::setTimerStop_r(){
    adPlotTimer_r->stop();
}

//********************************** PAINT  *****************************************
void AdPlot::DrawCircle(QPainter *paint){

   if (top==2){
        //paint->setPen(QPen(Qt::red,1,Qt::SolidLine));
        //paint->setBrush(QBrush(Qt::red,Qt::SolidPattern));
        ui->label->setMovie(movie3);
        movie3->start();
    }
   else if (top==1){
       //paint->setPen(QPen(Qt::yellow,1,Qt::SolidLine));
       //paint->setBrush(QBrush(Qt::yellow,Qt::SolidPattern));
       ui->label->setMovie(movie2);
       movie2->start();

   }
   else{
       //paint->setPen(QPen(Qt::green,1,Qt::SolidLine));
       //paint->setBrush(QBrush(Qt::green,Qt::SolidPattern));
       ui->label->setMovie(movie1);
       movie1->start();
   }
  //paint->drawEllipse(30,290,100,100);

    paint->setPen(QPen(Qt::red,2,Qt::SolidLine));
    paint->setBrush(QBrush(Qt::red,Qt::SolidPattern));
    //paint->drawRect(20,210,120,30);//drawRect(0, 0, squareSize, squareSize);
    paint->drawPie(60,260,250,250,5000,4400);

    paint->setPen(QPen(Qt::green,2,Qt::SolidLine)); //设置画笔形式
    paint->setBrush(QBrush(Qt::green,Qt::SolidPattern)); //设置画刷形式
   // paint->drawRect(20,210,LF_pre,30);
     paint->drawPie(60,260,250,250,5000,LF_pre);

    this->update();
}


void AdPlot::paintEvent(QPaintEvent *){
    QPainter paint(this);
    DrawCircle(&paint);
}

