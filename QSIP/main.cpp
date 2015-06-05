#include "qsip.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
    QSIP w;
	w.show();
	return a.exec();
}
