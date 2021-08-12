#define PLATFORM_COUNT 3
#define PLATFORMS_FACE_COUNT 6 * PLATFORM_COUNT

typedef struct {
    char ModelPath[50], TexturePath[50];
    float Vertices[12 * PLATFORMS_FACE_COUNT], ColourIndexes[16 * PLATFORMS_FACE_COUNT], TextureIndexes[8 * PLATFORMS_FACE_COUNT];
    float ColourIndexSource[16], TextureIndexSource[8];
    // float ColourIndexes[16 * PLATFORMS_FACE_COUNT], TextureIndexes[8 * PLATFORMS_FACE_COUNT];
    GLUINT_ Indices[6 * PLATFORMS_FACE_COUNT];
    unsigned int TextureIndex, IndiceCount, VerticeCount, TextureVerticeCount;
} structModelPlatforms;

structModelPlatforms gModelPlatforms = {   
    .TextureIndex = 2,  
    .ModelPath = "/models/platforms/",
    .TexturePath = "/textures/GroundTexture.png"
};

typedef struct {
    char ModelPath[50];
    float Vertices[CUBIOD_VERTICE_COUNT * 3],
        ColourIndexes[CUBIOD_VERTICE_COUNT * 4],
        TextureIndexes[CUBIOD_VERTICE_COUNT * 2],
        YPos;
    GLUINT_ Indices[CUBIOD_INDICE_COUNT];
    unsigned int IndiceCount, VerticeCount, TextureVerticeCount;
} structModelGround;

///////////////////////////////////

structCuboid gPlatforms[PLATFORM_COUNT] = {
    {.X = -3.25, .Y = 1.5,  .Z = 0.5, .Width = 1.4, .Height = 0.2, .Depth = 1.0},
    {.X = -0.6,  .Y = 0.95, .Z = 0.5, .Width = 1.1, .Height = 0.2, .Depth = 1.0},
    {.X = 2.0,  .Y = 2.0,  .Z = 0.5, .Width = 1.4, .Height = 0.2, .Depth = 1.0}
};

structModelGround gModelGround = { .YPos = -1.75f, .ModelPath = "/models/ground/" };
