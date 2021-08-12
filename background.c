#define BACKGOUND_SPRITE_COUNT 36

typedef struct {
    char ModelPath[50];
    float Vertices[12 * BACKGOUND_SPRITE_COUNT], ColourIndexes[16 * BACKGOUND_SPRITE_COUNT], TextureIndexes[8 * BACKGOUND_SPRITE_COUNT];
    GLUINT_ Indices[6 * BACKGOUND_SPRITE_COUNT];
    unsigned int TextureIndex, IndiceCount, VerticeCount, TextureVerticeCount;
} structBackground;


structBackground gBackground = { .ModelPath = "/models/background/" };

void BackgroundLoadModel() {

    ModelLoad(
        gBackground.ModelPath, 1,
        &gBackground.VerticeCount,
        &gBackground.IndiceCount,
        &gBackground.TextureVerticeCount,
        gBackground.Vertices,
        gBackground.Vertices,
        gBackground.ColourIndexes,
        gBackground.Indices,
        gBackground.TextureIndexes
    );
}


void BackgroundInitialise() {
    BackgroundLoadModel();
}