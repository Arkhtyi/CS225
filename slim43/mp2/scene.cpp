#include "scene.h"

Scene::Scene (int max){
   images = new Image*[max];
   curlength = max;   
   for(int i = 0; i < curlength; i++){
      images[i] = NULL;
   }
   xc = new int[max-1];
   yc = new int[max-1];
    for(int i = 0; i < curlength; i++){
      xc[i] = 0;
      yc[i] = 0;
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

	if(newmax < curlength){
		for(int i = newmax; i < curlength; i++){
			if(images[i] != NULL){		
			   cout << "invalid newmax" << endl;
			   return;
			   }
		   }
	}

	Image ** temp = new Image*[newmax-1];
	
	for(int i = 0; i < newmax; i++){
	
		if(temp[i] == NULL)
		   continue; 	

		temp[i] = images[i];

	}

	delete [] images;

	images = new Image*[newmax-1];
	
	for(int j = 0; j < newmax; j++){
	   images[j] = temp[j];
	}
	
	delete [] temp;

	

	curlength = newmax;


}
//Memory leak
void Scene::addpicture(const char * FileName, int index, int x, int y){

	if(curlength <= index){
	   cout<<"index out of bounds"<<endl;
	   return;
	}
	
	delete images[index];

	Image * temp = new Image();
	temp->readFromFile(FileName);

	images[index] = temp; 
	xc[index] = x;
	yc[index] = y;



	

}


void Scene::changelayer(int index, int newindex){
	
	if(index == newindex)	
	   return;


	if(index < 0 || index > curlength-1 || newindex < 0 || newindex > curlength-1){
	   cout<<"invalid index"<<endl;
	   return;}

	if(images[newindex] != NULL){
	   delete images[newindex];}

	
	images[newindex] = images[index];
	images[index] = NULL;
	
	xc[newindex] = xc[index];
	yc[newindex] = yc[index];

	xc[index] = 0;
	yc[index] = 0;
}


void Scene::translate(int index, int xcoord, int ycoord){

	if(index < 0 || images[index] == NULL){
	   cout<<"invalid index" <<endl;
	   return;
	}

	xc[index] = xcoord;
	yc[index] = ycoord;

	


}
//aint workin
void Scene::deletepicture(int index){

	if(index < 0 || index > curlength-1 || images[index] == NULL){
	   cout<<"invalid index"<<endl;
	   return;
	}
	
	   delete images[index]; 
	   images[index] = NULL;
	   xc[index] = 0;
	   yc[index] = 0;
	


}

Image *Scene::getpicture(int index)const{
	
	if(index < 0 || index > curlength-1){
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
	for(int i = 0; i < curlength; i++){
	
	if(images[i] != NULL){

	   int sizew = images[i]->width();
	   int sizeh = images[i]->height();

	   int width = xc[i] + sizew;
	   int height = yc[i] + sizeh;

	   if(width > tempw)
	      tempw = width;
	   if(height > temph)
	      temph = height;
	  }
	}
	
	//set the canvus size to the one found above
	canvus.resize(tempw,temph);
	Image tem;

	//drawing the images
	for(int i = 0; i < curlength; i++){

	   if(images[i] != NULL){

		int width = images[i]->width();
		int height = images[i]->height();
	
		tem = *images[i];
		
	
	      for(int x = 0; x < width; x++){
	         for(int y = 0; y < height; y++){
		
		   canvus(x+xc[i],y+yc[i])->red = tem(x,y)->red;
		   canvus(x+xc[i],y+yc[i])->green = tem(x,y)->green;
		   canvus(x+xc[i],y+yc[i])->blue = tem(x,y)->blue;

		}
	      }
	    }
	  }
	
	return canvus;
}

void Scene::clear(){
	
	
	if(images != NULL){
		for(int i = 0; i < curlength; i++){
			delete images[i];
		
		}
	}
	
	delete images;
	
	if(xc != NULL)
		delete [] xc;
	if(yc != NULL)
		delete [] yc;
}

void Scene::copy(const Scene & other){

   curlength = other.curlength;
   

   xc = new int[curlength];
   for(int i = 0; i < curlength; i++)
	xc[i] = other.xc[i];


   yc = new int[curlength];
   for(int i = 0; i < curlength; i++)
	yc[i] = other.yc[i];


  // if(images == NULL)
	   images = new Image*[curlength];
   //else   
	for(int i = 0; i < curlength; i++){
	   if(other.images[i] != NULL)
		images[i] = new Image(*(other.images[i]));
	   else
		images[i] = NULL;	
	
   }
 


}

