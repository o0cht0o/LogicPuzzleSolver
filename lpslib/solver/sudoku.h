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
	virtual void clean() override;
	virtual void clean(short, short) override;
	virtual void check() override;
	virtual short solve() override;
};
}
}
#endif // SUDOKU_H
