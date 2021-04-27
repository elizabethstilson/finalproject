#ifndef __LANE_CPP__
#define __LANE_CPP__

#include "Lane.h"
#include <iostream>
#include <string>

// Sets up a lane based on its size and direction
Lane::Lane(int halfsize, Direction direction, std::vector<VehicleBase*> vehicles){
  this->halfsize = halfsize;
  laneDirection = direction;
  numSections = halfsize*2 +2;
  for(int i =0; i < numSections; i++){
   //deciding if section is an intersection 
   if(i == halfsize || i == halfsize+1){
    
    Section newSection = new Section(true);
    lane.push_back(newSection);
   }
// if it isn't an inersection, set it to false
   else{
    Section newSection = new Section(false);
    lane.push_back(newSection);
   }
  }
  this->vehicles = vehicles;
}


Lane::~Lane(){}

std::string Lane::getLaneDirection(){
 if(Direction::east == laneDirection){
  return "east";}
 else if(Direction::west == laneDirection){
   return "west";}
 else if(Direction::south == laneDirection){
  return "south";}
 else if(Direction::north == laneDirection){
  return "north";}
 else{
  return "none";} 
} 


/*std::string Lane::getlaneDirection(){
          int tracker = 0;
         std::string vehDir;
         std::string laneDir;
         for(int x = numSections-1; x >= 0; x--){    
           Direction curVehDir = lane[x]->getVehicleDirection();
           Direction curLaneDir = laneDirection;
           if(curVehDir == curLaneDir){
            //  std::string vehDir;
             // std::string laneDir;
               if(curVehDir == (Direction::west)){
                   vehDir = "west";
               } else if(curVehDir == (Direction::north)){
                   vehDir = "north";
               } else if(curVehDir == (Direction::east)){
                   vehDir = "east";
               } else{
                   vehDir = "south";
               }
               if(curLaneDir == (Direction::north)){
                   laneDir = "north";
                   //tracker++;
               } else if(curLaneDir == (Direction::west)){
                   laneDir = "west";
                  // tracker++;
               } else if(curLaneDir ==  (Direction::east)){
                   laneDir = "east";
                  // tracker++;
                   laneDir = "south";
                  // tracker++;
               }
               tracker++;
               std::cout << "vehicle direction: " << vehDir <<std::endl;
               std::cout << "lane direction: " << laneDir << std::endl;
            }
           }
               std::cout << tracker << " : how many sections" << std::endl;
               return laneDir;
} */

// Have a new vehicle enter the lane
void Lane::assignVehicle(VehicleBase* vehicle){
  int numSectionsNeeded;

  if(vehicle->getVehicleType() == VehicleType::car){
    numSectionsNeeded = 2;
  } else if(vehicle->getVehicleType() == VehicleType::suv){
    numSectionsNeeded = 3;
  } else{
    numSectionsNeeded = 4;
  }

  for(int i=0; i <numSectionsNeeded; i++){

  
    // std::cout << "option 1" << std::endl;
    Section temp = lane.at(i);
    //std::cout << "option 2" << std::endl; 
    if(temp.isOccupied() == false){
    // std::cout << "option 3" << std::endl;
     lane.at(i).makeOccupied();
     
     vehicles.at(i) = vehicle; 
   //std::cout << "option 4" << std::endl;
   //  std::cout << (&temp) << std::endl;
   }
   std::cout << "option 5" << std::endl;
  /* Direction curVehDir = lane[i]->getVehicleDirection();
           Direction curLaneDir = laneDirection;
           if(curVehDir == curLaneDir){
              std::string vehDir;
              std::string laneDir;
               if(curVehDir == (Direction::west)){
                   vehDir = "west";
               } else if(curVehDir == (Direction::north)){
                   vehDir = "north";
               } else if(curVehDir == (Direction::east)){
                   vehDir = "east";
               } else{
                   vehDir = "south";
               }
               if(curLaneDir == (Direction::north)){
                   laneDir = "north";
               } else if(curLaneDir == (Direction::west)){
                   laneDir = "west";
               } else if(curLaneDir ==  (Direction::east)){
                   laneDir = "east";
               } else{
                   laneDir = "south";
               }
               std::cout << "vehicle direction: " << vehDir <<std::endl;
               std::cout << "lane direction: " << laneDir << std::endl;

            }*/
  }


}

//a get vector for the vehicle bases
std::vector<VehicleBase*> Lane::getVehicleBase(){
  return vehicles;
}

