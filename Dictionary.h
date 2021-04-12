#include <iostream>
#include <string>
#include <map>
#include <fstream>

using namespace std;

class Dictionary{

  public:
    string fileName;
    map<string, double> prob;

    Dictionary(string fileName);
    ~Dictionary();
    double getMaxSimTime();
    double getNumSection();
    double getGreenNS();
    double getYellowNS();
    double getRedNS();
    double getGreenEW();
    double getYellowEW();
    double getRedEW();
    double getProbVechEB();
    double getProbVechSB();
    double getProbVechNB();
    double getProbVechWB();
    double getPropCar();
    double getPropSUV();
    double getPropTruck();
    double getPropRTCar();
    double getPropRTSUV();
    double getPropRTTruck();




}
