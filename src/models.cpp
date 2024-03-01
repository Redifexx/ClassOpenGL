#include "models.h"

Model::Model(std::string fileDirectory)
{
    loadOBJ(fileDirectory);
}

void Model::loadOBJ(std::string fileDirectory)
{
    std::ifstream curFile(fileDirectory);
    if (!curFile.is_open()) {
        std::cerr << "Error opening the file!" << std::endl;
        //return 1;
    }
    std::string line;
    while (std::getline(inputFile, line)) {
        // Process each line here
        std::cout << line << std::endl;
    }

    // Close the file
    inputFile.close();

    return 0;
}

