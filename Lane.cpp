#ifndef __LANE_CPP__
#define __LANE_CPP__

#include "Lane.h"

// Sets up a lane based on its size and direction
Lane::Lane(int halfsize, Direction direction){
  this->halfsize = halfsize;
  Section newSection;
  this->numSections = halfsize*2 +2;
  //this->lane(numSections);
  for(int i =0; i < numSections; i++){
    lane.push_back(&newSection);
  }
  this->laneDirection = direction;
}

Lane::~Lane(){};

// Have a new vehicle enter the lane
void Lane::assignVehicle(VehicleBase vehicle){
  int numSectionsNeeded;

  // Figure out how many sections we need to assign
  if(vehicle.getVehicleType() == VehicleType::car){
    numSectionsNeeded = 2;
  } else if(vehicle.getVehicleType() == VehicleType::suv){
    numSectionsNeeded = 3;
  } else{
    numSectionsNeeded = 4;
  }

  for(int i=0; i <numSectionsNeeded; i++){

    // add as many parts of the VehicleType::car to the lane, if the lane is full, no VehicleType::car
    // can be added
    if(lane.at(i)->isOccupied() == false){
        lane.at(i)->makeOccupied(vehicle, vehicle.getVehicleOriginalDirection());
    }

  }


}

void Lane::moveLane(LightColor light, Lane* turnLane){
  int intersection = halfsize;
  // LightColor::green light moveLane
  if(light == LightColor::green){

    int i = numSections;

    while(i > 0){

      // If a vehicle is at the intersection and is set to turn
      if(i = intersection && lane[i]->getTurningStatus()){
        turnRight(lane[i], turnLane);
      }
      // Moves the other vehicles forward
      else{
        lane[i]= lane[i-1];
        i -= 1;
      }

    }
    VehicleType firstVehicleType = lane[1]->getVehicleType();

    // Because the sections are copied last to first, the first section
    // needs to either be changed to no vehicle or be a part of the vehicles
    // in the section(s) in front of it if only part of the VehicleType::car is in the lane
    if(firstVehicleType == VehicleType::car && lane[1] == lane[2]){
      lane[0]->unoccupy();
    } else if((firstVehicleType == VehicleType::suv) && (lane[1] == lane[2]) && (lane[2] == lane[3])){
      lane[0]->unoccupy();
    } else if(firstVehicleType == VehicleType::truck && (lane[1] == lane[2]) && (lane[2] == lane [3]) && (lane[3] == lane[4])){
      lane[0]->unoccupy();
    }
  }

  // Elizabeth to do
  // Three separate while loops - for VehicleType::cars that are beyond intersection, in intersection, and before intersection
   if(light == LightColor::yellow){


       int i = numSections;

       //this while loop is for the VehicleType::cars that are already passed the intersection
       //when the light is LightColor::yellow, so they just keep moving. Tests whether turning or not
       while(i > halfsize){

       if(i = intersection && lane[i]->getTurningStatus()){
         turnRight(lane[i], turnLane);
       }

       else{
         lane[i]= lane[i-1];
         i =i-1;
       }

       }
       lane[halfsize]->unoccupy();

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
    int i = numSections;

    while(i > halfsize){

      lane[i]= lane[i-1];
      i -= 1;

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
