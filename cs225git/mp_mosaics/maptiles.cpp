/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */

    MosaicCanvas* canvas = new MosaicCanvas(theSource.getRows(), theSource.getColumns());

    vector<Point<3>> points;
    map<Point<3>, TileImage*> map_;

    for(auto tileIterator = theTiles.begin(); tileIterator != theTiles.end(); tileIterator++){
        LUVAPixel pixelcolor = tileIterator->getAverageColor();
        Point<3> color = convertToXYZ(pixelcolor);
        points.push_back(color);
        map_[color] = &*tileIterator;
    }

    KDTree<3> coloTree(points);
    for(auto i = 0; i < canvas->getRows(); i++){
        for(auto j = 0; j < canvas->getColumns(); j++){
            Point<3> originColor = convertToXYZ(theSource.getRegionColor(i, j));
            Point<3> bestColor = coloTree.findNearestNeighbor(originColor);
            TileImage* tile = map_[bestColor];
            canvas->setTile(i, j, tile);
        }
    }
    return canvas;
}

