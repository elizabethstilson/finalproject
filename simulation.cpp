#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include "Animator.h"
//#include "VehicleBase.h"
#include "Dictionary.h"
#include "RandomNumber.h"
//#include "Lane.h"

///using namespace std;

int main(int argc, char* argv[])
{
    Animator::MAX_VEHICLE_COUNT = 999;  // vehicles will be displayed with three digits
    //Testing to see if there were enough arguments entered
    if(argc != 3)
    {
    	cerr << "error"<< endl;
        exit(1);
    }
    //declaring the initialSeed variable
    int initialSeed = atoi(argv[2]);

    //declaring the filename
    string filename = argv[1];

    //Testing Dictionary class
    Dictionary dict(filename);
    cout << "testing Dictionary class" << endl;
    cout << dict.getGreenEW() << endl;

    //Testing RandomNumber Class
    RandomNumber random(initialSeed, filename);
    cout << "testing randomNumber" << endl;
    cout << random.getVehicle() << endl;

    //Number of sections before intersection
    cout << "Number of sections before intersection" << endl;
    int halfSize = (int)(dict.getNumSection());
    cout << halfSize << endl;

    //call animator class
    Animator anim(halfSize);

    //Variables to control the lights
    double maxTime = dict.getMaxSimTime();
    int currentTime = 0;
    double greenNS = dict.getGreenNS();
    double yellowNS = dict.getYellowNS();
    double greenEW = dict.getGreenEW();
    double yellowEW = dict.getYellowEW();

    //vectors
    Lane westbound(halfSize, Direction::west);
    Lane eastbound(halfSize, Direction::east);
    Lane southbound(halfSize, Direction::south);
    Lane northbound(halfSize, Direction::north);

    //variable to control drawing everything
    char space;

    //trafic light change loop
    //have it set for 28, but will need to change to the maxTime = max simulation time
    cout << "testing traffic light" << endl;
    while(currentTime < 28){
      int x;
       //controlling the green north and south lights
       for(x =0; x < greenNS; x++){
        if(currentTime >= 28){
          break;
        }
	      else{
          anim.setLightNorthSouth(LightColor::green);
          anim.setLightEastWest(LightColor::red);
          anim.setVehiclesNorthbound(northbound.getLaneVector());
          anim.setVehiclesWestbound(westbound.getLaneVector());
          anim.setVehiclesSouthbound(southbound.getLaneVector());
          anim.setVehiclesEastbound(eastbound.getLaneVector());
          anim.draw(currentTime);
          cin.get(space);
          currentTime++;
         // cout << currentTime << endl;
       }
      }
      //controlling the yellow north and south light
      for(x =0; x < yellowNS; x++){
        if(currentTime >= 28){
          break;
        }
        else{
          anim.setLightNorthSouth(LightColor::yellow);
          anim.setLightEastWest(LightColor::red);
          anim.setVehiclesNorthbound(northbound.getLaneVector());
          anim.setVehiclesWestbound(westbound.getLaneVector());
          anim.setVehiclesSouthbound(southbound.getLaneVector());
          anim.setVehiclesEastbound(eastbound.getLaneVector());
          anim.draw(currentTime);
          cin.get(space);
          currentTime++;
          //cout << currentTime << endl;
        }
      }
      //controlling the green east and west light
      for(x =0; x < greenEW; x++){
        if(currentTime >= 28){
          break;
        }
        else{
          anim.setLightNorthSouth(LightColor::red);
          anim.setLightEastWest(LightColor::green);
          anim.setVehiclesNorthbound(northbound.getLaneVector());
          anim.setVehiclesWestbound(westbound.getLaneVector());
          anim.setVehiclesSouthbound(southbound.getLaneVector());
          anim.setVehiclesEastbound(eastbound.getLaneVector());
          anim.draw(currentTime);
          cin.get(space);
          currentTime++;
          //cout << currentTime << endl;
        }
      }
      //controlling yellow east and west light
      for(x =0; x < yellowEW; x++){
        if(currentTime >= 28){
          break;
        }
        else{
          anim.setLightNorthSouth(LightColor::red);
          anim.setLightEastWest(LightColor::yellow);
          anim.setVehiclesNorthbound(northbound.getLaneVector());
          anim.setVehiclesWestbound(westbound.getLaneVector());
          anim.setVehiclesSouthbound(southbound.getLaneVector());
          anim.setVehiclesEastbound(eastbound.getLaneVector());
          anim.draw(currentTime);
          cin.get(space);
          currentTime++;
          //cout << currentTime << endl;
        }
      }
    }


}

