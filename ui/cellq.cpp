#include "cellq.h"

#include "config.h"

#include <QPainter>

using namespace LPS;

CellQ::CellQ(QWidget *parent)
	: QWidget(parent), Cell(){
	//setMinimumSize(widCell, widCell);
	setGeometry(0,0,widCell,widCell);
}

CellQ::CellQ(const CellQ& c)
	: QWidget(c.parentWidget()), Cell(c){
	//setMinimumSize(widCell, widCell);
	setGeometry(0,0,widCell,widCell);
}

short CellQ::widCell = 40,
CellQ::widPan = 5,
CellQ::widShape = 80;
QColor CellQ::mainColor = QColor::fromHsv(230,128,240);
QFont CellQ::font("Sans");

const QColor CellQ::getColor(short s, bool b){
	if(s == 0) return b?QColor(0,0,0,0):palette().color(QPalette::Window);
	QColor r(mainColor);
	if(s == 1) return palette().color(QPalette::WindowText);
	else r.setHsv((mainColor.hue()+223*(s-2))%360,
				  (mainColor.saturation()+(s-2)*20/360)/(b?1:2),
				  (mainColor.value()-(s-2)/360*20)/(b?1:2));
	return r;
}

void CellQ::paintEvent(QPaintEvent *){
	QPainter p(this);
	p.setRenderHints(QPainter::SmoothPixmapTransform);
	QBrush brush(getColor(get(Data_group_back),0));
	QPen pn(getColor(get(Data_group_front)));
	qreal penwid = widCell*widPan/100.0;
	pn.setWidth((get(Data_shape)&Shape_blod? 2 : 1)*penwid+0.5);
	if(get(Data_shape)&Shape_dash) pn.setStyle(Qt::DotLine);
	pn.setJoinStyle(Qt::MiterJoin);
	p.setPen(pn);
	p.setBrush(brush);
	qreal rShape = widShape*widCell/200;
	p.scale((qreal)width()/widCell,(qreal)height()/widCell);
	p.translate(widCell/2.0,widCell/2.0);
	p.rotate(90*(get(Data_shape_direction))/Shape_hdir);
	switch (get(Data_shape_shape)){
	case Shape_blank:
		font.setPixelSize(2*rShape);
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
		p.setRenderHints(QPainter::Antialiasing);
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
		font.setPixelSize(2*rShape*widShape/100);
		pn.setStyle(Qt::SolidLine);
		QPen tmp(pn);
		tmp.setWidth(penwid);
		QBrush s(brush);
		s.setColor(get(Data_shape)&Shape_fill? pn.color() : brush.color());
		p.setPen(tmp);
		p.setBrush(s);
		p.drawEllipse(QPointF(0, -rShape), 1.5*penwid, 1.5*penwid);
	}

	switch (get(Data_shape_shape)){
	case Shape_circle:
	case Shape_triangle:
	case Shape_square:
	case Shape_diamond:
		font.setPixelSize(2*rShape*widShape/100);
	case Shape_blank:
		p.resetTransform();
		p.scale((qreal)width()/widCell,(qreal)height()/widCell);
		p.translate(widCell/2.0,widCell/2.0);
		QString disp;
		if(isMask()){
			for(short i=0;i<10;i++)
				if(num&1<<i+4) disp+=QString::number(i);
			short n=num&0xF, l=(n+5)/4, h=font.pixelSize()/l;
			font.setPixelSize(h);
			p.setFont(font);
			switch (l) {
			case 1:
				p.drawText(QRect(-CellQ::widCell>>1, -CellQ::widCell>>1,
								 CellQ::widCell, CellQ::widCell),
						   Qt::AlignCenter, disp);
				break;
			case 2:
				p.drawText(QRect(-CellQ::widCell>>1, -CellQ::widCell>>1,
								 CellQ::widCell, CellQ::widCell-h),
						   Qt::AlignCenter, disp.left(n-n/l));
				p.drawText(QRect(-CellQ::widCell>>1, -CellQ::widCell>>1,
								 CellQ::widCell, CellQ::widCell+h),
						   Qt::AlignCenter, disp.right(n/l));
				break;
			case 3:
				p.drawText(QRect(-CellQ::widCell>>1, -CellQ::widCell>>1,
								 CellQ::widCell, CellQ::widCell-2*h),
						   Qt::AlignCenter, disp.left(2+n/8));
				p.drawText(QRect(-CellQ::widCell>>1, -CellQ::widCell>>1,
								 CellQ::widCell, CellQ::widCell),
						   Qt::AlignCenter, disp.mid(2+n/8,n/10+3));
				p.drawText(QRect(-CellQ::widCell>>1, -CellQ::widCell>>1,
								 CellQ::widCell, CellQ::widCell+2*h),
						   Qt::AlignCenter, disp.right(2+n/9));
				break;
			}
			}
		else if(num>=0) {
			disp=QString::number(num%100);
			p.setFont(font);
			p.drawText(QRect(-CellQ::widCell>>1, -CellQ::widCell>>1,
							 CellQ::widCell, CellQ::widCell),
					   Qt::AlignCenter, disp);
		}
	}
	if(isFouce || isHover){
		p.setPen(Qt::NoPen);
		QColor tmp(mainColor);
		tmp.setAlpha(isFouce?127:63);
		p.setBrush(QBrush(tmp));
		p.drawRect(-rShape,-rShape,rShape*2,rShape*2);
	}
	/*

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
	emit enfouce();
	isFouce=true;
	QWidget::mousePressEvent(event);
	set(rand(),Data_shape);
	set(rand(),Data_group);
	set(rand(),Data_num);
	update();
}

void CellQ::mouseReleaseEvent(QMouseEvent *event){
	QWidget::mouseReleaseEvent(event);
	update();
}

CellQ& CellQ::operator=(Cell& c){
	group = c.get(Data_group);
	shape = c.get(Data_shape);
	num = c.get(Data_num);
	MaskCor();
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

void CellQ::setfouce(bool b){
	isFouce = b;
	update();
}
