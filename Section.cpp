#ifndef __SECTION_CPP__
#define __SECTION_CPP__

#include "Section.h"
#include <iostream>
Section::Section(bool intersection){
  occupied =false;
  this->intersection = intersection;
}
//Section::Section(Direction laneDirection){
  //occupied = false;
  //sectionDirection = laneDirection;
//}

/*Section::Section(int x){
  //std::cout << "in Section constructor" << std::endl;
  occupied = false;
  int number = x;
 // std::cout << occupied << " in section" << std::endl; 
}*/

/*Section::Section(Section& copy)
 : occupied{copy.occupied}
// , vehicleType{copy.vehicleType}
 , vehicle{copy.vehicle}
// , vehicleDirection{copy.vehicleDirection}
// , sectionDirection{copy.sectionDirection}
// , turnStatus{copy.turnStatus}
// , vehicleID{copy.vehicleID}
   , intersection{copy.intersection} {}

Section& Section::operator=(const Section& copy){
 if(this == &copy){
  return *this;
}

 occupied = copy.occupied;
// vehicleDirection =  copy.vehicleDirection;
// vehicleType = copy.vehicleType;
 vehicle = copy.vehicle;
// sectionDirection = copy.sectionDirection;
// turnStatus = copy.turnStatus;
// vehicleID = copy.vehicleID;
  intersection = copy.intersection;
  return *this;
}*/



Section::~Section(){
  //delete this; 
}

bool Section::isOccupied(){
  return occupied;
}

void Section::makeOccupied(){
  occupied = true;
//  vehicleType = vehicleX.getVehicleType();
//  vehicleID = vehicleX.getVehicleID();
//  sectionDirection = direction;
//  turnStatus = vehicleX.getTurningStatus();
  //vehicle = vehicleX;
 // vehicleDirection = vehicleX.getVehicleOriginalDirection();
}

//bool Section::getTurningStatus(){
 // return turnStatus;
//}

//VehicleType Section::getVehicleType(){
 // return vehicle.getVehicleType();
//}

//Direction Section::getSectionDirection(){
 // return sectionDirection;
//}

//Direction Section::getVehicleDirection(){
 // return vehicleDirection;
//}

//int Section::getVehicleID(){
 // return vehicleID;
//}

//VehicleBase Section::getVehicle(){
 // return vehicle;
//}

void Section::unoccupy(){
  occupied = false;
}


#endif
