#include <iostream>
#include <random>
//#include "Dictionary.h"
using namespace std;

class RandomNumber{

  public:
    int initialSeed;
    mt19937 rng;
    string filename;
    //const uniform_real_distribution<double> randomNum(0.0, 1.0);
    //uniform_real_distribution<double> randomNum(double begin, double end);
    //map<string, double> prob;
    //Dictionary prob(string filename);

    RandomNumber(int seed, string filename); //set intial seed in constructor
    ~RandomNumber();

    double getNum();

    bool turnRightCar();
    bool turnRightSUV();
    bool turnRightTruck();
    int getVechile(); //0,1,2 (if else) -generate num beginning
    char getBound(); //n,s,e,w (if else)
    //0-0.25 = nb, 0.26 - 0.35 = eb, 0.36 - 0.50 = wb, 0.51 - 0.65 = sb, 0.66+ none

};
