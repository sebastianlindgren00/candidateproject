#ifndef ASSIMPLOADER_H
#define ASSIMPLOADER_H

#include <string>
#include <vector>
#include <iostream>
#include "assimp/Importer.hpp"
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glad/glad.h>
#include "mesh.h"
#include "utility.h"
#include "shader.h"

class AssimpLoader 
{

    unsigned int TextureFromFile(const char *path, const string &directory, bool gamma = false);
    public:

        // model data
        std::vector<Mesh> meshes;
        std::string mDirectory;
        bool gammaCorrection;
        vector<Texture> textures_loaded;

        const std::vector<Mesh>& getMeshes() const { return meshes; }
        AssimpLoader(std::string const &path);
        
        void Draw();	
    private:

        void loadModel(std::string path);
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, 
                                             std::string typeName);
};

#endif