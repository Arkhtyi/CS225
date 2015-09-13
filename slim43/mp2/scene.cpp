#include "scene.h"

Scene::Scene (int max){
   images = new Image*[max];
   currentlength = max;   
   for(int i = 0; i < currentlength; i++){
      images[i] = NULL;
   }
   xcords = new int[max];
   ycords = new int[max];
    for(int i = 0; i < currentlength; i++){
      xcords[i] = 0;
      ycords[i] = 0;
   }


	

}

Scene::~Scene(){

	clear();	
	
}

Scene::Scene (const Scene & source){
	
	copy(source);

}

const Scene & Scene::operator=(const Scene & source){

    if (this != &source)
	{
		clear();
		copy(source);
	}
	return *this;
}



void Scene::changemaxlayers(int newmax){

	

	Image ** temp = new Image*[newmax];
	
	for(int i = 0; i < newmax; i++){
	
	if(temp[i] == NULL)
	   continue; 	

	temp[i] = images[i];

	}

	delete [] images;

	images = new Image*[newmax];
	
	for(int j = 0; j < newmax; j++){
	   images[j] = temp[j];
	}
	
	delete [] temp;

	if(newmax < currentlength-1){
	   cout << "invalid newmax" << endl;
	   return;
	}

	currentlength = newmax;


}
//Memory leak
void Scene::addpicture(const char * FileName, int index, int x, int y){

	if(currentlength-1 < index)
	   cout<<"index out of bounds"<<endl;

	delete images[index];

	Image * temp = new Image();
	temp->readFromFile(FileName);

	images[index] = temp; 
	xcords[index] = x;
	ycords[index] = y;



	
	//delete temp;

}
//doesnt work
void Scene::changelayer(int index, int newindex){
	
	if(index == newindex)
	   return;


	if(index < 0 || index > currentlength-1 || newindex < 0 || newindex > currentlength-1){
	   cout<<"invalid index"<<endl;
	   return;}

	if(images[newindex] != NULL){
	   delete images[newindex];}

	
	images[newindex] = images[index];
	images[index] = NULL;
	
	xcords[newindex] = xcords[index];
	ycords[newindex] = ycords[index];

	xcords[index] = 0;
	ycords[index] = 0;
}


void Scene::translate(int index, int xcoord, int ycoord){

	if(index < 0 || images[index] == NULL){
	   cout<<"invalid index" <<endl;
	   return;
	}

	xcords[index] = xcoord;
	ycords[index] = ycoord;

	


}
//aint workin
void Scene::deletepicture(int index){

	if(index < 0 || index > currentlength-1 || images[index] == NULL){
	   cout<<"invalid index"<<endl;
	   return;
	}
	
	   delete images[index]; 
	   images[index] = NULL;
	   xcords[index] = 0;
	   ycords[index] = 0;
	


}

Image *Scene::getpicture(int index)const{
	
	if(index < 0 || index > currentlength-1){
	   cout<< "invalid index" <<endl;
	   return NULL;
	}

	


	return images[index];
	

}


Image Scene::drawscene() const{

	Image canvus;

	int tempw = 0;
	int temph = 0;

	//find the size for the canvus
	for(int i = 0; i < currentlength-1; i++){
	
	if(images[i] != NULL){

	   int sizew = images[i]->width();
	   int sizeh = images[i]->height();

	   int width = xcords[i] + sizew;
	   int height = ycords[i] + sizeh;

	   if(width > tempw)
	      tempw = width;
	   if(height > temph)
	      temph = height;
	  }
	}
	
	//set the canvus size to the one found above
	canvus.resize(tempw,temph);
	Image tempRGB;

	//drawing the images
	for(int i = 0; i < currentlength; i++){

	   if(images[i] != NULL){

		int width = images[i]->width();
		int height = images[i]->height();
	
		tempRGB = *images[i];
		
	
	      for(int x = 0; x < width; x++){
	         for(int y = 0; y < height; y++){
		
		   canvus(x+xcords[i],y+ycords[i])->red = tempRGB(x,y)->red;
		   canvus(x+xcords[i],y+ycords[i])->green = tempRGB(x,y)->green;
		   canvus(x+xcords[i],y+ycords[i])->blue = tempRGB(x,y)->blue;

		}
	      }
	    }
	  }
	
	return canvus;
}

void Scene::clear(){
	
	
	if(images != NULL){
		for(int i = 0; i < currentlength -1 ; i++){
			delete images[i];
		
		}
	}
	
	delete images;
	
	if(xcords != NULL)
		delete [] xcords;
	if(ycords != NULL)
		delete [] ycords;
}

void Scene::copy(const Scene & other){

   currentlength = other.currentlength;
   

   xcords = new int[currentlength];
   for(int i = 0; i < currentlength; i++)
	xcords[i] = other.xcords[i];


   ycords = new int[currentlength];
   for(int i = 0; i < currentlength; i++)
	ycords[i] = other.ycords[i];


  // if(images == NULL)
	   images = new Image*[currentlength];
   //else   
	for(int i = 0; i < currentlength; i++){
	   if(other.images[i] != NULL)
		images[i] = new Image(*(other.images[i]));
	   else
		images[i] = NULL;	
	
   }
 


}

