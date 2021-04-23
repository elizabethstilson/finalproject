#ifdef __ROADSIM_H__
#define __ROADSIM_H__

#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include "VehicleBase.h"
#include "Dictionary.h"
#include "Animator.h"
#include "Lane.h"
#include "Section.h"

using namespace std;

class roadSim{
  public:
    roadSim(int seed, string filename);
    ~roadSim();

    Dictionary prob();
    RandomNumber num();
    int numSecs;
    int maxTime;
    int currentTime;
    Animator anim();
    vector<VehicleBase*> westbound();
    vector<VehicleBase*> eastbound();
    vector<VehicleBase*> southbound();
    vector<VehicleBase*> northbound();


    void execute(); //executes while loops
    void builder(); //builds simulation


};

#endif

