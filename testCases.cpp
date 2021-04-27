#include <stdexcept>
#include "Dictionary.h"
#include "RandomNumber.h"
#include <iostream>
#include <exception>
#include "Lane.h"
#include "Section.h"
#include "VehicleBase.h"

using namespace std;

constexpr void assert_that(bool statement, const char* message) {
 if (!statement) throw std::runtime_error{ message }; 
}

void RandomNumber_prints_correct_numbers(){
  RandomNumber number(1234, "input_file_format.txt");
  assert_that(0.0 <= number.getNum() <= 1.0, "number is not between 0 and 1");
}
void RandomNumber_car_boolean(){
  RandomNumber number(1234, "input_file_format.txt"); 
  assert_that(number.turnRightCar() == true || number.turnRightCar() == false, "turnRightCar() does not return a boolean value");
}
void RandomNumber_suv_boolean(){
   RandomNumber number(1234, "input_file_format.txt");
   assert_that(number.turnRightSUV() == true || number.turnRightSUV() == false, "turnRightSUV() does not return a boolean value");
  }
void RandomNumber_truck_boolean(){
   RandomNumber number(1234, "input_file_format.txt");
   std::cout << number.turnRightTruck() << std::endl; 
   assert_that(number.turnRightTruck() == true || number.turnRightTruck() == false, "turnRightTruck() does not return a boolean value");
}
void RandomNumber_vehicle(){
   RandomNumber number(1234, "input_file_format.txt");
   assert_that(0 <= number.getVehicle() <= 1, "getVehicle() does not return a vehicle");
}
void RandomNumber_bound(){
   RandomNumber number(1234, "input_file_format.txt"); 
   assert_that(number.getBound() == 'e' || number.getBound() == 'n' || number.getBound() == 's' || number.getBound() == 'w' || number.getBound() == 'x', "getBound() deos not return a bound");
}

void run_test(void(*unit_test)(), const char* name) {
  try {
    unit_test();
    printf("[+] Test %s successful.\n", name);
  } 
  catch (const std::exception& e) {
    printf("[-] Test failure in %s. %s.\n", name, e.what());
  }
}

// Tests the isOccupied() method in the Section class to ensure the proper boolean is returned 
// after any modification.
void Section_isOccupied(){
  // Makes a section not set to be in the intersection 
  Section section(false);
   
  // Tests after creating a new section 
  assert_that(section.isOccupied() == false, "isOccupied() does notn return the correct boolean upon initial creation");
   
  // Tests after making a section occupied
  section.makeOccupied();
  assert_that(section.isOccupied() == true, "isOccupied() does not return the correct boolean after assigning vehicle");

  // Tests after unoccupying a section
  section.unoccupy();
  assert_that(section.isOccupied() == false, "isOccupied() does not return the correct boolean after calling unoccupy()");

  // Makes a section not set to be in the intersection 
  Section section2(true);
   
  // Tests after creating a new section 
  assert_that(section2.isOccupied() == false, "isOccupied() does notn return the correct boolean upon initial creation");
   
  // Tests after making a section occupied
  section.makeOccupied();
  assert_that(section2.isOccupied() == true, "isOccupied() does not return the correct boolean after assigning vehicle");

  // Tests after unoccupying a section
  section.unoccupy();
  assert_that(section2.isOccupied() == false, "isOccupied() does not return the correct boolean after calling unoccupy()");
}

// Tests the getLaneDirection method upon creation of a lane
void Lane_getLaneDirection(){
  Lane lane1(4, Direction::north, std::vector<VehicleBase*> vehicles);
  std::string lane1Dir = lane1.getLaneDirection();
  assert_that((lane1Dir == "north"), "getLaneDirection() does not return the correct direction");
}

