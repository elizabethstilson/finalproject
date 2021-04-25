#ifndef __SECTION_CPP__
#define __SECTION_CPP__

#include "Section.h"
#include <iostream>
Section::Section(){
  occupied =false;
}

Section::Section(int x){
  std::cout << "in Section constructor" << std::endl;
  occupied = false;
  int number = x;
  std::cout << occupied << " in section" << std::endl; 
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

int Section::getNumber(){
  return number;
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
