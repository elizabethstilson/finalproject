#ifndef __LANE_CPP__
#define __LANE_CPP__

#include "Lane.h"
#include <iostream>
#include <string>

//Lane copy constructor
Lane::Lane(Lane& copy)
 : numSections{copy.numSections}
 , halfsize{copy.halfsize}
 , yellowEW{copy.yellowEW}
 , yellowNS{copy.yellowNS}
 , vehicles{copy.vehicles}
 , lane{copy.lane}
 , laneDirection{copy.laneDirection} {}

Lane& Lane::operator=(const Lane& copy){
 if(this == &copy){
  return *this;}
 laneDirection =  copy.laneDirection;
 halfsize = copy.halfsize;
 numSections = copy.numSections;
 yellowNS = copy.yellowNS;
 yellowEW = copy.yellowEW;
 vehicles = copy.vehicles;
 lane = copy.lane;
 return *this;
}
// Sets up a lane based on its size and direction
Lane::Lane(int halfsize, Direction direction, std::vector<VehicleBase*> vehicles){
  this->halfsize = halfsize;
  laneDirection = direction;
  numSections = halfsize*2 +2;
  for(int i =0; i < numSections; i++){
   //deciding if section is an intersection
   if(i == halfsize || i == halfsize+1){

    Section newSection = new Section(true);
    lane.push_back(newSection);
   }
// if it isn't an inersection, set it to false
   else{
    Section newSection = new Section(false);
    lane.push_back(newSection);
   }
  }
  this->vehicles = vehicles;
}

//destructor
Lane::~Lane(){}

//gets what direction the lane is going
std::string Lane::getLaneDirection(){
 if(Direction::east == laneDirection){
  return "east";}
 else if(Direction::west == laneDirection){
   return "west";}
 else if(Direction::south == laneDirection){
  return "south";}
 else if(Direction::north == laneDirection){
  return "north";}
 else{
  return "none";}
}


// Have a new vehicle enter the lane, takes in a vehicle and decides
//how many sections the vehicle needs based off of vehicleType
void Lane::assignVehicle(VehicleBase* vehicle){
  int numSectionsNeeded;

  if(vehicle->getVehicleType() == VehicleType::car){
    numSectionsNeeded = 2;
  } else if(vehicle->getVehicleType() == VehicleType::suv){
    numSectionsNeeded = 3;
  } else{
    numSectionsNeeded = 4;
  }

//If the section is not occupied, add the vehicle to the lane
  for(int i=0; i <numSectionsNeeded; i++){
    Section temp = lane.at(i);
    if(temp.isOccupied() == false){
     lane.at(i).makeOccupied();
     vehicles.at(i) = vehicle;
   }
}
}//end assignVehicle

//get a vector for the vehicle bases
std::vector<VehicleBase*> Lane::getVehicleBase(){
  return vehicles;
}

