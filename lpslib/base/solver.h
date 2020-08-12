#ifndef SOLVER_H
#define SOLVER_H

#include <vector>
#include "cell.h"

using std::vector;

namespace LPS{
class Solver{
protected:
	vector<vector<Cell>>& world;
	short r,c;

public:
	Solver(vector<vector<Cell>>&);

	virtual void clean();
	virtual void resize(short col, short row,
						 bool cb=true, bool rb=true);
	virtual Cell& get(short col, short row,
					  bool cb=true, bool rb=true);
	virtual void set(short col, short row,
					 short, char=0,
					 bool cb=true, bool rb=true);
	virtual short solve();
};
}
#endif // SOLVER_H
