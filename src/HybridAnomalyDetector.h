// Author: Aviad Saadi, ID: 212330567

#ifndef HYBRIDANOMALYDETECTOR_H_
#define HYBRIDANOMALYDETECTOR_H_

#include "SimpleAnomalyDetector.h"
#include "minCircle.h"

class HybridAnomalyDetector : public SimpleAnomalyDetector{
    Circle currentMinCircle = {{0, 0}, 0};
    bool isCircleAnomalyDetector = false;
public:
    HybridAnomalyDetector();

    virtual ~HybridAnomalyDetector();

    void
    createAndAddCorrelatedFeaturesVector(const vector<float> &currentColumn, const vector<float> &maxColumn,
                                         const string &currentFeatureName,
                                         const string &maxFeatureName, float maxCorrelation) override;

    bool anomalyCheck(Point &p, correlatedFeatures &features) override;

    float calculate_threshold(vector<Point> &pointsVector, Line &linearReg) override;

};

#endif /* HYBRIDANOMALYDETECTOR_H_ */
