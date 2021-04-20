#ifndef __SECTION_CPP__
#define __SECTION_CPP__

#include "Section.h"

Section::Section(){
  this->occupied = false;
  vehicleID = 0;
}

Section::~Section(){}

bool Section::isOccupied(){
  return this->occupied;
}

int Section::getVehicleID(){
  return this->vehicleID;
}

Direction Section::getSectionDirection(){
  return this->sectionDirection;
}

void Section::makeOccupied(VehicleBase vehicleX, Direction direction){
  this->vehicleID = vehicleX.getVehicleID();
  this->sectionDirection = direction;
  this->occupied = true;
}

#endif
