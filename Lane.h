#ifndef __LANE_H__
#define __LANE_H__


#include <string>
#include <vector>

#include "VehicleBase.h"
#include "Section.h"


class Lane{
  private:
    int numSections;
    int halfsize;
    Direction laneDirection;
    Section emptySec;
    Section* temp;

  public:
    std::vector<Section*> lane;
   // std::vector<Section> lane;
    Lane(int halfsize, Direction direction);
    ~Lane();
    void assignVehicle(VehicleBase vehicle);
    void moveLane(LightColor light, Lane* turnLane, Lane* straightLane); // turn lane is first section in intersection straightLane is second
    void intersection(Section* curLaneSection, Lane* sharedLane, int interSection);
    void turnRight(Section* turningSection, Lane* turnLane);
    std::vector<Section*> getLaneVector();
   // std::vector<Section> getLaneVector();
    void updateVector(std::vector<Section*> updatedVector);
   
};

#endif