//
void Lane_assignVehicle(){
  // Creating a lane based on halfize of 4 (total num sections =  10)
  std::vector<VehicleBase*> testLaneVeh(10, nullptr);
  Lane testLane(4, Direction::east, testLaneVeh);
  
  //We will test based on a car that only uses 2 sections 
  VehicleBase* vehicle2 = new VehicleBase(VehicleType::car, Direction::east, false);
  int veh2ID = vehicle2.getVehicleID();
  testLane.assignVehicle(vehicle2);
  std::vector<Vehicles*> testVehicleVector = testLane.getVehicleBase();
 
  // The two test ID variables should be the same as the veh2ID since each section is referencing the same vehicle. 
  int testID1 = testVehicleVector[0]->getVehicleID();
  int testID2 = testVehicleVector[1]->getVehicleID();

  assert_that(veh2ID == testID1, "the vehicle ID recieved from position 0 in the lane vector does not equal what it should");
  assert_that(veh2ID == testID2, "the vehicleID recieved from position 1 in the lane vector does not equal what it should");
  
  //Here we make sure no vehicle can be added if sections 0 and 1 are occupied in the lane
  VehicleBase* vehicle3 = new VehicleBase(VehicleType::truck, Direction::east, false);
  testLane.assignVehicle(vehicle3);
  int veh3ID = vehicle3.getVehicleID();
  testLaneVeh = testLane.getVehicleBase();
  int testID3 = testLaneVeh[0]->getVehicleID();
  assert_that(veh3ID != testID3, "the vehicleID recieved from position 0 after adding a new vehicle to an occupied section does not equal what it should");

  //We will test whether or not the partial car code will work 
  testLaneVeh = testLane.getVehicleBase();
  testLaneVeh.at(0) = nullptr;
  
  // Creates a new Lane after removing the vehicle in section 0
  Lane testLane2(4, Direction::east, testLaneVeh);
  
  // add vehicle2 which was created above. 
  testLane2.assignVehicle(vehicle2);

  testVehicleVector = testLane2.getVehicleBase();
  
  // The two test ID variables should be the same as the veh2ID since each section is referencing the same vehicle. 
  testID1 = testVehicleVector[0]->getVehicleID();
  testID2 = testVehicleVector[1]->getVehicleID();

  assert_that(veh2ID == testID1, "the vehicle ID recieved from position 0 in the lane vector does not equal what it should for partial vehicle addition");
  assert_that(veh2ID == testID2, "the vehicleID recieved from position 1 in the lane vector does not equal what it should for partial vehicle addition");
  
}

