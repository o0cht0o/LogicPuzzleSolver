#ifndef CELL_H
#define CELL_H

namespace LPS{
class Cell{
protected:
	short group, shape, num;
	/*group: 0 null
	 *shape: 0 blank, 1 dot, 2 line , 3 triangle...
	 *	while shape==2, num: 0 line, 1 dashed line, 2 bold line, 3 bold dashed line */

public:
	Cell(short=0, short=0, short=0x7FFA);
	short get(char='n') const;
	void set(short, char='n');
	void set(short, short, short);

	void Mask(bool=false); // No Zero
	bool Maskcheck() const;
	void Maskadd(short);
	void Masksub(short);
};
}

#endif
