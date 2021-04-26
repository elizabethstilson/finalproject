#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include "Animator.h"
//#include "VehicleBase.h"
#include "Dictionary.h"
#include "RandomNumber.h"
#include "Lane.h"
#include "Section.h"

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
    //double maxTime = dict.getMaxSimTime();
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
    /*for(int a = 0; a < (northbound.getLaneVector()).size(); a++){
       cout << boolalpha << (*(northbound.getLaneVector()).at(a)).isOccupied() << endl;}
    VehicleBase vehicleA(VehicleType::car, Direction::east, false);
    eastbound.assignVehicle(vehicleA);
    cout << (*(eastbound.getLaneVector()).at(0)).isOccupied() << " : east " << endl;
    cout << (*(eastbound.getLaneVector()).at(1)).isOccupied() << " : east " << endl;
    cout << (*(eastbound.getLaneVector()).at(2)).isOccupied() << " : east " << endl;
    Lane *npntr = &northbound;
    eastbound.moveLane(LightColor::green, npntr); 
    cout << (*(eastbound.getLaneVector()).at(0)).isOccupied() << " : east " << endl;
    cout << (*(eastbound.getLaneVector()).at(1)).isOccupied() << " : east " << endl;
    cout << (*(eastbound.getLaneVector()).at(2)).isOccupied() << " : east " << endl;
    cout << "testing whatVehicle" << endl;
    VehicleBase vB = random.whatVehicle();
    cout << vB.getVehicleID() << " : vehicleID" << endl;
    cout << vB.getTurningStatus() << " : turnStatus" << endl;
    VehicleBase vC = random.whatVehicle();
    cout << vC.getVehicleID() << " : vehicleID" << endl;
    cout << vC.getTurningStatus() << " : turnStatus" << endl;*/
    
    //variable to control drawing everything
    char space;
    
    Section sect1;
    //sect1.makeOccupied(vC, Direction::east); 
    Section sect2 = Section(sect1);
    cout << "is occupied/testing copy constructor" << endl;
    cout << "sect1: " << sect1.isOccupied() << endl;
    cout << "sect2: " << sect2.isOccupied() << endl;
    
     
     
     
     
    
    //trafic light change loop
    //have it set for 28, but will need to change to the maxTime = max simulation time
    cout << "testing traffic light" << endl;
    while(currentTime < 28){
      int x;
      int test = 0;
       //made pointers to lane objects
       Lane *wpntr = &westbound;
       Lane *epntr = &eastbound;
       Lane *npntr = &northbound;
       Lane *spntr = &southbound;
       //controlling the green north and south lights
       for(x =0; x < greenNS; x++){
        if(currentTime >= 28){
          break;
        }
	 else{
          anim.setLightNorthSouth(LightColor::green);
          anim.setLightEastWest(LightColor::red);
          westbound.moveLane(LightColor::red, spntr);
          eastbound.moveLane(LightColor::red, npntr);
          northbound.moveLane(LightColor::green, wpntr);
          southbound.moveLane(LightColor::green, epntr);
          VehicleBase veh = random.whatVehicle();
          if(veh.getVehicleOriginalDirection() == Direction::south){
           southbound.assignVehicle(veh);
           cout << "south" << endl;
           test++;
          }
          else if(veh.getVehicleOriginalDirection() == Direction::north){
           northbound.assignVehicle(veh);
           cout << "north" << endl;
           test++;
          }
          else if(veh.getVehicleOriginalDirection() == Direction::east){
           for(int a = 0; a < (northbound.getLaneVector()).size(); a++){
            cout << boolalpha << (northbound.getLaneVector()).at(a)->isOccupied() << endl;}
           eastbound.assignVehicle(veh); 
           cout << "east" << endl;
           test++;
          //for(int a = 0; a < (northbound.getLaneVector()).size(); a++){
           // cout << boolalpha << (northbound.getLaneVector()).at(a)->isOccupied() << endl;}
          }
          else{
           westbound.assignVehicle(veh);
           cout << "west" << endl;
           test++;
          }
          //for(int a = 0; a < (northbound.getLaneVector()).size(); a++){
           // cout << boolalpha << (northbound.getLaneVector()).at(a)->isOccupied() << endl;} 
          anim.setVehiclesNorthbound(northbound.getLaneVector());
          anim.setVehiclesWestbound(westbound.getLaneVector());
          anim.setVehiclesSouthbound(southbound.getLaneVector());
          anim.setVehiclesEastbound(eastbound.getLaneVector());
          //cout << "i made it before new stuff" << endl;
          /*westbound.moveLane(LightColor::red, spntr); 
          eastbound.moveLane(LightColor::red, npntr);
          northbound.moveLane(LightColor::green, wpntr);
          southbound.moveLane(LightColor::green, epntr); */
           
          //cout << "i made it after new stuff" << endl;
          anim.draw(currentTime);
          cin.get(space);
          currentTime++;
         // cout << currentTime << endl;

       }
      }
      cout << test << " number of vehicles" << endl;
      //controlling the yellow north and south light
      for(x =0; x < yellowNS; x++){
        if(currentTime >= 28){
          break;
        }
        else{
          anim.setLightNorthSouth(LightColor::yellow);
          anim.setLightEastWest(LightColor::red);
          VehicleBase veh = random.whatVehicle();
          if(veh.getVehicleOriginalDirection() == Direction::south){
           southbound.assignVehicle(veh);
           cout << "south" << endl;
           test++;
          }
          else if(veh.getVehicleOriginalDirection() == Direction::north){
           northbound.assignVehicle(veh);
           cout << "north" << endl;
           test++;
          }
          else if(veh.getVehicleOriginalDirection() == Direction::east){
           eastbound.assignVehicle(veh);
           cout << "east" << endl;
           test++;
          }
          else{
           westbound.assignVehicle(veh);
           cout << "west" << endl;
           test++;
          }
          anim.setVehiclesNorthbound(northbound.getLaneVector());
          anim.setVehiclesWestbound(westbound.getLaneVector());
          anim.setVehiclesSouthbound(southbound.getLaneVector());
          anim.setVehiclesEastbound(eastbound.getLaneVector());
          westbound.moveLane(LightColor::red, spntr);
          eastbound.moveLane(LightColor::red, npntr);
          northbound.moveLane(LightColor::yellow, wpntr);
          southbound.moveLane(LightColor::yellow, epntr);         
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
          VehicleBase veh = random.whatVehicle();
          if(veh.getVehicleOriginalDirection() == Direction::south){
           southbound.assignVehicle(veh);
           cout << "south" << endl;
           test++;
          }
          else if(veh.getVehicleOriginalDirection() == Direction::north){
           northbound.assignVehicle(veh);
           cout << "north" << endl;
           test++;
          }
          else if(veh.getVehicleOriginalDirection() == Direction::east){
           eastbound.assignVehicle(veh);
           cout << "east" << endl;
           test++;
          }
          else{
           westbound.assignVehicle(veh);
           cout << "west" << endl;
           test++;
          }
          anim.setVehiclesNorthbound(northbound.getLaneVector());
          anim.setVehiclesWestbound(westbound.getLaneVector());
          anim.setVehiclesSouthbound(southbound.getLaneVector());
          anim.setVehiclesEastbound(eastbound.getLaneVector());
          westbound.moveLane(LightColor::green, spntr);
          eastbound.moveLane(LightColor::green, npntr);
          northbound.moveLane(LightColor::red, wpntr);
          southbound.moveLane(LightColor::red, epntr);
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
          VehicleBase veh = random.whatVehicle();
          if(veh.getVehicleOriginalDirection() == Direction::south){
           southbound.assignVehicle(veh);
           cout << "south" << endl;
           test++;
          }
          else if(veh.getVehicleOriginalDirection() == Direction::north){
           northbound.assignVehicle(veh);
           cout << "north" << endl;
           test++;
          }
          else if(veh.getVehicleOriginalDirection() == Direction::east){
           eastbound.assignVehicle(veh);
           cout << "east" << endl;
           test++;
          }
          else{
           westbound.assignVehicle(veh);
           cout << "west" << endl;
           test++;
          }
          anim.setVehiclesNorthbound(northbound.getLaneVector());
          anim.setVehiclesWestbound(westbound.getLaneVector());
          anim.setVehiclesSouthbound(southbound.getLaneVector());
          anim.setVehiclesEastbound(eastbound.getLaneVector());
          westbound.moveLane(LightColor::yellow, spntr);
          eastbound.moveLane(LightColor::yellow, npntr);
          northbound.moveLane(LightColor::red, wpntr);
          southbound.moveLane(LightColor::red, epntr);
          anim.draw(currentTime);
          cin.get(space);
          currentTime++;
          //cout << currentTime << endl;
        }
      }
    }


}
