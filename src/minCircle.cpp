// 33384347	21233056
#include "minCircle.h"
// implement

// This function creates an empty vector of boundary points,
// and returns the minimal enclosing circle of the given points in an array
Circle findMinCircle(Point *points, size_t size) {
    vector<Point> boundaryPoints;
    return mecAlg(points, boundaryPoints, size);
}

// you may add helper functions here

// this function calculates the minimal enclosing circle,
// that is corresponding to the points array and the boundary points
Circle mecAlg(Point *points, vector<Point> boundaryPoints, size_t size) {
    if (size == 0 || boundaryPoints.size() == 3) // If we have an empty array of points,
        // or if we have 3 points we know that are supposed to be on the boundary of the minimal enclosing circle
        // we return the trivial solution that is corresponding to the current boundary points
        // (see documentation of make-circle function)
        return makeCircle(boundaryPoints);
    int removedIndex = rand() % size;
    // We "remove" the last point in the points array
    Point removedPoint(points[removedIndex].x, points[removedIndex].y);
    swap(points[removedIndex], points[size-1]);
    size--;
    // We calculate the minimal enclosing circle of the points array after removing the point
    Circle currentCircle = mecAlg(points, boundaryPoints, size);
    // If the removed point is inside the minimal enclosing circle of the remaining points
    if (isInCircle(currentCircle, removedPoint))
        return currentCircle; // We have found the minimal enclosing circle that encloses the points that are currently
    // in points array, and we are returning it.
    // Otherwise, we know the removed point is supposed to be on the boundary of the minimal enclosing circle,
    // so we add it to the boundaryPoints vector.
    boundaryPoints.push_back(removedPoint);
    // And we return the minimal enclosing circle of the updated points array and boundary points vector.
    return mecAlg(points, boundaryPoints, size);
}


// This function calculates the trivial solution of minimal enclosing circle of 0-3 points.
Circle makeCircle(vector<Point> &boundaryPoints) {
    if (boundaryPoints.empty()) // If we have zero points.
        return {{0, 0}, 0}; // We return a circle with the center (0,0) and with radius 0.
    else if (boundaryPoints.size() == 1) // If we have one point.
        return {boundaryPoints[0], 0}; // We return a circle with the given point as the center and with radius 0.
    else if (boundaryPoints.size() == 2) // If we have two points.
        // We returns the trivial solution for two points.
        return circleFromTwo(boundaryPoints[0], boundaryPoints[1]);
    else // If we have three points.
        return circleFromThree(boundaryPoints); // We return the trivial solution for three points.
}

// This function calculates the trivial solution for a minimal enclosing circle of two given points.
Circle circleFromTwo(const Point &point1, const Point &point2) {
    float radius = sqrt((float) pow(point1.x - point2.x, 2) + (float) pow(point1.y - point2.y, 2)) / 2;
    Point midPoint((point1.x + point2.x) / 2, (point1.y + point2.y) / 2);
    // We return a circle with the middle point of the given two points as it's center,
    // and with the half the distance between the two points as it's radius.
    return {midPoint, radius};
}

// This function calculates the trivial solution for a minimal enclosing circle of the given three points.
Circle circleFromThree(const vector<Point> &p) {
    // We try to calculate the trivial solution for a minimal enclosing circle with only two of the three points.
    Circle possCircle1 = circleFromTwo(p[0], p[1]);
    Circle possCircle2 = circleFromTwo(p[0], p[2]);
    Circle possCircle3 = circleFromTwo(p[1], p[2]);
    // If the third point is inside the minimal enclosing circle that was created from the other two points,
    // we have found the minimal enclosing circle of the three points.
    if (isInCircle(possCircle1, p[2])) {
        return possCircle1;
    } else if (isInCircle(possCircle2, p[1])) {
        return possCircle2;
    } else if (isInCircle(possCircle3, p[0])) {
        return possCircle3;
    } else // Otherwise, we know the three points have to be on the boundary of the minimal enclosing circle.
        return circleFromThreePoints(p[0], p[1], p[2]);
}

// This function calculates the center (that we know three points that are on its boundary) of a circle,
// we are using some distances between x and y values of these three boundary points.
Point getTempCenterFromThreePoints(float distXP2P1, float distYP2P1, float distXP3P1, float distYP3P1) {
    float dest1 = distXP2P1 * distXP2P1 + distYP2P1 * distYP2P1;
    float dest2 = distXP3P1 * distXP3P1 + distYP3P1 * distYP3P1;
    float dest3 = distXP2P1 * distYP3P1 - distYP2P1 * distXP3P1;
    return {(distYP3P1 * dest1 - distYP2P1 * dest2) / (2 * dest3),
            (distXP2P1 * dest2 - distXP3P1 * dest1) / (2 * dest3)};

}

// This function calculates a circle that the three given points are on its boundary.
// (there is only one circle that is defined like this)
// We use some mathematical calculations of the circle formula that is corresponding all three of the given points.
Circle circleFromThreePoints(const Point &p1, const Point &p2, const Point &p3) {
    Point tempCenter = getTempCenterFromThreePoints(p2.x - p1.x, p2.y - p1.y, p3.x - p1.x,
                                                    p3.y - p1.y);
    tempCenter.x += p1.x;
    tempCenter.y += p1.y;
    float radius = sqrt((float) pow(tempCenter.x - p1.x, 2) + (float) pow(tempCenter.y - p1.y, 2));
    return {tempCenter, radius};
}

// This function returns true if the given point is inside the given circle, false otherwise.
bool isInCircle(const Circle &c, const Point &p) {
    // We use the circle formula that determines whatever or not a point is inside a circle or on it's boundary.
    return (pow(p.x - c.center.x, 2) + pow(p.y - c.center.y, 2) <= pow(c.radius, 2));
}