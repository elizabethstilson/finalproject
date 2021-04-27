#ifndef __SECTION_H__
#define __SECTION_H__

#include <string>
#include <vector>
#include "VehicleBase.h"

class Section{
  private:

    bool occupied;
    bool intersection;

  public:
    Section(bool intersection);
    ~Section();

    bool isOccupied();
    bool ifIntersection();

    void unoccupy();
    void makeOccupied();
};


#endif
