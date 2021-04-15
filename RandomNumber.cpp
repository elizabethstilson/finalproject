#include "RandomNumber.h"
//#include "Dictionary.h"
#include <string>

using namespace std;

RandomNumber::RandomNumber(int seed, string file) : initialSeed(seed){
  //rng.seed(initialSeed);
 // uniform_real_distribution<double> randomNum(0.0, 1.0);
  //Dictionary prob(filename); 
  filename = file;
}

RandomNumber::~RandomNumber() {}

double RandomNumber::getNum(){
  rng.seed(initialSeed);
  uniform_real_distribution<double> randomNum(0.0, 1.0);
  return randomNum(rng);
}

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

int RandomNumber::getVechile(){
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
