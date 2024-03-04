#include "models.h"

Model::Model(std::string fileDirectory)
{
    loadOBJ(fileDirectory);
}

Model::~Model()
{
    delete vertices;
    delete indices;
}

void Model::loadOBJ(std::string fileDirectory)
{
    std::vector<float> allVerts;
    std::vector<int> allInds;
    std::ifstream curFile(fileDirectory);
    if (!curFile.is_open()) {
        std::cerr << "Error opening the file!" << std::endl;
    }
    std::string line;
    while (std::getline(curFile, line)) {
        //std::cout << line << std::endl;
        char firstChar = line[0];
        std::istringstream iss(line);
        std::string cur;
        if (firstChar == 'v')
        {  
            std::cout << line << std::endl;
            while (iss >> cur)
            {
                if (cur != "v")
                {
                    allVerts.push_back(std::stof(cur));
                    std::cout << "CurVert: " << std::stof(cur) << std::endl;
                }
            }
        }
        else if (firstChar == 'f')
        {
            while (iss >> cur)
            {
                if (cur != "f")
                {
                    allInds.push_back(std::stof(cur));
                    std::cout << "CurInd: " << std::stof(cur) << std::endl;
                }
            }
        }
    }

    curFile.close();

    //Making this an array
    this->vertices = new float[allVerts.size()];
    this->indices = new int[allInds.size()];

    for (int i = 0; i < allVerts.size(); i++)
    {
        vertices[i] = allVerts[i];
        //std::cout << "Vertex #" << i << " " << vertices[i] << std::endl;
    }

    for (int i = 0; i < allInds.size(); i++)
    {
        indices[i] = allInds[i];
    }
}

