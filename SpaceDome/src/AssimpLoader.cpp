#include "AssimpLoader.h"

//found info at
// https://learnopengl.com/Model-Loading/Model

AssimpLoader::AssimpLoader(std::string const &path){
    loadModel(path);
}

void AssimpLoader::Draw(){
    for(unsigned int i = 0; i < meshes.size(); i++)
        meshes[i].Draw();
} 

void AssimpLoader::loadModel(std::string path) {
    Assimp::Importer import;
    import.SetPropertyBool(AI_CONFIG_PP_PTV_NORMALIZE, true);
    const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate| aiProcess_FlipUVs | aiProcess_PreTransformVertices);
    //const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);	
	
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
    {
        std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << "\n";
        return;
    }
    mDirectory = path.substr(0, path.find_last_of('/'));

    processNode(scene->mRootNode, scene);

    std::cout << "Loaded " << meshes.size() << " meshes.\n";
}

void AssimpLoader::processNode(aiNode *node, const aiScene *scene){
    // process all the node's meshes (if any)
    for(unsigned int i = 0; i < node->mNumMeshes; i++){
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]]; 
        meshes.push_back(processMesh(mesh, scene));			
    }
    // then do the same for each of its children
    for(unsigned int i = 0; i < node->mNumChildren; i++){
        processNode(node->mChildren[i], scene);
    }
} 

Mesh AssimpLoader::processMesh(aiMesh *mesh, const aiScene *scene){

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        // process vertex positions, normals and texture coordinates
        glm::vec3 vector; 
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z; 
        vertex.mPosition = vector;

        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.mNormal = vector;  

        if(mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x; 
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.mTexCoords = vec;
        }
        else
            vertex.mTexCoords = glm::vec2(0.0f, 0.0f); 
        
            vertices.push_back(vertex);
    }

    // process indices
    for(unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
        } 
    // process material
    if(mesh->mMaterialIndex >= 0) {
    aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
    std::vector<Texture> diffuseMaps = loadMaterialTextures(material, 
                                        aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    std::vector<Texture> specularMaps = loadMaterialTextures(material, 
                                        aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    std::cout << "Textures inserted: " << textures.size() << "\n";
    } 
    
    return Mesh(vertices, indices, textures);
} 


std::vector<Texture> AssimpLoader::loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName)
{
    std::vector<Texture> textures;
    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        Texture texture;
        texture.mId = Utility::textureFromFile(str.C_Str(), mDirectory);

        std::string full_path = mDirectory + "/" + str.C_Str();
        std::cout << "Loading texture from path: " << full_path << std::endl;

        texture.mType = typeName;
        texture.mPath = mDirectory + "/" + str.C_Str();
        textures.push_back(texture);
    }
    return textures;
}  