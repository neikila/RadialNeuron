//
// Created by k.neyman on 01.12.2016.
//

#ifndef NEIRONETS_NEURALNET_H
#define NEIRONETS_NEURALNET_H

#include "Neuron.h"

class NeuralNet {
private:
    vector<Neuron> neurons;
    vector<double> teta;

    void countFirst() {
        teta.clear();
        teta.push_back(1);
    }

public:
    NeuralNet() : neurons(vector<Neuron>()), teta(vector<double>()) {
        neurons.push_back(Neuron(NPoint(0, 0), NPoint(1, 1)));
        teta.push_back(1);
    }

    NeuralNet(Neuron n) : neurons(vector<Neuron>()), teta(vector<double>()) {
        neurons.push_back(n);
        teta.push_back(1);
    }

    Neuron& operator[] (int i) { return neurons[i]; }

    double countY(NPoint& p) {
        vector<Neuron>::iterator neurons_p = neurons.begin();
        vector<double>::iterator tetas_p = teta.begin();
        double y = 0;
        for(; neurons_p != neurons.end(); ++neurons_p, ++tetas_p)
            y += *tetas_p * neurons_p->f(p);
        return y;
    }

    void evolve(vector<NPoint>& points, vector<double> results) {
        vector<NPoint>::iterator pPoints= points.begin();
        vector<double>::iterator pResults = results.begin();

        vector<double> error = vector<double>();
        for (; pPoints != points.end(); ++pPoints, ++pResults)
            error.push_back(countY(*pPoints) - *pResults);

        vector<Neuron>::iterator pNeurons = neurons.begin();
        for (; pNeurons != neurons.end(); ++pNeurons)
            pNeurons->adjust(points, error);
    }

    friend ostream& operator<<(ostream& os, NeuralNet& net);
};

ostream &operator<<(ostream &os, NeuralNet &net) {
    os << "Net size: " << net.neurons.size() << endl;
    vector<Neuron>::iterator it = net.neurons.begin();
    for(; it != net.neurons.end(); ++it)
        os << "Neuron: " << *it << endl;
    return os;
}

#endif //NEIRONETS_NEURALNET_H
