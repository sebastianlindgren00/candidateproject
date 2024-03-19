#ifndef ASSIMPLOADER_H
#define ASSIMPLOADER_H

#include <string>
#include <vector>
#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glad/glad.h>
#include "mesh.h"
#include "utility.h"

class AssimpLoader 
{
    public:
        AssimpLoader(char *path);

        void Draw() const;	
    private:
        // model data
        std::vector<Mesh> meshes;
        std::string directory;

        void loadModel(const std::string& path);
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, 
                                             std::string typeName);
};

#endif