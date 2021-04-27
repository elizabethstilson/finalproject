#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include "Animator.h"
#include "VehicleBase.h"
#include "Dictionary.h"
#include "RandomNumber.h"
#include "Lane.h"
#include "Section.h"

using namespace std;

int main(int argc, char* argv[])
{
    //Animator::MAX_VEHICLE_COUNT = 9999;  // vehicles will be displayed with four digits
     Animator::MAX_VEHICLE_COUNT = 999;  // vehicles will be displayed with three digits
    //Animator::MAX_VEHICLE_COUNT = 99;  // vehicles will be displayed with two digits
	
    //Testing to see if there were enough arguments entered
    if(argc != 3)
    {
    	cerr << "There was an error with running simulation. You need to have an inputfile and an int for the seed number"<< endl;
        exit(1);
    }
    //declaring the initialSeed variable
    int initialSeed = atoi(argv[2]);

    //declaring the filename
    string filename = argv[1];

    //The Dictionary class object 
    Dictionary dict(filename);

    //The RandomNumber class object
    RandomNumber random(initialSeed, filename);
	
    //Number of sections before intersection
    int halfSize = (int)(dict.getNumSection());

    //call animator class
    Animator anim(halfSize);

    //Variables to control the lights
    double maxTime = dict.getMaxSimTime();
    int currentTime = 0;
    int greenNS = int(dict.getGreenNS());
    int yellowNS = int(dict.getYellowNS());
    int greenEW = int(dict.getGreenEW());
    int yellowEW = int(dict.getYellowEW()); 
   

    //vectors of VehicleBases
    std::vector<VehicleBase*> wb(halfSize * 2 + 2, nullptr);
    std::vector<VehicleBase*> eb(halfSize * 2 + 2, nullptr);
    std::vector<VehicleBase*> sb(halfSize * 2 + 2, nullptr);
    std::vector<VehicleBase*> nb(halfSize * 2 + 2, nullptr);
    
    //vectors of lanes 	
    Lane westbound(halfSize, Direction::west, wb);
    Lane eastbound(halfSize, Direction::east, eb);
    Lane northbound(halfSize, Direction::north, nb);
    Lane southbound(halfSize, Direction::south, sb);
    
    //variable to control drawing everything
    char space;
   
    //controlling the trafic lights
    while(currentTime < maxTime){
       //used to for the for loop
       int x;
	    
       //pointers to lane objects
       Lane *wpntr = &westbound;
       Lane *epntr = &eastbound;
       Lane *npntr = &northbound;
       Lane *spntr = &southbound;
	    
       //controlling the green north and south lights
       //if max simulation time is reached end for loop
       for(x =0; x < greenNS; x++){
        if(currentTime >= maxTime){
          break;
        }
	 else{
	  //set the light colors 
          anim.setLightNorthSouth(LightColor::green);
          anim.setLightEastWest(LightColor::red);
          //move the lanes            
          westbound.moveLane(LightColor::red, npntr, spntr, yellowEW-x);
          eastbound.moveLane(LightColor::red, spntr, npntr, yellowEW-x);
          northbound.moveLane(LightColor::green, epntr, wpntr, yellowNS-x);
          southbound.moveLane(LightColor::green, wpntr, epntr, yellowNS-x);
     
           //create a vehicle based on probability 
          VehicleBase* veh = random.whatVehicle();
          if(veh != nullptr){
             if(veh->getVehicleOriginalDirection() == Direction::south){
               southbound.assignVehicle(veh);
             }
             else if(veh->getVehicleOriginalDirection() == Direction::north){
               northbound.assignVehicle(veh);
             }
             else if(veh->getVehicleOriginalDirection() == Direction::east){
               eastbound.assignVehicle(veh); 
             }
             else{
               westbound.assignVehicle(veh);
             }   
	  }//end of if statement to determine vehicles
          
          //set the vehicles onto the lanes
          anim.setVehiclesWestbound(westbound.getVehicleBase());
          anim.setVehiclesSouthbound(southbound.getVehicleBase());
          anim.setVehiclesNorthbound(northbound.getVehicleBase());
          anim.setVehiclesEastbound(eastbound.getVehicleBase());
	  	 
          //draw by calling Animator class
          anim.draw(currentTime);
		 
          //change each road image with hitting a key 
          cin.get(space);
		 
          //increase currentTime
          currentTime++;
       }
     }//end of individual for loop
      //controlling the yellow north and south light
      //if max simulation time is reached end for loop   
      for(x =0; x < yellowNS; x++){
        if(currentTime >= maxTime){
          break;
        }
        else{
	  //set the light colors 
          anim.setLightNorthSouth(LightColor::yellow);
          anim.setLightEastWest(LightColor::red);
	  //move the lanses 
          westbound.moveLane(LightColor::red, npntr, spntr, yellowEW-x);
          eastbound.moveLane(LightColor::red, spntr, npntr, yellowEW-x);
          northbound.moveLane(LightColor::yellow, epntr, wpntr, yellowNS-x);
          southbound.moveLane(LightColor::yellow, wpntr, epntr, yellowNS-x);
	  	
	  //create a new vehicle based on probability 
          VehicleBase* veh = random.whatVehicle();
          if(veh != nullptr){
             if(veh->getVehicleOriginalDirection() == Direction::south){
               southbound.assignVehicle(veh);
             }
             else if(veh->getVehicleOriginalDirection() == Direction::north){
               northbound.assignVehicle(veh);
             }
             else if(veh->getVehicleOriginalDirection() == Direction::east){
               eastbound.assignVehicle(veh);
             }
             else{
               westbound.assignVehicle(veh);
             }
	  }//end of if statment to determine vehicles 
		
	  //set the vehicles to the lanes 	
          anim.setVehiclesNorthbound(northbound.getVehicleBase());
          anim.setVehiclesWestbound(westbound.getVehicleBase());
          anim.setVehiclesSouthbound(southbound.getVehicleBase());
          anim.setVehiclesEastbound(eastbound.getVehicleBase());
          
	  //draw by calling Animator class	
	  anim.draw(currentTime);
          
          //change each road image with hitting a key
	  cin.get(space);
	
	  //increase currentTime
          currentTime++;
        }//end of else
      }//end of individual for loop
      //controlling the green east and west light
      //if max simulation time is reached end for loop   
      for(x =0; x < greenEW; x++){
        if(currentTime >= maxTime){
          break;
        }
        else{
	  //set the lights 
          anim.setLightNorthSouth(LightColor::red);
          anim.setLightEastWest(LightColor::green);
	  //move the lanes 	
          westbound.moveLane(LightColor::green, npntr, spntr, yellowEW-x);
          eastbound.moveLane(LightColor::green, spntr, npntr, yellowEW-x);
          northbound.moveLane(LightColor::yellow, epntr, wpntr, yellowNS-x);
          southbound.moveLane(LightColor::yellow, wpntr, epntr, yellowNS-x);
	   	
          //create a new vehicle based on probability 
          VehicleBase* veh = random.whatVehicle();
          if(veh != nullptr){ 
             if(veh->getVehicleOriginalDirection() == Direction::south){
               southbound.assignVehicle(veh);
             }
             else if(veh->getVehicleOriginalDirection() == Direction::north){
               northbound.assignVehicle(veh);
	     }
             else if(veh->getVehicleOriginalDirection() == Direction::east){
               eastbound.assignVehicle(veh);
	     }
             else{
               westbound.assignVehicle(veh);
             }//end of else
	   }//end of if statement to determine vehicles 
          //set vehicles to lanes 
          anim.setVehiclesNorthbound(northbound.getVehicleBase());
          anim.setVehiclesWestbound(westbound.getVehicleBase());
          anim.setVehiclesSouthbound(southbound.getVehicleBase());
          anim.setVehiclesEastbound(eastbound.getVehicleBase());
       
	  //draw by calling Animator class	
	  anim.draw(currentTime);
          
          //change each road image with hitting a key
	  cin.get(space);
	
	  //increase currentTime
          currentTime++;
        }//end of else 
      }//end of individual for loop
      //controlling yellow east and west light
      //if max simulation time is reached end for loop	    
      for(x =0; x < yellowEW; x++){
        if(currentTime >= maxTime){
          break;
        }
        else{
	  //set the light colors 
          anim.setLightNorthSouth(LightColor::red);
          anim.setLightEastWest(LightColor::yellow);
	  //move the lanes 	
          westbound.moveLane(LightColor::yellow, npntr, spntr, yellowEW-x);
          eastbound.moveLane(LightColor::yellow, spntr, npntr, yellowEW-x);
          northbound.moveLane(LightColor::red, epntr, wpntr, yellowNS-x);
          southbound.moveLane(LightColor::red, wpntr, epntr, yellowNS-x);
		
	  //create a vehicle based on probability 	
          VehicleBase* veh = random.whatVehicle();
          if(veh != nullptr){
             if(veh->getVehicleOriginalDirection() == Direction::south){
               southbound.assignVehicle(veh);
             }
             else if(veh->getVehicleOriginalDirection() == Direction::north){
               northbound.assignVehicle(veh);
	     }
             else if(veh->getVehicleOriginalDirection() == Direction::east){
               eastbound.assignVehicle(veh);
	     }
             else{
               westbound.assignVehicle(veh);
             }
	  }//end of if statement to determine vehicles 
	
	  //set the vehicles on the lanes	
          anim.setVehiclesNorthbound(northbound.getVehicleBase());
          anim.setVehiclesWestbound(westbound.getVehicleBase());
          anim.setVehiclesSouthbound(southbound.getVehicleBase());
          anim.setVehiclesEastbound(eastbound.getVehicleBase());
         
          //draw by calling Animator class	
	  anim.draw(currentTime);
          
          //change each road image with hitting a key
	  cin.get(space);
	
	  //increase currentTime
          currentTime++;
        }//end of else 
      }//end ofindividual for loop 
    //end of while loop


}//end of simulation 
