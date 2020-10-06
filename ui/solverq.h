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

public:
	explicit SolverQ(QWidget *parent = nullptr);

	void resizeS(short col, short row,
				bool cb=true, bool rb=true);

protected:
	virtual void resizeEvent(QResizeEvent*) override;

signals:

};
}

#endif // SOLVERQ_H
