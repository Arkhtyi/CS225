/* Your code here! */

#ifndef dsets_h
#define dsets_h

#include <vector>

class DisjointSets {

private:
	
	std::vector<int> joints;

public:

	void addelements (int num) ;

	int find(int elem);
	
	void setunion(int a, int b);

};

#endif
