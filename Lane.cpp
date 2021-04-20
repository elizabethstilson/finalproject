#ifndef __LANE_CPP__
#define __LANE_CPP__

#include "Lane.h"

// Sets up a lane based on its size and direction
Lane::Lane(int halfsize, Direction direction){
  this->numSectionsBeforeIntersection = halfsize;
  Section newSection;
  this->numSections = halfsize*2 +2;
  lane(numSections, nullptr);
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

void Lane::moveLane(LightColor light, Lane turnLane){
  int intersection = halfsize;
  // Green light moveLane
  if(light == green){

    int i = numSections;

    while(i > 0){

      // If a vehicle is at the intersection and is set to turn
      if(i = intersection && lane[i].getTurningStatus){
        turnRight(lane[i], turnLane);
      }
      // Moves the other vehicles forward
      else{
        lane[i]= lane[i-1];
        i -= 1;
      }

    }
    VehicleType firstVehicleType = lane[1].getVehicleType();

    // Because the sections are copied last to first, the first section
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

  // Three separate while loops - for cars that are beyond intersection, in intersection, and before intersection
  if(light == yellow){
      

      int i = numsections;

      //this while loop is for the cars that are already passed the intersection
      //when the light is yellow, so they just keep moving. Tests whether turning or not
      while(i > halfsize){

      if(i = intersection && lane[i].getTurningStatus){
        turnRight(lane[i], turnLane);
      }

      else{
        lane[i]= lane[i-1];
        i =i-1;
      }

      }
      lane[halfsize].unoccupy();

    if(lane[halfsize].isOccupied() ||  || lane[halfsize+2].isOccupied()){
      VehicleType interVehicleType = lane[halfSize].getvehicleType();

      if(interVehicleType == car && lane[halfsize] == lane[halfsize+1]){
        lane[halfsize-1].unoccupy();
      }
      else if(interVehicleType == SUV && lane[halfsize] == lane[halfsize+1] == lane[halfsize+2]){
        lane[halfsize-1].unoccupy();
      }
        else if(interVehicleType == truck && lane[halfsize] == lane[halfsize+1] == lane[halfsize+2] == lane[halfsize+3]){
        lane[halfsize-1].unoccupy();
      }
    }
    if(lane[halfsize-1].isOccupied()){
      VehicleType beforeinterVehicleType = lane[halfSize-1].getvehicleType();
      if(interVehicleType == car && lane[halfsize-1] == lane[halfsize]){
        lane[halfsize-2].unoccupy();
      }
      else if(interVehicleType == SUV && lane[halfsize-1] == lane[halfsize] == lane[halfsize+1]){
        lane[halfsize-2].unoccupy();
      }
    //truck must stop
  //      else if(interVehicleType == truck && lane[halfsize] == lane[halfsize] == lane[halfsize+1] == lane[halfsize+2]){
//        lane[halfsize-2].unoccupy();
      }
      if(lane[halfsize-2].isOccupied()){
        VehicleType beforeinterVehicleType = lane[halfSize-2].getvehicleType();
        if(interVehicleType == car && lane[halfsize-2] == lane[halfsize-1]){
          lane[halfsize-3].unoccupy();
        }
      //SUV must stop
      //  else if(interVehicleType == SUV && lane[halfsize-1] == lane[halfsize] == lane[halfsize+1]){
    //      lane[halfsize-2].unoccupy();
        }
    }

  // Red light
  else{
    int i = numSections;

    while(i > halfsize){

      lane[i]= lane[i-1];
      i -= 1;

    }
    lane[halfsize].unoccupy();

    // THIS ALL DEPENDS ON YELLOW LIGHT RULES, MAY NOT HAVE TO WORRY ABOUT PARTIAL
    // CARS
    //if(lane[halfsize].isOccupied()){
      //VehicleType interVehicleType = lane[halfSize].getVehicleType();

      // Because the sections are copied last to first, the first section
      // needs to either be changed to no vehicle or be a part of the vehicles
      // in the section(s) in front of it if only part of the car is in the lane
      //if(interVehicleType == car && lane[halfsize] == lane[halfsize+1]){
        //lane[halfsize-1].unoccupy();
      //} else if(interVehicleType == SUV && lane[halfsize] == lane[halfsize+1] == lane[halfsize+2]){
        //lane[halfsize-1].unoccupy();
      //} else if(interVehicleType == truck && lane[halfsize] == lane[halfsize+1] == lane[halfsize+2] == lane[halfsize+3]){
        //lane[halfsize-1].unoccupy();
      //}
    //}
  }
}

void Lane::turnRight(Section turningSection, Lane turnLane){
  turnLane[halfsize+2] = turningSection;

}
