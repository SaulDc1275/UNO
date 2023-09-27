#include "../include/Cards.h"  
#include <iostream>
#include <string>
 
using namespace std;


void Cards::setNumber(int _number)
{
    number = _number;
}

void Cards::setColor(int _color)
{
    color = _color;
}

int Cards::getColor() {
    return color;
}

int Cards::getNumber() {
    return number;
}