void Lane_moveLane_Green(){
   //create vehicle vectors
   std::vector<VehicleBases*> vehiclesE;
   std::vector<VehicleBases*> vehiclesN;
   std::vector<VehicleBases*> vehiclesS;
   std::vector<VehicleBases*> vehiclesW;
   //create VehicleBase object 
   VehicleBase* v1(VehicleType::car, Direction::east, false);
   Lane test1(4, Direction::east, vehiclesE);
   Lane test2(4, Direction::north, vehiclesN);
   Lane test3(4, Direction::south, vehiclesS);
   Lane test4(4, Direction::west, vehiclesW);
 
   //assign the vehicle to the lane
   test1.assignVehicle(v1);
 
   //pointers 
   Lane *wpntr = &test4;
   Lane *epntr = &test1;
   Lane *npntr = &test2;
   Lane *spntr = &test3;
 
   assert_that(test1.at(0).isOccupied() && test1.at(1).isOccupied(), "the vehicle did not add to the lane vector");
   //moveLane
   test1.moveLane(LightColor::green, spntr, npntr, 1); //east
   test2.moveLane(LightColor::red, epntr, wpntr, 1); //north
   test3.moveLane(LightColor::red, wpntr, epntr, 1); //south
   test4.moveLane(LightColor::green, npntr, spntr, 1); //west
 
   assert_that(test1.at(1).isOccupied() && test1.at(2).isOccupied(), "the vehicle did not move forward");

}
void Lane_moveLane_Red(){
 
   //create vehicle vectors
   std::vector<VehicleBases*> vehiclesE;
   std::vector<VehicleBases*> vehiclesN;
   std::vector<VehicleBases*> vehiclesS;
   std::vector<VehicleBases*> vehiclesW;
   //create VehicleBase object 
   VehicleBase* v1(VehicleType::truck, Direction::north, false);
   Lane test1(4, Direction::east, vehiclesE);
   Lane test2(4, Direction::north, vehiclesN);
   Lane test3(4, Direction::south, vehiclesS);
   Lane test4(4, Direction::west, vehiclesW);
 
   //assign the vehicle to the lane
   test3.assignVehicle(v1);
 
   //pointers 
   Lane *wpntr = &test4;
   Lane *epntr = &test1;
   Lane *npntr = &test2;
   Lane *spntr = &test3;
 
   assert_that(test3.at(0).isOccupied() && test3.at(1).isOccupied() && test3.at(2).isOccupied() && test3.at(3).isOccupied() , "the vehicle did not add to the lane vector");
   //moveLane
   test1.moveLane(LightColor::green, spntr, npntr, 1); //east
   test2.moveLane(LightColor::red, epntr, wpntr, 1); //north
   test3.moveLane(LightColor::red, wpntr, epntr, 1); //south
   test4.moveLane(LightColor::green, npntr, spntr, 1); //west
 
   assert_that(test3.at(0).isOccupied() && test3.at(1).isOccupied() && test3.at(2).isOccupied() && test3.at(3).isOccupied() && !(test3.at(4).isOccupied()), "the vehicle moved forward");
 
}
void Lane_moveLane_Red2(){
 //create vehicle vectors
   std::vector<VehicleBases*> vehiclesE;
   std::vector<VehicleBases*> vehiclesN;
   std::vector<VehicleBases*> vehiclesS;
   std::vector<VehicleBases*> vehiclesW;
   //create VehicleBase object 
   VehicleBase* v1(VehicleType::car, Direction::north, false);
   Lane test1(4, Direction::east, vehiclesE);
   Lane test2(4, Direction::north, vehiclesN);
   Lane test3(4, Direction::south, vehiclesS);
   Lane test4(4, Direction::west, vehiclesW);
 
   //assign the vehicle to the lane
   test3.assignVehicle(v1);
 
   //pointers 
   Lane *wpntr = &test4;
   Lane *epntr = &test1;
   Lane *npntr = &test2;
   Lane *spntr = &test3;
 
   assert_that(test3.at(0).isOccupied() && test3.at(1).isOccupied(), "the vehicle did not add to the lane vector");
   //moveLane
   test1.moveLane(LightColor::green, spntr, npntr, 1); //east
   test2.moveLane(LightColor::red, epntr, wpntr, 1); //north
   test3.moveLane(LightColor::red, wpntr, epntr, 1); //south
   test4.moveLane(LightColor::green, npntr, spntr, 1); //west
   //moveLane again
   test1.moveLane(LightColor::green, spntr, npntr, 1); //east
   test2.moveLane(LightColor::red, epntr, wpntr, 1); //north
   test3.moveLane(LightColor::red, wpntr, epntr, 1); //south
   test4.moveLane(LightColor::green, npntr, spntr, 1); //west
   //moveLane again
   test1.moveLane(LightColor::green, spntr, npntr, 1); //east
   test2.moveLane(LightColor::red, epntr, wpntr, 1); //north
   test3.moveLane(LightColor::red, wpntr, epntr, 1); //south
   test4.moveLane(LightColor::green, npntr, spntr, 1); //west
   //moveLane again
   test1.moveLane(LightColor::green, spntr, npntr, 1); //east
   test2.moveLane(LightColor::red, epntr, wpntr, 1); //north
   test3.moveLane(LightColor::red, wpntr, epntr, 1); //south
   test4.moveLane(LightColor::green, npntr, spntr, 1); //west
   assert_that(test3.at(2).isOccupied() && test3.at(3).isOccupied() && !(test3.at(4).isOccupied()), "the vehicle moved forward");
} 


void Lane_moveLane_Yellow(){
 
 
 
 
}

