#include "cell.h"

using namespace LPS;

Cell::Cell(short g, short s, short n)
	: group(g), shape(s), num(n){}

short Cell::get(Data d) const{
	switch(d){
	case Data_group:
		return group;
	case Data_group_back:
		return group & groupmask;
	case Data_group_front:
		return group>>groups & groupmask;
	case Data_shape:
		return shape;
	case Data_shape_shape:
		return shape & shapesmask;
	case Data_shape_linestyle:
		return shape & shapelmask;
	case Data_shape_direction:
		return shape & shapedmask;
	case Data_num:
		return num;
	default:
		return -1;
	}
}

void Cell::set(short data, Data d){
	switch(d){
	case Data_group:
		group = data;
		return;
	case Data_group_back:
		shape &= ~groupmask;
		shape |= data & shapesmask;
		return;
	case Data_group_front:
		shape &= ~(groupmask<<groups);
		shape |= (data & shapesmask)<<groups;
		return;
	case Data_shape:
		shape = data;
		return;
	case Data_shape_shape:
		shape &= ~shapesmask;
		shape |= data & shapesmask;
		return;
	case Data_shape_linestyle:
		shape &= ~shapelmask;
		shape |= data & shapelmask;
		return;
	case Data_shape_direction:
		shape &= ~shapedmask;
		shape |= data & shapedmask;
		return;
	case Data_num:
		num = data;
	default:
		return;
	}
}

void Cell::set(short g, short s, short n){
	this->group = g;
	this->shape = s;
	this->num = n;
}

void Cell::Mask(bool zero){
	num = zero? 0x7FFA : 0x7FE9;
	if(!group) group = -1;
}

bool Cell::Maskcheck() const{
	return num&1<<14;
}

void Cell::Maskadd(short n){
	if(!Maskcheck()) return;
	if(num&1<<n+4) return;
	num ^= 1<<n+4;
	num++;
	return;
}

void Cell::Masksub(short n){
	if(!Maskcheck()) return;
	if(~num&1<<n+4) return;
	num ^= 1<<n+4;
	num--;
	return;
}

Cell& Cell::operator=(const Cell& t){
	this->group = t.group;
	this->shape = t.shape;
	this->num = t.num;
	return *this;
}
