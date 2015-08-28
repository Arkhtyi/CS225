#include <iostream>
#include "rgbapixel.h"
#include "png.h"
using namespace std;

int main(){

  PNG first("in.png");
  PNG second(first.width(),first.height());
  
 
  for(int x = 0; x < first.width(); x++){
    for(int y = 0; y < first.height(); y++){
      
	
     second(first.width()-x-1,first.height()-y-1)->red = first(x,y)-> red;
     second(first.width()-x-1,first.height()-y-1)->green = first(x,y)-> green;
     second(first.width()-x-1,first.height()-y-1)->blue = first(x,y)-> blue;
	
    
    }
  }

  second.writeToFile("out.png");

	return 0;

  
  
}