void Lane::moveLane(LightColor light, Lane* turnLane, Lane* straightLane, int yellowLight){
//if light is green 
  int numIntersection = halfsize;
  if (light == LightColor::green){
     std::cout << "in green light" << std::endl;
      if(lane.at(numSections-1).isOccupied()){
          vehicles.at(numSections-1) = nullptr;
          lane.at(numSections-1).unoccupy();
      }
      for(int i = numSections-2; i >= 0; i--){
        
        if((i==numIntersection) && (lane[i].isOccupied() == true)  && (vehicles[i]->getTurningStatus())){
         turnRight(vehicles[i], turnLane);   
         lane[i].unoccupy();
         vehicles.at(i) = nullptr;
       }
       else if(i == numIntersection && lane[i].isOccupied()){
         vehicles.at(i+1) = vehicles.at(i);
         lane[i+1].makeOccupied();
         lane[i].unoccupy();
         vehicles.at(i) = nullptr;
       }
       else if(i == numIntersection+1 && lane[i].isOccupied()){
         vehicles.at(i+1) = vehicles.at(i);
         lane[i+1].makeOccupied();
         lane[i].unoccupy();
         vehicles.at(i) = nullptr;
       }     
       else{
         if(vehicles.at(i) != nullptr){
           std::cout << "in where it is suppose to be" << std::endl;
           vehicles.at(i+1) = vehicles.at(i);
           vehicles.at(i) = nullptr;
           lane[i+1].makeOccupied();
           lane[i].unoccupy();
         
          }

       }
     
     } //end of for loop 
     std::cout << "after for loop" << std::endl;
     //to handle partial cars entering
     std::cout << "occupy? : " << (lane.at(1)).isOccupied() << std::endl; 
    /* if(lane.at(1).isOccupied()){
       VehicleType firstVehicleType = vehicles.at(1)->getVehicleType();
       VehicleBase* firstVehicle = (vehicles.at(1));
       std::cout << "before if" << std::endl;
        if(partialVehicle(firstVehicleType, firstVehicle)){
         vehicles.at(0) = firstVehicle;
         (lane.at(0)).makeOccupied();
         std::cout << "after if in partial part" << std::endl; 
       } 
      }*///end of if statment 
   }//end of green light

//start of yellow light
  else if(light == LightColor::yellow){
    if(lane.at(numSections-1).isOccupied()){
          vehicles.at(numSections-1) = nullptr;
          lane.at(numSections-1).unoccupy();
      }
      std::cout << "halfsize: " << halfsize << std::endl;
      for(int i = numSections-2; i >= 0; i--){
         if(!lane.at(i+1).isOccupied()){
         std::cout << "i : " << i << std::endl;
         if(i < halfsize-1 || i >= halfsize){
           if(vehicles.at(i) != nullptr){
             std::cout << "in where it is suppose to be 2" << std::endl;
             vehicles.at(i+1) = vehicles.at(i);
             vehicles.at(i) = nullptr;
             lane[i+1].makeOccupied();
             lane[i].unoccupy();
           }  
          /* if(lane.at(1).isOccupied()){
             VehicleType firstVehicleType = vehicles.at(1)->getVehicleType();
             VehicleBase* firstVehicle = (vehicles.at(1));
             std::cout << "before if" << std::endl;
             if(partialVehicle(firstVehicleType, firstVehicle)){
              vehicles.at(0) = firstVehicle;
              (lane.at(0)).makeOccupied();
              std::cout << "after if in partial part" << std::endl;
             }
            }*/
          } //end of greater than halfsize
        else{
           std::cout << "enters else" << std::endl;
         if(lane.at(i).isOccupied()){ 
           int numSectionsNeeded = getNumSections(vehicles.at(i));
           if(vehicles.at(i)->getTurningStatus()){
              numSectionsNeeded += 1;
              if(numSectionsNeeded <= yellowLight){
                turnRight(vehicles[i], turnLane);
                lane[i].unoccupy();
                vehicles.at(i) = nullptr;
                yellowLight--;
              }
             else if(lane.at(i+1).isOccupied() && vehicles.at(i)->getVehicleID() == vehicles.at(i+1)->getVehicleID()){
                turnRight(vehicles[i], turnLane);
                lane[i].unoccupy();
                vehicles.at(i) = nullptr;
                yellowLight--;
            }
            else if(lane.at(halfsize+1).isOccupied() && vehicles.at(i)->getVehicleID() == vehicles.at(halfsize+1)->getVehicleID()){
               vehicles.at(halfsize) = vehicles.at(halfsize-1);
               vehicles.at(i) = nullptr;
               lane[halfsize].makeOccupied();
               lane[i].unoccupy();
               yellowLight--;

            }  
           }
           else{
             std::cout << "enters other else" << std::endl;
             numSectionsNeeded += 2;
             std::cout << numSectionsNeeded << std::endl;
             if(numSectionsNeeded <= yellowLight){
               vehicles.at(i+1) = vehicles.at(i);
               vehicles.at(i) = nullptr;
               lane[i+1].makeOccupied();
               lane[i].unoccupy();
               yellowLight--;
            }
            else if(lane.at(i+1).isOccupied() && vehicles.at(i)->getVehicleID() == vehicles.at(i+1)->getVehicleID()){
               vehicles.at(i+1) = vehicles.at(i);
               vehicles.at(i) = nullptr;
               lane[i+1].makeOccupied();
               lane[i].unoccupy();
               yellowLight--;

            }
             else if(lane.at(halfsize+1).isOccupied() && vehicles.at(i)->getVehicleID() == vehicles.at(halfsize+1)->getVehicleID()){
               vehicles.at(halfsize) = vehicles.at(i);
               vehicles.at(i) = nullptr;
               lane[halfsize].makeOccupied();
               lane[i].unoccupy();
               yellowLight--;

            }
          }
         }
        }}
     }// end of for loop







  }
//start of red light 
   else {
      if(lane.at(numSections-1).isOccupied()){
          vehicles.at(numSections-1) = nullptr;
          lane.at(numSections-1).unoccupy();
      }
      for(int i = numSections-2; i >= 0; i--){
         if(!lane.at(i+1).isOccupied()){
         if(i < halfsize-1 || i >= halfsize){
           if(vehicles.at(i) != nullptr){
             std::cout << "in where it is suppose to be 2" << std::endl;
            // if(i+1 != numSections)
             vehicles.at(i+1) = vehicles.at(i);
             vehicles.at(i) = nullptr;
             lane[i+1].makeOccupied();
             lane[i].unoccupy();
           }
         /*  if(lane.at(1).isOccupied()){
             VehicleType firstVehicleType = vehicles.at(1)->getVehicleType();
             VehicleBase* firstVehicle = (vehicles.at(1));
             std::cout << "before if" << std::endl;
             if(partialVehicle(firstVehicleType, firstVehicle)){
              vehicles.at(0) = firstVehicle;
              (lane.at(0)).makeOccupied();
              std::cout << "after if in partial part" << std::endl;
             }
            }*/
          }}//end of halfsize if
         else{
           


         } 
         } //end of for loop




}
 
  // for partial vehicle
   if(lane.at(1).isOccupied()){
             VehicleType firstVehicleType = vehicles.at(1)->getVehicleType();
             VehicleBase* firstVehicle = (vehicles.at(1));
             std::cout << "********before if********" << std::endl;
             std::cout << partialVehicle(firstVehicleType, firstVehicle);
             if(partialVehicle(firstVehicleType, firstVehicle)){
              vehicles.at(0) = firstVehicle;
              (lane.at(0)).makeOccupied();
              std::cout << "after if in partial part" << std::endl;
             }
            } 


std::cout << "end of method" << std::endl;
}//end of move lane method

