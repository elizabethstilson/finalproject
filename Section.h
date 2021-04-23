#ifndef __SECTION_H__
#define __SECTION_H__

#include <string>
#include <vector>
#include "VehicleBase.h"

//Declared in the VehicleBase class
//enum class Direction   {north, south, east, west};

class Section{
  private:

    bool occupied = false;
    VehicleType vehicleType;
    VehicleBase vehicle;
    Direction sectionDirection;
    bool turnStatus;
    int vehicleID;

  public:
    Section();
    ~Section();

    bool isOccupied();
    bool getTurningStatus();
    VehicleType getVehicleType();
    Direction getSectionDirection();
    int getVehicleID();
    void unoccupy();
    void makeOccupied(VehicleBase vehicleX, Direction direction);

};


#endif
