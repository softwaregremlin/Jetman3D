#define LASER_COUNT 6
// #define LASER_TEXTURE_INDEX 6
#define LASER_COLOUR_CYCLES 30

float VertexArrayLasers[12 * LASER_COUNT];
GLUINT IndiceArrayLasers[6 * LASER_COUNT];
float TextureCoordinateArrayLasers[8 * LASER_COUNT];
float TextureCoordinateArrayLaserSourceLine[]   = { 0, 0, 0.5f, 0, 0, 0.5f, 0.5f, 0.5f };
float TextureCoordinateArrayLaserSourceDashed[] = { 0, 0, 5.0f, 0, 0, 0.5f, 5.0f, 0.5f };
float ColorArrayLasers[16 * LASER_COUNT];

typedef struct { float Red, Green, Blue;  } structLaserColour;

typedef struct {
    float X, Y, Z, Alpha,  DistanceTravelled, XOffset, YOffset;
    unsigned int On, FacingRight, Frame, PreShotDelay;
    structLaserColour Colour;
} structLaser;


typedef struct {
    float Z, ZIncrement, Width, Height, JetmanXOffset, JetmanYOffset, ScreenWrapX, ScreenWrapXLimit, Range, Speed;
    unsigned int FramesPerFrame, DelayBetweenShots, ColourCycleCounter;
    char TexturePath[50];
    unsigned int TextureIndex;
    structLaser Laser[LASER_COUNT];
    structLaserColour ColourCycle[LASER_COLOUR_CYCLES];
} structLasers;




///////////////////////////////////////////////////////////////////////////////////////////////////
// .Width = 2.0f, .Height = 0.05f,  .JetmanYOffset = -0.24f
// .Range = 3.5f, .Speed = 0.15,


structLasers gLasers = {
    .TexturePath = "/textures/laser.png",
    .TextureIndex = 6,
    .Z = 0.1f, .ZIncrement = 0.01f, .Width = 3.0f, .Height = 0.15f,
    .JetmanXOffset = 0.32f, .JetmanYOffset = -0.275f, .ScreenWrapX = 5.5f, .ScreenWrapXLimit = 4.0f,
    .Range = 4.0f, .Speed = 0.15,
    .FramesPerFrame = 1, .DelayBetweenShots = 10 };
///////////////////////////////////////////////////////////////////////////////////////////////////

void LasersInitialise() {
    
    unsigned int i;

    // Load the Texture
    TextureLoad(gLasers.TexturePath, gLasers.TextureIndex);

    // Colour Cycles (cyan - white - magenta)
    for (i = 0; i < 10; i++) {
        gLasers.ColourCycle[i].Red   = 0.35f + ((float)i * ((1.0f - 0.35f) / 10.0f));
        gLasers.ColourCycle[i].Green = 0.85f + ((float)i * ((1.0f - 0.85f) / 10.0f));
        gLasers.ColourCycle[i].Blue  = 1.0f;

        gLasers.ColourCycle[i + 10].Red = 1.0f - ((float)i * ((1.0f - 0.75f) / 10.0f));
        gLasers.ColourCycle[i + 10].Green = 1.0f - ((float)i * (1.0f / 10.0f));
        gLasers.ColourCycle[i + 10].Blue = 1.0f - ((float)i * ((1.0f - 0.75f) / 10.0f));

        gLasers.ColourCycle[i + 20].Red = 0.75f - ((float)i * ((0.75 - 0.35f) / 10.0f));
        gLasers.ColourCycle[i + 20].Green = 0.0f + ((float)i * (0.85f / 10.0f));
        gLasers.ColourCycle[i + 20].Blue = 0.75f + ((float)i * ((1.0f - 0.75f) / 10.0f));

    }

    // Texture Array - Solid / Dashed Lasers
    for (i = 0; i < 8 * LASER_COUNT; i++) { 
        TextureCoordinateArrayLasers[i] = i < 8 ?
            TextureCoordinateArrayLaserSourceLine[i % 8] : TextureCoordinateArrayLaserSourceDashed[i % 8];
    }

    // Indice Array
    for (i = 0; i < LASER_COUNT; i++) {
        IndiceArrayLasers[i * 6] = i * 4;
        IndiceArrayLasers[(i * 6) + 1] = (i * 4) + 1;
        IndiceArrayLasers[(i * 6) + 2] = (i * 4) + 2;
        IndiceArrayLasers[(i * 6) + 3] = (i * 4) + 1;
        IndiceArrayLasers[(i * 6) + 4] = (i * 4) + 2;
        IndiceArrayLasers[(i * 6) + 5] = (i * 4) + 3;
    }
}


//////////////////////////////////////////

