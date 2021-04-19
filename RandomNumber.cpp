#include "RandomNumber.h"
#include "Dictionary.h"
#include <string>

using namespace std;
//Random number class
//Main purpose is to generate a random number, decide if a vehicle can turn right, which vehicle is gerated and where it will appear 
//need a int and a string to create a RandomNumber object 



//constructor: need a number to use for the seed and then a string of the file name
RandomNumber::RandomNumber(int seed, string file) : initialSeed(seed){
  //rng.seed(initialSeed);
 // uniform_real_distribution<double> randomNum(0.0, 1.0);
  //Dictionary prob(filename); 
  filename = file;
}

//destructor 
RandomNumber::~RandomNumber() {}

//generates a random number based on the seed
double RandomNumber::getNum(){
  rng.seed(initialSeed);
  uniform_real_distribution<double> randomNum(0.0, 1.0);
  return randomNum(rng);
}

//returns true or false if the car can turn right based on the random number and the input probability
bool RandomNumber::turnRightCar(){
  Dictionary prob(filename);
  double x = this->getNum();
  double car = prob.getPropRTCar();
  double truck = prob.getPropRTTruck();
  double suv = prob.getPropRTSUV();
  if (x <= 1*car){
    return true;
  }
  else{
    return false; 
  }  
}

//returns true or false if the SUV can turn right based on the random number and the input probability
bool RandomNumber::turnRightSUV(){
  Dictionary prob(filename);
  double x = this->getNum();
  double car = prob.getPropRTCar(); 
  double suv = prob.getPropRTSUV(); 
  if(1*car < x <= (1*car)+suv){  
    return true;
  }
  else{
    return false; 
  }
}

//returns true or false if the truck can turn right based on the random number and the input probability
bool RandomNumber::turnRightTruck(){
  Dictionary prob(filename);
  double x = this->getNum();
  double truck = prob.getPropRTTruck();
  double car = prob.getPropRTCar();
  double suv = prob.getPropRTSUV();
  if((1*car)+suv < x < ((1*car)+suv)+truck){
    return true;
  }
  else{
    return false;
  }
}

//returns a number (0 = car, 1 = suv and 2 = truck) indicating the type of vehicle that will be created based on a random number and the probability inputed 
int RandomNumber::getVehicle(){
  Dictionary prob(filename);
  double propCar = prob.getPropCar();
  double propTruck = prob.getPropTruck();
  double propSuv = prob.getPropSUV(); 
  double x = this->getNum();
  if (x < 1*propCar){
    return 0;   
  }
  else if (1*propCar < x < (1*propCar)+propSuv){
    return 1;
  }
  else{
    return 2;
  }  
 
}

//returns a character indicatign where the vehicle will enter based on a random number and the probability inputed 
char RandomNumber::getBound(){
  Dictionary prob(filename);
  double x = this->getNum();
  double eb = prob.getProbVechEB();
  double nb = prob.getProbVechNB();
  double sb = prob.getProbVechSB();
  double wb = prob.getProbVechWB(); 

  if(x <= 1*eb){
    return 'e';
  }
  else if(1*eb < x <= (1*eb)+nb){
    return 'n';
  }
  else if((1*eb+nb) < x <= (1*eb+nb)+sb){
    return 's';
  }
  else if((1*eb+nb)+sb < x <= (1*eb+nb+sb)+wb){
    return 'w';
  }
  else{
   return 'x';
  }
}
