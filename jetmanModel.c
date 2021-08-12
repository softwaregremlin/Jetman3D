#define JETMAN_TORSO_FACE_COUNT 74
#define JETMAN_LEG_FACE_COUNT 23
#define JETMAN_LEG_VERTICE_COUNT JETMAN_LEG_FACE_COUNT * 12
#define JETMAN_LEG_MODEL_COUNT 6
#define JETMAN_WALKING_FRAME_COUNT 8

typedef struct {
    float Vertices[12 * JETMAN_LEG_FACE_COUNT],
          ColourIndexes[16 * JETMAN_LEG_FACE_COUNT],
          TextureIndexes[8 * JETMAN_LEG_FACE_COUNT];
    GLUINT_ Indices[6 * JETMAN_LEG_FACE_COUNT];
    unsigned int VerticeCount, ColourIndexCount, TextureIndexCount, IndiceCount;
}
structJetmanModelLeg;

typedef struct {

    char ModelPath[50], ModelPathLegs[50], TexturePath[50];
    float VerticesTorso[12 * JETMAN_TORSO_FACE_COUNT], 
          ColourIndexes[16 * JETMAN_TORSO_FACE_COUNT], 
          TextureIndexes[8 * JETMAN_TORSO_FACE_COUNT];
    
    GLUINT_  IndiceSource[6], Indices[6 * JETMAN_TORSO_FACE_COUNT];

    unsigned int TextureIndex, VerticeCount, ColourIndexSourceCount, TextureIndexSourceCount, IndiceSourceCount,
        WalkingFrames[JETMAN_WALKING_FRAME_COUNT][2];

    structJetmanModelLeg LegModels[JETMAN_LEG_MODEL_COUNT];

    float VerticesLegs[12 * 2 * JETMAN_LEG_FACE_COUNT],
        VerticesLegLeft[12 * JETMAN_LEG_FACE_COUNT],
        VerticesLegRight[12 * JETMAN_LEG_FACE_COUNT],
        ColourIndexesLegs[16 * 2 * JETMAN_LEG_FACE_COUNT],
        TextureIndexesLegs[8 * 2 * JETMAN_LEG_FACE_COUNT];


} structModelJetman;

enum JetManLegFrames { 
    JetManLegFrameStraight, 
    JetManLegFrameStepForward1, JetManLegFrameStepForward2, 
    JetManLegFrameStepBack1, JetManLegFrameStepBack2, 
    JetManLegFrameSitting
};

structModelJetman gModelJetman = {
    .ModelPath = "/models/jetman/",
    .ModelPathLegs = "/models/jetman/legs/",
    .TexturePath = "/textures/astro.png",
    .TextureIndex = 3,
    .WalkingFrames = { 
        {JetManLegFrameStraight,JetManLegFrameStraight},
        {JetManLegFrameStepForward1, JetManLegFrameStepBack1},
        {JetManLegFrameStepForward2, JetManLegFrameStepBack2},
        {JetManLegFrameStepForward1, JetManLegFrameStepBack1},
        {JetManLegFrameStraight,JetManLegFrameStraight},
        {JetManLegFrameStepBack1, JetManLegFrameStepForward1},
        {JetManLegFrameStepBack2, JetManLegFrameStepForward2},
        {JetManLegFrameStepBack1, JetManLegFrameStepForward1}
    }
};

void JetManModelLegLoad(unsigned int index) {

    ModelLoad(
        gModelJetman.ModelPathLegs, index + 1,
        &gModelJetman.LegModels[index].VerticeCount, 
        &gModelJetman.LegModels[index].IndiceCount, 
        &gModelJetman.LegModels[index].TextureIndexCount,
        gModelJetman.LegModels[index].Vertices, gModelJetman.LegModels[index].Vertices,
        gModelJetman.LegModels[index].ColourIndexes,
        gModelJetman.LegModels[index].Indices, 
        gModelJetman.LegModels[index].TextureIndexes);
}

void JetmanModelInitialise() {
    unsigned int i;
    TextureLoad(gModelJetman.TexturePath, gModelJetman.TextureIndex);
    ////////////////////////////
    ModelLoad(gModelJetman.ModelPath, 1,
        &gModelJetman.VerticeCount, &gModelJetman.IndiceSourceCount, &gModelJetman.TextureIndexSourceCount,
        gModelJetman.VerticesTorso, gModelJetman.VerticesTorso,
        gModelJetman.ColourIndexes, gModelJetman.IndiceSource, gModelJetman.TextureIndexes);
    
    //for (i = 0; i < 8 * JETMAN_TORSO_FACE_COUNT; i++) {
    //    gModelJetman.TextureIndexes[i] = gModelJetman.TextureIndexes[i % 8];
    //}
    for (i = 0; i < 8 * 2 * JETMAN_LEG_FACE_COUNT; i++) {
        gModelJetman.TextureIndexesLegs[i] = 0;
    }

    // Indices Array
    for (i = 0; i < JETMAN_TORSO_FACE_COUNT; i++) {
        gModelJetman.Indices[i * 6] = i * 4;
        gModelJetman.Indices[(i * 6) + 1] = (i * 4) + 1;
        gModelJetman.Indices[(i * 6) + 2] = (i * 4) + 2;
        gModelJetman.Indices[(i * 6) + 3] = (i * 4);
        gModelJetman.Indices[(i * 6) + 4] = (i * 4) + 2;
        gModelJetman.Indices[(i * 6) + 5] = (i * 4) + 3;
    }

    float scaleFactor = gJetman.Scale * (gGame.State != GameStateModelView ? 1.0f : 2.0f);

    VerticeArrayScale(scaleFactor, gModelJetman.VerticesTorso, 12 * JETMAN_TORSO_FACE_COUNT);
    VerticeArrayRotate90(gModelJetman.VerticesTorso, 12 * JETMAN_TORSO_FACE_COUNT);
    
    for (unsigned int ll = 0; ll < JETMAN_LEG_MODEL_COUNT; ll++) {
        JetManModelLegLoad(ll);

        VerticeArrayScale(scaleFactor, gModelJetman.LegModels[ll].Vertices, 12 * JETMAN_LEG_FACE_COUNT);
        VerticeArrayRotate90(gModelJetman.LegModels[ll].Vertices, 12 * JETMAN_LEG_FACE_COUNT);
        
    }
 }