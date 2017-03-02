/********************************************************************************
** Form generated from reading UI file 'adplot.ui'
**
** Created: Thu Mar 27 13:58:38 2014
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADPLOT_H
#define UI_ADPLOT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QTabWidget>
#include <QtGui/QWidget>
#include "qwt_plot.h"

QT_BEGIN_NAMESPACE

class Ui_AdPlot
{
public:
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QPushButton *Button_1;
    QPushButton *Button_2;
    QLCDNumber *lcd_2;
    QLCDNumber *lcd_1;
    QLabel *label_1;
    QLabel *label_2;
    QTabWidget *tabWidget;
    QWidget *tab;
    QwtPlot *qwtPlot;
    QWidget *tab_2;
    QwtPlot *ratioPlot;
    QLabel *label;
    QwtPlot *psdPlot;

    void setupUi(QWidget *AdPlot)
    {
        if (AdPlot->objectName().isEmpty())
            AdPlot->setObjectName(QString::fromUtf8("AdPlot"));
        AdPlot->resize(751, 557);
        label_3 = new QLabel(AdPlot);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(130, 470, 121, 31));
        QFont font;
        font.setFamily(QString::fromUtf8("URW Bookman L"));
        font.setPointSize(16);
        font.setBold(true);
        font.setWeight(75);
        label_3->setFont(font);
        label_4 = new QLabel(AdPlot);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(50, 470, 51, 17));
        label_5 = new QLabel(AdPlot);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(280, 470, 51, 17));
        Button_1 = new QPushButton(AdPlot);
        Button_1->setObjectName(QString::fromUtf8("Button_1"));
        Button_1->setGeometry(QRect(560, 510, 111, 31));
        Button_2 = new QPushButton(AdPlot);
        Button_2->setObjectName(QString::fromUtf8("Button_2"));
        Button_2->setGeometry(QRect(430, 510, 111, 31));
        lcd_2 = new QLCDNumber(AdPlot);
        lcd_2->setObjectName(QString::fromUtf8("lcd_2"));
        lcd_2->setGeometry(QRect(290, 510, 101, 31));
        QFont font1;
        font1.setPointSize(22);
        font1.setBold(true);
        font1.setItalic(true);
        font1.setWeight(75);
        lcd_2->setFont(font1);
        lcd_1 = new QLCDNumber(AdPlot);
        lcd_1->setObjectName(QString::fromUtf8("lcd_1"));
        lcd_1->setGeometry(QRect(130, 510, 101, 31));
        lcd_1->setFont(font1);
        label_1 = new QLabel(AdPlot);
        label_1->setObjectName(QString::fromUtf8("label_1"));
        label_1->setGeometry(QRect(30, 520, 101, 21));
        QFont font2;
        font2.setFamily(QString::fromUtf8("URW Bookman L"));
        font2.setPointSize(18);
        font2.setBold(true);
        font2.setItalic(false);
        font2.setWeight(75);
        label_1->setFont(font2);
        label_2 = new QLabel(AdPlot);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(250, 520, 41, 20));
        label_2->setFont(font2);
        tabWidget = new QTabWidget(AdPlot);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(10, 10, 731, 241));
        tabWidget->setTabPosition(QTabWidget::West);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        qwtPlot = new QwtPlot(tab);
        qwtPlot->setObjectName(QString::fromUtf8("qwtPlot"));
        qwtPlot->setGeometry(QRect(0, 10, 691, 221));
        QFont font3;
        font3.setPointSize(10);
        font3.setBold(false);
        font3.setItalic(false);
        font3.setWeight(50);
        qwtPlot->setFont(font3);
        qwtPlot->setLineWidth(1);
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        ratioPlot = new QwtPlot(tab_2);
        ratioPlot->setObjectName(QString::fromUtf8("ratioPlot"));
        ratioPlot->setGeometry(QRect(0, 0, 691, 231));
        ratioPlot->setFont(font3);
        tabWidget->addTab(tab_2, QString());
        label = new QLabel(AdPlot);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(90, 290, 191, 191));
        psdPlot = new QwtPlot(AdPlot);
        psdPlot->setObjectName(QString::fromUtf8("psdPlot"));
        psdPlot->setGeometry(QRect(360, 260, 381, 241));

        retranslateUi(AdPlot);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(AdPlot);
    } // setupUi

    void retranslateUi(QWidget *AdPlot)
    {
        AdPlot->setWindowTitle(QApplication::translate("AdPlot", "AdPlot", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("AdPlot", "Energy Bar", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("AdPlot", "SLEEP", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("AdPlot", "WAKE", 0, QApplication::UnicodeUTF8));
        Button_1->setText(QApplication::translate("AdPlot", "Close", 0, QApplication::UnicodeUTF8));
        Button_2->setText(QApplication::translate("AdPlot", "Start", 0, QApplication::UnicodeUTF8));
        label_1->setText(QApplication::translate("AdPlot", "LF / HF", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("AdPlot", "HR", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("AdPlot", "ECG Waveform ", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("AdPlot", "LF/HF Record", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("AdPlot", "Fig", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class AdPlot: public Ui_AdPlot {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADPLOT_H
