#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include "Animator.h"
#include "VehicleBase.h"
//#include "Dictionary.h"
#include "Dictionary.cpp"

using namespace std;

int main(int argc, char* argv[])
{
   // Animator::MAX_VEHICLE_COUNT = 999;  // vehicles will be displayed with three digits
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
   
    //opening the file
    ifstream inputFile;
    inputFile.open(argv[1]);

    //creating variables to hold values in the input file
    string name;
    double value;

    //creating a map/dictionary
    map<string, double> controls;

    //trying to access information out of the file
    while (inputFile >> name >> value){
      controls[name] = value;
    }

    //closing input file
    inputFile.close();
    
    
    //printing out the map/dictionary
    map<string, double>::iterator it;
    for(it=controls.begin(); it!=controls.end(); it++){
      cout<< it->first << ": " << it->second << endl;
    }
    
    cout << controls["green_east_west:"] << endl;
    
    Dictionary dict(filename);
    cout << "testing Dictionary class" << endl;
    cout << dict.getGreenEW() << endl;

 
    //int max_simulated_time = values[0];
    //Animator anim(values[1]);
 }
