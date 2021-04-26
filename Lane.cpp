#ifndef __LANE_CPP__
#define __LANE_CPP__

#include "Lane.h"
#include <iostream>
#include <string>

// Sets up a lane based on its size and direction
Lane::Lane(int halfsize, Direction direction){
  this->halfsize = halfsize;
  temp = &emptySec;
 // Section newSection;
  numSections = halfsize*2 +2;
  //this->lane(numSections);
  Section* newSection;
  for(int i =0; i < numSections; i++){
   newSection = new Section();

   lane.push_back(newSection);
   laneDirection = direction;

  }
}


Lane::~Lane(){}

// Have a new vehicle enter the lane
void Lane::assignVehicle(VehicleBase vehicle){
  int numSectionsNeeded;

  // Figure out how many sections we need to assign
  if(vehicle.getVehicleType() == VehicleType::car){
    numSectionsNeeded = 2;
  } else if(vehicle.getVehicleType() == VehicleType::suv){
    numSectionsNeeded = 3;
  } else{
    numSectionsNeeded = 4;
  }

  for(int i=0; i <numSectionsNeeded; i++){

  
    // std::cout << "option 1" << std::endl;
    Section temp = *lane.at(i);
    //std::cout << "option 2" << std::endl; 
    if(temp.isOccupied() == false){
    // std::cout << "option 3" << std::endl;
     lane.at(i)->makeOccupied(vehicle, vehicle.getVehicleOriginalDirection());
     //std::cout << "option 4" << std::endl;
   //  std::cout << (&temp) << std::endl;
   }
   std::cout << "option 5" << std::endl;

  }


}

