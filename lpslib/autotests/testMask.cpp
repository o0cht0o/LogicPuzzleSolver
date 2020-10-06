#include <iostream>
#include <ctime>
#include "../base/cell.h"

using LPS::Cell;
using namespace std;

void Maskshow(Cell c){
	short tmp=c.get();
	cout<<endl<<tmp<<endl;
	for(int i=0;i<10;i++){
		if(~tmp&1<<i+4) continue;
		cout<<i<<' ';
	}
	cout<<(tmp&0xF)<<endl;
	return;
}

bool Maskcheck(Cell c, short a, bool b){
	short tmp=c.get(),s=0;
	if(~tmp&1<<14) return false;
	for(int i=0;i<10;i++){
		if(~tmp&1<<i+4) continue;
		s++;
	}
	if(s!=(tmp&0xF)) return false;
	return b? tmp&1<<a+4 : ~tmp&1<<a+4;
}

int main(){
	srand(time(0));
	Cell cell;
	cell.Mask();
	short a, b;
	unsigned short i = -1;
	while(i--){
		cout<<"\r"<<i<<"\t tests left.";
		b = rand()%10;
		a = rand()%2;
		a? cell.Maskadd(b) : cell.Masksub(b);
		if(!Maskcheck(cell,b,a)) {
			cout<<"\r"<<(a?'+':'-')<<b;
			Maskshow(cell);
		}
	}
	cout<<"\r"<<(unsigned short)-1<<"\t tests done."<<endl;
	return 0;
}
