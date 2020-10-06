#include<QApplication>

#include "ui/mainui.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	LPS::Mainui w;
	w.show();
	return a.exec();
}
