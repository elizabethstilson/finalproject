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
  }
