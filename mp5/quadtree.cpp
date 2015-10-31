// **************************************************************
// *		   
// *  quadtree.cpp
// *		   
// *  Quadtree class
// *		   
// *  CS 225 Spring 2008
// *		   
// **************************************************************

#include "quadtree.h"

Quadtree::Quadtree(){

	root = NULL;
	res = 0;

}




Quadtree::Quadtree(PNG const & source, int resolution){

	root = NULL;
	buildTree(source, resolution);
	res = resolution;
	
}

Quadtree::Quadtree (Quadtree const & other){

	
	this->res = other.res;
	copy(root, other.root);

}

void Quadtree:: copy(QuadtreeNode * &node, QuadtreeNode * node2 ){
	
	if(node2 == NULL)
		return;	
		
		
	node = new QuadtreeNode();

	if(node2->nwChild == NULL && node2->neChild == NULL && node2->swChild == NULL && node2->seChild == NULL){
		node->element = node2->element;
		node->xcord = node2->xcord;
		node->ycord = node2->ycord;
		node->pixres = node2->pixres;
	}else{
		copy(node->neChild,node2->neChild);
		copy(node->nwChild,node2->nwChild);	
		copy(node->seChild,node2->seChild);	
		copy(node->swChild,node2->swChild);
		
		node->element = node2->element;
		node->xcord = node2->xcord;
		node->ycord = node2->ycord;
		node->pixres = node2->pixres;
		
	} 


}

Quadtree const & Quadtree::operator= (Quadtree const & other){

	if (this != &other)
	{
		clear(root);
		this->res = other.res;
		copy(root, other.root);
	}
		
	return *this;
}


Quadtree::~Quadtree(){

	clear(root);
	root = NULL;

}


void Quadtree::clear(QuadtreeNode * node){
	
	if(node == NULL)
		return;
	
	clear(node->nwChild);
	clear(node->neChild);
	clear(node->swChild);
	clear(node->seChild);
	delete node;
	
	
	

}



void Quadtree::buildTree(PNG const & source, int resolution){

	root = buildTree(source, 0,  0, resolution);
	

}

Quadtree::QuadtreeNode * Quadtree::buildTree(PNG const & source, int xstart, int ystart, int resolution){

	QuadtreeNode * temp = new QuadtreeNode();

	if(resolution < 1){
		delete temp;
		return NULL;
	}
	if(resolution == 1){
		temp->nwChild = NULL;
		temp->neChild = NULL;
		temp->swChild = NULL;
		temp->seChild = NULL;		
		temp->pixres = 1;
		temp->xcord = xstart;
		temp->ycord = ystart;
		temp->element = *source(temp->xcord,temp->ycord);	
		return temp;	
	}else{
		temp->nwChild = buildTree(source,xstart, ystart,  resolution/2);
		temp->neChild = buildTree(source,xstart+resolution/2, ystart,  resolution/2);
		temp->swChild = buildTree(source,xstart, ystart+resolution/2, resolution/2);
		temp->seChild = buildTree(source,xstart+resolution/2, ystart+resolution/2,  resolution/2);
		
		RGBAPixel tempo;
		tempo.red = (temp->nwChild->element.red + temp->neChild->element.red + temp->swChild->element.red + temp->seChild->element.red)/4;
		tempo.green = (temp->nwChild->element.green + temp->neChild->element.green + temp->swChild->element.green + temp->seChild->element.green)/4;
		tempo.blue = (temp->nwChild->element.blue + temp->neChild->element.blue + temp->swChild->element.blue + temp->seChild->element.blue)/4;
		
		temp->element = tempo;
		temp->pixres = resolution;
		temp->xcord = xstart;
		temp->ycord = ystart;
		return temp;
	}

}



RGBAPixel Quadtree:: getPixel(int x, int y) const{

	return getPixel( x, y, root);

}

/*
RGBAPixel Quadtree:: getPixel(int x, int y, QuadtreeNode * node, int resolution) const{

	if(resolution == 1)
		return node->element;
	
	if(getPixel(x,y,node->nwChild,resolution/2) != NULL)
		return getPixel(x,y,node->nwChild,resolution/2) 
	if(getPixel(x+resolution/2,y,node->nwChild,resolution/2) != NULL)
		return getPixel(x,y,node->nwChild,resolution/2) 
	if(getPixel(x,y,node->nwChild+resolution/2,resolution/2) != NULL)
		return getPixel(x,y,node->swChild,resolution/2) 
	if(getPixel(x+resolution/2,y,node->nwChild+resolution/2,resolution/2) != NULL)
		return getPixel(x,y,node->seChild,resolution/2)
	
	else{
		return  RGBAPixel();

	}


}
*/

RGBAPixel Quadtree:: getPixel(int x, int y, QuadtreeNode * node) const{

	

	if(node->nwChild == NULL && node->neChild == NULL && node->swChild == NULL && node->seChild == NULL)
		return node->element;

	if(x > node->xcord  && x < node->xcord + (node->pixres/2) && y > node->ycord && y < node->ycord + (node->pixres/2))
		return getPixel(x,y,node->nwChild);
	if(x < node->xcord + node->pixres && x > node->xcord + (node->pixres/2) && y > node->ycord && y < node->ycord + (node->pixres/2))
		return getPixel(x,y,node->neChild);
	if(x > node->xcord && x < node->xcord + (node->pixres/2) && y > node->ycord + (node->pixres/2) && y < node->ycord + node->pixres)
		return getPixel(x,y,node->swChild);
	if(x > node->xcord + (node->pixres/2) && x < node->xcord + node->pixres && y >node->ycord+(node->pixres/2) && y < node->ycord + node->pixres)
		return getPixel(x,y,node->seChild);
	else{

		return RGBAPixel();

	}

}


