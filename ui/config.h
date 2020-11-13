#ifndef CONFIG_H
#define CONFIG_H

#include <QWidget>
#include <QPen>



namespace LPS {
class Config{
private:
	QPalette palette;
	QVector<QColor> colorlist;

public:
	int widCell=40, dot_rate=2, font_x=0, font_y=-3,
	shape_rate=70, cross_r=20;
	QString stylesheet;
	QPen pen, dbpen;
	QFont font;
	QPointF tripoints[3]={
		QPoint(0,-2-shape_rate*2/3),
		QPoint(4+shape_rate>>1,1+shape_rate/3),
		QPoint(-4-shape_rate>>1,1+shape_rate/3)
	};

	Config();

	QPalette& Palette();
	void updataSS();
};

static Config config;

class Configui : public QWidget{
	Q_OBJECT

private:
	Config& conf;
public:
	explicit Configui(Config& c=config, QWidget* parent = nullptr);

};
}

#endif // CONFIG_H
