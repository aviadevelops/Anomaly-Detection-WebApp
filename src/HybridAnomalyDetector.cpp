// Author: Aviad Saadi, ID: 212330567
#include "HybridAnomalyDetector.h"

HybridAnomalyDetector::HybridAnomalyDetector() {
    // TODO Auto-generated constructor stub

}

HybridAnomalyDetector::~HybridAnomalyDetector() {
    // TODO Auto-generated destructor stub
}

void
HybridAnomalyDetector::createAndAddCorrelatedFeaturesVector(const vector<float> &currentColumn,
                                                            const vector<float> &maxColumn,
                                                            const string &currentFeatureName,
                                                            const string &maxFeatureName, float maxCorrelation) {
    if (maxCorrelation >= this->threshold) {
        this->isCircleAnomalyDetector = false;
        SimpleAnomalyDetector::createAndAddCorrelatedFeaturesVector(currentColumn, maxColumn, currentFeatureName,
                                                                    maxFeatureName, maxCorrelation);

    } else if (maxCorrelation > 0.5) {
        float thresholdBackup = this->threshold;
        this->threshold = 0.5;
        this->isCircleAnomalyDetector = true;
        SimpleAnomalyDetector::createAndAddCorrelatedFeaturesVector(currentColumn, maxColumn, currentFeatureName,
                                                                    maxFeatureName, maxCorrelation);
        this->cf[cf.size() - 1].centerX = this->currentMinCircle.center.x;
        this->cf[cf.size() - 1].centerY = this->currentMinCircle.center.y;
        this->cf[cf.size() - 1].lin_reg = {0, 0};
        this->threshold = thresholdBackup;
        this->isCircleAnomalyDetector = false;
        this->currentMinCircle = {{0, 0}, 0};
    }


}

bool HybridAnomalyDetector::anomalyCheck(Point &p, correlatedFeatures &features) {
    if (features.corrlation >= this->threshold) {
        return SimpleAnomalyDetector::anomalyCheck(p, features);
    } else if (features.corrlation > 0.5) {
        return (pow(p.x - features.centerX, 2) + pow(p.y - features.centerY, 2) > pow(features.threshold, 2));
    }
}

float HybridAnomalyDetector::calculate_threshold(vector<Point *> &pointsVector, Line &linearReg) {
    if (!this->isCircleAnomalyDetector) {
        return SimpleAnomalyDetector::calculate_threshold(pointsVector, linearReg);
    } else {
        this->currentMinCircle = findMinCircle(pointsVector.data(), pointsVector.size());
        int x = pointsVector.size();
        return this->currentMinCircle.radius;
    }

}

