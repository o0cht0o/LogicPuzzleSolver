#include "cellq.h"

#include "config.h"

#include <QPainter>

using namespace LPS;

short CellQ::widCell=40;

CellQ::CellQ(QWidget *parent)
	: QWidget(parent), Cell(){
	setMinimumSize(widCell, widCell);
	setGeometry(0,0,widCell,widCell);
}

CellQ::CellQ(const CellQ& c)
	: QWidget(c.parentWidget()), Cell(c){
	setMinimumSize(widCell, widCell);
	setGeometry(0,0,widCell,widCell);
}

void CellQ::paintEvent(QPaintEvent *){/*
	QPainter p(this);
	p.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
	QBrush brush(config.getColor(get(Data_group)&0xFF));
	QPen pn(config.pen);
	if(get(Data_shape_style)){
		int i=get(Data_shape_style);
		if(i&Shape_dash) pn.setStyle(config.dbpen.style());
		if(i&Shape_blod) pn.setWidth(config.dbpen.width());
	}
	pn.setColor(config.getColor((get(Data_group)&0xFF00)>>8));
	p.scale(width()/100.0,height()/100.0);
	p.translate(50,50);
	p.rotate(90*(get(Data_shape_direction))>>8);
	switch (get(Data_shape_shape)){
	case Shape_blank:
		break;
	case Shape_dot:{
		QPen tmp(pn);
		tmp.setWidth(pn.width()*config.dot_rate);
		p.setPen(tmp);
		p.drawPoint(0,0);}
		break;
	case Shape_cross:{
		p.setPen(pn);
		int r=config.cross_r>>1;
		p.drawLine(-r,-r,r,r);
		p.drawLine(-r,r,r,-r);}
		break;
	case Shape_circle:{
		p.setPen(pn);
		p.setBrush(brush);
		int r=config.shape_rate>>1;
		p.drawEllipse(-r,-r,r<<1,r<<1);}
		break;
	case Shape_triangle:{
		p.setPen(pn);
		p.setBrush(brush);
		p.drawPolygon(config.tripoints,3);}
		break;
	case Shape_square:{
		p.setPen(pn);
		p.setBrush(brush);
		int r=config.shape_rate>>1;
		p.drawRect(-r,-r,r<<1,r<<1);}
		break;
	case Shape_line:{
		p.setPen(pn);
		p.drawLine(QLineF(0, -50, 0, 50));}
		break;
	}
	if(isPress){
		p.setPen(Qt::NoPen);
		QColor tmp(palette().color(QPalette::Light));
		tmp.setAlpha(127);
		p.setBrush(QBrush(tmp));
		int r=config.shape_rate*50;
		p.drawRect(-r,-r,r<<1,r<<1);
	}
	else if(isHover) {
		p.setPen(Qt::NoPen);
		QColor tmp(palette().color(QPalette::Light));
		tmp.setAlpha(63);
		p.setBrush(QBrush(tmp));
		int r=config.shape_rate*50;
		p.drawRect(-r,-r,r<<1,r<<1);

	}
	p.resetTransform();
	p.scale(width()/100.0,height()/100.0);
	p.setPen(config.pen);
	p.setFont(config.font);
	/*QString stage;
	stage = QString::number(get(Data_group),16) + "\n" +
			QString::number(get(Data_shape),16) + "\n" +
			QString::number(get(Data_num),16) + "\n" +
			QString::number(x(),10) + "\n" +
			QString::number(y(),10) + "\n" +
			QString::number(width(),10) + "\n" +
			QString::number(height(),10);*/
	//p.drawText(QRect(0+config.font_x,0+config.font_y,100,100), Qt::AlignCenter, QString::number(rand()%10,16));
}

void CellQ::enterEvent(QEvent *event)
{
	isHover = true;
	QWidget::enterEvent(event);
	update();
}

void CellQ::leaveEvent(QEvent *event)
{
	isHover = false;
	QWidget::leaveEvent(event);
	update();
}

void CellQ::mousePressEvent(QMouseEvent *event)
{
	isPress = true;
	QWidget::mousePressEvent(event);
	set((get(Data_shape_shape)+1)%7,Data_shape_shape);
	update();
}

void CellQ::mouseReleaseEvent(QMouseEvent *event){
	isPress = false;
	QWidget::mouseReleaseEvent(event);
	update();
}

CellQ& CellQ::operator=(Cell& c){
	group = c.get(Data_group);
	shape = c.get(Data_shape);
	num = c.get(Data_num);
	return *this;
}


void CellQ::set(short n, Data d){
	Cell::set(n, d);
	update();
}

void CellQ::set(short g, short s, short n){
	Cell::set(g, s, n);
	update();
}

void CellQ::Mask(bool zero){
	Cell::Mask(zero);
	update();
}

short CellQ::Maskadd(short n){
	short r=Cell::Maskadd(n);
	if(!r) update();
	return r;
}

short CellQ::Masksub(short n){
	short r=Cell::Masksub(n);
	if(!r) update();
	return r;
}
