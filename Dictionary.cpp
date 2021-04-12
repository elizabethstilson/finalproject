#include <map>
#include <fstream>

Dictionary::Dictionary(string filename){
   ifstream inputFile(filename);

   //creating a map/dictionary
   map<string, double> controls;

   string name;
   double value;

   //trying to access information out of the file
   while (inputFile >> name >> value){
     controls[name] = value;
   }
   //closing input file
   inputFile.close();

   //assigning values in the dictionary
   for(int x = 0; x <= values.size(); x++){
     m[names[x]] = values[x];
     cout << values[x] << endl;}

  double getMaxSimTime(){
    return controls["maximum_simulated_time: "];
  }

  double getNumSection(){
    return controls["number_of_sections_before_intersection:"];
  }

  double getGreenNS(){
    return controls["green_north_south:"];
  }

  double getYellowNS(){
    return controls["yellow_north_south:"];
  }

  double getGreenEW(){
    return controls["green_east_west:"];
  }

  double getYellowEW(){
    return controls["yellow_east_west:"];
  }

  double getProbVechEB(){
    return controls["prob_new_vehicle_eastbound:"];
  }

  double getProbVechSB(){
    return controls["prob_new_vehicle_southbound:"];
  }

  double getProbVechNB(){
    return controls["prob_new_vehicle_northbound:"];
  }

  double getProbVechWB(){
    return controls["prob_new_vehicle_westbound:"];
  }

  double getPropCar(){
    return controls["proportion_of_cars:"];
  }

  double getPropSUV(){
    return controls["proportion_of_SUVs:"];
  }

  double getPropTruck(){
    return 1-getPropCar()-getPropSUV();
  }

  double getPropRTCar(){
    return controls["proportion_right_turn_cars:"];
  }

  double getPropRTSUV(){
    return controls["proportion_right_turn_SUVs:"];
  }

  double getPropRTTruck(){
    return controls["proportion_right_turn_trucks:"];
  }
}
