#include <raylib.h>
#include <rlgl.h>
#include <stdlib.h>
#include <string.h>


#include "glsl.h"
#include "sky.h"


/*
    essa função foi gerado por IA
    esta funcionando, mas precisa da biblioteca string
    a função dela é carregar o cubemap pelas 6 fotos em resources/sky
    não vou otimizar isso, se ta funcionando é o que importa
*/
TextureCubemap LoadCubemapFrom6Faces(
    const char *right,
    const char *left,
    const char *up,
    const char *down,
    const char *front,
    const char *back
)
{
    Image faces[6] = {
        LoadImage(right), // +X
        LoadImage(left),  // -X
        LoadImage(up),    // +Y
        LoadImage(down),  // -Y
        LoadImage(front), // +Z
        LoadImage(back)   // -Z
    };

    // Validação básica
    int size = faces[0].width;
    for (int i = 0; i < 6; i++)
    {
        if (faces[i].data == NULL ||
            faces[i].width != size ||
            faces[i].height != size)
        {
            TraceLog(LOG_ERROR, "Cubemap faces must be square and same size");
        }
    }

    // Converter todas para o mesmo formato
    for (int i = 0; i < 6; i++)
    {
        if (faces[i].format != PIXELFORMAT_UNCOMPRESSED_R8G8B8A8)
        {
            ImageFormat(&faces[i], PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
        }
    }

    // Alocar buffer contínuo (6 faces)
    int faceSize = size * size * 4;
    unsigned char *cubemapData = MemAlloc(faceSize * 6);

    for (int i = 0; i < 6; i++)
    {
        memcpy(
            cubemapData + (faceSize * i),
            faces[i].data,
            faceSize
        );
    }

    // Upload para GPU
    unsigned int id = rlLoadTextureCubemap(
        cubemapData,
        size,
        PIXELFORMAT_UNCOMPRESSED_R8G8B8A8,
        1
    );

    // Cleanup CPU
    MemFree(cubemapData);
    for (int i = 0; i < 6; i++) UnloadImage(faces[i]);

    // Criar TextureCubemap
    TextureCubemap cubemap = { 0 };
    cubemap.id = id;
    cubemap.width = size;
    cubemap.height = size;
    cubemap.mipmaps = 1;
    cubemap.format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8;

    return cubemap;
}

//cria o skybox, retorna struct Sky
Sky createSkybox()
{
    const char *sky_shader_dir = TextFormat("resources/shaders/glsl%i/", GLSL_VERSION);

    //carrega as shaders
    Shader skybox_shader = LoadShader(
        TextFormat("%sskybox.vs", sky_shader_dir),
        TextFormat("%sskybox.fs", sky_shader_dir)
    );

    //objeto real do skybox (cubo)
    Mesh cube = GenMeshCube(1.0f, 1.0f, 1.0f);
    Model skybox = LoadModelFromMesh(cube);
    skybox.materials[0].shader = skybox_shader;

    //define as shaders
    SetShaderValue(
        skybox.materials[0].shader,
        GetShaderLocation(skybox.materials[0].shader, "environmentMap"),
        (int[1]){ MATERIAL_MAP_CUBEMAP },
        SHADER_UNIFORM_INT
    );

    SetShaderValue(
        skybox.materials[0].shader,
        GetShaderLocation(skybox.materials[0].shader, "doGamma"),
        (int[1]){ 0 },
        SHADER_UNIFORM_INT
    );

    SetShaderValue(
        skybox.materials[0].shader,
        GetShaderLocation(skybox.materials[0].shader, "vflipped"),
        (int[1]){ 0 },
        SHADER_UNIFORM_INT
    );

    //n é mais necessario, libera
    UnloadTexture(
    skybox.materials[0]
        .maps[MATERIAL_MAP_CUBEMAP]
        .texture
);

//chama aquela função horrivel gerada por IA
TextureCubemap cubemap = LoadCubemapFrom6Faces(
    "resources/sky/right.png",
    "resources/sky/left.png",
    "resources/sky/up.png",
    "resources/sky/down.png",
    "resources/sky/front.png",
    "resources/sky/back.png"
);

//atribui a textura ao skybox
skybox.materials[0]
    .maps[MATERIAL_MAP_CUBEMAP]
    .texture = cubemap;

    return (Sky){ .model = skybox }; //struct sky usado aqui para retorno
}