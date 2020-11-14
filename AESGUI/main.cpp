#include <QtWidgets/QApplication>
#include <QTextCodec>

#include "AESMain.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	QTextCodec::setCodecForLocale(QTextCodec::codecForName("Big5"));


    AESMain w;
    w.show();
    return a.exec();
}
