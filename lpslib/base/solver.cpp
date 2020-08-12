#include "solver.h"

using namespace LPS;

Solver::Solver(vector<vector<Cell>>& W)
	:world(W){
	if(!world.size()){
		c = r = 0;
		return;
	}
	c = (world.size()-1)>>1;
	r = (world[0].size()-1)>>1;
}

void Solver::clean(){
	for(int i=0;i<=c<<1;i++)
		for(int j=0;j<=r<<1;j++)
			if((i^j)&1) world[i][j] = {};
			else world[i][j] = {0, 2, 0};
	for(int i=0;i<c;i++){
		this->get(i,0,1,0).set(2);
		this->get(i,r,1,0).set(2);
	}
	for(int i=0;i<r;i++){
		this->get(0,i,0,1).set(2);
		this->get(c,i,0,1).set(2);
	}
}

void Solver::resize(short col, short row,
					 bool cb, bool rb){
	short tmpc=col-1+cb, tmpr=row-1+rb, tmp=tmpr<<1|1;
	world.resize(tmpc<<1|1);
	for(auto i:world) i.resize(tmp);
	c=tmpc, r=tmpr;
}

Cell& Solver::get(short col, short row,
				  bool cb, bool rb){
	return world[col<<1|cb][row<<1|rb];
}

void Solver::set(short col, short row,
				  short data, char t,
				  bool cb, bool rb){
	world[col<<1|cb][row<<1|rb].set(data, t?t:'n');
}

short Solver::solve(){
	return 0;
}
