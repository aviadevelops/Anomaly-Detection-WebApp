// Author: Aviad Saadi, ID: 212330567

#ifndef SIMPLEANOMALYDETECTOR_H_
#define SIMPLEANOMALYDETECTOR_H_

#include "anomaly_detection_util.h"
#include "AnomalyDetector.h"
#include <vector>
#include <algorithm>
#include <string.h>
#include <math.h>
#include <memory>


void deleteVectorMembers(vector<Point *> &vector);


struct correlatedFeatures {
    string feature1, feature2;  // names of the correlated features
    float corrlation;
    Line lin_reg;
    float threshold, centerX, centerY;
};


class SimpleAnomalyDetector : public TimeSeriesAnomalyDetector {
protected:
    vector<correlatedFeatures> cf;
    float threshold;
public:
    SimpleAnomalyDetector();

    virtual ~SimpleAnomalyDetector();

    virtual void learnNormal(const TimeSeries &ts);

    virtual vector<AnomalyReport> detect(const TimeSeries &ts);

    void putPointsVector(vector<Point *> &pointsVector, const vector<float> &f1, const vector<float> &f2);

    virtual float calculate_threshold(vector<Point *> &pointsVector, Line &linearReg);

    virtual bool anomalyCheck(Point &p, correlatedFeatures &features);

    virtual void
    createAndAddCorrelatedFeaturesVector(const vector<float> &currentColumn, const vector<float> &maxColumn,
                                         const string &currentFeatureName,
                                         const string &maxFeatureName, float maxCorrelation);


    vector<correlatedFeatures> getNormalModel() {
        return cf;
    }

    string getCorrelatedFeature(string s) {
        for (correlatedFeatures c: this->cf) {
            if (s == c.feature1) {
                return c.feature2;
            }
        }
        return "";
    }

    float getThreshold();

    void setThreshold(float newThreshold);

};


#endif /* SIMPLEANOMALYDETECTOR_H_ */
