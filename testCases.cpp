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
/*void Section_isOccupied(){
  Section section;
  assert_that(section.isOccupied() == false, "isOccupied() does notn return the correct boolean upon initial creation");
  
  VehicleBase vehicle1(VehicleType::car, Direction::north, true);
  section.makeOccupied(vehicle1, Direction::north);
  assert_that(section.isOccupied() == true, "isOccupied() does not return the correct boolean after assigning vehicle");
  
  Section section2(section);
  assert_that(section2.isOccupied() == true, "isOccupied() does not return the correct boolean after using copy const");

  section.unoccupy();
  assert_that(section.isOccupied() == false, "isOccupied() does not return the correct boolean after calling unoccupy()");

}*/

/*void Lane_assignVehicle(){
  Lane testLane(4, Direction::east);

  //We will test based on a car that only uses 2 sections 
  VehicleBase vehicle2(VehicleType::car, Direction::east, false);
  int veh2ID = vehicle2.getVehicleID();
  testLane.assignVehicle(vehicle2);
  std::vector<Section*> testLaneVector = testLane.getLaneVector();
 
  // The two test ID variables should be the same as the veh2ID since each section is referencing the same vehicle. 
  int testID1 = testLaneVector[0]->getVehicleID();
  int testID2 = testLaneVector[1]->getVehicleID();

  assert_that(veh2ID == testID1, "the vehicle ID recieved from position 0 in the lane vector does not equal what it should");
  assert_that(veh2ID == testID2, "the vehicleID recieved from position 1 in the lane vector does not equal what it should");
  
  //Here we make sure no vehicle can be added if sections 0 and 1 are occupied in the lane
  VehicleBase vehicle3(VehicleType::truck, Direction::east, false);
  testLane.assignVehicle(vehicle3);
  int veh3ID = vehicle3.getVehicleID();
  testLaneVector = testLane.getLaneVector();
  int testID3 = testLaneVector[0]->getVehicleID();
  assert_that(veh3ID != testID3, "the vehicleID recieved from position 0 after adding a new vehicle to an occupied section does not equal what it should");

  // I do not think we can test unoccupying the first section of the lane as of now, but add a test to see if you can add half of a car with the testlane created

}

void Lane_moveLane_Green(){
   Lane test1(4, Direction::east);
   


}
void Lane_moveLane_Red(){
}
void Lane_moveLane_Yellow(){
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

/*  run_test(Section_isOccupied, "isOccupied() returns the correct boolean value");
  
  run_test(Lane_assignVehicle, "assignVehicle() properly assigns the correct vehicle to the correct seection");
*/
}

