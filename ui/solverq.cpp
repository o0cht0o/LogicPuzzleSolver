#include "solverq.h"
#include "../lpslib/base/solverlist.h"
#include "cellq.h"
#include <QString>
#include <QKeyEvent>

inline short getwid(short w, short n){
	return w/(n+1);
}

using namespace LPS;

SolverQ::SolverQ(QWidget *parent)
	: QWidget(parent), mode(Mode::Mode_Input), s(nullptr){
	this->grabKeyboard();
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
			connect(&w[i][j],&CellQ::enfouce,this,[=]{enFouce(i, j);});
			w[i][j].show();
		}
	}
	for(short i=0;i < w.size();i++)
		for(short j=0; j<tmp; j++)
			if(i&1^~j&1) i&1? w[i][j].lower():w[i][j].raise();
	s->resize(col, row, cb, rb);
	setMinimumSize(CellQ::Widcell()*(tmpc+1), CellQ::Widcell()*(tmpr+1));
	clean_io(Md());
}

void SolverQ::resizeEvent(QResizeEvent* e){
	if(!s) return QWidget::resizeEvent(e);
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

void changedir(CellQ* tmp, Cell::Shape s){
	if(!tmp) return;
	if(tmp->get(Cell::Data_shape_direction)==s)
		return tmp->set(tmp->get(Cell::Data_shape)^Cell::Shape_dir,Cell::Data_shape);
	tmp->set(s, Cell::Data_shape_direction);
	return tmp->set(tmp->get(Cell::Data_shape)|Cell::Shape_dir,Cell::Data_shape);
}

void display(CellQ* tmp, bool b=true){
	if(tmp->get(Cell::Data_group_front)) return;
	tmp->set(Cell::Shape_blank, Cell::Data_shape_shape);
	tmp->set(b?1:2, Cell::Data_group_front);
}

void SolverQ::keyPressEvent(QKeyEvent* event){
	auto tmp=Fouce();
	if(event->modifiers() == Qt::ControlModifier){
		if(!tmp) return;
		switch (event->key()) {
		case Qt::Key_Control:
			tmp->set(0, Cell::Data_num);
			display(tmp, mode==Mode_Input);
			return;
		case Qt::Key_0:
		case Qt::Key_1:
		case Qt::Key_2:
		case Qt::Key_3:
		case Qt::Key_4:
		case Qt::Key_5:
		case Qt::Key_6:
		case Qt::Key_7:
		case Qt::Key_8:
		case Qt::Key_9:
			return tmp->set(tmp->get(Cell::Data_num) * 10 +
							event->key() - Qt::Key_0,
							Cell::Data_num);
		}
	}
	else if(event->modifiers() == Qt::AltModifier){
		if(!tmp) return;
		switch (event->key()) {
		case Qt::Key_0:
		case Qt::Key_1:
		case Qt::Key_2:
		case Qt::Key_3:
		case Qt::Key_4:
		case Qt::Key_5:
		case Qt::Key_6:
		case Qt::Key_7:
		case Qt::Key_8:
		case Qt::Key_9:
			tmp->Maskxor(event->key() - Qt::Key_0);
		}
	}
	else
		switch (event->key()) {
		case Qt::Key_Up:
		case Qt::Key_Down:
		case Qt::Key_Left:
		case Qt::Key_Right:
			return changeFouce(event->key());
		case Qt::Key_0:
		case Qt::Key_1:
		case Qt::Key_2:
		case Qt::Key_3:
		case Qt::Key_4:
		case Qt::Key_5:
		case Qt::Key_6:
		case Qt::Key_7:
		case Qt::Key_8:
		case Qt::Key_9:
			if(!tmp) return;
			tmp->set(event->key() - Qt::Key_0,
					 Cell::Data_num);
		case Qt::Key_O:
			if(!tmp) return;
			display(tmp, mode==Mode_Input);
			return;
		case Qt::Key_W:
			return changedir(tmp, Cell::Shape_up);
		case Qt::Key_S:
			return changedir(tmp, Cell::Shape_down);
		case Qt::Key_A:
			return changedir(tmp, Cell::Shape_left);
		case Qt::Key_D:
			return changedir(tmp, Cell::Shape_right);
		case Qt::Key_Q:
			if(!tmp) return;
			return tmp->set((tmp->get(Cell::Data_shape_direction) +
							 Cell::Shape_left) % (Cell::Shape_down<<1),
							Cell::Data_shape_direction);
		case Qt::Key_E:
			if(!tmp) return;
			return tmp->set((tmp->get(Cell::Data_shape_direction) +
							 Cell::Shape_right) % (Cell::Shape_down<<1),
							Cell::Data_shape_direction);
		case Qt::Key_F:
			if(!tmp) return;
			return tmp->set(tmp->get(Cell::Data_shape)^Cell::Shape_fill,
							Cell::Data_shape);
		case Qt::Key_B:
			if(!tmp) return;
			return tmp->set(tmp->get(Cell::Data_shape)^Cell::Shape_blod,
							Cell::Data_shape);
		case Qt::Key_Bar:
			if(!tmp) return;
			return tmp->set(tmp->get(Cell::Data_shape)^Cell::Shape_dash,
							Cell::Data_shape);
		case Qt::Key_R:
			if(!tmp) return;
			s->clean(fouce[0], fouce[1]);
			return tmp->update();
		case Qt::Key_Escape:
			return enFouce();
		case Qt::Key_Period:
			if(!tmp) return;
			tmp->set(tmp->get(Cell::Data_group_front)?
						 (tmp->get(Cell::Data_num)+1)%100:
						 0,
					 Cell::Data_num);
			return display(tmp, mode==Mode_Input);
		case Qt::Key_Comma:
			if(!tmp) return;
			tmp->set(tmp->get(Cell::Data_group_front)?
						 (tmp->get(Cell::Data_num)+99)%100:
						 0,
					 Cell::Data_num);
			return display(tmp, mode==Mode_Input);
		case Qt::Key_BracketRight:
			if(!tmp) return;
			tmp->set((tmp->get(Cell::Data_shape_shape)+1) %
					 Cell::Shape_num, Cell::Data_shape_shape);
			return display(tmp, mode==Mode_Input);
		case Qt::Key_BracketLeft:
			if(!tmp) return;
			tmp->set((tmp->get(Cell::Data_shape_shape) +
					  Cell::Shape_num-1)%Cell::Shape_num,
					 Cell::Data_shape_shape);
			return display(tmp, mode==Mode_Input);
		}
}

void SolverQ::clean_io(short o){
	for(short i=0;i<=s->nc<<1;i++){
		short bi = i<<1&2;
		for(short j=0;j<=s->nr<<1;j++)
			w[i][j].setAttribute(Qt::WA_TransparentForMouseEvents,
								  o&1<<(bi | j&1)?false:true);
	}
}

inline CellQ* SolverQ::Fouce(){
	try {return &w.at(fouce[0]).at(fouce[1]);}
	catch (...) {return nullptr;}
};

inline void SolverQ::enFouce(short i, short j){
	CellQ* tmp=Fouce();
	if(tmp) tmp->setfouce(false);
	fouce[0]=i, fouce[1]=j;
	tmp=Fouce();
	if(tmp) tmp->setfouce();
};


inline bool SolverQ::checkMd(short i, short j){
	return Md()&1<<(j&1|i<<1&2);
}

inline short SolverQ::changeFouce_(short b, bool a){
	short tmp=(a?wp[fouce[0]].size():wp.size());
	return (fouce[a] + b + tmp) % tmp;
}

void SolverQ::changeFouce(int d){
	CellQ* tmp=Fouce();
	short md=Md();
	if(tmp) tmp->setfouce(false);
	else{
		for(short i=0; i<4; i++){
			if(~md&1<<i) continue;
			fouce[0]=(d==Qt::Key_Right||d==Qt::Key_Up? i&1:i>>1), fouce[1]=(d==Qt::Key_Right||d==Qt::Key_Up? i>>1:i&1);
			tmp=Fouce();
			if(tmp) tmp->setfouce();
			return;
		}
		return;
	}
	if(!md) fouce[0]=fouce[1]=-1;
	bool f=0, p=1;
	switch (d) {
	case Qt::Key_Up:
		p = 0;
	case Qt::Key_Down:
		f = 1;
		break;
	case Qt::Key_Left:
		p = 0;
		break;
	}
	if(f?checkMd(fouce[0], changeFouce_(p?1:-1, 1)):
			checkMd(changeFouce_(p?1:-1, 0), fouce[1]))
		fouce[f]=changeFouce_(p?1:-1, f);
	else if(md&md>>3&1 | md&md>>1&2){
		fouce[f]=changeFouce_(p?1:-1, f);
		fouce[!f]=changeFouce_(fouce[f]&1?1:-1, !f);
	}else
		fouce[f]=changeFouce_(p?2:-2, f);
	tmp=Fouce();
	if(tmp) tmp->setfouce();
};

inline short SolverQ::Md(){
	switch (mode) {
	case Mode_Input:
		return s? s->io():0;
	case Mode_Play:
		return s? s->io()>>4:0;
	case Mode_Solve:
		return 0;
	}
}


void SolverQ::run(){
	for (short i=0; i<s->nc; i++)
		for (short j=0; j<s->nr; j++)
			w[i<<1|1][j<<1|1].set(rand(),rand(),rand());
}

void SolverQ::changeSolver(const QString& svt){
	if(s) delete s;
	s = SolverList::getList().creat(svt.toStdString(), wp);
	if(!s) {
		setMinimumSize(CellQ::Widcell(), CellQ::Widcell());
		for(auto i:wp)
			for(auto j:i)
				((CellQ*)j)->hide();
		return;
	}
	resizeS(s->nc, s->nr);
	s->clean();
	update();
}
