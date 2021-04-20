#include <string>
#include <vector>

#include "VehicleBase.h"
#include "Section.h"


class Lane{
  private:
    double numSections;
    Direction laneDirection;

  public:
    vector<Section> lane;
    Lane(int halfsize, Direction direction);
    ~Lane();
    void assignVehicle(VehicleBase vehicle);
    void moveLane(LightColor light);
    void turnRight(VehicleBase vehicle, Lane turnLane);


}

