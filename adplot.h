#ifndef ADPLOT_H
#define ADPLOT_H

#include <QWidget>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qfile.h>
#include <qwt_plot_magnifier.h>
#include "define.h"
#include <QLCDNumber>
#include <QPainter>
#include <QPushButton>
#include <QMovie>


#include <phonon/MediaObject>
#include <phonon/MediaSource>
#include <phonon/AudioOutput>

namespace Ui {
class AdPlot;
}

class AdPlot : public QWidget
{
    Q_OBJECT
    
public:
    explicit AdPlot(QWidget *parent = 0);
    void readAdData(QVector<double> &xData,  QVector<double> &yData);
    void cal();
    void pre_load();

    void so ();
    void remove ();
    void resample ();
    void RRI_mean ();
    void PSD ();
    void determine ();


    void readPsdData(QVector<double> &fData, QVector<double> &powerData);
    void readRatioData(QVector<double> &uptimeData, QVector<double> &ratioData);

   // void readPsdData(QVector< double > &xData_p,  QVector< double > &yData_p);
    //void so(double RRI[]);




    void setTimerStop();
    void setTimerStop_p();
    void setTimerStop_r();
    ~AdPlot();

 public slots:

    void plotAdCurve();
    void plotPsdCurve();
    void plotRatioCurve();

    void start();
 //   void warm_off();



 protected:
   void  paintEvent(QPaintEvent * );
   void  DrawCircle(QPainter *paint);


private:
    Ui::AdPlot *ui;

    QwtPlotCurve *p_adplot;
    QwtPlotCurve *p_psdplot;
    QwtPlotCurve *p_ratioplot;

    QVector< double > xData;
    QVector< double > yData;

    QVector< double > fData;
    QVector< double > powerData;

    QVector< double > uptimeData;
    QVector< double > ratioData;


    double  ecg_data[cal_point];
    int  time_data[cal_point];


     double  RRI[600];
     double  R_found[600];
     double  yi[resample_point];
     double  Im[resample_point];
     double  f[nfft/2];
     double  pow[nfft];

     double  ratio;
     int     resample_mo;
     int     HR;
     int     LF_pre;
     int     str;
     double  org_RRImean;
     double  first_R_found;
     int     haN;
     int     xxx;
     int     top,z,G,B,R;
     int     po;
     int     uptime_con1;

     double  ratio_reg[2000];
     int     ratio_time[2000];




   // QVector< double > xData_p;
    //QVector< double > yData_p;
    QFile *localFile;

  //  double RRI;
    double time;
    double frq;
    QwtPlotMagnifier *PM;

    int xMaxScale;
    int xMinScale;
    int yMaxScale;
    QTimer *adPlotTimer;
    QTimer *adPlotTimer_p;
    QTimer *adPlotTimer_r;
 //==============================================


    QLCDNumber *q_lcd;
    QPainter   *paint;
    Phonon::MediaObject *music;
    Phonon::AudioOutput * audioOutput;
     QMovie *movie1;
     QMovie *movie2;
     QMovie *movie3;






};

#endif // ADPLOT_H
