#ifndef CELL_H
#define CELL_H

namespace LPS{
class Cell{
private:
	static const short
		groups = sizeof(short)<<2,
		shapes = 6,
		shapel = 2,
		shaped = 3,
		groupmask = (1<<groups)-1,
		shapesmask = (1<<shapes)-1,
		shapelmask = (1<<shapel)-1<<shapes,
		shapedmask = (1<<shaped)-1<<shapes+shapel;

protected:
	short group, shape, num;
	bool Maskcheck() const;

public:
	enum Data: short {
		Data_Null,
		Data_group,
		Data_group_back,
		Data_group_front,
		Data_shape,
		Data_shape_shape,
		Data_shape_linestyle,
		Data_shape_direction,
		Data_num
	};
	enum Shape: short {
		Shape_blank=0,
		Shape_dot,
		Shape_cross,
		Shape_circle,
		Shape_circle_d,
		Shape_triangle,
		Shape_square,
		Shape_diamond,
		Shape_line,
		Shape_slash,
		Shape_blod	= 1<<shapes,
		Shape_dash	= 2<<shapes,
		Shape_nodir	= 0<<shapes+shapel,
		Shape_hdir	= 1<<shapes+shapel,
		Shape_vdir	= 2<<shapes+shapel,
		Shape_up	= 4<<shapes+shapel,
		Shape_left	= 5<<shapes+shapel,
		Shape_down	= 6<<shapes+shapel,
		Shape_right	= 7<<shapes+shapel,
	};
	enum Group: short {
		Group_null=0,
		Group_defined,
		Group_comfired,
		Group_possible
	};

	explicit Cell(short g=0, short s=0, short n=0x7FE9);

	short get(Data=Data_num) const;
	virtual void set(short, Data=Data_num);
	virtual void set(short, short, short);

	virtual void Mask(bool=false); // No Zero
	virtual void Maskadd(short);
	virtual void Masksub(short);

	bool Bold() const;
	bool Dashed() const;

	Cell& operator=(const Cell&);
};
}

#endif
