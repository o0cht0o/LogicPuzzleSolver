#include "cell.h"

using namespace LPS;

Cell::Cell(short group, short shape, short num)
	: group(group), shape(shape), num(num){}

short Cell::get(char t) const{
	switch(t){
	case 'g':
		return group;
	case 's':
		return shape;
	case 'n':
		return num;
	default:
		return -1;
	}
}

void Cell::set(short data, char t){
	switch(t){
	case 'g':
		group = data;
		return;
	case 's':
		shape = data;
		return;
	case 'n':
		num = data;
	default:
		return;
	}
}

void Cell::set(short g, short s, short n){
	*this={g,s,n};
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
