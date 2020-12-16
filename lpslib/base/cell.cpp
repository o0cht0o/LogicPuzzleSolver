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
	case Data_shape_style:
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
		group &= ~groupmask;
		group |= data & shapesmask;
		return;
	case Data_group_front:
		group &= ~(groupmask<<groups);
		group |= (data & shapesmask)<<groups;
		return;
	case Data_shape:
		shape = data;
		return;
	case Data_shape_shape:
		shape &= ~shapesmask;
		shape |= data & shapesmask;
		return;
	case Data_shape_style:
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
	MaskCor();
}

void Cell::Mask(bool zero){
	num = zero? 0x7FFA : 0x7FE9;
	if(!group) group = -1;
}

bool Cell::isMask() const{
	return num&1<<14;
}

void Cell::MaskCor() {
	if(!isMask()) return;
	num &= ~0xF;
	for(short i=0;i<10;i++)
		if(num&1<<i+4) num++;
}

short Cell::Maskadd(short n){
	if(!isMask()) return 2;
	if(num&1<<n+4) return 1;
	num ^= 1<<n+4;
	num++;
	return 0;
}

short Cell::Masksub(short n){
	if(!isMask()) return 2;
	if(~num&1<<n+4) return 1;
	num ^= 1<<n+4;
	num--;
	return 0;
}

short Cell::Maskxor(short n){
	if(!isMask()) return 2;
	num ^= 1<<n+4;
	num&1<<n+4? num++:num--;
	return 0;
}

Cell& Cell::operator=(const Cell& t){
	this->group = t.group;
	this->shape = t.shape;
	this->num = t.num;
	return *this;
}
