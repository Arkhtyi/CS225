// **************************************************************
// *		   
// *  quadtree.h
// *		   
// *  Quadtree class
// *		   
// *  CS 225 Spring 2008
// *		   
// **************************************************************

#ifndef QUADTREE_H
#define QUADTREE_H

#include "png.h"

class Quadtree
{

	
	private:

	// A simple class representing a single node of a Quadtree.
	// You may want to add to this class; in particular, it could probably
	// use a constructor or two...
	class QuadtreeNode
	{
		public:
		QuadtreeNode* nwChild;  // pointer to northwest child
		QuadtreeNode* neChild;  // pointer to northeast child
		QuadtreeNode* swChild;  // pointer to southwest child
		QuadtreeNode* seChild;  // pointer to southeast child

		RGBAPixel element;  // the pixel stored as this node's "data"
		
		int xcord;
		int ycord;
		int pixres;
		
		QuadtreeNode(){
			nwChild = NULL;
			neChild = NULL;
			swChild = NULL;
			seChild = NULL;
		}
		
		QuadtreeNode(RGBAPixel value){
			element = value;
			nwChild = NULL;
			neChild = NULL;
			swChild = NULL;
			seChild = NULL;
		
		
		
		};
	};

	
	int res;
	
	
	QuadtreeNode* root;    // pointer to root of quadtree
	
	public:
	
	
	Quadtree();
	Quadtree(PNG const & source, int resolution);
	
	void copy(QuadtreeNode * &node, QuadtreeNode * node2 );
	
	Quadtree(Quadtree const & other);
	~Quadtree();
	
	void clear(QuadtreeNode * node);
		
	void buildTree(PNG const & source, int resolution);
	QuadtreeNode * buildTree(PNG const & source, int xstart, int ystart, int resolution);
	
	
	RGBAPixel getPixel(int x, int y) const;
	RGBAPixel getPixel(int x, int y, QuadtreeNode * node) const;
	
	PNG decompress();
	void decompress(QuadtreeNode * node, PNG & temp, int x, int y);
	
	void prune(int tolerance);
	bool prunechecker(QuadtreeNode * node, int tolerance, RGBAPixel base) const;
	void prune(QuadtreeNode * node, int tolerance);
	int pruneSize (int  tolerance)const;
	void pruneSize (QuadtreeNode * node, int tolerance, int & count) const;
	int idealPrune (int numLeaves) const;
	
	Quadtree const & operator= (Quadtree const & other);
	
	void clockwiseRotate( );
	void clockwiseRotate(QuadtreeNode * node);

	
	/**** Functions added for testing/grading                ****/
	/**** Do not remove this line or copy its contents here! ****/
	#include "quadtree_given.h"
};

#endif
