#include "qsip.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QSIP w;
	w.show();
	return a.exec();
}
