#ifndef MAINUI_H
#define MAINUI_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QComboBox;
class QMenu;
class QPushButton;
QT_END_NAMESPACE

namespace LPS {

class SolverQ;

class Mainui : public QWidget
{
	Q_OBJECT
public:
	explicit Mainui(QWidget *parent = nullptr);

private:
	QComboBox* solvertype;
	QPushButton* solve;
	SolverQ* solver;
	QMenu* menu;

	bool isPress=false;
	QPoint mouseSP;

	void contextMenuEvent(QContextMenuEvent*);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);

signals:

};
}

#endif // MAINUI_H
