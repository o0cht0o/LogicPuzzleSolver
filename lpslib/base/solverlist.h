#ifndef SOLVERLIST_H
#define SOLVERLIST_H

#include <map>
#include "solver.h"

using std::map;

namespace LPS{

class Cell;
class Solver;

typedef Solver* (*PTRCO)(CellMap&);

class SolverList{
private:
	map<const string, PTRCO> svl;
	inline SolverList(){};

public:
	Solver* creat(const string, CellMap&);
	void registClass(const string, PTRCO);
	static SolverList& getList();
	inline static const map<const string, PTRCO>& sl(){
		return getList().svl;
	};
};

class RegAct{
public:
	inline RegAct(const string svt, PTRCO cf){
		SolverList::getList().registClass(svt, cf);
	}
};

}

#define REGSVT(svt)								\
	namespace LPS{namespace RSV{				\
	Solver* OC##svt(CellMap& cm){return new svt(cm);}		\
	RegAct reg##svt(#svt, OC##svt);}}

#endif // SOLVERLIST_H
