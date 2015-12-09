/* Your code here! */

#include <unordered_map>
#include "maze.h"

SquareMaze::SquareMaze(){
	
	

}

int SquareMaze::getx(int i, int width){

	return i%width;

};
	
int SquareMaze::gety(int i, int width){
	
	return i/width;	
	
}

int SquareMaze::getId(int x, int y, int width) const{

	return width*y+x;
}


void SquareMaze::makeMaze(int width, int height){


	srand (time(NULL));

	int curx = 1;
	int cury = 1;
	int random = 0;
	int random2 = 0;
	int index = 0;
	int count = 0;

	if(!Q.empty()){
		while(!Q.empty()){
			Q.pop();
		}
	}			

	int size = width * height;
	
	wid = width;
	hi = height;
	
	section.addelements(size);
	right.resize(size);
	down.resize(size);
	visited.resize(size);
	path.resize(size);
	
	for(int i = 0; i<width; i++){
		for(int j = 0; j < height; j++){
			index = getId(i,j,wid);
			right[index] = true;
			down[index] = true;
			visited[index] = false;	
		}
	}	
		index = getId(0,0,width);
		
	
	
	while(count < wid*hi-1){
		
		//pop out coordinates from the queue
		
		random = rand() % wid;
		random2 = rand() % hi;
		
		index = wid * random2 + random;
	
		
		//decrypt it to get coordinates
		curx = getx(index, wid);
		cury = gety(index, wid);
		//std::cout << "curx:" << curx << std::endl;
		//std::cout << "cury:" << cury << std::endl;
		//check if it was visited before
		if(visited[index] == false){
			//mark this section visited
			
			visited[index] = true;
			//make random number and use it to open right or down
	
			//open random number meets requirement && the new section was not visited && doesnt make it cycle(?)
			
			int cur = section.find(index);
			int nex;
			if(curx+1 < wid){
				nex = section.find(getId(curx+1,cury,wid));
					
				if(cur != nex){
					right[index] = false;
					section.setunion(cur, nex);
					count++;
				}
				
			}
			
			cur = section.find(index);
			
			
			
			if(cury+1 < hi){
				nex = section.find(getId(curx,cury+1,wid));
				
				if(cur != nex ){
					down[index] = false;
					section.setunion(cur,nex);
					count++;
				}			
			
			}
		}
		
		visited[index] = true;
		
	}
	

	
}

bool SquareMaze::canTravel(int x,int y,int dir) const{

	
	if(dir == 0){
		return(!right[getId(x,y,wid)]);
			
		
	}

	if(dir == 1){
		return(!down[getId(x,y,wid)]);
	}

	if(dir == 2){
		return(!right[getId(x-1,y,wid)]);
	}

	if(dir == 3){
		return(!down[getId(x,y-1,wid)]);
	}

	return false;
}
	
void SquareMaze::setWall(int x, int y, int dir, bool exists){

	if(dir == 0){
		right[getId(x,y,wid)] = exists;
			 
	}

	if(dir == 1){
		down[getId(x,y,wid)] = exists;
	}


}
	
