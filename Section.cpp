#ifndef __SECTION_CPP__
#define __SECTION_CPP__

#include "Section.h"

Section::Section(){
  this->occupied = false;
}

Section::~Section(){}

bool Section::isOccupied(){
  return this->occupied;
}

bool Section::getTurningStatus(){
  return this->turnStatus;
}

int Section::getVehicleType(){
  return this->vehicleType;
}

Direction Section::getSectionDirection(){
  return this->sectionDirection;
}

void Section::unoccupy(){
  occupied = false;
}

void Section::makeOccupied(VehicleBase vehicleX, Direction direction){
  this->vehicleType = vehicleX.getVehicleType();
  this->sectionDirection = direction;
  this->occupied = true;
  this->turnStatus = vehicleX.getTurningStatus();
}

#endif
