//#pragma once
//#include <fstream>
//#include <string>
//#include <sstream>
//#include <iostream>
//#include <vector>
//#include <assimp/scene.h>

//struct Model 
//{
//    float* vertices;
//    unsigned int* indices;
//    void loadOBJ(std::string fileDirectory);
//    Model(std::string fileDirectory);
//    ~Model();
//};

#include "mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

unsigned int TextureFromFile(const char *path, const string &directory, bool gamma = false);

class Model 
{
    public:
        Model(char *path)
        {
            loadModel(path);
        }
        void Draw();	
    private:
        // model data
        vector<Mesh> meshes;
        string directory;
        vector<Texture> textures_loaded; 

        void loadModel(string path);
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, 
                                             string typeName);
};