#include <map>
#include <fstream>
#include "Dictionary.h"


Dictionary::Dictionary(string file){
  
   fileName = file;
   ifstream inputFile(fileName);

   //creating a map/dictionary
  // map<string, double> cfontrols;

   string name;
   double value;

   //trying to access information out of the file and assign to dictionary
   while (inputFile >> name >> value){
     prob[name] = value;
   }
   //closing input file
   inputFile.close();

   //assigning values in the dictionary
   //for(int x = 0; x <= values.size(); x++){
     //prob[names[x]] = values[x];
    // cout << values[x] << endl;}
}

Dictionary::~Dictionary(){}

double Dictionary::getMaxSimTime(){
   return prob["maximum_simulated_time: "];
}

double Dictionary::getNumSection(){
   return prob["number_of_sections_before_intersection:"];
  }

double Dictionary::getGreenNS(){
   return prob["green_north_south:"];
  }

double Dictionary::getYellowNS(){
   return prob["yellow_north_south:"];
  }

double Dictionary::getGreenEW(){
   return prob["green_east_west:"];
  }

double Dictionary::getYellowEW(){
   return prob["yellow_east_west:"];
  }

double Dictionary::getProbVechEB(){
   return prob["prob_new_vehicle_eastbound:"];
  }

double Dictionary::getProbVechSB(){
   return prob["prob_new_vehicle_southbound:"];
  }

double Dictionary::getProbVechNB(){
   return prob["prob_new_vehicle_northbound:"];
  }

double Dictionary::getProbVechWB(){
   return prob["prob_new_vehicle_westbound:"];
  }

double Dictionary::getPropCar(){
   return prob["proportion_of_cars:"];
  }

double Dictionary::getPropSUV(){
   return prob["proportion_of_SUVs:"];
  }

double Dictionary::getPropTruck(){
   return 1-getPropCar()-getPropSUV();
  }

double Dictionary::getPropRTCar(){
   return prob["proportion_right_turn_cars:"];
  }

double Dictionary::getPropRTSUV(){
   return prob["proportion_right_turn_SUVs:"];
  }

double Dictionary::getPropRTTruck(){
   return prob["proportion_right_turn_trucks:"];
  }

