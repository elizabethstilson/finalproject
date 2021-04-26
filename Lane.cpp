#ifndef __LANE_CPP__
#define __LANE_CPP__

#include "Lane.h"
#include <iostream>

// Sets up a lane based on its size and direction
Lane::Lane(int halfsize, Direction direction){
  this->halfsize = halfsize;
  temp = &emptySec;
  this->numSections = halfsize*2 +2;
  //this->lane(numSections);
  Section* newSection = new Section[numSections];
  for(int i =0; i < numSections; i++){
    //newSection = new Section(i);
   // std::cout << &newSection[i] << std::endl;
    lane.push_back(&newSection[i]);
   // std::cout << (*lane.at(i)).isOccupied() << " in Lane" << std::endl;
  }
  this->laneDirection = direction;
}

Lane::~Lane(){
  //for(int x = 0; x <lane.size(); x++){
   // delete lane[x];
   // this will give a segmentation fault error
  }

// Have a new vehicle enter the lane
void Lane::assignVehicle(VehicleBase vehicle){
  int numSectionsNeeded;

  // Figure out how many sections we need to assign
  if(vehicle.getVehicleType() == VehicleType::car){
    numSectionsNeeded = 2;
    std::cout << "car" << std::endl;
  } else if(vehicle.getVehicleType() == VehicleType::suv){
    numSectionsNeeded = 3;
    std::cout << "suv" << std::endl;
  } else{
    numSectionsNeeded = 4;
    std::cout << "truck" << std::endl;
  }

  for(int i=0; i <numSectionsNeeded; i++){

    // add as many parts of the VehicleType::car to the lane, if the lane is full, no VehicleType::car
    // can be added
    std::cout << (*lane.at(i)).isOccupied() << std::endl;
    //Section temp = *lane.at(i);
    if((*lane.at(i)).isOccupied() == false){
       (*lane.at(i)).makeOccupied(vehicle, vehicle.getVehicleOriginalDirection());
       std::cout << "1" << std::endl; 
    }
    std::cout << "c" << std::endl;
  }


}

