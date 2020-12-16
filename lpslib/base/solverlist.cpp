#include "solverlist.h"

using namespace LPS;
namespace LPS{namespace RSV{
Solver* OC(CellMap&){return nullptr;}
RegAct reg("", OC);}}

Solver* SolverList::creat(const string svt, CellMap& cm){
	auto tmp = svl.find(svt);
	if(tmp==svl.end()) return nullptr;
	return tmp->second(cm);
}

void SolverList::registClass(const string svt, PTRCO cf){
	svl.insert(std::make_pair(svt, cf));
}
SolverList& SolverList::getList(){
	static SolverList svl;
	return svl;
}
