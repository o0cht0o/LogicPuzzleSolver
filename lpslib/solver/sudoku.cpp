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
	clean();
}

void Sudoku::clean(){}
void Sudoku::clean(short, short){}
void Sudoku::check(){}
short Sudoku::solve(){}
