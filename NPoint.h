//
// Created by k.neyman on 01.12.2016.
//

#ifndef NEIRONETS_NPOINT_H
#define NEIRONETS_NPOINT_H

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class NPoint {
private:
    vector<double> coords;
public:
    NPoint() : coords(vector<double>()) { }
    NPoint(vector<double> coords_val) : coords(coords_val) { }
    NPoint(double x, double y) : coords(vector<double>()) {
        coords.push_back(x);
        coords.push_back(y);
    }

    NPoint(double x, double y, double z) : coords(vector<double>()) {
        coords.push_back(x);
        coords.push_back(y);
        coords.push_back(z);
    }

    NPoint operator + (NPoint& p) {
        NPoint result;
        vector<double>::iterator it = coords.begin();
        vector<double>::iterator pIt = p.coords.begin();
        for(; it != coords.end(); ++it, ++pIt)
            result.coords.push_back(*it + *pIt);

        return result;
    }

    NPoint operator - (NPoint& p) {
        NPoint result;
        vector<double>::iterator it = coords.begin();
        vector<double>::iterator pIt = p.coords.begin();
        for(; it != coords.end(); ++it, ++pIt)
            result.coords.push_back(*it - *pIt);

        return result;
    }

    NPoint operator / (NPoint& p) {
        NPoint result;
        vector<double>::iterator it = coords.begin();
        vector<double>::iterator pIt = p.coords.begin();
        for(; it != coords.end(); ++it, ++pIt)
            result.coords.push_back(*it / *pIt);

        return result;
    }

    NPoint abs () {
        NPoint result;
        vector<double>::iterator it = coords.begin();
        for(; it != coords.end(); ++it)
            result.coords.push_back(fabs(*it));

        return result;
    }

    void set(int i, double val) { coords[i] = val; }

    double operator[] (const int i) { return coords[i]; }

    vector<double>& getCoords() { return coords; }

    friend ostream& operator<<(ostream& os, NPoint& p);
};

ostream &operator<<(ostream &os, NPoint &p) {
    vector<double>::iterator it = p.coords.begin();
    os << '(' << *it++;
    for(; it != p.coords.end(); ++it)
        os << ", " << *it;
    os << ')';
    return os;
}

#endif //NEIRONETS_NPOINT_H
