#ifndef __RANDOMNUMBER_H__
#define __RANDOMNUMBER_H__

#include <iostream>
#include <random>
#include "VehicleBase.h"
using namespace std;

class RandomNumber{

  public:
    int initialSeed;
    mt19937 rng;
    string filename;

    RandomNumber(int seed, string filename); //set intial seed in constructor
    ~RandomNumber();

    double getNum();

    bool turnRightCar();
    bool turnRightSUV();
    bool turnRightTruck();
    int getVehicle(); //0,1,2 (if else) -generate num beginning
    char getBound(); //n,s,e,w (if else)
    VehicleBase* whatVehicle();

};

#endif
