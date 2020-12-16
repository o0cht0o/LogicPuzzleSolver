#ifndef SOLVERQ_H
#define SOLVERQ_H

#include <QWidget>
#include <vector>
#include <string>

using std::vector;
using std::string;

QT_BEGIN_NAMESPACE
class QString;
QT_END_NAMESPACE

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

	enum Mode: short{
		Mode_Input,
		Mode_Play,
		Mode_Solve
	}mode;

	inline short Md();
	void clean_io(short);
	CellQ* Fouce();
	void enFouce(short=-1, short=-1);
	bool checkMd(short=-1, short=-1);
	short changeFouce_(short,bool);
	void changeFouce(int);

public:
	explicit SolverQ(QWidget *parent = nullptr);

	void resizeS(short col, short row,
				bool cb=true, bool rb=true);


protected:
	virtual void resizeEvent(QResizeEvent*) override;
	virtual void keyPressEvent(QKeyEvent*) override;

public slots:
	void run();
	void changeSolver(const QString&);
};
}

#endif // SOLVERQ_H
