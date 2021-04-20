#ifndef __SECTION_H__
#define __SECTION_H__

#include <string>
#include <vector>
#include "VehicleBase.h"

//Declared in the VehicleBase class
//enum class Direction   {north, south, east, west};

class Section{
  private:

    bool occupied;
    int vehicleID;
    Direction sectionDirection;

  public:
    Section();
    ~Section();

    bool isOccupied();
    int getVehicleID();
    Direction getSectionDirection();
    void makeOccupied(VehicleBase vehicleX, Direction direction);

};


#endif
