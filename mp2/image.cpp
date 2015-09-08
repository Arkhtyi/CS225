#include "image.h"

using std::uint8_t;

void Image::flipleft(){

RGBAPixel *pixel = new RGBAPixel();

for(int i = 0; i+1 <= (this->width())/2 ; i++){
   for(int j = 0; j+1 <= (this->height())  ; j++){
	
	

	pixel->red = (*this)(i,j)-> red;
	pixel->green = (*this)(i,j)-> green;
	pixel->blue = (*this)(i,j)-> blue;
	
	(*this)(i,j) -> red = (*this)(this->width()-i-1,j) -> red;
	(*this)(i,j) -> green = (*this)(this->width()-i-1,j) -> green;
	(*this)(i,j) -> blue = (*this)(this->width()-i-1,j) -> blue;
	
	(*this)(this->width()-i-1,j)-> red = pixel->red;
	(*this)(this->width()-i-1,j)-> green = pixel->green;
	(*this)(this->width()-i-1,j)-> blue = pixel->blue;
	

  }
}
	
	delete pixel;
	
}
void Image::adjustbrightness(int r, int g, int b){

int reed;
int greeen;
int bluee;

for(int x = 0; x+1 <= (this->width()); x++){
   for(int y = 0; y+1 <= (this->height()); y++){

	reed =  (* this)(x,y)-> red + r; 
	if( reed > 255)
	 reed = 255;
	if( reed < 0)
	 reed = 0;
	(* this)(x,y)-> red = reed;

	greeen =  (* this)(x,y)-> green + g; 
	if( greeen > 255)
	 greeen = 255;
	if( greeen < 0)
	 greeen = 0;
	(* this)(x,y)-> green = greeen;

	bluee =  (* this)(x,y)-> blue + b; 
	if( bluee > 255)
	 bluee = 255;
	if( bluee < 0)
	 bluee = 0;
	(* this)(x,y)-> blue = bluee;



  }
 }
}
void Image::invertcolors(){


for(int x = 0; x+1 <= (this->width()); x++){
   for(int y = 0; y+1 <= (this->height()); y++){

	(* this)(x,y)-> red = 255 - (* this)(x,y)-> red;  
	(* this)(x,y)-> green =  255 - (* this)(x,y)-> green; 
	(* this)(x,y)-> blue =  255 -(* this)(x,y)-> blue; 
	



  }
 }

}
