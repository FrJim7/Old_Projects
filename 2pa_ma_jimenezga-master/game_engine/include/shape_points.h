/**
* @file shape_points.h
* @author Francisco Jimenez Garcia
* jimenezga@esat-alumni.com
*/
#ifndef __SHAPEPOINTS_H__
#define __SHAPEPOINTS_H__ 1

enum ShapePointCount {
  kDefaultPoints = 2,
  kTrianglePoints = 3,
  kSquarePoints = 4
};

/**
* @brief Square Points
*
* Defines the points of a Square. 
*/
const float kDefault[] = {0, 0};
/**
* @brief Triangle Points
*
* Defines the points of a Square. 
*/
const float kTriangle[] = {0, 0, 1, 1, -1, 1};
/**
* @brief Square Points
*
* Defines the points of a Square. 
*/
const float kSquare[] = {-1, -1, 1, -1, 1, 1, -1, 1};

#endif //__SHAPEPOINTS_H__