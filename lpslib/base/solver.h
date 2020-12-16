#ifndef SOLVER_H
#define SOLVER_H

#include <vector>
#include <string>

using std::vector;
using std::string;

namespace LPS{

class Cell;
typedef vector<vector<Cell*>> CellMap;

class Solver{
private:
	vector<vector<Cell>> world;
	CellMap wp;

protected:
	CellMap& w;
	short r,c;

public:
	Solver();
	Solver(CellMap&);

	enum ToB : short {
		dot=0b00,
		block=0b11,
		hline=0b10,
		vline=0b01
	};

	enum IO : short {
		IO_dotin	=1<<dot,
		IO_blockin	=1<<block,
		IO_hlinein	=1<<hline,
		IO_vlinein	=1<<vline,
		IO_dotout	=0x100<<dot,
		IO_blockout	=0x100<<block,
		IO_hlineout	=0x100<<hline,
		IO_vlineout	=0x100<<vline
	};

	const short& nc,& nr;

	Cell& get(short col, short row,
			  bool cb=true, bool rb=true) const;
	void resize(short col, short row,
				bool cb=true, bool rb=true);

	virtual inline short io(){return 0x9;};
	virtual void clean();
	virtual void clean(short, short);
	virtual void check();
	virtual short solve();
};
}
#endif // SOLVER_H
