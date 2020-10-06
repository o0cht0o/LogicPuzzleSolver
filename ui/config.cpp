#include "config.h"

using namespace LPS;

Config::Config()
	:palette(QColor(38,38,40)),
	  pen(palette.color(QPalette::WindowText)),
	  dbpen(pen){
	pen.setWidth(3);
	dbpen.setWidth(pen.width()<<1);
	dbpen.setStyle(Qt::DotLine);
	font.setBold(true);
	font.setPixelSize(50);
	colorlist.append(palette.color(QPalette::Window));
	colorlist.append(palette.color(QPalette::WindowText));
	colorlist.append(QColor::fromHsv(230,128,240));
}

QPalette& Config::Palette(){
	return palette;
}

QColor& Config::getColor(short n){
	if(n<colorlist.size()) return colorlist[n];
	for(short i=colorlist.size();i<=n;i++)
		colorlist.append(QColor::fromHsv((colorlist[i-1].hue()+223)%360,128+n/360*20,240-n/360*20));
	return colorlist[n];
};


Configui::Configui(Config& c, QWidget *parent)
	: QWidget(parent), conf(c){
}
