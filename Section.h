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
    VehicleType vehicleType;
    Direction sectionDirection;

  public:
    Section();
    ~Section();

    bool isOccupied();
    VehicleType getVehicleType();
    Direction getSectionDirection();
    void unoccupy();
    void makeOccupied(VehicleBase vehicleX, Direction direction);

};


#endif
