#ifndef __LANE_CPP__
#define __LANE_CPP__

#include "Lane.h"

Lane::Lane(int numSections, Direction direction){
  Section newSection;
  for(int i =0; i < numSections; i++){
    newSection = new Section();
    lane.pushback(newSection);
  }
  this->laneDirection = direction;
}

Lane::~Lane();

// Have a new vehicle enter the lane
void Lane::assignVehicle(VehicleBase vehicle){
  int numSectionsNeeded;

  // Figure out how many sections we need to assign
  if(vehicle.getVehicleType() == car){
    numSectionsNeeded = 2;
  } else if(vehicle.getVehicleType() == suv){
    numSectionsNeeded = 3;
  } else{
    numSectionsNeeded = 4;
  }

  for(int i=0; i <numSectionsNeeded; i++){

    // add as many parts of the car to the lane, if the lane is full, no Car
    // can be added
    if(lane.at(i).isOccupied() == false){
        lane.at(i).makeOccupied(vehicle, vehicle.getVehicleOriginalDirection);
    }

  }


}

void Lane::moveLane(LightColor light){
  if(light == green){
    
    int i = numSections;
    
    while(i > 0){
      
      lane[i]= lane[i-1];
      i -= 1;
      
    }
    VehicleType firstVehicleType = lane[1].getVehicleType();

    //Because the sections are copied last to first, the first section 
    // needs to either be changed to no vehicle or be a part of the vehicles
    // in the section(s) in front of it if only part of the car is in the lane
    if(firstVehicleType == car && lane[1] == lane[2]){
      lane[0].unoccupy();
    } else if(firstVehicleType == SUV && lane[1] == lane[2] == lane[3]){
      lane[0].unoccupy();
    } else if(firstVehicleType == truck && lane[1] == lane[2] == lane[3] == lane[4]){
      lane[0].unoccupy();
    }
  }
}

void Lane::turnRight(VehicleBase vehicle, Lane turnLane){

}
