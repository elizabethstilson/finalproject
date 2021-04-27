#ifndef __SECTION_CPP__
#define __SECTION_CPP__

#include "Section.h"
#include <iostream>

//cosntructor for Section takes in a bool based on whether the section is an intersection and sets occupied status to false
Section::Section(bool intersection){
  occupied = false;
  this->intersection = intersection;
}

//default destructor for Section objects
Section::~Section(){
}

//returns whether Section is occupied or not
bool Section::isOccupied(){
  return occupied;
}

//changes Section to occupied
void Section::makeOccupied(){
  occupied = true;
}

//changes Section to unocupied
void Section::unoccupy(){
  occupied = false;
}


#endif
