#include <iostream>
#include <random>

using namespace std;

class RandomNumber{

  public:
    int initialSeed;
    mt19937 rng;
    uniform_real_distribution<double> randomNum(0.0, 1.0);
    //map<string, double> prob;

    RandomNumber(int seed); //set intial seed in constructor
    ~RandomNumber();

    int getNum();

    boolean turnRightCar();
    boolean turnRightSUV();
    boolean turnRightTruck();
    int getVechile(); //0,1,2 (if else) -generate num beginning
    char getBound(); //n,s,e,w (if else)
    //0-0.25 = nb, 0.26 - 0.35 = eb, 0.36 - 0.50 = wb, 0.51 - 0.65 = sb, 0.66+ none

};
