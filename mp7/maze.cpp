/* Your code here! */

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
			path[index] = -1;
		}
	}	
		index = getId(0,0,width);
	
		Q.push(index);
	
	while(count != wid*hi){
		
		//pop out coordinates from the queue
		
		random = rand() % wid;
		random2 = rand() % hi;
		
		index = wid * random2 + random;
	
		
		//decrypt it to get coordinates
		curx = getx(index, wid);
		cury = gety(index, wid);
		
		//check if it was visited before
		if(visited[index] == false){
			//mark this section visited
			count++;
			visited[index] = true;
			//make random number and use it to open right or down
			
			
			//open random number meets requirement && the new section was not visited && doesnt make it cycle(?)
			
			int cur = section.find(index);
			int nex;
			if(curx+1 < wid){
				nex = section.find(getId(curx+1,cury,wid));
					
				if(visited[getId(curx+1,cury,wid)] == false && cur != nex){
					right[index] = false;
					section.setunion(cur, nex);
					if(curx+1 < wid)
						path[getId(curx+1,cury,wid)] = index;
				}
			}
			if(cury+1 < hi){
				nex = section.find(getId(curx,cury+1,wid));
				
				if(visited[getId(curx,cury+1,wid)] == false && cur != nex ){
					down[index] = false;
					section.setunion(cur,nex);
					if(cury+1 < hi)
						path[getId(curx,cury+1,wid)] = index;
				}			
			
			}
		}
		
		
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
	
	std::vector <int>  temp;
	
	std::vector <int>  blah;
	int curcount = 0;
	int prevcount = 0;
	int index = 0;	

	//traverse all the sections on the bottom row
	for(int i = 0; i < wid; i++){
		curcount = 0; //default the count
		index = getId(i, hi-1, wid); //get the index of each row section
	
		while( index != 0){ //until we get to the origin
			index = path[index]; //moving on to the next disjoint node
			blah[index] = blah[path[index]]; //applying the same to the path
			curcount++; //count it up
		
		}
	
		if(curcount > prevcount){ //swapping the results if the newer path is longer
			prevcount = curcount;
			temp = blah;
		}
	}

	
	return temp;
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