int Lane::getNumSections(VehicleBase* vehicle){
 int numSectionsNeeded;

  if(vehicle->getVehicleType() == VehicleType::car){
    numSectionsNeeded = 2;
  } else if(vehicle->getVehicleType() == VehicleType::suv){
    numSectionsNeeded = 3;
  } else{
    numSectionsNeeded = 4;
  } 
 return numSectionsNeeded;
}




bool Lane::partialVehicle(VehicleType firstVehicleType, VehicleBase* firstVehicle){
    bool partialVeh = false;
    if((firstVehicleType == VehicleType::car) && (vehicles.at(1) != vehicles.at(2))){
       partialVeh = true;
     }
       else if((firstVehicleType == VehicleType::suv) && (vehicles.at(1) != vehicles.at(2)) && (vehicles.at(2) != vehicles.at(3))){
       partialVeh = true; 
       }
       else if((firstVehicleType == VehicleType::truck) && (vehicles.at(1) != vehicles.at(2)) && (vehicles.at(2) != vehicles.at(3)) && (vehicles.at(3) != vehicles.at(4)) ){
       partialVeh = true;
       }
     return partialVeh;

} //end of partialVehicle method










/*void Lane::moveLane(LightColor light, Lane* turnLane, Lane* straightLane){
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
               if(curVehDir == (Direction::west)){
                   vehDir = "west";
               } else if(curVehDir == (Direction::north)){
                   vehDir = "north";
               } else if(curVehDir == (Direction::east)){
                   vehDir = "east";
               } else{
                   vehDir = "south";
               }
               if(curLaneDir == (Direction::north)){
                   laneDir = "north";
               } else if(curLaneDir == (Direction::west)){
                   laneDir = "west";
               } else if(curLaneDir ==  (Direction::east)){
                   laneDir = "east";
               } else{
                   laneDir = "south";
               }
               std::cout << "vehicle direction: " << vehDir <<std::endl;
               std::cout << "lane direction: " << laneDir << std::endl;
            
            } //else{
             // std::cout << "i: " << i << std::endl;
           // }     
               lane[i]= lane[i-1];
            }
	    else{
              std::cout << "i: " << i << std::endl;
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
       //
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
*/
void Lane::turnRight(VehicleBase* vehicle, Lane* turnLane){
  turnLane->vehicles.at(halfsize+1) = vehicle;
  ((turnLane->getLaneVector()).at(halfsize+1)).makeOccupied();
}
/*
void Lane::intersection(Section* curLaneSection, Lane* sharedLane, int interSection){
   sharedLane->lane[interSection+1] = curLaneSection;
}
*/

std::vector<Section> Lane::getLaneVector(){
   return lane;
}



#endif
