#pragma once
#include <fstream>
#include <string>
#include <iostream>

class Model 
{
    float vertices;
    float indices;
    void loadOBJ(std::string fileDirectory);
    Model(std::string fileDirectory);
};