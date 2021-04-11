#include "RandomNumber.h"

RandomNumber::RandomNumber(int seed) : intialSeed(seed){
  rng.seed(intialSeed);
}

RandomNumber::~RandomNumber() {}

RandomNumber::getNum(){
  return randomNum(rng);
}
