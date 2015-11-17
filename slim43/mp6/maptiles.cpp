/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */
	 			
#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

MosaicCanvas * mapTiles(SourceImage const & theSource, vector<TileImage> const & theTiles)
{
    /**
     * @todo Implement this function!
     */
  
    MosaicCanvas* canvas = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
   /* 
    KDTree theTree;
    Point<Dim> rightPoint;
    Point<Dim> SourceAverage;
    vector < Point<Dim> > TilesRGBA;
    RGBAPixel sourceColor;
    RGBAPixel tileColor;
    RGBAPixel rightColor;
    int	tileNum;
    
    for(int i = 0; i < theSource.getColumns(); i++){
    	for(int j = 0; j < theSource.getRows(); j++){
    		sourceColor = theSource.getRegionColor(j,i);
    		TilesRGBA.resize(theTiles.size());
    		
    		SourceAverage[0] = sourceColor.red;
    		SourceAverage[1] = sourceColor.green;
			SourceAverage[2] = sourceColor.blue;
				
    		
    		for(size_t z = 0; z < theTiles.size(); z++){
    			
    			tileColor =theTiles[z].getAverageColor();
    			
				Tiles.RGBA[z][0] = tileColor.red;
				Tiles.RGBA[z][1] = tileColor.green;
				Tiles.RGBA[z][2] = tileColor.blue;
				
				
    		}
    		theTree = theTree(TilesRGBA);
    		rightPoints = theTree.findNearestNeighbor(SourceAverage);
    		
    		rightColor.red = rightPoints[0];
    		rightColor.green = rightPoints[1];
    		rightColor.blue = rightPoints[1];
    		
    		
    		canvas->setTile(j, i, rightColor);
    		
    	}
    }
    */
     
	return canvas;
}


