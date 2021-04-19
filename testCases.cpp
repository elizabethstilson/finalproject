#include <stdexcept>
#include "Dictionary.h"
#include "RandomNumber.h"
#include <iostream>
#include <exception>

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

//the random number 
int main() {
  
  run_test(RandomNumber_prints_correct_numbers, "getNum() produces a double between 0 and 1");   
  
  run_test(RandomNumber_car_boolean, "turnRightCar() returns a boolean value");

  run_test(RandomNumber_suv_boolean, "turnRightSUV() returns a boolean value");

  run_test(RandomNumber_truck_boolean, "turnRightTruck() returns a boolean value");

  run_test(RandomNumber_vehicle, "getVehicle() decides which vehicle enters the simulation");

  run_test(RandomNumber_bound, "getBound() decides which bound the vehicle enters in the simulation"); 
}
