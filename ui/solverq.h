#ifndef SOLVERQ_H
#define SOLVERQ_H

#include <QWidget>
#include <vector>

using std::vector;

namespace LPS {

class Cell;
class CellQ;
class Solver;

class SolverQ : public QWidget
{
	Q_OBJECT

private:
	Solver* s;
	vector<vector<CellQ>> w;
	vector<vector<Cell*>> wp;
	short fouce[2] = {-1, -1};

	enum class Mode: short{
		Mode_Input,
		Mode_Play,
		Mode_Solve
	}mode;

public:
	explicit SolverQ(QWidget *parent = nullptr);

	void resizeS(short col, short row,
				bool cb=true, bool rb=true);

	void clean_io(short);
	inline CellQ* Fouce();

protected:
	virtual void resizeEvent(QResizeEvent*) override;

public slots:
	void run();
};
}

#endif // SOLVERQ_H
