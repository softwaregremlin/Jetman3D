
#define EXPLOSIONS_MAX_COUNT 20

// Settings for all Explosions
typedef struct {

    GLUINT_ IndiceArray[BILLBOARD_INDICE_COUNT * EXPLOSIONS_MAX_COUNT];

    char TexturePath[50];
    unsigned int FrameLoopCount, FramesPerFrame, FrameCount, FadeFrame, TextureIndex;
    float Growth, InitialSize, Fade, ZPos, XPerspectiveFactor, 
          YPerspectiveFactorPlatform, YPerspectiveFactorGround, YPerspectiveFactorLaser;

} structExplosionSettings;

typedef struct {
    float VertexArray[BILLBOARD_VERTICE_COUNT * 3 * EXPLOSIONS_MAX_COUNT];
    float ColorArray[BILLBOARD_VERTICE_COUNT * 4 * EXPLOSIONS_MAX_COUNT];
    float TextureCoordinateArray[BILLBOARD_VERTICE_COUNT * 2 * EXPLOSIONS_MAX_COUNT];
    GLUINT_ IndiceArray[BILLBOARD_INDICE_COUNT * EXPLOSIONS_MAX_COUNT];

    unsigned int ActiveCount;
} structExplosions;

// Individual Explosion Instances
typedef struct {
    float VertexArray[BILLBOARD_VERTICE_COUNT * 3];
    float ColorArray[BILLBOARD_VERTICE_COUNT * 4];
    float TextureCoordinateArray[BILLBOARD_VERTICE_COUNT * 2];
    float X, Y, Z, Size, InitialSize;
    float originalX, originalY;
    unsigned int On, Frame, FrameCounter;
} structExplosion;

/////////////////////////////////////////////////

structExplosions gExplosions;

structExplosionSettings gExplosionSettings = { 
    .IndiceArray = BILLBOARD_INDICE_ARRAY,
    .TexturePath = "/textures/explosion.png",
    .TextureIndex = 5,
    .FrameLoopCount = 4, .FramesPerFrame = 3, .FrameCount = 24, .FadeFrame = 12,
    .Growth = 0.05f, .Fade = 0.05f, .InitialSize = 0.5f,
    .ZPos = 1.0f, .XPerspectiveFactor = 0.15f, 
    .YPerspectiveFactorPlatform = -0.4f,
    .YPerspectiveFactorLaser = -0.2f,
    .YPerspectiveFactorGround = 0.2f
};

///////////////////////////////////////////////////////////



void ExplosionsInitialise() {
    // At this stage we just load the texture
    TextureLoad(gExplosionSettings.TexturePath, gExplosionSettings.TextureIndex);
}

void ExplosionInitialise(structExplosion* explosion) {

    explosion->On = FALSE;
    explosion->FrameCounter = 0;
    explosion->Size = explosion->InitialSize != 0 ? explosion->InitialSize : gExplosionSettings.InitialSize;
    if(explosion->Z == 0) explosion->Z = gExplosionSettings.ZPos;

    //for (unsigned int cc = 0; cc < 4 * EXPLOSION_VERTICE_COUNT; cc++) {
    for (unsigned int cc = 0; cc < BILLBOARD_VERTICE_COUNT; cc++) {

        unsigned int cornerColour = 0;
        randMinMax(0, 6, &cornerColour);

        float whitener = 0.65f;

        // green
        if (cornerColour == 0) {
            explosion->ColorArray[(cc * 4) + 0] = whitener;
            explosion->ColorArray[(cc * 4) + 1] = 1.0f;
            explosion->ColorArray[(cc * 4) + 2] = whitener;
        }

        // red
        if (cornerColour == 1) {
            explosion->ColorArray[(cc * 4) + 0] = 1.0f;
            explosion->ColorArray[(cc * 4) + 1] = whitener;
            explosion->ColorArray[(cc * 4) + 2] = whitener;
        }

        // cyan
        if (cornerColour == 2) {
            explosion->ColorArray[(cc * 4) + 0] = whitener;
            explosion->ColorArray[(cc * 4) + 1] = 1.0f;
            explosion->ColorArray[(cc * 4) + 2] = 1.0f;
        }

        // yellow
        if (cornerColour == 3) {
            explosion->ColorArray[(cc * 4) + 0] = 1.0f;
            explosion->ColorArray[(cc * 4) + 1] = 1.0f;
            explosion->ColorArray[(cc * 4) + 2] = whitener;
        }

        // magenta
        if (cornerColour == 4) {
            explosion->ColorArray[(cc * 4) + 0] = 1.0f;
            explosion->ColorArray[(cc * 4) + 1] = whitener;
            explosion->ColorArray[(cc * 4) + 2] = 1.0f;
        }

        // white
        if (cornerColour == 5) {
            explosion->ColorArray[(cc * 4) + 0] = 1.0f;
            explosion->ColorArray[(cc * 4) + 1] = 1.0f;
            explosion->ColorArray[(cc * 4) + 2] = 1.0f;
        }

        //alpha
        explosion->ColorArray[(cc * 4) + 3] = 1.0f;
    }
}


