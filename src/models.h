#pragma once
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>

struct Model 
{
    float* vertices;
    int* indices;
    void loadOBJ(std::string fileDirectory);
    Model(std::string fileDirectory);
    ~Model();
};