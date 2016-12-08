//
// Created by k.neyman on 01.12.2016.
//

#ifndef NEIRONETS_NEURON_H
#define NEIRONETS_NEURON_H

#include "NPoint.h"
#include <math.h>

typedef double DiffCenter;
typedef double DiffRadius;

extern double kLearning;

class Neuron {
private:
    NPoint center;
    NPoint rads;

public:
    Neuron(NPoint initialPos, NPoint initialRads) :
            center(initialPos), rads(initialRads) {
    };

    NPoint& getRadius() { return rads; }
    NPoint& getCenter() { return center; }

    double f(NPoint& x) {
        return exp(-norma(x) / 2);
    }

    double norma(NPoint& x) {
        NPoint partedSum = (x - center) / rads;
        double result = 0;
        vector<double>::iterator it = partedSum.getCoords().begin();
        for(; it != partedSum.getCoords().end(); ++it)
            result += pow(*it, 2);

        return result;
    }

    void adjust(vector<NPoint>& points, vector<double>& errors) {
        for(size_t i = 0; i < center.getCoords().size(); ++i)
            adjustByJAxis(points, errors, i);
    }

    pair<DiffCenter, DiffRadius> diffByJAxis(vector<NPoint>& points, vector<double>& errors, size_t j) {
        vector<NPoint>::iterator pPoints = points.begin();
        vector<double>::iterator pErrors = errors.begin();

        double diffByCenterByJAxis = 0;
        double diffByRadiusByJAxis = 0;
        for(; pPoints != points.end(); ++pPoints, ++pErrors) {
            double base = *pErrors * f(*pPoints) * ((*pPoints)[j] - center[j]) / pow(rads[j], 2);
            diffByCenterByJAxis += base;
            diffByRadiusByJAxis += base * ((*pPoints)[j] - center[j]) / rads[j];
        }

        return pair<DiffCenter, DiffRadius>(diffByCenterByJAxis, diffByRadiusByJAxis);
    };

    void adjustByJAxis(vector<NPoint>& points, vector<double>& errors, size_t j) {
        pair<DiffCenter, DiffRadius> diffs = diffByJAxis(points, errors, j);

        center.set(j, center[j] - kLearning * diffs.first);
        rads.set(j, rads[j] - kLearning * diffs.second);
    }

    void correct(vector<NPoint>& points, vector<double>& result) {
        vector<NPoint> pointsNotIncluded = notIncl(points, result);
        cout << "Size: " << pointsNotIncluded.size() << endl;

        cout << *this << endl;
        NPoint toIncl = max(pointsNotIncluded);
        NPoint backupRads = rads;
        adjustRad(toIncl);
        cout << *this << endl;
        cout << "Size: " << notIncl(points, result).size() << endl;
    }

    vector<NPoint> notIncl(vector<NPoint>& points, vector<double>& result) {
        vector<NPoint>::iterator p = points.begin();
        vector<double>::iterator pResult = result.begin();

        vector<NPoint> pointsNotIncluded;
//        vector<NPoint> badPoints;

        for(; p != points.end(); ++p, ++pResult) {
            if (*pResult > 0.5) {
                if (!isIn(*p))
                    pointsNotIncluded.push_back(*p);
            }
        }
        return pointsNotIncluded;
    }

    void adjustRad(NPoint &point) {
        while(!isIn(point)) {
            vector<double> newRads;
            vector<double>::iterator p = rads.getCoords().begin();
            for (; p != rads.getCoords().end(); ++p) {
                newRads.push_back(*p * 1.05);
                cout << *this << endl;
            }
            rads = NPoint(newRads);
        }
    }

    NPoint& max(vector<NPoint> &points) {
        vector<NPoint>::iterator p = points.begin();

        NPoint& min = points.front();
        double minValue = norma(min);

        for(++p; p != points.end(); ++p) {
            double temp = norma(*p);
            if (temp > minValue) {
                min = *p;
                minValue = temp;
            }
        }
        return min;
    }

    bool isIn(NPoint& point) {
        return norma(point) <= 1;
    }

    friend ostream& operator<<(ostream& os, Neuron& neuron);
};

ostream &operator<<(ostream &os, Neuron &n) {
    os << "Center: " << n.center << "; Rads: " << n.rads;
    return os;
}


#endif //NEIRONETS_NEURON_H
