#include "solver.h"
#include "cell.h"

using namespace LPS;

const class Solverdefine{
public:
	vector<Cell> list[4];

	Solverdefine(){
		list[Solver::dot].push_back(Cell(Cell::Group_defined<<(sizeof(short)<<2) | Cell::Group_null, Cell::Shape_dot, 0));
		list[Solver::block].push_back(Cell(0,0));
		list[Solver::vline].push_back(Cell(Cell::Group_defined<<(sizeof(short)<<2) | Cell::Group_null,
						   Cell::Shape_line|Cell::Shape_vdir, 0));
		list[Solver::hline].push_back(Cell(Cell::Group_defined<<(sizeof(short)<<2) | Cell::Group_null,
						   Cell::Shape_line|Cell::Shape_hdir, 0));
	}

}Sd={};

Solver::Solver()
	:w(wp), nc(c), nr(r), c(0), r(0){}

Solver::Solver(CellMap& W)
	:w(W), nc(c), nr(r){
	if(!w.size()||!w[0].size()){
		c = r = 0;
		return;
	}
	c = (w.size()-1)>>1;
	w.resize(c<<1|1);
	r = (w[0].size()-1)>>1;
	for(short i=0; i<w.size(); i++) w[i].resize(r<<1|1);
	clean();
}


Cell& Solver::get(short col, short row,
				  bool cb, bool rb) const{
	return *w[col<<1|cb][row<<1|rb];
}

void Solver::resize(short col, short row,
					 bool cb, bool rb){
	short tmpc=col-!cb, tmpr=row-!rb, tmp=tmpr<<1|1;
	if(&w==&wp){
		w.resize(tmpc<<1|1);
		world.resize(tmpc<<1|1);
		for(short i=0; i < w.size(); i++){
			w[i].resize(tmp);
			world[i].resize(tmp);
			for(short j=0; j < tmp; j++) w[i][j] = &world[i][j];
		}
	}
	c=tmpc, r=tmpr;
}

void Solver::clean(){
	for(short i=0;i<=c<<1;i++){
		for(short j=0;j<=r<<1;j++)
			clean(i,j);
	}
}

void Solver::clean(short i, short j){
	*w[i][j] = Sd.list[i<<1&2 | j&1][0];
	if(!i || !j || i==nc<<1 || j==nr<<1)
		w[i][j]->set(Cell::Shape_blod, Cell::Data_shape_style);
}

inline void Solver::check(){}

inline short Solver::solve(){return 0;}
