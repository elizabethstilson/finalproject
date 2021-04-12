#include "RandomNumber.h"
#include "Dictionary.h"

using namespace std;

RandomNumber::RandomNumber(int seed, Dictionary& dict) : intialSeed(seed){
  rng.seed(intialSeed);
  prob = dict; 
}

RandomNumber::~RandomNumber() {}

int RandomNumber::getNum(){
  return randomNum(rng);
}

boolean RandomNumber::turnRightCar(){
  return true;
}

boolean RandomNumber::turnRightSUV(){
  return true;
}

boolean RandomNumber::turnRightTruck(){
  return true;
}

int RandomNumber::getVechile(){
  return 0;
}

char RandomNumber::getBound(){
  return 'c';
}
//generate a random number than create boundaries with the probablities from the 
//dictionary. then compare and the random number with the boundaries 