//Moves the lane based off of the color of the light - this method has three
//main if statements dealing with green, yello, and red.
void Lane::moveLane(LightColor light, Lane* turnLane, Lane* straightLane, int yellowLight){
//if light is green, lane moves all sections
  int numIntersection = halfsize;
  if (light == LightColor::green){
     std::cout << "in green light" << std::endl;
      if(lane.at(numSections-1).isOccupied()){
          vehicles.at(numSections-1) = nullptr;
          lane.at(numSections-1).unoccupy();
      }
      for(int i = numSections-2; i >= 0; i--){

        if((i==numIntersection) && (lane[i].isOccupied() == true)  && (vehicles[i]->getTurningStatus())){
         turnRight(vehicles[i], turnLane);
         lane[i].unoccupy();
         vehicles.at(i) = nullptr;
       }
       else if(i == numIntersection && lane[i].isOccupied()){
         vehicles.at(i+1) = vehicles.at(i);
         lane[i+1].makeOccupied();
         lane[i].unoccupy();
         vehicles.at(i) = nullptr;
       }
       else if(i == numIntersection+1 && lane[i].isOccupied()){
         vehicles.at(i+1) = vehicles.at(i);
         lane[i+1].makeOccupied();
         lane[i].unoccupy();
         vehicles.at(i) = nullptr;
       }
       else{
         if(vehicles.at(i) != nullptr){
           vehicles.at(i+1) = vehicles.at(i);
           vehicles.at(i) = nullptr;
           lane[i+1].makeOccupied();
           lane[i].unoccupy();

          }

       }

     } //end of for loop

   }//end of green light

//start of yellow light
  else if(light == LightColor::yellow){
    if(lane.at(numSections-1).isOccupied()){
          vehicles.at(numSections-1) = nullptr;
          lane.at(numSections-1).unoccupy();
      }
      for(int i = numSections-2; i >= 0; i--){
         if(!lane.at(i+1).isOccupied()){
         if(i < halfsize-1 || i >= halfsize){
           if(vehicles.at(i) != nullptr){
             vehicles.at(i+1) = vehicles.at(i);
             vehicles.at(i) = nullptr;
             lane[i+1].makeOccupied();
             lane[i].unoccupy();
           }
          } //end of greater than halfsize
        else{
         if(lane.at(i).isOccupied()){
           int numSectionsNeeded = getNumSections(vehicles.at(i));
           if(vehicles.at(i)->getTurningStatus()){
              numSectionsNeeded += 1;
              if(numSectionsNeeded <= yellowLight){
                turnRight(vehicles[i], turnLane);
                lane[i].unoccupy();
                vehicles.at(i) = nullptr;
                yellowLight--;
              }
             else if(lane.at(i+1).isOccupied() && vehicles.at(i)->getVehicleID() == vehicles.at(i+1)->getVehicleID()){
                turnRight(vehicles[i], turnLane);
                lane[i].unoccupy();
                vehicles.at(i) = nullptr;
                yellowLight--;
            }
            else if(lane.at(halfsize+1).isOccupied() && vehicles.at(i)->getVehicleID() == vehicles.at(halfsize+1)->getVehicleID()){
               vehicles.at(halfsize) = vehicles.at(halfsize-1);
               vehicles.at(i) = nullptr;
               lane[halfsize].makeOccupied();
               lane[i].unoccupy();
               yellowLight--;

            }
           }
           else{
             numSectionsNeeded += 2;
             std::cout << numSectionsNeeded << std::endl;
             if(numSectionsNeeded <= yellowLight){
               vehicles.at(i+1) = vehicles.at(i);
               vehicles.at(i) = nullptr;
               lane[i+1].makeOccupied();
               lane[i].unoccupy();
               yellowLight--;
            }
            else if(lane.at(i+1).isOccupied() && vehicles.at(i)->getVehicleID() == vehicles.at(i+1)->getVehicleID()){
               vehicles.at(i+1) = vehicles.at(i);
               vehicles.at(i) = nullptr;
               lane[i+1].makeOccupied();
               lane[i].unoccupy();
               yellowLight--;

            }
             else if(lane.at(halfsize+1).isOccupied() && vehicles.at(i)->getVehicleID() == vehicles.at(halfsize+1)->getVehicleID()){
               vehicles.at(halfsize) = vehicles.at(i);
               vehicles.at(i) = nullptr;
               lane[halfsize].makeOccupied();
               lane[i].unoccupy();
               yellowLight--;

            }
          }
         }
        }}
     }// end of for loop
  }//end of yellow light
//start of red light
   else {
      if(lane.at(numSections-1).isOccupied()){
          vehicles.at(numSections-1) = nullptr;
          lane.at(numSections-1).unoccupy();
      }
      for(int i = numSections-2; i >= 0; i--){
         if(!lane.at(i+1).isOccupied()){
         if(i < halfsize-1 || i >= halfsize){
           if(vehicles.at(i) != nullptr){
             vehicles.at(i+1) = vehicles.at(i);
             vehicles.at(i) = nullptr;
             lane[i+1].makeOccupied();
             lane[i].unoccupy();
           }
          }}//end of halfsize if
         else{

         }
         } //end of for loop

}
  // for partial vehicle
   if(lane.at(1).isOccupied()){
             VehicleType firstVehicleType = vehicles.at(1)->getVehicleType();
             VehicleBase* firstVehicle = (vehicles.at(1));
             std::cout << partialVehicle(firstVehicleType, firstVehicle);
             if(partialVehicle(firstVehicleType, firstVehicle)){
              vehicles.at(0) = firstVehicle;
              (lane.at(0)).makeOccupied();
             }
            }
}//end of move lane method

//Method to get the number of sections needed for a vehicle
int Lane::getNumSections(VehicleBase* vehicle){
 int numSectionsNeeded;

  if(vehicle->getVehicleType() == VehicleType::car){
    numSectionsNeeded = 2;
  } else if(vehicle->getVehicleType() == VehicleType::suv){
    numSectionsNeeded = 3;
  } else{
    numSectionsNeeded = 4;
  }
 return numSectionsNeeded;
}


//method to check if only a partial vehicle is in the lane
bool Lane::partialVehicle(VehicleType firstVehicleType, VehicleBase* firstVehicle){
    bool partialVeh = false;
    if((firstVehicleType == VehicleType::car) && (vehicles.at(1) != vehicles.at(2))){
       partialVeh = true;
     }
       else if((firstVehicleType == VehicleType::suv) && (vehicles.at(1) != vehicles.at(2)) && (vehicles.at(2) != vehicles.at(3))){
       partialVeh = true;
       }
       else if((firstVehicleType == VehicleType::truck) && (vehicles.at(1) != vehicles.at(2)) && (vehicles.at(2) != vehicles.at(3)) && (vehicles.at(3) != vehicles.at(4)) ){
       partialVeh = true;
       }
     return partialVeh;

} //end of partialVehicle method


//Method to handle turning right
void Lane::turnRight(VehicleBase* vehicle, Lane* turnLane){
  turnLane->vehicles.at(halfsize+1) = vehicle;
  ((turnLane->getLaneVector()).at(halfsize+1)).makeOccupied();
}

//method to get a vector of sections
std::vector<Section> Lane::getLaneVector(){
   return lane;
}



#endif
