#include "presentationwindow.h"
#include "managementwindow.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PresentationWindow w;
    w.show();
    //w.setStyleSheet("background-image: url(:/Palais de Justice.png)");


    QPixmap px("./Palais de justice - degrade.png");
    px.scaled(w.size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::ColorRole::Window, px);
    w.setPalette(palette);

    ManagementWindow managmentWindow;
    managmentWindow.TargetPresentation = &w;
    managmentWindow.show();
    w.ManagementWindowReference = &managmentWindow;

    return QCoreApplication::exec();
}
