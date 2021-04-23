#include <string>
#include <vector>

#include "VehicleBase.h"
#include "Section.h"


class Lane{
  private:
    int numSections;
    int halfsize;
    Direction laneDirection;

  public:
    std::vector<Section*> lane;
    Lane(int halfsize, Direction direction);
    ~Lane();
    void assignVehicle(VehicleBase vehicle);
    void moveLane(LightColor light, Lane* turnLane);
    void turnRight(Section* turningSection, Lane* turnLane);
    std::vector<Section*> getLaneVector();


};
