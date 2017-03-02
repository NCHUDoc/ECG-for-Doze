#include <QtGui/QApplication>
#include "adplot.h"
//#include "qpushbutton.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AdPlot w;
    w.show();


    return a.exec();
}
