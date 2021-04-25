#ifndef __SECTION_CPP__
#define __SECTION_CPP__

#include "Section.h"

Section::Section(){
  occupied = false;
}

Section::~Section(){}

void Section::makeOccupied(VehicleBase vehicleX, Direction direction){
  occupied = true;
  vehicleType = vehicleX.getVehicleType();
  vehicleID = vehicleX.getVehicleID();
  sectionDirection = direction;
  turnStatus = vehicleX.getTurningStatus();
  vehicle = vehicleX;
}


bool Section::isOccupied(){
  return occupied;
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