PNG Quadtree::decompress(){

	PNG temp;
	if(root == NULL)
		return temp;
	else{
		temp.resize((size_t)root->pixres,(size_t)root->pixres);
		decompress(root,temp, 0, 0);
		return temp;
	}
}

void Quadtree::decompress(QuadtreeNode * node, PNG & temp, int x, int y){

	if(node->nwChild == NULL && node->neChild == NULL && node->swChild == NULL && node->seChild == NULL){
		for(int i = 0; i < node->pixres; i++){
			for(int j = 0; j<node->pixres; j++){
			temp(x+i,y+j)->red = node->element.red;
			temp(x+i,y+j)->green = node->element.green;
			temp(x+i,y+j)->blue = node->element.blue;		
			}
		}
	}
	else{
		decompress(node->nwChild, temp, x, y);
		decompress(node->neChild, temp, x + node->pixres/2, y);
		decompress(node->swChild, temp, x, y + node->pixres/2);
		decompress(node->seChild, temp, x + node->pixres/2, y + node->pixres/2);
	}

}


void Quadtree::prune(int tolerance){
	prune(root, tolerance);

}

bool Quadtree::prunechecker(QuadtreeNode * node, int tolerance, RGBAPixel base) const{

	if(node == NULL)
		return false;
	if(node->nwChild == NULL && node->nwChild == NULL && node->swChild == NULL && node->seChild == NULL){
		int tol = (node->element.red - base.red) * (node->element.red - base.red) + (node->element.green - base.green) * (node->element.green - base.green) + (node->element.blue - base.blue) * (node->element.blue - base.blue);
		if(tol <= tolerance)
			return true;
		else
			return false;
	}else{
		if(prunechecker(node->neChild, tolerance, base) == false)
			return false;
		if(prunechecker(node->nwChild, tolerance, base) == false)
			return false;
		if(prunechecker(node->swChild, tolerance, base) == false)
			return false;
		if(prunechecker(node->seChild, tolerance, base) == false)
			return false;	
		else
			return true;
	
	
	}

}

void Quadtree::prune(QuadtreeNode * node, int tolerance){
	
	if(node == NULL)
		return;
		
	if(prunechecker(node, tolerance, node->element)){
		clear(node->neChild);
		clear(node->nwChild);
		clear(node->seChild);
		clear(node->swChild);	
		
		node->neChild = NULL;
		node->nwChild = NULL;
		node->seChild = NULL;
		node->swChild = NULL;
		
	}
	else {
		prune(node->neChild, tolerance);
		prune(node->nwChild, tolerance);
		prune(node->seChild, tolerance);
		prune(node->swChild, tolerance);
	
	
	}
}



int Quadtree::pruneSize (int tolerance) const{

	int count = 0;

	pruneSize(root, tolerance, count);

	return count;
}


void Quadtree::pruneSize (QuadtreeNode * node, int tolerance, int & count) const{

	if(node == NULL)
		return;
		
	if(prunechecker(node, tolerance, node->element)){
		count++;
	}	
	else if(node->nwChild == NULL && node->nwChild == NULL && node->swChild == NULL && node->seChild == NULL){
		count++;
	}
	else {
	
		pruneSize(node->neChild, tolerance, count);
		pruneSize(node->nwChild, tolerance, count);
		pruneSize(node->seChild, tolerance, count);
		pruneSize(node->swChild, tolerance, count);
		
	}


}


int Quadtree::idealPrune (int numLeaves) const{

	int min = 0;
	int max = 3 * 255 * 255;
	int tol = 0;
	int save = 0;
	
	int result = 0;
	
	
	while(max >= min){ 
		tol = (max-min)/2 + min;
		result = pruneSize(tol);
		
		std::cout<< result <<" " << min << " " << max << std::endl;
		
		if(result <= numLeaves)
			max = tol-1;
			
		
		
		if(result > numLeaves){
			min = tol+1; 
			save = tol;
		}
		
		
	}
	if(result > numLeaves){
		tol = (max-min)/2 + min;
		result = pruneSize(tol);
		min = tol+1; 
		save = tol;
	}
	return tol;
}

void Quadtree::clockwiseRotate(){
	clockwiseRotate(root);

}

void Quadtree::clockwiseRotate(QuadtreeNode * node){
	QuadtreeNode * temp;
	
	if(node == NULL){
		return;
	}else{
		temp = node->neChild;
		
		node->neChild = node->nwChild;
		
		node->nwChild = node->swChild;
		
		node->swChild = node->seChild;	
		
		
		node->seChild = temp;
	

		clockwiseRotate(node->neChild);
		clockwiseRotate(node->nwChild);
		clockwiseRotate(node->seChild);
		clockwiseRotate(node->swChild);
		
	}
}
