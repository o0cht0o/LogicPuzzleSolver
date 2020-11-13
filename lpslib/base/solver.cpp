#include "solver.h"
#include "cell.h"

using namespace LPS;

const class Solverdefine{
public:
	vector<Cell> list[4];

	Solverdefine(){
		list[Solver::dot].push_back(Cell(Cell::Group_defined<<(sizeof(short)<<2) | Cell::Group_null, Cell::Shape_dot, 0));
		list[Solver::block].push_back(Cell(0,0,0));
		list[Solver::vline].push_back(Cell(Cell::Group_defined<<(sizeof(short)<<2) | Cell::Group_null,
						   Cell::Shape_line|Cell::Shape_vdir, 0));
		list[Solver::hline].push_back(Cell(Cell::Group_defined<<(sizeof(short)<<2) | Cell::Group_null,
						   Cell::Shape_line|Cell::Shape_hdir, 0));
	}

}Sd={};

const short Solver::io=0;

Solver::Solver()
	:w(wp), nc(c), nr(r), c(0), r(0){}

Solver::Solver(vector<vector<Cell*>>& W)
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
		short bi = i<<1&2;
		for(short j=0;j<=r<<1;j++)
			*w[i][j] = Sd.list[bi | j&1][0];
	}
	for(short i=0;i<c;i++){
		this->get(i,0,1,0).set(Cell::Shape_blod,
							   Cell::Data_shape_style);
		this->get(i,r,1,0).set(Cell::Shape_blod,
								Cell::Data_shape_style);
	}
	for(short i=0;i<r;i++){
		this->get(0,i,0,1).set(Cell::Shape_blod,
							   Cell::Data_shape_style);
		this->get(c,i,0,1).set(Cell::Shape_blod,
							   Cell::Data_shape_style);
	}
	this->get(0,0,0,0).set(Cell::Shape_blod|Cell::Shape_dir|Cell::Shape_fill,
						   Cell::Data_shape_style);
	this->get(c,0,0,0).set(Cell::Shape_blod|Cell::Shape_dir|Cell::Shape_fill,
						   Cell::Data_shape_style);
	this->get(0,r,0,0).set(Cell::Shape_blod|Cell::Shape_dir,
						   Cell::Data_shape_style);
	this->get(c,r,0,0).set(Cell::Shape_blod|Cell::Shape_dir,
						   Cell::Data_shape_style);
	this->get(0,0,0,0).set(Cell::Shape_up,
						   Cell::Data_shape_direction);
	this->get(c,0,0,0).set(Cell::Shape_left,
						   Cell::Data_shape_direction);
	this->get(0,r,0,0).set(Cell::Shape_down,
						   Cell::Data_shape_direction);
	this->get(c,r,0,0).set(Cell::Shape_right,
						   Cell::Data_shape_direction);
}

short Solver::solve(){
	return 0;
}
