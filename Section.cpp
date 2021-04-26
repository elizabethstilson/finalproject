#ifndef __SECTION_CPP__
#define __SECTION_CPP__

#include "Section.h"
#include <iostream>
Section::Section(){
  occupied =false;
}

/*Section::Section(int x){
  //std::cout << "in Section constructor" << std::endl;
  occupied = false;
  int number = x;
 // std::cout << occupied << " in section" << std::endl; 
}*/

Section::Section(Section& copy)
 : occupied{copy.occupied}
 , vehicleType{copy.vehicleType}
 , vehicle{copy.vehicle}
 , sectionDirection{copy.sectionDirection}
 , turnStatus{copy.turnStatus}
 , vehicleID{copy.vehicleID} {}

Section& Section::operator=(const Section& copy){
 if(this == &copy){
  return *this;}
 occupied = copy.occupied;
 vehicleType = copy.vehicleType;
 vehicle = copy.vehicle;
 sectionDirection = copy.sectionDirection;
 turnStatus = copy.turnStatus;
 vehicleID = copy.vehicleID;
 return *this;
}



Section::~Section(){
  //delete this; 
}

bool Section::isOccupied(){
  return occupied;
  //return false;
}

void Section::makeOccupied(VehicleBase vehicleX, Direction direction){
  occupied = true;
  vehicleType = vehicleX.getVehicleType();
  vehicleID = vehicleX.getVehicleID();
  sectionDirection = direction;
  turnStatus = vehicleX.getTurningStatus();
  vehicle = vehicleX;
}

bool Section::getTurningStatus(){
  return turnStatus;
}

VehicleType Section::getVehicleType(){
  return vehicleType;
}

Direction Section::getSectionDirection(){
  return sectionDirection;
}

int Section::getVehicleID(){
  return vehicleID;
}

void Section::unoccupy(){
  occupied = false;
}


#endif
