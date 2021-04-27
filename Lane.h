#ifndef __LANE_H__
#define __LANE_H__


#include <string>
#include <vector>

#include "VehicleBase.h"
#include "Section.h"
#include "Dictionary.h"

class Lane{
  private:
    int numSections;
    int halfsize;
    Direction laneDirection;
    int yellowNS;
    int yellowEW;
    //Section emptySec;
    //Section* temp;    

  public:
    std::vector<VehicleBase*> vehicles; 
    std::vector<Section> lane;
   // std::vector<Section> lane;
    Lane(int halfsize, Direction direction, std::vector<VehicleBase*> vehicles);
    ~Lane();
    void assignVehicle(VehicleBase* vehicle);
    void moveLane(LightColor light, Lane* turnLane, Lane* straightLane, int yellow); // turn lane is first section in intersection straightLane is second
    //void intersection(Section* curLaneSection, Lane* sharedLane, int interSection);
     void turnRight(VehicleBase* vehicle, Lane* turnLane);
      std::vector<Section> getLaneVector();
   // void updateVector(std::vector<Section*> updatedVector);
   // std::string getlaneDirection(); 
    std::string getLaneDirection(); 
    std::vector<VehicleBase*> getVehicleBase();
    bool partialVehicle(VehicleType firstVehicleType, VehicleBase* firstVehicle);
    int getNumSections(VehicleBase* vehicle);
   
};

#endif