void Lane::moveLane(LightColor light, Lane* turnLane){
  int intersection = halfsize;
  //std::cout << "numsections: " << numSections << std::endl;
  // LightColor::green light moveLane
//  int i = numSections;
  if(light == LightColor::green){
    std::cout << "in green light" << std::endl;
    int i = numSections;
    while(i > 0){
      // If a vehicle is at the intersection and is set to turn also the section should be occupied 
      if((i == intersection) && (lane[i]->getTurningStatus() && (lane[i]->isOccupied()==true))){
        std::cout << "in if" << std::endl;
        turnRight(lane[i], turnLane);
      }
      //when there is a vehicle hanging off
     // else if(   ){
      
      //}
      // Moves the other vehicles forward
      else{
        Section temp(*lane[i-1]);
        lane[i] = &temp;

       /* temp = lane[i-1];
        lane[i] = temp;
        lane[i]= lane[i-1];*/
       // i = i-1;
      }
      i = i-1;
    }
    VehicleType firstVehicleType = lane[1]->getVehicleType();

    // Because the sections are copied last to first, the first section
    // needs to either be changed to no vehicle or be a part of the vehicles
    // in the section(s) in front of it if only part of the VehicleType::car is in the lane
      //Section* temp;
      if((firstVehicleType == VehicleType::car) && (lane[1]->getVehicleID() == lane[2]->getVehicleID())){
      std::cout << "in moveLane/unoccupy" << std::endl;
      lane[0] = temp;
      lane[0]->unoccupy();
    } else if((firstVehicleType == VehicleType::suv) && (lane[1] == lane[2]) && (lane[2] == lane[3])){
      std::cout << "in moveLane/unoccupy" << std::endl;
      lane[0] = temp;
      lane[0]->unoccupy();
    } else if(firstVehicleType == VehicleType::truck && (lane[1] == lane[2]) && (lane[2] == lane [3]) && (lane[3] == lane[4])){
      std::cout << "in moveLane/unoccupy" << std::endl;
      lane[0] = temp;
      lane[0]->unoccupy();
    }
     //delete temp;
  }

  // Elizabeth to do
  // Three separate while loops - for VehicleType::cars that are beyond intersection, in intersection, and before intersection
   else if(light == LightColor::yellow){
       std::cout << "in yellow light" << std::endl; 

       int i = numSections;

       //this while loop is for the VehicleType::cars that are already passed the intersection
       //when the light is LightColor::yellow, so they just keep moving. Tests whether turning or not
       while(i > halfsize){

       if((i == intersection) && (lane[i]->getTurningStatus())){
         turnRight(lane[i], turnLane);
       }

       else{
        /*Section* temp1;
        temp1 = lane[i-1];
        lane[i] = temp1;*/
        lane[i]= lane[i-1];
        i =i-1;
       }
       i = i-1;
       }
       lane[halfsize]->unoccupy();
      /* 
       VehicleType firstVehicleType = lane[1]->getVehicleType();
       Section* temp2;
       
       if((firstVehicleType == VehicleType::car) && (lane[1]->getVehicleID() == lane[2]->getVehicleID())){
        std::cout << "in moveLane/unoccupy" << std::endl;
        lane[0] = temp2;
        lane[0]->unoccupy();
    } else if((firstVehicleType == VehicleType::suv) && (lane[1] == lane[2]) && (lane[2] == lane[3])){
        lane[0] = temp2;
        lane[0]->unoccupy();
    } else if(firstVehicleType == VehicleType::truck && (lane[1] == lane[2]) && (lane[2] == lane [3]) && (lane[3] == lane[4])){
        lane[0] = temp2;
      	lane[0]->unoccupy();}*/
       
    if(lane[halfsize]->isOccupied() || lane[halfsize+2]->isOccupied()){
       VehicleType beforeInterVehicleType = lane[halfsize]->getVehicleType();

       if(beforeInterVehicleType == VehicleType::car && lane[halfsize] == lane[halfsize+1]){
         lane[halfsize-1]->unoccupy();
       }
       else if((beforeInterVehicleType == VehicleType::suv) && (lane[halfsize] == lane[halfsize+1]) && (lane[halfsize+1] == lane[halfsize+2])){
         lane[halfsize-1]->unoccupy();
       }
         else if(beforeInterVehicleType == VehicleType::truck && (lane[halfsize] == lane[halfsize+1]) && (lane[halfsize+1] == lane[halfsize+2]) && (lane[halfsize+2] == lane[halfsize+3])){
         lane[halfsize-1]->unoccupy();
       }
     }
     if(lane[halfsize-1]->isOccupied()){
       VehicleType beforeInterVehicleType = lane[halfsize-1]->getVehicleType();
       if(beforeInterVehicleType == VehicleType::car && lane[halfsize-1] == lane[halfsize]){
         lane[halfsize-2]->unoccupy();
       }
       else if(beforeInterVehicleType == VehicleType::suv && (lane[halfsize-1] == lane[halfsize]) && (lane[halfsize] == lane[halfsize+1])){
         lane[halfsize-2]->unoccupy();
       }
     //VehicleType::truck must stop
   //      else if(beforeInterVehicleType == VehicleType::truck && lane[halfsize] == lane[halfsize] == lane[halfsize+1] == lane[halfsize+2]){
 //        lane[halfsize-2]->unoccupy();
       }
       if(lane[halfsize-2]->isOccupied()){
         VehicleType beforeInterVehicleType = lane[halfsize-2]->getVehicleType();
         if(beforeInterVehicleType == VehicleType::car && lane[halfsize-2] == lane[halfsize-1]){
           lane[halfsize-3]->unoccupy();
         }
       //VehicleType::suv must stop
       //  else if(beforeInterVehicleType == VehicleType::suv && lane[halfsize-1] == lane[halfsize] == lane[halfsize+1]){
     //      lane[halfsize-2]->unoccupy();
         }
     }


  // Red light
  else{
    std::cout << "in red" << std::endl; 
    int x = numSections;

    while(x > halfsize){

      lane[x]= lane[x-1];
      x -= 1;

    }
    lane[halfsize]->unoccupy();

    // THIS ALL DEPENDS ON LightColor::yellow LIGHT RULES, MAY NOT HAVE TO WORRY ABOUT PARTIAL
    // VehicleType::carS
    //if(lane[halfsize]->isoccupied()){
      //VehicleType beforeInterVehicleType = lane[halfsize].getVehicleType();

      // Because the sections are copied last to first, the first section
      // needs to either be changed to no vehicle or be a part of the vehicles
      // in the section(s) in front of it if only part of the VehicleType::car is in the lane
      //if(beforeInterVehicleType == VehicleType::car && lane[halfsize] == lane[halfsize+1]){
        //lane[halfsize-1]->unoccupy();
      //} else if(beforeInterVehicleType == VehicleType::suv && lane[halfsize] == lane[halfsize+1] == lane[halfsize+2]){
        //lane[halfsize-1]->unoccupy();
      //} else if(beforeInterVehicleType == VehicleType::truck && lane[halfsize] == lane[halfsize+1] == lane[halfsize+2] == lane[halfsize+3]){
        //lane[halfsize-1]->unoccupy();
      //}
    //}
  }
}

void Lane::turnRight(Section* turningSection, Lane* turnLane){
  turnLane->lane[this->halfsize+2] = turningSection;

}

std::vector<Section*> Lane::getLaneVector(){
  return this-> lane;
}

#endif