void ExplosionAnimate(structExplosion* explosion, unsigned int* isEnd) {

    if (!explosion->On) return;

    // Animation
    explosion->FrameCounter++;
    if (explosion->FrameCounter % gExplosionSettings.FramesPerFrame != 0) return;

    explosion->Frame++;

    // Growth
    explosion->Size += gExplosionSettings.Growth;

    // Fade out
    if (explosion->FrameCounter >= gExplosionSettings.FadeFrame * gExplosionSettings.FramesPerFrame) {
        for (unsigned int aa = 0; aa < 4; aa++) {
            explosion->ColorArray[(aa * 4) + 3] -= gExplosionSettings.Fade;
        }
    }

    // Loop the textures
    if (explosion->Frame == gExplosionSettings.FrameLoopCount) explosion->Frame = 0;

    // End of animation - Loop
    if (explosion->FrameCounter ==
        gExplosionSettings.FrameCount * gExplosionSettings.FramesPerFrame) {
        explosion->On = FALSE;
        explosion->FrameCounter = 0;
        *isEnd = TRUE;
    }
}

void ExplosionSetTexturePositions(structExplosion* explosion) {

    if (!explosion->On) return;

    // Set one of the 4 quarters of the texture depending on the frame
    float xOffset = 0, yOffset = 0;
    if (explosion->Frame == 0) yOffset = 0.5f;
    if (explosion->Frame == 1) { yOffset = 0.5f;  xOffset = 0.5f; }
    if (explosion->Frame == 3) xOffset = 0.5f;

    for (unsigned int tt = 0; tt < 8; tt++) {
        explosion->TextureCoordinateArray[tt] = (tt == 2 || tt > 4) ? 0.5f : 0;
        if (tt % 2 == 0) explosion->TextureCoordinateArray[tt] += xOffset;
        if (tt % 2 != 0) explosion->TextureCoordinateArray[tt] += yOffset;
    }
}

void ExplosionSetVerticePositions(structExplosion* explosion, float zIncrement) {

    if (!explosion->On) return;

    BillboardSetVerticePositionsByCenter(
        explosion->VertexArray, 0, explosion->X, explosion->Y, explosion->Z + zIncrement,
        explosion->Size, explosion->Size);
}

void ExplosionDraw(structExplosion* explosion, float zIncrement) {

    // return;

    if (!explosion->On) return;

    //ExplosionSetVerticePositions(explosion, zIncrement);
    ExplosionSetVerticePositions(explosion, zIncrement * 3.0f);
    ExplosionSetTexturePositions(explosion);

    /*
    drawTriangles(
        explosion->VertexArray,
        explosion->ColorArray,
        explosion->TextureCoordinateArray,
        gExplosionSettings.IndiceArray,
        BILLBOARD_INDICE_COUNT);
    */

    ArrayAppendFloat(explosion->VertexArray, gExplosions.VertexArray,
        BILLBOARD_VERTICE_COUNT * 3 * gExplosions.ActiveCount, BILLBOARD_VERTICE_COUNT * 3);
    ArrayAppendFloat(explosion->ColorArray, gExplosions.ColorArray,
        BILLBOARD_VERTICE_COUNT * 4 * gExplosions.ActiveCount, BILLBOARD_VERTICE_COUNT * 4);
    ArrayAppendFloat(explosion->TextureCoordinateArray, gExplosions.TextureCoordinateArray,
        BILLBOARD_VERTICE_COUNT * 2 * gExplosions.ActiveCount, BILLBOARD_VERTICE_COUNT * 2);

    // 0,1,2,1,2,3
    ArrayAppendGluintWithOffset(gExplosionSettings.IndiceArray, gExplosions.IndiceArray,
        BILLBOARD_VERTICE_COUNT * gExplosions.ActiveCount,
        BILLBOARD_INDICE_COUNT * gExplosions.ActiveCount, BILLBOARD_INDICE_COUNT);

    gExplosions.ActiveCount++;
}

void ExplosionsDraw() {
    if (gExplosions.ActiveCount == 0) return;
    drawTriangles(
        gExplosions.VertexArray,
        gExplosions.ColorArray,
        gExplosions.TextureCoordinateArray,
        gExplosions.IndiceArray,
        gExplosions.ActiveCount * BILLBOARD_INDICE_COUNT);
}