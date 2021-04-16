#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include "Animator.h"
#include "VehicleBase.h"
#include "Dictionary.h"
//#include "Dictionary.cpp"
#include "RandomNumber.h"
//#include "RandomNumber.cpp"

using namespace std;

int main(int argc, char* argv[])
{
    Animator::MAX_VEHICLE_COUNT = 999;  // vehicles will be displayed with three digits
    //Testing to see if there were enough arguments entered
    if(argc != 3)
    {
    	cerr << "error"<< endl;
        exit(1); 
    }
    //declaring the initialSeed variable
    int initialSeed = atoi(argv[2]);
    
    //declaring the filename
    string filename = argv[1];
   
    //Testing Dictionary class 
    Dictionary dict(filename);
    cout << "testing Dictionary class" << endl;
    cout << dict.getGreenEW() << endl;
 
    //Testing RandomNumber Class
    RandomNumber random(initialSeed, filename);
    cout << "testing randomNumber" << endl;
    cout << random.getVechile() << endl; 
    
    int halfSize = (int)(dict.getNumSection());
    cout << halfSize << endl; 


}
