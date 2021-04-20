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

void Lane::moveLane(){

}

void Lane::turnRight(VehicleBase vehicle, Lane turnLane){

}