// Test the method that determines how many sections are needed per vehicle type
void Lane_getNumSections{
  std::vector<VehicleBase*> testLaneVeh(10, nullptr);
  Lane testLane(4, Direction::north, testLaneVeh);

  // Test car
  VehicleBase* vehicle1 = new VehicleBase(VehicleType::car, Direction::north, false);
  int numSecV1 = testLane.getNumSecitions(vehicle1);
  assert_that(numSecV1 == 2, "the num sections returned for the car is incorrect");
 
  // Test SUV
  VehicleBase* vehicle2 = new VehicleBase(VehicleType::suv, Direction::north, false);
  int numSecV2 = testLane.getNumSecitions(vehicle1);
  assert_that(numSecV1 == 3, "the num sections returned for the suv is incorrect");

  // Test truck
  VehicleBase* vehicle3 = new VehicleBase(VehicleType::truck, Direction::north, false);
  int numSecV1 = testLane.getNumSecitions(vehicle3);
  assert_that(numSecV1 == 4, "the num sections returned for the truck is incorrect");
} 


// Tests the method that determines whether or not there is a partial vehicle in position 0 (first section) of the lane
void Lane_partialVehicle{
  std::vector<VehicleBase*> testLaneVeh(10, nullptr);
  Lane testLane(4, Direction::north, testLaneVeh);
  
  // Tests method for car
  VehicleBase* partialCar = new VehicleBase(VehicleType::car, Direction::north, false);
  (testLane.getVehicleBase()).at(1) = partialCar;
  bool testCarPartial = testLane.partialVehicle(partialCar->getVehicleType(), partialCar);  
  assert_that(testCarPartial == true, "the partial car boolean returned is incorrect");
  
  // Sets the sections occupied by a car back to nullptr
  (testLane.getVehicleBase()).at(1) = nullptr;
  
  VehicleBase* partialSUV = new VehicleBase(VehicleType::suv, Direction::north, false);
  (testLane.getVehicleBase()).at(1) = partialSUV;
  (testLane.getVehicleBase()).at(2) = partialSUV;
  bool testSUVPartial = testLane.partialVehicle(partialSUV->getVehicleType(), partialSUV);  
  assert_that(testSUVPartial == true, "the partial suv boolean returned is incorrect");

   // Sets the sections occupied by a suv back to nullptr
  (testLane.getVehicleBase()).at(1) = nullptr;
  (testLane.getVehicleBase()).at(2) = nullptr;

  VehicleBase* partialTruck = new VehicleBase(VehicleType::truck, Direction::north, false);
  (testLane.getVehicleBase()).at(1) = partialTruck;
  (testLane.getVehicleBase()).at(2) = partialTruck;
  (testLane.getVehicleBase()).at(3) = partialTruck;
  bool testTruckPartial = testLane.partialVehicle(partialTruck->getVehicleType(), partialTruck);  
  assert_that(testTruckPartial == true, "the partial truck boolean returned is incorrect");
  
  
}
void Lane_turnRight(){
}




*/


//the random number 
int main() {
  
  run_test(RandomNumber_prints_correct_numbers, "getNum() produces a double between 0 and 1");   
  
  run_test(RandomNumber_car_boolean, "turnRightCar() returns a boolean value");

  run_test(RandomNumber_suv_boolean, "turnRightSUV() returns a boolean value");

  run_test(RandomNumber_truck_boolean, "turnRightTruck() returns a boolean value");

  run_test(RandomNumber_vehicle, "getVehicle() decides which vehicle enters the simulation");

  run_test(RandomNumber_bound, "getBound() decides which bound the vehicle enters in the simulation"); 

  run_test(Section_isOccupied, "isOccupied() returns the correct boolean value");
  
  run_test(Lane_getVehicleDirection, "getVehicleDirection() returns the correct direction");
 
  run_test(Lane_assignVehicle, "assignVehicle() properly assigns the correct vehicle to the correct seection");
 
  run_test(Lane_moveLane_Green, "moveLane() properly moves a vehicle forward when the light is green");
 
  run_test(Lane_moveLane_Red, "moveLane() properly stops a vehicle at a red light");
 
  run_test(Lane_moveLane_Red2, "moveLane() properly moves a vehicle until it needs to stop");
  
  run_test(Lane_getNumSections, "getNumSections() properly returns the correct number of sections per vehicle type");
 
  run_test(Lane_partialVehicle, "partialVehicle() properly returns whether or not a partial vehicle is in the lane");
*/
}

