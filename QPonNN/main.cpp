#include <iostream>
#include <fstream>
#include "QPonNN.h"
#include "sigmoid.h"
#include "backpropagationlearning.h"
using namespace std;

bool openInFile(ifstream &infile, char* path)
{
    infile.open(path);
    if (!infile.is_open())
    {
        cout << "Oops, i can't read your file! (maybe it is in wrong place)" << endl;
        return false;
    }
    else
    {
        cout << "File successfuly loaded" << endl;
    }
    cout << endl;
    return true;
}

bool openOutFile(fstream &outfile, char* path)
{
    outfile.open(path, ios_base::out | ios_base::trunc);
    if (!outfile.is_open())//if don't exists
    {
        outfile.open(path, ios_base::in | ios_base::out | ios_base::trunc);//create
        return false;
    }
    else
    {
        return true;
    }
}

using namespace QPonNN;

int main()
{
//    ifstream in;
//    openInFile(in, "in.txt");
//    fstream out;
//    openOutFile(out, "out.txt");

    QList<QList<double>*>* xorInput = new QList<QList<double>*>;
    QList<QList<double>*>* xorOutput = new QList<QList<double>*>;

    xorInput->append(new QList<double>({0.0, 0.0}));
    xorOutput->append(new QList<double>({0.0}));

    xorInput->append(new QList<double>({0.0, 1.0}));
    xorOutput->append(new QList<double>({0.0}));

    xorInput->append(new QList<double>({1.0, 0.0}));
    xorOutput->append(new QList<double>({0.0}));

    xorInput->append(new QList<double>({1.0, 1.0}));
    xorOutput->append(new QList<double>({1.0}));

    NeuroNet NN(2);
    NN.appendLayer(new Sigmoid(), 1)
           .appendLayer(new Sigmoid(), 2);

    cout << "===start training===\n";
    BackPropagationLearning la(&NN, 0.5, 0.05);
    la.setTrainingSet(xorInput, xorInput);
    la.train(10000000);
    cout << "===end training===\n";
    //
    for (int iN = 0; iN < xorInput->size(); iN++)
    {
        QList<double>* in = xorInput->at(iN);
        NN.input(in);
        cout << "Input: ";
        QListIterator<double> i(*in);
        while (i.hasNext())
            cout << " " << i.next();
        cout << " -> " << xorOutput->at(iN)->first() << endl;
        QList<double>* out = NN.output();
        cout << "Output: ";
        QListIterator<double> o(*out);
        while (o.hasNext())
            cout << " " << o.next();
        cout << endl;
    }
    NN.printConfig();

    return 0;
}

