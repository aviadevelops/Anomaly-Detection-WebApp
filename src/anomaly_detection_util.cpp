/*
 * animaly_detection_util.cpp
 *
 * Author: Aviad Saadi, ID: 212330567
 */

#include <math.h>

#include "anomaly_detection_util.h"

using namespace std;

float avg(vector<float> &x, int size) {
    float sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += x[i];
    }
    return sum / size;
}

// returns the variance of X and Y
float var(vector<float> &x, int size) {
    vector<float> xSquare;
    for (int i = 0; i < size; ++i) {
        xSquare.push_back(pow(x[i], 2));
    }
    float res = avg(xSquare, size) - pow(avg(x, size), 2);
    return res;
}

// returns the covariance of X and Y
float cov(vector<float> &x, vector<float> &y, int size) {
    vector<float> multiplyArray;
    for (int i = 0; i < size; ++i) {
        multiplyArray.push_back(x[i] * y[i]);
    }
    float res = avg(multiplyArray, size) - avg(x, size) * avg(y, size);
    return res;
}


// returns the Pearson correlation coefficient of X and Y
float pearson(vector<float> &x, vector<float> &y, int size) {
    return cov(x, y, size) / (sqrt(var(x, size) * var(y, size)));
}

// performs a linear regression and returns the line equation
Line linear_reg(vector<Point> &points, int size) {

    vector<float> xArray, yArray;
    for (int i = 0; i < size; ++i) {
        xArray.push_back(points[i].x);
        yArray.push_back(points[i].y);
    }
    float a = cov(xArray, yArray, size) / var(xArray, size);
    float b = avg(yArray, size) - a * avg(xArray, size);
    return Line(a, b);
}

// returns the deviation between point p and the line equation of the points
float dev(Point& p, vector<Point> &points, int size) {
    Line line = linear_reg(points, size);
    return dev(p, line);
}

// returns the deviation between point p and the line
float dev(Point& p, Line& l) {
    float deviation = l.f(p.x) - p.y;
    if (deviation >= 0) {
        return deviation;
    }
    return -deviation;
}





