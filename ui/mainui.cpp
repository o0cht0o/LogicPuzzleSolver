#include "mainui.h"

#include <QComboBox>
#include <QMenu>
#include <QPushButton>
#include <QMouseEvent>
#include <QBoxLayout>

#include "config.h"
#include "solverq.h"
#include "../lpslib/base/solverlist.h"

using namespace LPS;

Mainui::Mainui(QWidget *parent) : QWidget(parent){
	isPress = false;
	setPalette(config.Palette());
	//this->setWindowFlags(Qt::FramelessWindowHint);

	solvertype = new QComboBox(this);
	for(auto i:SolverList::sl())
		solvertype->addItem(QString::fromStdString(i.first));

	solve = new QPushButton("&Run", this);

	solver = new SolverQ(this);
	connect(solve, SIGNAL(clicked()), solver, SLOT(run()));
	connect(solvertype, SIGNAL(currentTextChanged(const QString &)),
			solver, SLOT(changeSolver(const QString&)));

	auto cLayout = new QHBoxLayout;
	cLayout->addWidget(solvertype,1);
	cLayout->addWidget(solve);

	auto mLayout = new QVBoxLayout;
	mLayout->addLayout(cLayout);
	mLayout->addWidget(solver,1);

	setLayout(mLayout);

	menu = new QMenu();

	menu->addAction("&Quit", this, SLOT(close()));

}

void Mainui::contextMenuEvent(QContextMenuEvent* ){
	this->setCursor(Qt::ArrowCursor);
	menu->exec(cursor().pos());
}

void Mainui::mousePressEvent(QMouseEvent *e)
{
	if(e->button() == Qt::LeftButton)
	{
		isPress = true;
		mouseSP = e->pos();
	}
}

void Mainui::mouseMoveEvent(QMouseEvent *e)
{
	if(isPress)
		this->move(e->pos() - mouseSP + this->pos());
}

void Mainui::mouseReleaseEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton)
		isPress = false;
}
