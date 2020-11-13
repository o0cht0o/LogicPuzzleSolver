#include "cellq.h"

#include "config.h"

#include <QPainter>

using namespace LPS;

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

short CellQ::widCell = 40,
CellQ::widPan = 5,
CellQ::widShape = 80;
QColor CellQ::mainColor = QColor::fromHsv(230,128,240);

const QColor CellQ::getColor(short s){
	if(s == 0) return palette().color(QPalette::Window);
	QColor r(mainColor);
	if(s == 1) return palette().color(QPalette::WindowText);
	else r.setHsv((mainColor.hue()+223*(s-2))%360,
				  mainColor.saturation()+(s-2)*20/360,
				  mainColor.value()-(s-2)/360*20);
	return r;
}

void CellQ::paintEvent(QPaintEvent *){
	QPainter p(this);
	p.setRenderHints(QPainter::SmoothPixmapTransform);
	QBrush brush(getColor(get(Data_group_back)));
	QPen pn(getColor(get(Data_group_front)));
	qreal penwid = widCell*widPan/100.0;
	pn.setWidth((get(Data_shape)&Shape_blod? 2 : 1)*penwid+0.5);
	if(get(Data_shape)&Shape_dash) pn.setStyle(Qt::DotLine);
	pn.setJoinStyle(Qt::MiterJoin);
	p.setPen(pn);
	p.setBrush(brush);
	bool F = (widCell^pn.width())&1;
	qreal rShape = F*0.5 + (widShape*widCell+100)/200;
	p.scale((qreal)width()/widCell,(qreal)height()/widCell);
	p.translate(widCell/2.0,widCell/2.0);
	p.rotate(-90*(get(Data_shape_direction))/Shape_hdir);
	switch (get(Data_shape_shape)){
	case Shape_blank:
		break;
	case Shape_dot:
		p.drawPoint(0,0);
		break;
	case Shape_cross:{
		qreal r=rShape/2;
		p.drawLine(QPointF(-r,-r), QPointF(r,r));
		p.drawLine(QPointF(-r,r), QPointF(r,-r));}
		break;
	case Shape_circle:
		p.setRenderHints(QPainter::Antialiasing);
		p.drawEllipse(QPointF(0,0), rShape, rShape);
		break;
	case Shape_triangle:{
		p.setRenderHints(QPainter::Antialiasing);
		QPointF tri[]={
			QPointF(0, -rShape),
			QPointF(rShape, rShape),
			QPointF(-rShape, rShape)
		};
		p.drawPolygon(tri,3);}
		break;
	case Shape_square:
		p.drawRect(QRectF(QPointF(-rShape, -rShape),
						  QPointF(rShape, rShape)));
		break;
	case Shape_diamond:{
		QPointF dia[]={
			QPointF(0, -rShape),
			QPointF(-rShape, 0),
			QPointF(0, rShape),
			QPointF(rShape, 0)
		};
		p.drawPolygon(dia,4);}
		break;
	case Shape_line:{
		qreal r=widCell/2.0;
		p.drawLine(QLineF(0, -r, 0, r));}
		break;
	case Shape_slash:{
		qreal r=widCell/2.0;
		p.drawLine(QLineF(-r, -r, r, r));}
		break;
	}
	p.setRenderHints(QPainter::Antialiasing);
	if(get(Data_shape)&Shape_dir){
		pn.setStyle(Qt::SolidLine);
		QPen tmp(pn);
		tmp.setWidth(penwid);
		QBrush s(brush);
		s.setColor(get(Data_shape)&Shape_fill? pn.color() : brush.color());
		p.setPen(tmp);
		p.setBrush(s);
		p.drawEllipse(QPointF(0, -rShape), 1.5*penwid, 1.5*penwid);
	}/*
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
