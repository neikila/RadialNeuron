//
// Created by k.neyman on 01.12.2016.
//

#ifndef NEIRONETS_DATASOURCE_H
#define NEIRONETS_DATASOURCE_H

#include <fstream>
#include "NPoint.h"

class DataSource {
private:
    vector<pair<NPoint, double>> pointsToEvolve;
public:
    DataSource(string filename, double multiplierX, double multiplierY) {
        ifstream file;
        file.open(filename);

        pointsToEvolve = vector<pair<NPoint, double>>();
        double val, x, y;
        while(file >> val >> x >> y) {
            pointsToEvolve.push_back(pair<NPoint, double>(NPoint(x * multiplierX, y * multiplierY), val));
        }
    }

    vector<pair<NPoint, double>>& getPointsToEvolve() {
        return pointsToEvolve;
    }
};

#endif //NEIRONETS_DATASOURCE_H
