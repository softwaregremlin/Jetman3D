#define JETMAN_TORSO_FACE_COUNT 74
#define JETMAN_LEG_FACE_COUNT 23

typedef struct {
    float VerticesTorso[12 * JETMAN_TORSO_FACE_COUNT], ColourIndexes[16 * JETMAN_TORSO_FACE_COUNT], TextureIndexes[8 * JETMAN_TORSO_FACE_COUNT];
    
    float VerticesLegs[12 * 2 * JETMAN_LEG_FACE_COUNT],
        VerticesLegLeft[12 * JETMAN_LEG_FACE_COUNT],
        VerticesLegRight[12 * JETMAN_LEG_FACE_COUNT];

    float VerticesLegRightStraight[12 * JETMAN_LEG_FACE_COUNT],
        VerticesLegRightStepForward1[12 * JETMAN_LEG_FACE_COUNT],
        VerticesLegRightStepForward2[12 * JETMAN_LEG_FACE_COUNT],
        VerticesLegRightStepBack1[12 * JETMAN_LEG_FACE_COUNT],
        VerticesLegRightStepBack2[12 * JETMAN_LEG_FACE_COUNT],
        VerticesLegRightSitting[12 * JETMAN_LEG_FACE_COUNT];

   float ColourIndexSource[16], TextureIndexSource[8];
    unsigned int Indices[600], IndicesCount;
} structModelJetman;