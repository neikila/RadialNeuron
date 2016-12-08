//
// Created by k.neyman on 01.12.2016.
//

#ifndef NEIRONETS_GNUPLOT_H
#define NEIRONETS_GNUPLOT_H

#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include "NPoint.h"
#include "NeuralNet.h"

using namespace std;
extern double pauseTime;

class Gnuplot {
private:
    ofstream* script;
    int setAmount;
    vector<string> setNames;
    vector<string> colors = {"green", "red", "blue"};

    double multiplierX;
    double multiplierY;

public:
    Gnuplot(string filename, double multiplierX, double multiplierY) {
        setNames = vector<string>();

        this->multiplierX = multiplierX;
        this->multiplierY = multiplierY;

        setAmount = 0;

        script = new ofstream();
        script->open(filename);
    }

    ~Gnuplot() {
        *script << "pause -1;";
        script->close();
    }

    void prepare() {
        *script << "set xlabel \"x1\";" << endl <<
                  "set ylabel \"x2\";" << endl <<
                  "set xrange [-" << multiplierX << ":" << multiplierX << "];" << endl <<
                  "set yrange [-" << multiplierY << ":" << multiplierY << "];" << endl <<
                  "set colorbox vertical user origin .02,.1 size .04,.8;" << endl <<
                  "set view 0,0;" << endl <<
                  "set term x11;" << endl <<
                  "set parametric;" << endl <<
                  "unset ztics;" << endl;
    }

    void printSet(vector<NPoint> points) {
        ++setAmount;
        ofstream out;

        ostringstream stringStream;
        stringStream << "point_set" << setAmount;
        string newSetName = stringStream.str();

        setNames.push_back(newSetName);
        out.open(newSetName);

        for (NPoint p: points) {
            for (double coord: p.getCoords())
                out << coord << ' ';
            out << endl;
        }
        out.close();
    }

    void plotNeuron(NeuralNet net) {
        Neuron n = net[0];
        *script << "fx(t)=" << n.getCenter()[0] << "+" << n.getRadius()[0] << "*cos(t)" << endl
               << "fy(t)=" << n.getCenter()[1] << "+" << n.getRadius()[1] << "*sin(t)" << endl;

        *script << "plot '" << setNames[0] << "' notitle w p pt 8 lc rgb '"
                          << colors[0] << "'";

        for (int i = 1; i < setNames.size(); ++i) {
            *script << ",\\" << endl << "     '"
                   << setNames[i] << "' notitle w p pt 8 lc rgb '"
                   << colors[i] << "'";
        }
        *script << ",\\" << endl << "      fx(t),fy(t) notitle";
        *script << ";" << endl
               << "pause " << pauseTime << ";" << endl;
    }
};


#endif //NEIRONETS_GNUPLOT_H