void LasersSetVerticesAndColours() {
    
    // Shift the vertices and set colours in the array for all particles
    for (unsigned int ll1 = 0; ll1 < LASER_COUNT; ll1++) {

        for (unsigned int ll2 = 0; ll2 < 4; ll2++) {
            VertexArrayLasers[(ll1 * 12) + 0 + (ll2 * 3)] = gLasers.Laser[ll1].X;
            VertexArrayLasers[(ll1 * 12) + 1 + (ll2 * 3)] = gLasers.Laser[ll1].Y;
            VertexArrayLasers[(ll1 * 12) + 2 + (ll2 * 3)] = gLasers.Laser[ll1].Z;

            
            // Alpha 1 or 0 to switch on or off
            ColorArrayLasers[(ll1 * 16) + 3 + (ll2 * 4)] = gLasers.Laser[ll1].On ? 1.0f : 0;
            
            // Set the Colour
            ColorArrayLasers[(ll1 * 16) + 0 + (ll2 * 4)] = gLasers.Laser[ll1].Colour.Red;
            ColorArrayLasers[(ll1 * 16) + 1 + (ll2 * 4)] = gLasers.Laser[ll1].Colour.Green;
            ColorArrayLasers[(ll1 * 16) + 2 + (ll2 * 4)] = gLasers.Laser[ll1].Colour.Blue;
        }

        VertexArrayLasers[(ll1 * 12) + 3]  += gLasers.Width;
        VertexArrayLasers[(ll1 * 12) + 7]  += gLasers.Height;
        VertexArrayLasers[(ll1 * 12) + 9]  += gLasers.Width;
        VertexArrayLasers[(ll1 * 12) + 10] += gLasers.Height;
    }

}


/////////////////////////////////////////

void LaserMove(unsigned int index) {

    if (!gLasers.Laser[index].On) return;

    // "FramesPerFrame" = slow motion for debugging)
    gLasers.Laser[index].Frame++;
    if (gLasers.Laser[index].Frame < gLasers.FramesPerFrame) return;
    gLasers.Laser[index].Frame = 0;

    // Move
    gLasers.Laser[index].DistanceTravelled += gLasers.Speed;
    gLasers.Laser[index].X += (gLasers.Laser[index].FacingRight ? 1 : -1) * gLasers.Speed;

    // Screen Wrap
    if (gLasers.Laser[index].FacingRight && 
        gLasers.Laser[index].X >= gLasers.ScreenWrapXLimit) gLasers.Laser[index].X = -gLasers.ScreenWrapX;
    if (!gLasers.Laser[index].FacingRight && 
        gLasers.Laser[index].X <= -gLasers.ScreenWrapXLimit) gLasers.Laser[index].X = gLasers.ScreenWrapX;

    // Range Limit
    if (gLasers.Laser[index].DistanceTravelled <= gLasers.Range) return;
    gLasers.Laser[index].On = FALSE;
    gLasers.Laser[index].DistanceTravelled = 0;
}

void LasersMove() {
    for (unsigned int ll = 0; ll < LASER_COUNT; ll++) LaserMove(ll);
}

unsigned int LaserGetNextFreeSlot() {
    for (unsigned int ll = 0; ll < LASER_COUNT; ll++) {
        if (!gLasers.Laser[ll].On) return ll;
    }
    // All slots taken
    return -1;
}

void LaserStartNew() {

    unsigned int nextFreeSlot = LaserGetNextFreeSlot();
    if(nextFreeSlot == -1) return;

    if (gJetman.Exploding) return;
    if (gJetman.InRocket) return;

    //delay between shots (except the first one)
    if (nextFreeSlot > 0 && gLasers.Laser[nextFreeSlot].PreShotDelay < gLasers.DelayBetweenShots) {
        gLasers.Laser[nextFreeSlot].PreShotDelay++;
        return;
    }
    gLasers.Laser[nextFreeSlot].PreShotDelay = 0;

    SoundPlay(gFireSound);
    gLasers.Laser[nextFreeSlot].On = TRUE;

    // Set the colour
    gLasers.ColourCycleCounter++;
    if (gLasers.ColourCycleCounter == LASER_COLOUR_CYCLES) gLasers.ColourCycleCounter = 0;
    gLasers.Laser[nextFreeSlot].Colour.Red = gLasers.ColourCycle[gLasers.ColourCycleCounter].Red;
    gLasers.Laser[nextFreeSlot].Colour.Green = gLasers.ColourCycle[gLasers.ColourCycleCounter].Green;
    gLasers.Laser[nextFreeSlot].Colour.Blue = gLasers.ColourCycle[gLasers.ColourCycleCounter].Blue;

    // Align with Jetman's gun
    if (gJetman.FacingRight) {
        gLasers.Laser[nextFreeSlot].X = gJetman.XPos + gLasers.JetmanXOffset;
        gLasers.Laser[nextFreeSlot].FacingRight = TRUE;
    }
    else {
        gLasers.Laser[nextFreeSlot].X = gJetman.XPos - gLasers.Width - gLasers.JetmanXOffset;
        gLasers.Laser[nextFreeSlot].FacingRight = FALSE;
    }
    gLasers.Laser[nextFreeSlot].Y = gJetman.YPos + gLasers.JetmanYOffset;

}

void LasersDraw() {

    // if (!gLasers.Laser[0].On) return;

    glBindTexture(GL_TEXTURE_2D, gGame.Textures[gLasers.TextureIndex]);
    glVertexPointer(3, GL_FLOAT, 0, VertexArrayLasers);
    glColorPointer(4, GL_FLOAT, 0, ColorArrayLasers);
    glTexCoordPointer(2, GL_FLOAT, 0, TextureCoordinateArrayLasers);
    glDrawElements(GL_TRIANGLES, LASER_COUNT * 6, GL_DRAW_ELEMENTS_TYPE, IndiceArrayLasers);
}

void LasersMoveAndDraw() {

    LasersMove();
    
    if (InputCrossPressed() && !gInput.FingerOnCross) LaserStartNew();
    if (!InputCrossPressed()) {
        gInput.FingerOnCross = FALSE;
    }

    LasersSetVerticesAndColours();
    LasersDraw();
}