std::vector <int> SquareMaze::solveMaze(){
	
	std::queue <int>  Q;
	std::vector <int>  temp;
	std::vector <int>  best;
	std::vector <int>  solution;
	std::unordered_map<int, int> parent; //use the map to store the 'parent' of current room
	int par = 0;
	int cur = 0;
	int nex = 0;
	int curcount = 0;
	int prevcount = 0;
	int index = 0;	
	int xval = 0;
	int yval = 0;

	//BFS SEARCH
	//Get the starting point
	//Check if the left/right/top/bottom are open
	//if so, put them in the queue.
	//continue until find an end(Y is at bottom).
	//
  
	Q.push(getId(0,0,wid));
	if(right[getId(0,0,wid)] == false)
		Q.push(getId(1,0,wid));
	if(right[getId(0,0,wid)] == false)
		Q.push(getId(0,1,wid));
	
		
	while(!Q.empty()){
			index = Q.front();
			Q.pop();
			xval = getx(index,wid);
			yval = gety(index,wid);
			visited[index] = true;
		
			curcount++;
		
			//push in the surrounding rooms
			if(right[getId(xval,yval,wid)] == false && xval+1 < wid && visited[getId(xval+1,yval,wid)] == false){ //right			
				Q.push(getId(xval+1,yval,wid));
				cur = section.find(index);
				nex = section.find(getId(xval+1,yval,wid));
				section.setunion(cur, nex);
				parent[getId(xval+1,yval,wid)] = index;
			}
			if(right[getId(xval,yval,wid)] == false && yval+1 < hi && visited[getId(xval,yval+1,wid)] == false){ //bottom
				Q.push(getId(xval,yval+1,wid));
				cur = section.find(index);
				nex = section.find(getId(xval,yval+1,wid));
				section.setunion(cur, nex);
				parent[getId(xval,yval+1,wid)] = index;
			}
			if(xval-1 >= 0 && right[getId(xval-1,yval,wid)] == false &&  visited[getId(xval-1,yval,wid)] == false){ //left
				Q.push(getId(xval-1,yval,wid));
				cur = section.find(index);
				nex = section.find(getId(xval-1,yval,wid));
				section.setunion(cur, nex);
				parent[getId(xval-1,yval,wid)] = index;
			}
			if(yval-1 >= 0 && right[getId(xval,yval-1,wid)] == false && visited[getId(xval,yval-1,wid)] == false){ //top
				Q.push(getId(xval,yval-1,wid));
				cur = section.find(index);
				nex = section.find(getId(xval,yval-1,wid));
				section.setunion(cur, nex);
				parent[getId(xval,yval-1,wid)] = index;
				
			}
		
		
		
			//push in the current path index(==potential solution) in solution vector
			
		}
		
		int besti = 0;	
		
		for(int i = 0; i < wid; i++){
			
			int point = getId(i, hi-1, wid);
			int start = section.find(getId(0,0,wid));
			int end	= section.find(point);
			
			if(start == end){
				while(point != getId(0,0,wid)){
					
					solution.push_back(point);
					
					point = parent[point];
					
					
					
					curcount++;
				}
				
				reverse(solution.begin(), solution.end());
			}
			if(curcount > prevcount){
				prevcount = curcount;
				besti = i;
				best = solution;
			}
		
			solution.clear();
			curcount = 0;
		
		}
	
		
		
		
		
		
	

/*
	//traverse all the sections on the bottom row
	for(int i = 0; i < wid; i++){
		curcount = 0; //default the count
		index = getId(i, hi-1, wid); //get the index of each row section
	
		while( index != 0){ //until we get to the origin
			index = path[index]; //moving on to the next disjoint node
			//std::cout<<index<<" "<<path[index]<<std::endl;
			blah[index] = blah[path[index]]; //applying the same to the path
			curcount++; //count it up
		
		}
	
		if(curcount > prevcount){ //swapping the results if the newer path is longer
			prevcount = curcount;
			temp = blah;
		}
	}

	*/
	return best;
}
	
PNG* SquareMaze::drawMaze()const{
  
	PNG* maze = new PNG(wid*10+1,hi*10+1);
	int index = 0;
	
	for(int i = 10 ; i < (int) maze->width(); i++){
		(*maze)(i,0)->red = 0;
		(*maze)(i,0)->green = 0;
		(*maze)(i,0)->blue = 0;
	}
	
	for(int i = 0 ; i < (int)maze->height(); i++){
		(*maze)(0,i)->red = 0;
		(*maze)(0,i)->green = 0;
		(*maze)(0,i)->blue = 0;
	}
	
	for(int x = 0 ; x < wid; x++){
		for(int y = 0 ; y < hi; y++){
			index = getId(x,y,wid);
			if(right[index]){
				for(int k = 0 ; k <= 10; k++){
					(*maze)((x+1)*10,y*10+k)->red = 0;
					(*maze)((x+1)*10,y*10+k)->green = 0;
					(*maze)((x+1)*10,y*10+k)->blue = 0;	
				}
			}
			if(down[index]){
				for(int k = 0 ; k <= 10; k++){
					(*maze)(x*10+k, (y+1)*10)->red = 0;
					(*maze)(x*10+k, (y+1)*10)->green = 0;
					(*maze)(x*10+k, (y+1)*10)->blue = 0;	
				}
			}
		
		
	
		}
	} 
	
	
	return maze;
}
	
PNG* SquareMaze::drawMazeWithSolution(){

	PNG * maze = drawMaze();
	std::vector <int> solution = solveMaze();
	
	


	return maze;
}
