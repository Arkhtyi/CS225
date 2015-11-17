/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */
	 			
#include <iostream>
#include <map>
#include <vector>
#include "maptiles.h"

using namespace std;

MosaicCanvas * mapTiles(SourceImage const & theSource, vector<TileImage> const & theTiles)
{
    /**
     * @todo Implement this function!
     */
  
    MosaicCanvas* canvas = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
   
    
    Point<3> rightPoint;
    Point<3> SourceAverage;
    vector < Point<3> > TilesRGBA;
    RGBAPixel sourceColor;
    RGBAPixel tileColor;
    RGBAPixel rightColor;
    int	tileNum = 0;
    
    
    TilesRGBA.resize(theTiles.size());
    for(size_t z = 0; z < theTiles.size(); z++){
    			
    			tileColor =theTiles[z].getAverageColor();
    			
				TilesRGBA[z][0] = tileColor.red;
				TilesRGBA[z][1] = tileColor.green;
				TilesRGBA[z][2] = tileColor.blue;
				
				
    		}
    KDTree<3> theTree(TilesRGBA);
    
    
    for(int i = 0; i < theSource.getColumns(); i++){
    	for(int j = 0; j < theSource.getRows(); j++){
    		sourceColor = theSource.getRegionColor(j,i);
    		
    		
    		SourceAverage[0] = sourceColor.red;
    		SourceAverage[1] = sourceColor.green;
			SourceAverage[2] = sourceColor.blue;
				
    		
    		
    		rightPoint = theTree.findNearestNeighbor(SourceAverage);
    		
    		for(int k = 0; k < (int)TilesRGBA.size(); k++){
    			if((TilesRGBA[k][0] == rightPoint[0]) && (TilesRGBA[k][1] == rightPoint[1]) && (TilesRGBA[k][2] == rightPoint[2]))
    				tileNum = k;
    		}
    		
    		
    		
    		canvas->setTile(j, i, theTiles[tileNum]);
    		
    	}
    }
    
     
	return canvas;
}


