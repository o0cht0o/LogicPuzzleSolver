#ifndef CELLQ_H
#define CELLQ_H

#include <QWidget>
#include "../lpslib/base/cell.h"

namespace LPS {
class CellQ : public QWidget , public Cell{
	Q_OBJECT

public:
	explicit CellQ(QWidget* parent = nullptr);
	explicit CellQ(const CellQ&);


private:
	static short widCell;

protected:
	bool isHover=false, isPress=false;

	void paintEvent(QPaintEvent *) override;
	void enterEvent(QEvent *event) override;
	void leaveEvent(QEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;

public:
	inline static const short& Widcell(){
		return widCell;}
	inline static void setWidcell(short w){
		widCell=w;}

	CellQ& operator=(Cell&);
	inline CellQ& operator=(CellQ& c){
		return *this=(Cell&)c;}


	virtual void set(short, Data=Data_num) override;
	virtual void set(short, short, short) override;

	virtual void Mask(bool=false) override; // No Zero
	virtual short Maskadd(short) override;
	virtual short Masksub(short) override;
};
}

#endif // CELLQ_H
