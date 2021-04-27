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
    //VehicleType vehicleType;
    //VehicleBase vehicle;
    bool intersection;
   // Direction sectionDirection;
   // Direction vehicleDirection;
   // bool turnStatus;
   // int vehicleID;

  public:
    Section(bool intersection);
    //Section(Direction laneDirection);
   // Section(Section& copy);
   // Section& operator=(const Section& copy);
    ~Section();

    bool isOccupied();
    bool ifIntersection();
   // bool getTurningStatus();
    //VehicleType getVehicleType();
   // Direction getSectionDirection();
   // Direction getVehicleDirection();
   // int getVehicleID();
    //VehicleBase getVehicle();
    void unoccupy();
    void makeOccupied();
};


#endif
