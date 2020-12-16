#ifndef SUDOKU_H
#define SUDOKU_H

#include "../base/solver.h"

using std::vector;

namespace LPS{

class Cell;

namespace SVR{

class Sudoku:public Solver{

protected:

public:
	Sudoku();
	Sudoku(CellMap&);
	~Sudoku();

	virtual inline short io() override {return 0x88;};
	virtual void clean();
	virtual void clean(short, short);
	virtual void check();
	virtual short solve();
};
}
}
#endif // SUDOKU_H
