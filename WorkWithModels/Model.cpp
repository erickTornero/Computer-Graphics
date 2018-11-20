# include "Model.hpp"

void Model::LoadModel(std::string & fileName){
    Assimp::Importer importer;
    const aiScene * scene = importer.ReadFile(fileName, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);

    if( !scene){
        printf("Model (%s)faild to load into scene %s", fileName, importer.GetErrorString());
        return;
    }    
    LoadNode(scene->mRootNode, scene);

    LoadMaterials(scene);
}

void Model::LoadNode(aiNode * node, const aiScene * scene){
    for(size_t i = 0; i < node->mNumMeshes; i++){
        LoadMesh(scene->mMeshes[node->mMeshes[i]], scene);
    }
    for(size_t i = 0; i < node->mNumChildren; i++){
        LoadNode(node->mChildren[i], scene);
    }
}

void Model::LoadMesh(aiMesh * mesh, const aiScene * scene){
    std::vector<GLfloat> vertices;
    std::vector<unsigned int> indexes;

    for(size_t i = 0; i< mesh->mNumVertices; i++){
        vertices.insert(vertices.end(), {mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z});
        if(mesh->mTextureCoords[0]){
            vertices.insert(vertices.end(), {mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y});
        }
        else{
            vertices.insert(vertices.end(), {0.0f, 0.0f});
        }
        vertices.insert(vertices.end(), {-mesh->mNormals[i].x, -mesh->mNormals[i].y, -mesh->mNormals[i].z});
    }

    for(size_t i = 0; i < mesh->mNumFaces; i++){
        aiFace face = mesh->mFaces[i];
        for(size_t j = 0; j < face.mNumIndices; j++){
            indexes.push_back(face.mIndices[j]);
        }
    }

    Mesh * newMesh = new Mesh();
    newMesh->CreateMesh(&vertices[0], &indexes[0], vertices.size(), indexes.size());
    this->meshList.push_back(newMesh);
    this->meshToTex.push_back(mesh->mMaterialIndex);
}

void Model::LoadMaterials(const aiScene * scene){
    this->textureList.resize(scene->mNumMaterials);
    for(size_t i = 0; i < scene->mNumMaterials; i++){
        aiMaterial * material = scene->mMaterials[i];
        
        this->textureList[i] = nullptr;
        if(material->GetTextureCount(aiTextureType_DIFFUSE)){
            aiString path;
            if(material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS){
                int idx = std::string(path.data).rfind("\\");
                std::string filename = std::string(path.data).substr(idx + 1);

                std::string textPath = std::string("textures/") + filename;

                textureList[i] = new Texture((const char *)textPath.c_str());

                if(!textureList[i]->LoadTexture()){
                    printf("Failed loading Texture at: %s", textPath);
                    delete textureList[i];
                    textureList[i] = nullptr;
                }
            }
        }
        if(!textureList[i]){
            textureList[i] = new Texture("textures/plain.png");
        }
    }
}

void Model::RenderModel(){
    for(size_t i = 0; i < meshList.size(); i++){
        unsigned int materialIndex = meshToTex[i];
        if(materialIndex < textureList.size() && textureList[materialIndex]){
            textureList[materialIndex]->UseTexture();
        }
        meshList[i]->RenderMesh();
    }
}

void Model::ClearModel(){
    for(size_t i = 0; i < meshList.size(); i++){
        if(meshList[i]){
            delete meshList[i];
            meshList[i] = nullptr;
        }
    }
    for(size_t i = 0; i < textureList.size(); i++){
        if(textureList[i]){
            delete textureList[i];
            textureList[i] = nullptr;
        }
    }
}