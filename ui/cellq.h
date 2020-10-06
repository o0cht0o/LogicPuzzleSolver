#ifndef CELLQ_H
#define CELLQ_H

#include <QWidget>
#include "../lpslib/base/cell.h"

namespace LPS {
class CellQ : public QWidget , public Cell{
	Q_OBJECT

protected:
	bool isHover=false, isPress=false;

	void paintEvent(QPaintEvent *) override;
	void enterEvent(QEvent *event) override;
	void leaveEvent(QEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;

public:
	explicit CellQ(QWidget* parent = nullptr);
	explicit CellQ(const CellQ&);

	virtual void set(short, Data=Data_num) override;
	virtual void set(short, short, short) override;

	virtual void Mask(bool=false) override; // No Zero
	virtual void Maskadd(short) override;
	virtual void Masksub(short) override;

	CellQ& operator=(Cell&);

};
}

#endif // CELLQ_H
