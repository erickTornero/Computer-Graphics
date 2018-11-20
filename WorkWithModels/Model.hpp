# ifndef __MODELM__
# define __MODELM__

# include <vector>
# include <string>

# include <assimp/Importer.hpp>
# include <assimp/scene.h>
# include <assimp/postprocess.h>

# include "Mesh.hpp"
# include "Texture.hpp"

class Model{
public:
    Model(){};

    void LoadModel(std::string & fileName);
    void RenderModel();
    void ClearModel();
    ~Model(){};

private:

    void LoadNode(aiNode * node, const aiScene * scene);
    void LoadMesh(aiMesh * mesh, const aiScene * scene);
    void LoadMaterials(const aiScene * scene);

    std::vector<Mesh * > meshList;
    std::vector<Texture *> textureList;
    std::vector<unsigned int> meshToTex;
};

# endif