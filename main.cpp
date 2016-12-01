#include <iostream>
#include <vector>
#include "NPoint.h"
#include "Neuron.h"
#include "NeuralNet.h"
#include "DataSource.h"
#include "Gnuplot.h"

using namespace std;

double multiplierX = 10;
double multiplierY = 10;
double kLearning = 1;

Gnuplot plotter("result.gpl", multiplierX, multiplierY);

double count(vector<NPoint>& points, NeuralNet& net) {
    double result = 0;
    for (NPoint p: points)
        result += net.countY(p);
    return result;
}

int main() {
    NeuralNet net(Neuron(NPoint(2.78061, 5.00458), NPoint(1, 1)));
    cout << net << endl;

    DataSource source("C:\\Users\\k.neyman\\ClionProjects\\NeiroNets\\data\\input\\sigmo25.txt",
                      multiplierX, multiplierY);

    vector<NPoint> points;
    vector<double> result;

    vector<NPoint> correctPoints;
    vector<NPoint> failPoints;

    for (pair<NPoint, double> p: source.getPointsToEvolve()) {
        points.push_back(p.first);
        result.push_back(p.second);

        if (p.second > 0.5)
            correctPoints.push_back(p.first);
        else
            failPoints.push_back(p.first);
    }

    plotter.prepare();
    plotter.printSet(correctPoints);
    plotter.printSet(failPoints);

    plotter.plotNeuron(net);

    double prev = -2;
    double actual = 0;
    for (int i = 0; i < 100; ++i) {
        net.evolve(points, result);
        plotter.plotNeuron(net);
        actual = count(points, net);
        cout << "Iteration #" << ++i << " is over. Diff:" << actual - prev << endl;
    }
//    double prev = -2;
//    double actual = 0;
//    int i = 0;
//    do {
//        net.evolve(points, result);
//        plotter.plotNeuron(net);
//        actual = count(points, net);
//        cout << "Iteration #" << ++i << " is over. Diff:" << actual - prev << endl;
//    } while(actual - prev > accuracy);

    cout << net << endl;
    return 0;
}