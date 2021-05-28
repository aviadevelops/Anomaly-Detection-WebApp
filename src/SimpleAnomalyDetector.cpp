// Author: Aviad Saadi, ID: 212330567
#include <iostream>
#include "SimpleAnomalyDetector.h"

using namespace std;


// deletes all the vector data that has been allocated
void deleteVectorMembers(vector<Point *> &vector) {
    int size = vector.size();
    for (int i = 0; i < size; i++) {
        delete vector[i];
    }
}

// default constructor
SimpleAnomalyDetector::SimpleAnomalyDetector() {
    this->threshold = 0.9;

}

// default destructor
SimpleAnomalyDetector::~SimpleAnomalyDetector() {
    // TODO Auto-generated destructor stub
}

float SimpleAnomalyDetector::getThreshold() {
    return this->threshold;
}

void SimpleAnomalyDetector::setThreshold(float newThreshold) {
    this->threshold = newThreshold;
}

// a function that gets two vectors - a vector of x values and a vector of y values,
// and puts a vector of the corresponding points in the given pointsVector
void SimpleAnomalyDetector::putPointsVector(vector<Point> &pointsVector, const vector<float> &f1,
                                            const vector<float> &f2) {
    for (int i = 0; i < f1.size(); i++) {
        pointsVector.push_back(Point(f1[i], f2[i]));
    }
}

float SimpleAnomalyDetector::calculate_threshold(vector<Point> &pointsVector, Line &linearReg) {
    float maxDev = 0, currentDev = 0;
    int size = pointsVector.size();
    for (int k = 0; k < size; k++) {
        currentDev = abs(linearReg.f(pointsVector[k].x) - pointsVector[k].y);
        if (currentDev > maxDev) {
            maxDev = currentDev;
        }
    }
    return maxDev;
}


// this function learns the normal behaviour of a given TimeSeries object
void SimpleAnomalyDetector::learnNormal(const TimeSeries &ts) {
    const vector<string> &propertiesRow = ts.getPropertiesRow();
    vector<float> vectorColumn1, vectorColumn2, maxColumn;
    string propertyNameOfMaxCorrelation;
    float maxCorrelation = 0, absoluteCorrelation = 0;
    int size = propertiesRow.size();
    int vSize;
    for (int i = 0; i < size - 1; i++) {
        maxCorrelation = 0;
        absoluteCorrelation = 0;

        vectorColumn1 = ts.getColumnByProperyName(propertiesRow[i]);


         vSize = vectorColumn1.size();
        for (int j = i + 1; j < size; j++) {
            vectorColumn2 = ts.getColumnByProperyName(propertiesRow[j]);


            absoluteCorrelation = abs(pearson(vectorColumn1, vectorColumn2, vSize));


            if (absoluteCorrelation > maxCorrelation) {
                maxCorrelation = absoluteCorrelation;
                maxColumn = vectorColumn2;
                propertyNameOfMaxCorrelation = propertiesRow[j];
            }

        }
        //if the correlation is greater or equal than the threshold
        // we are adding the correlated features to the cf vector
//        std::cout << "hello data" << std::endl;
        createAndAddCorrelatedFeaturesVector(vectorColumn1, maxColumn, propertiesRow[i], propertyNameOfMaxCorrelation,
                                             maxCorrelation);
//        std::cout << "bye data" << std::endl;
    }
}

void SimpleAnomalyDetector::createAndAddCorrelatedFeaturesVector(const vector<float> &currentColumn,
                                                                 const vector<float> &maxColumn,
                                                                 const string &currentFeatureName,
                                                                 const string &maxFeatureName, float maxCorrelation) {
    if (maxCorrelation >= this->threshold) {
        vector<Point> pointsVector;
        int size = currentColumn.size();
        for (int i = 0; i < size; i++) {
            pointsVector.push_back(Point(currentColumn[i], maxColumn[i]));
        }
        Line linearReg = linear_reg(pointsVector, pointsVector.size());
        // we find the threshold
        float threshold = calculate_threshold(pointsVector, linearReg);
        pointsVector.clear();
        correlatedFeatures cFeatures;
        cFeatures.corrlation = maxCorrelation;
        cFeatures.feature1 = currentFeatureName;
        cFeatures.feature2 = maxFeatureName;
        cFeatures.lin_reg = linearReg;
        cFeatures.threshold = 1.1 * threshold;
        this->cf.push_back(cFeatures);
    }


}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries &ts) {
    vector<AnomalyReport> reportsVector;
    vector<float> column1, column2;
    int size1 = this->cf.size(), size2;
    for (int i = 0; i < size1; i++) {
        column1 = ts.getColumnByProperyName(cf[i].feature1);
        column2 = ts.getColumnByProperyName(cf[i].feature2);
        vector<Point> pointsVector;
        putPointsVector(pointsVector, column1, column2);
         size2 = pointsVector.size();
        for (int j = 0; j < size2; j++) {
            if (anomalyCheck(pointsVector[j], this->cf[i])) { //if we have found aמ anomaly
                // we add the anomaly to the reportsVector
                AnomalyReport anomalyReport(cf[i].feature1 + "-" + cf[i].feature2, j + 1);
                reportsVector.push_back(anomalyReport);
            }
        }
        pointsVector.clear(); //we delete the allocated memory
    }
    return reportsVector; //we return the reportsVector

}


bool SimpleAnomalyDetector::anomalyCheck(Point &p, correlatedFeatures &features) {

    float currentDev = abs(features.lin_reg.f(p.x) - p.y);
    return currentDev > features.threshold;
}

