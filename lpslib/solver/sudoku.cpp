#include "sudoku.h"
#include "../base/cell.h"
#include "../base/solverlist.h"

using namespace LPS::SVR;

REGSVT(Sudoku)

Sudoku::Sudoku()
	:Solver(){
	clean();
}

Sudoku::Sudoku(CellMap& W)
	:Solver(W){
	resize(9,9);
}

void Sudoku::clean(){
	if(&w==&wp) resize(9,9);
	for(short i=0;i<=c<<1;i++)
		for(short j=0;j<=r<<1;j++)
			clean(i, j);
}

void Sudoku::clean(short i, short j){
	Solver::clean(01221, i, j);
	if(i%6==0||j%6==0)
		w[i][j]->set(Cell::Shape_blod, Cell::Data_shape_style);
}
void Sudoku::check(){}
short Sudoku::solve(){}
