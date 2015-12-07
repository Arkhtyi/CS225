/* Your code here! */

#include "dsets.h"

void DisjointSets::addelements (int  num){
	
	
	for(int i = 0; i < num; i++){
		joints.push_back(-1);
	}
	

}

int DisjointSets::find(int elem){

	if(joints[elem] < 0) return elem;
	else return find(joints[elem]);

}

void DisjointSets::setunion(int a, int b){
	int roota = find(a);
	int rootb = find(b);
	int newsize = joints[roota] + joints[rootb];
	if(roota > rootb){
		joints[rootb] = roota;
		joints[roota] = newsize;
	}
	else{
		joints[roota] = rootb;
		joints[rootb] = newsize;
	}

}


