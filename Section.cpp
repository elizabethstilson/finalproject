#ifndef __SECTION_CPP__
#define __SECTION_CPP__

#include "Section.h"

Section::Section(){
  this->occupied = false;
}

Section::~Section(){}

void Section::makeOccupied(VehicleBase vehicleX, Direction direction){
  this->occupied = true;
  this->vehicleType = vehicleX.getVehicleType();
  this->vehicleID = vehicleX.getVehicleID();
  this->sectionDirection = direction;
  this->turnStatus = vehicleX.getTurningStatus();
  this->vehicle = vehicleX;
}


bool Section::isOccupied(){
  return this->occupied;
}

bool Section::getTurningStatus(){
  return this->turnStatus;
}

VehicleType Section::getVehicleType(){
  return this->vehicleType;
}

Direction Section::getSectionDirection(){
  return this->sectionDirection;
}

int Section::getVehicleID(){
  return this->vehicleID;
}

void Section::unoccupy(){
  occupied = false;
}


#endif
