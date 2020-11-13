#include "solverq.h"
#include "../lpslib/base/solver.h"
#include "cellq.h"
#include "config.h"

inline short getwid(short w, short n){
	return w/(n+1);
}

using namespace LPS;

SolverQ::SolverQ(QWidget *parent)
	: QWidget(parent){
	s = new Solver(wp);
	resizeS(3, 3);
	s->clean();
}

void SolverQ::resizeS(short col, short row,
					  bool cb, bool rb){
	short tmpc=col-!cb, tmpr=row-!rb, tmp=tmpr<<1|1;
	w.resize(tmpc<<1|1);
	wp.resize(tmpc<<1|1);
	for(short i=0;i < w.size();i++){
		w[i].resize(tmp);
		wp[i].resize(tmp);
		for(short j=0; j<tmp; j++){
			w[i][j].setParent(this);
			wp[i][j]=&w[i][j];
		}
	}
	for(short i=0;i < w.size();i++)
		for(short j=0; j<tmp; j++)
			if(i&1^~j&1) i&1? w[i][j].lower():w[i][j].raise();
	s->resize(col, row, cb, rb);
	setMinimumSize(tmpc*CellQ::Widcell()+CellQ::Widcell()&~1,
				   tmpr*CellQ::Widcell()+CellQ::Widcell()&~1);
	resizeEvent(nullptr);
}

void SolverQ::resizeEvent(QResizeEvent*){
	short x0=getwid(width(),s->nc),
			y0=getwid(height(), s->nr),
			wid = x0<y0? x0 : y0;
	x0 = width() - wid*s->nc - wid&~1;
	y0 = height() - wid*s->nr - wid&~1;
	for(short i=0; i<(s->nc<<1|1); i++){
		short tmpx = x0 + i*wid>>1;
		for(short j=0; j<(s->nr<<1|1); j++){
			w[i][j].setGeometry(tmpx, y0 + j*wid>>1,
								i&1?wid:wid&~1, j&1?wid:wid&~1);
		}
	}
}
