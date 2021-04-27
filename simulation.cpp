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
    int greenNS = int(dict.getGreenNS());
    int yellowNS = int(dict.getYellowNS());
    int greenEW = int(dict.getGreenEW());
    int yellowEW = int(dict.getYellowEW()); 
   

    //vectors
    std::vector<VehicleBase*> wb(halfSize * 2 + 2, nullptr);
    std::vector<VehicleBase*> eb(halfSize * 2 + 2, nullptr);
    std::vector<VehicleBase*> sb(halfSize * 2 + 2, nullptr);
    std::vector<VehicleBase*> nb(halfSize * 2 + 2, nullptr);
    Lane westbound(halfSize, Direction::west, wb);
    Lane eastbound(halfSize, Direction::east, eb);
    Lane northbound(halfSize, Direction::north, nb);
    Lane southbound(halfSize, Direction::south, sb);
    
  /*  std::cout << "testing the lane direction get method" << std::endl;
    std::cout << westbound.getlaneDirection() << " : westbound" << std::endl;
    std::cout << eastbound.getlaneDirection() << " : eastbound" << std::endl;
    std::cout << southbound.getlaneDirection() << " : southbound" << std::endl;
    std::cout << northbound.getlaneDirection() << " : northbound" << std::endl;
    std::cout << "testing getLane method using instance variable" << std::endl;
    std::cout << westbound.getLaneDirection() << " : westbound" << std::endl;
    std::cout << eastbound.getLaneDirection() << " : eastbound" << std::endl;
    std::cout << southbound.getLaneDirection() << " : southbound" << std::endl;
    std::cout << northbound.getLaneDirection() << " : northbound" << std::endl;
     
     for(int a = 0; a < (northbound.getLaneVector()).size(); a++){
       cout << boolalpha << (*(northbound.getLaneVector()).at(a)).isOccupied() << endl;}
  */ /* VehicleBase vehicleA(VehicleType::car, Direction::east, false);
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
    
   // Section sect1;
    //VehicleBase vC = random.whatVehicle();
   // sect1.makeOccupied(vC, Direction::east); 
   // Section sect2 = Section(sect1);
   // cout << "is occupied/testing copy constructor" << endl;
   // cout << "sect1: " << sect1.isOccupied() << endl;
   // cout << "sect2: " << sect2.isOccupied() << endl;
    
  // VehicleBase first(VehicleType::truck,Direction::west,false); 
  // cout << "made it here" <<endl;
  // westbound.assignVehicle(first); 
  // cout << "made it to this" << endl;
  // cout << westbound.getLaneVector().at(0).isOccupied() << endl; 
   
    
    //trafic light change loop
    //have it set for 28, but will need to change to the maxTime = max simulation time
    cout << "testing traffic light" << endl;
    while(currentTime < 30){
      int x;
      int test = 0;
       //made pointers to lane objects
       Lane *wpntr = &westbound;
       Lane *epntr = &eastbound;
       Lane *npntr = &northbound;
       Lane *spntr = &southbound;
       //controlling the green north and south lights
       for(x =0; x < greenNS; x++){
        if(currentTime >= 30){
          break;
        }
	 else{
          anim.setLightNorthSouth(LightColor::green);
          anim.setLightEastWest(LightColor::red);
          //anim.setLightEastWest(LightColor::green);
          std::cout << "after lights" << std::endl;
          westbound.moveLane(LightColor::red, npntr, spntr, yellowEW-x);
          eastbound.moveLane(LightColor::red, spntr, npntr, yellowEW-x);
          northbound.moveLane(LightColor::green, epntr, wpntr, yellowNS-x);
          southbound.moveLane(LightColor::green, wpntr, epntr, yellowNS-x);
          VehicleBase* veh = random.whatVehicle();
          if(veh != nullptr){
          if(veh->getVehicleOriginalDirection() == Direction::south){
           southbound.assignVehicle(veh);
           cout << "south" << endl;
           test++;
          }
          else if(veh->getVehicleOriginalDirection() == Direction::north){
            northbound.assignVehicle(veh);
            cout << "north" << endl;
            test++;
           }
           else if(veh->getVehicleOriginalDirection() == Direction::east){
           //for(int a = 0; a < (northbound.getLaneVector()).size(); a++){
           // cout << boolalpha << (northbound.getLaneVector()).at(a)->isOccupied() << endl;}
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
          }}
          //for(int a = 0; a < (northbound.getLaneVector()).size(); a++){
           // cout << boolalpha << (northbound.getLaneVector()).at(a)->isOccupied() << endl;} 
          //anim.setVehiclesNorthbound(northbound.getLaneVector());
          anim.setVehiclesWestbound(westbound.getVehicleBase());
          anim.setVehiclesSouthbound(southbound.getVehicleBase());
          anim.setVehiclesNorthbound(northbound.getVehicleBase());
          anim.setVehiclesEastbound(eastbound.getVehicleBase());
          //cout << "i made it before new stuff" << endl;
          /*westbound.moveLane(LightColor::red, spntr); 
          eastbound.moveLane(LightColor::red, npntr);
          northbound.moveLane(LightColor::green, wpntr);
          southbound.moveLane(LightColor::green, epntr); */
           
          cout << "i made it after new stuff" << endl;
          anim.draw(currentTime);
         /* westbound.moveLane(LightColor::red, spntr, npntr, yellowEW);//was red
          eastbound.moveLane(LightColor::red, npntr, spntr, yellowEW);//was red
          northbound.moveLane(LightColor::green, epntr, wpntr, yellowNS);
          southbound.moveLane(LightColor::green, wpntr, epntr, yellowNS);*/
         
          cin.get(space);
          currentTime++;
          cout << currentTime << endl;

       }
     }
      cout << test << " number of vehicles" << endl;
      //controlling the yellow north and south light
      for(x =0; x < yellowNS; x++){
        if(currentTime >= 30){
          break;
        }
        else{
           //anim.setLightNorthSouth(LightColor::green);
           anim.setLightNorthSouth(LightColor::yellow);
           //anim.setLightEastWest(LightColor::green);
           anim.setLightEastWest(LightColor::red);
            westbound.moveLane(LightColor::red, npntr, spntr, yellowEW-x);
          eastbound.moveLane(LightColor::red, spntr, npntr, yellowEW-x);
          northbound.moveLane(LightColor::yellow, epntr, wpntr, yellowNS-x);
          southbound.moveLane(LightColor::yellow, wpntr, epntr, yellowNS-x);
          VehicleBase* veh = random.whatVehicle();
          if(veh != nullptr){
          if(veh->getVehicleOriginalDirection() == Direction::south){
           southbound.assignVehicle(veh);
           cout << "south" << endl;
           test++;
          }
          else if(veh->getVehicleOriginalDirection() == Direction::north){
           northbound.assignVehicle(veh);
           cout << "north" << endl;
           test++;
          }
          else if(veh->getVehicleOriginalDirection() == Direction::east){
           eastbound.assignVehicle(veh);
           cout << "east" << endl;
           test++;
          }
          else{
           westbound.assignVehicle(veh);
           cout << "west" << endl;
           test++;
          }}
          anim.setVehiclesNorthbound(northbound.getVehicleBase());
          anim.setVehiclesWestbound(westbound.getVehicleBase());
          anim.setVehiclesSouthbound(southbound.getVehicleBase());
          anim.setVehiclesEastbound(eastbound.getVehicleBase());
        /*  westbound.moveLane(LightColor::red, spntr, npntr, yellowEW);//was red
          eastbound.moveLane(LightColor::red, npntr, spntr, yellowEW);//was red
          northbound.moveLane(LightColor::yellow, epntr, wpntr, yellowNS);//was yellow
          southbound.moveLane(LightColor::yellow, wpntr, epntr, yellowNS);//was yellow      
         */ anim.draw(currentTime);
          cin.get(space);
          currentTime++;
          //cout << currentTime << endl;
        }
      }
      //controlling the green east and west light
      for(x =0; x < greenEW; x++){
        if(currentTime >= 30){
          break;
        }
        else{
          anim.setLightNorthSouth(LightColor::red);
          anim.setLightEastWest(LightColor::green);
           westbound.moveLane(LightColor::green, npntr, spntr, yellowEW-x);
          eastbound.moveLane(LightColor::green, spntr, npntr, yellowEW-x);
          northbound.moveLane(LightColor::yellow, epntr, wpntr, yellowNS-x);
          southbound.moveLane(LightColor::yellow, wpntr, epntr, yellowNS-x);
          VehicleBase* veh = random.whatVehicle();
         if(veh != nullptr){ 
         if(veh->getVehicleOriginalDirection() == Direction::south){
           southbound.assignVehicle(veh);
           cout << "south" << endl;
           test++;
          }
          else if(veh->getVehicleOriginalDirection() == Direction::north){
           northbound.assignVehicle(veh);
           cout << "north" << endl;
           test++;
          }
          else if(veh->getVehicleOriginalDirection() == Direction::east){
           eastbound.assignVehicle(veh);
           cout << "east" << endl;
           test++;
          }
          else{
           westbound.assignVehicle(veh);
           cout << "west" << endl;
           test++;
          }}
          anim.setVehiclesNorthbound(northbound.getVehicleBase());
          anim.setVehiclesWestbound(westbound.getVehicleBase());
          anim.setVehiclesSouthbound(southbound.getVehicleBase());
          anim.setVehiclesEastbound(eastbound.getVehicleBase());
        /*  westbound.moveLane(LightColor::green, spntr, npntr, yellowEW);
          eastbound.moveLane(LightColor::green, npntr, spntr, yellowEW);
          northbound.moveLane(LightColor::red, epntr, wpntr, yellowNS);
          southbound.moveLane(LightColor::red, wpntr, epntr, yellowNS);
          */anim.draw(currentTime);
          cin.get(space);
          currentTime++;
          //cout << currentTime << endl;
        }
      }
      //controlling yellow east and west light
      for(x =0; x < yellowEW; x++){
        if(currentTime >= 30){
          break;
        }
        else{
          anim.setLightNorthSouth(LightColor::red);
          anim.setLightEastWest(LightColor::yellow);
           westbound.moveLane(LightColor::yellow, npntr, spntr, yellowEW-x);
          eastbound.moveLane(LightColor::yellow, spntr, npntr, yellowEW-x);
          northbound.moveLane(LightColor::red, epntr, wpntr, yellowNS-x);
          southbound.moveLane(LightColor::red, wpntr, epntr, yellowNS-x);
          VehicleBase* veh = random.whatVehicle();
         if(veh != nullptr){
         if(veh->getVehicleOriginalDirection() == Direction::south){
           southbound.assignVehicle(veh);
           cout << "south" << endl;
           test++;
          }
          else if(veh->getVehicleOriginalDirection() == Direction::north){
           northbound.assignVehicle(veh);
           cout << "north" << endl;
           test++;
          }
          else if(veh->getVehicleOriginalDirection() == Direction::east){
           eastbound.assignVehicle(veh);
           cout << "east" << endl;
           test++;
          }
          else{
           westbound.assignVehicle(veh);
           cout << "west" << endl;
           test++;
          }}
          anim.setVehiclesNorthbound(northbound.getVehicleBase());
          anim.setVehiclesWestbound(westbound.getVehicleBase());
          anim.setVehiclesSouthbound(southbound.getVehicleBase());
          anim.setVehiclesEastbound(eastbound.getVehicleBase());
         /* westbound.moveLane(LightColor::yellow, spntr, npntr, yellowEW);
          eastbound.moveLane(LightColor::yellow, npntr, spntr, yellowEW);
          northbound.moveLane(LightColor::red, epntr, wpntr, yellowNS);
          southbound.moveLane(LightColor::red, wpntr, epntr, yellowNS);
         */ anim.draw(currentTime);
          cin.get(space);
          currentTime++;
          //cout << currentTime << endl;
        }
      }
    }


}
