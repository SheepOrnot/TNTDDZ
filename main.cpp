#include "mainwindow.h"
#include "messagecenter.h"
#include "widgetrevpacker.h"

#include <QApplication>

std::shared_ptr<MessageCenter> MessageCenter::instance(new MessageCenter(), destoryInstance);
std::shared_ptr<WidgetRevPacker> WidgetRevPacker::instance(new WidgetRevPacker(), destoryInstance);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