void Lane::moveLane(LightColor light, Lane* turnLane, Lane* straightLane){
   int intersection = halfsize;
  //std::cout << "numsections: " << numSections << std::endl;
  // LightColor::green light moveLane
//  int i = numSections;
  if(light == LightColor::green){
    std::cout << "in green light" << std::endl;
   // int i = numSections;

    for(int i= numSections; i > 0; i--){
      // If a vehicle is at the intersection and is set to turn also the section should be occupied 
      if((i == intersection) && (lane[i]->getTurningStatus() && (lane[i]->isOccupied()==true))){
        
        std::cout << "in if" << std::endl;
        turnRight(lane[i], turnLane);
    
      // if it is the firsst section of the intersection and there is a car in the intersection
      } else if(i == intersection && (lane[i]->isOccupied() == true)){
        std::cout << "made it to first intersection if" << std::endl;
        std::cout << lane[i]->getVehicleID() << std::endl;
        std::cout << lane[i]->isOccupied() << std::endl;
        this->intersection(lane[i], turnLane, i+1);
        std::cout << "post intersection" << std::endl;
        std::cout << lane[i]->isOccupied() << std::endl;
          
      // if it is in the second section of the intersection and there is a car there
      } else if(i == intersection+1 &&(lane[i]->isOccupied() == true)){
        std::cout << "made it to  second intersection if" << std::endl;
        this->intersection(lane[i], straightLane, i-1);
      }
      //when there is a vehicle hanging off
     // else if(   ){
      
      //}
      // Moves the other vehicles forward
      else{
         // 
         if(lane[i] != NULL){
	   Direction curVehDir = lane[i]->getVehicleDirection();
           Direction curLaneDir = laneDirection;
           if(curVehDir == curLaneDir){ 
	      std::string vehDir;
              std::string laneDir; 
               if(curVehDir == (Direction::north)){
                   vehDir = "north";
               } else if(curVehDir == (Direction::west)){
                   vehDir = "west";
               } else if(curVehDir == (Direction::east)){
                   vehDir = "east";
               } else if(curVehDir == (Direction::south)){
                   vehDir = "south";
               }
               if(curLaneDir == (Direction::north)){
                   laneDir = "north";
               } else if(curLaneDir == (Direction::west)){
                   laneDir = "west";
               } else if(curLaneDir ==  (Direction::east)){
                   laneDir = "east";
               } else if(curLaneDir == (Direction::south)){
                   laneDir = "south";
               }
               std::cout << "vehicle direction: " << vehDir <<std::endl;
               std::cout << "lane direction: " << laneDir << std::endl;
            
            } else{
              std::cout << "i: " << i << std::endl;
            }     
               lane[i]= lane[i-1];
            }
         
      }
     // i = i-1;
    }
    VehicleType firstVehicleType = lane[1]->getVehicleType();
    VehicleBase firstVehicle = lane[1]->getVehicle();
    // Because the sections are copied last to first, the first section
    // needs to either be changed to no vehicle or be a part of the vehicles
    // in the section(s) in front of it if only part of the VehicleType::car is in the lane

   
    if((firstVehicleType == VehicleType::car) && (lane[1]->getVehicleID() == lane[2]->getVehicleID())){
      std::cout << "in moveLane/unoccupy" << std::endl;
      lane[0] = temp;
      lane[0]->unoccupy();
    }else if(firstVehicleType == VehicleType::car){
      Section test =*lane[1];
     Section * testptr =  &test;
      test.makeOccupied(firstVehicle, firstVehicle.getVehicleOriginalDirection());
      lane[0] = testptr; 
    }

 
    
    if((firstVehicleType == VehicleType::suv) && (lane[1] == lane[2]) && (lane[2] == lane[3])){
      std::cout << "in moveLane/unoccupy" << std::endl;
      lane[0] =temp;
      lane[0]->unoccupy();
    } else if(firstVehicleType == VehicleType::suv){
      Section test2 = *lane[1];
      Section * testptr2 = &test2;
      test2.makeOccupied(firstVehicle, firstVehicle.getVehicleOriginalDirection());
      lane[0] = testptr2;
    }
   
    if(firstVehicleType == VehicleType::truck && (lane[1] == lane[2]) && (lane[2] == lane [3]) && (lane[3] == lane[4])){
      std::cout << "in moveLane/unoccupy" << std::endl;
      lane[0] =temp;
      lane[0]->unoccupy();
    } else if(firstVehicleType == VehicleType::truck){
      Section test3 = *lane[1];
      Section *testptr3 = &test3;
      test3.makeOccupied(firstVehicle, firstVehicle.getVehicleOriginalDirection());
      lane[0] = testptr3;
    }
  }

  // Elizabeth to do
  // Three separate while loops - for VehicleType::cars that are beyond intersection, in intersection, and before intersection
    else if(light == LightColor::yellow){
       std::cout << "in yellow light" << std::endl;

       int i = numSections;

       //this while loop is for the VehicleType::cars that are already passed the intersection
       //when the light is LightColor::yellow, so they just keep moving. Tests whether turning or not
       while(i > halfsize){

       if((i = intersection) && (lane[i]->getTurningStatus())){
         turnRight(lane[i], turnLane);
       }

       else{
         lane[i]= lane[i-1];
         i = i-1;
       }
       }
    
       //lane[halfsize]->unoccupy();
       //if the vehicle is in the intersection, have it go forward.
     if(lane[halfsize]->isOccupied() || lane[halfsize+1]->isOccupied() || lane[halfsize+2]->isOccupied()){
       VehicleType beforeInterVehicleType = lane[halfsize]->getVehicleType();
	
       if(beforeInterVehicleType == VehicleType::car && lane[halfsize] == lane[halfsize+1]){
         lane[halfsize-1]->unoccupy();
       }
       else if((beforeInterVehicleType == VehicleType::suv) && (lane[halfsize] == lane[halfsize+1]) && (lane[halfsize+1] == lane[halfsize+2])){
         lane[halfsize-1]->unoccupy();
       }
         else if(beforeInterVehicleType == VehicleType::truck && (lane[halfsize] == lane[halfsize+1]) && (lane[halfsize+1] == lane[halfsize+2]) && (lane[halfsize+2] == lane[halfsize+3])){
         lane[halfsize-1]->unoccupy();
       }
     }

     //if the vehicle is just before the intersection, let all through but have the truck stop
     if(lane[halfsize-1]->isOccupied()){
       VehicleType beforeInterVehicleType = lane[halfsize-1]->getVehicleType();
       if(beforeInterVehicleType == VehicleType::car && lane[halfsize-1] == lane[halfsize]){
         lane[halfsize-2]->unoccupy();
       }
       else if(beforeInterVehicleType == VehicleType::suv && (lane[halfsize-1] == lane[halfsize]) && (lane[halfsize] == lane[halfsize+1])){
         lane[halfsize-2]->unoccupy();
       }
     //VehicleType::truck must stop
   //      else if(beforeInterVehicleType == VehicleType::truck && lane[halfsize] == lane[halfsize] == lane[halfsize+1] == lane[halfsize+2]){
 //        lane[halfsize-2]->unoccupy();
      // }

       //if the vehicle is 2 before the intersection, only let car go
       if(lane[halfsize-2]->isOccupied()){
         VehicleType beforeInterVehicleType = lane[halfsize-2]->getVehicleType();
         if(beforeInterVehicleType == VehicleType::car && lane[halfsize-2] == lane[halfsize-1]){
           lane[halfsize-3]->unoccupy();
         }
       //VehicleType::suv must stop
       //  else if(beforeInterVehicleType == VehicleType::suv && lane[halfsize-1] == lane[halfsize] == lane[halfsize+1]){
     //      lane[halfsize-2]->unoccupy();
         }
     }
  }
  // Red light
  else{
    std::cout << "in red" << std::endl; 
    int x = numSections;
    // TO DO *********
    while(x > halfsize){

      lane[x]= lane[x-1];
      x -= 1;

    }
    lane[halfsize]->unoccupy();

    // THIS ALL DEPENDS ON LightColor::yellow LIGHT RULES, MAY NOT HAVE TO WORRY ABOUT PARTIAL
    // VehicleType::carS
    //if(lane[halfsize]->isoccupied()){
      //VehicleType beforeInterVehicleType = lane[halfsize].getVehicleType();

      // Because the sections are copied last to first, the first section
      // needs to either be changed to no vehicle or be a part of the vehicles
      // in the section(s) in front of it if only part of the VehicleType::car is in the lane
      //if(beforeInterVehicleType == VehicleType::car && lane[halfsize] == lane[halfsize+1]){
        //lane[halfsize-1]->unoccupy();
      //} else if(beforeInterVehicleType == VehicleType::suv && lane[halfsize] == lane[halfsize+1] == lane[halfsize+2]){
        //lane[halfsize-1]->unoccupy();
      //} else if(beforeInterVehicleType == VehicleType::truck && lane[halfsize] == lane[halfsize+1] == lane[halfsize+2] == lane[halfsize+3]){
        //lane[halfsize-1]->unoccupy();
      //}
    //}
  }
}

void Lane::turnRight(Section* turningSection, Lane* turnLane){
  turnLane->lane[this->halfsize+2] = turningSection;
}

void Lane::intersection(Section* curLaneSection, Lane* sharedLane, int interSection){
   sharedLane->lane[interSection+1] = curLaneSection;
}


//std::vector<Section> Lane::getLaneVector(){
//}

std::vector<Section*> Lane::getLaneVector(){
  return lane;
}

void Lane::updateVector(std::vector<Section*> updatedVector){
   lane = updatedVector;
}



#endif
