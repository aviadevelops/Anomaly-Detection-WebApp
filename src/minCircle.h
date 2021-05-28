// 33384347	21233056

#ifndef MINCIRCLE_H_
#define MINCIRCLE_H_

#include "anomaly_detection_util.h"
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Circle {
public:
    Point center;
    float radius;

    Circle(Point c, float r) : center(c), radius(r) {}
};
// --------------------------------------
Circle findMinCircle(Point *points, size_t size);

Circle mecAlg(Point *points, vector<Point> boundaryPoints, size_t size);

Circle makeCircle(vector<Point> &boundaryPoints);

Circle circleFromTwo(const Point &point1, const Point &point2);

Circle circleFromThree(const vector<Point> &p);

Point getTempCenterFromThreePoints(float distXP2P1, float distYP2P1, float distXP3P1, float distYP3P1);

Circle circleFromThreePoints(const Point &p1, const Point &p2, const Point &p3);

bool isInCircle(const Circle &c, const Point &p);





#endif /* MINCIRCLE_H_ */
