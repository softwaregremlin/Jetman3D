#define INTRO_MODEL_COUNT 2

enum { IntroStatePreIntro, IntroStateIntro };

typedef struct {
    char ModelPath[50], TexturePath[50];
    float Rotation, RotationSpeed, DestinationYPos;
    float Vertices[TRINKET_MODEL_MAX_VERTICES * 3],
        ColourIndexes[TRINKET_MODEL_MAX_VERTICES * 4],
        TextureIndexes[TRINKET_MODEL_MAX_VERTICES * 2],
        YPos;
    GLUINT_ Indices[TRINKET_MODEL_MAX_INDICES];
    unsigned int TextureIndex, ModelNumber, IndiceCount, VerticeCount, TextureVerticeCount;
} structIntroModel;


typedef struct {
    unsigned int State, IsStart;
    int BackGroundFrames, BackGroundFrameLimits[2];
    float BackGroundSpeed,
        LogoZPos, LogoZSpeed,
        TrinketYPos, TrinketYSpeed,
        LogoYPos, LogoYSpeed,
        TextColourDirection, TextColourSpeed, TextScrollSpeed;
    structIntroModel Models[INTRO_MODEL_COUNT];
} structIntro;

///////////////////////////////////////////////////////////////

structIntro gIntro = {
    .IsStart = TRUE,
    .BackGroundFrameLimits = {-10, 50 },
    .BackGroundSpeed = -0.06f,    
    .TrinketYPos = 4.0f, .TrinketYSpeed = 0.01f,
    .LogoYPos = 1.0f, .LogoYSpeed = 0.01f,
    .LogoZPos = 4.0f, .LogoZSpeed = 0.01f,
    .TextColourDirection = 1.0f, .TextColourSpeed = 0.005f, .TextScrollSpeed = -0.02f,
    .Models = {
        {   .RotationSpeed = 2.0f,
            .DestinationYPos = 0.7f,
            .ModelPath = "/models/trinkets/",
            .ModelNumber = 3,
            .TextureIndex = 7
        },
        {   .RotationSpeed = 1.5f,
            .ModelPath = "/models/intro/",
            .TexturePath = "/textures/intro.png",
            .ModelNumber = 1,
            .TextureIndex = 0
        }
    }
};


void IntroInitialise() {
    for (unsigned int mm = 0; mm < INTRO_MODEL_COUNT; mm++) {
        ModelLoad(
            gIntro.Models[mm].ModelPath, 
            gIntro.Models[mm].ModelNumber,
            &gIntro.Models[mm].VerticeCount,
            &gIntro.Models[mm].IndiceCount,
            &gIntro.Models[mm].TextureVerticeCount,
            gIntro.Models[mm].Vertices,
            gIntro.Models[mm].Vertices,
            gIntro.Models[mm].ColourIndexes,
            gIntro.Models[mm].Indices,
            gIntro.Models[mm].TextureIndexes
        );
    }


    TextureLoad(gIntro.Models[1].TexturePath, gIntro.Models[1].TextureIndex);

    ColorArrayBWToRed(gIntro.Models[0].ColourIndexes, gIntro.Models[0].VerticeCount * 4);
}

/////////////////////////////////////


void IntroPart1() {
    glLoadIdentity();
    glTranslatef(0, 0.0f, gGame.WorldZOffset);

    // Background
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glBindTexture(GL_TEXTURE_2D, gGame.Textures[gParticleSettings.TextureIndex]);

    drawTriangles(gBackground.Vertices, gBackground.ColourIndexes,
        gBackground.TextureIndexes, gBackground.Indices, gBackground.IndiceCount);
   
    

    // Trinket
    if (gIntro.LogoZPos <= 0) {
        glPushMatrix();


        glTranslatef(0, gIntro.TrinketYPos, 0);
        if(gIntro.TrinketYPos > gIntro.Models[0].DestinationYPos)  gIntro.TrinketYPos -= gIntro.TrinketYSpeed;

        if (gIntro.TrinketYPos <= gIntro.Models[0].DestinationYPos) gIntro.State = IntroStateIntro;

        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
        glBindTexture(GL_TEXTURE_2D, gGame.Textures[gTrinketSettingsGame.TextureIndex]);
        drawTriangles(
            gIntro.Models[0].Vertices,
            gIntro.Models[0].ColourIndexes,
            gIntro.Models[0].TextureIndexes,
            gIntro.Models[0].Indices,
            gIntro.Models[0].IndiceCount);
        glPopMatrix();
    }

    // Logo
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, gGame.Textures[gIntro.Models[1].TextureIndex]);

    glPushMatrix();
        glTranslatef(0, gIntro.LogoYPos, gIntro.LogoZPos);

        if(gIntro.LogoZPos > 0) gIntro.LogoZPos -= gIntro.LogoZSpeed;

        if(gIntro.LogoZPos <= 0   && gIntro.LogoYPos >= 0 )  gIntro.LogoYPos -= gIntro.LogoYSpeed;
        
        drawTriangles(
            gIntro.Models[1].Vertices,
            gIntro.Models[1].ColourIndexes,
            gIntro.Models[1].TextureIndexes,
            gIntro.Models[1].Indices,
            gIntro.Models[1].IndiceCount);
    glPopMatrix();

}

void IntroPart2() {
    glLoadIdentity();
    glTranslatef(0, 0.0f, gGame.WorldZOffset);


    // Background
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glBindTexture(GL_TEXTURE_2D, gGame.Textures[gParticleSettings.TextureIndex]);

    drawTriangles(gBackground.Vertices, gBackground.ColourIndexes,
        gBackground.TextureIndexes, gBackground.Indices, gBackground.IndiceCount);

    gIntro.BackGroundFrames -= 1;

    if (gIntro.BackGroundFrames < gIntro.BackGroundFrameLimits[0]) {
        gIntro.BackGroundFrames = gIntro.BackGroundFrameLimits[1];

        int framesForward = gIntro.BackGroundFrameLimits[1] - gIntro.BackGroundFrameLimits[0];
        VerticeArrayTransformSection(0.0f, gIntro.BackGroundSpeed * framesForward, gIntro.BackGroundSpeed * -framesForward,
            gBackground.Vertices, 12, gBackground.VerticeCount * 3 - 1);
    }
    else {
        VerticeArrayTransformSection(0.0f, -gIntro.BackGroundSpeed, gIntro.BackGroundSpeed, gBackground.Vertices, 12, gBackground.VerticeCount * 3 - 1);

    }


    // Trinket
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, gGame.Textures[gTrinketSettingsGame.TextureIndex]);
    glPushMatrix();
        glTranslatef(0, gIntro.Models[0].DestinationYPos, 0);
        glRotatef(gIntro.Models[0].Rotation, 1.0f, 1.0f, 0.0f);
        gIntro.Models[0].Rotation += gIntro.Models[0].RotationSpeed;
        if (gIntro.Models[0].Rotation >= 360.0f) gIntro.Models[0].Rotation = 0;

        drawTriangles(
            gIntro.Models[0].Vertices,
            gIntro.Models[0].ColourIndexes,
            gIntro.Models[0].TextureIndexes,
            gIntro.Models[0].Indices,
            gIntro.Models[0].IndiceCount);

    glPopMatrix();

    // Logo
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, gGame.Textures[gIntro.Models[1].TextureIndex]);

    glPushMatrix();

    glRotatef(-gIntro.Models[1].Rotation, 0.0f, 1.0f, 0.0f);
    gIntro.Models[1].Rotation += gIntro.Models[1].RotationSpeed;
    if (gIntro.Models[1].Rotation >= 360.0f) gIntro.Models[1].Rotation = 0;

    drawTriangles(
        gIntro.Models[1].Vertices,
        gIntro.Models[1].ColourIndexes,
        gIntro.Models[1].TextureIndexes,
        gIntro.Models[1].Indices,
        gIntro.Models[1].IndiceCount);

    glPopMatrix();

    // Text
    gIntroText[gTextSettings.IntroTextLineIndex].CharacterWidth = 0.2f;
    gIntroText[gTextSettings.IntroTextLineIndex].CharacterHeight = 0.3f;

    TextDraw();

    gIntroText[gTextSettings.IntroTextLineIndex].Colour[1] += 
                (gIntro.TextColourSpeed * gIntro.TextColourDirection);
    if (gIntroText[gTextSettings.IntroTextLineIndex].Colour[1] >= 1.0f ||
        gIntroText[gTextSettings.IntroTextLineIndex].Colour[1] <= 0.0f ) {
        gIntro.TextColourDirection = gIntro.TextColourDirection * -1.0f;
    }
    gIntroText[gTextSettings.IntroTextLineIndex].X += gIntro.TextScrollSpeed;
       

    if (gIntroText[gTextSettings.IntroTextLineIndex].X <= gIntroText[gTextSettings.IntroTextLineIndex].ScrollLimits[0]) {
        gIntroText[gTextSettings.IntroTextLineIndex].X = gIntroText[gTextSettings.IntroTextLineIndex].ScrollLimits[1];
        gTextSettings.IntroTextLineIndex++;
        
        if (gTextSettings.IntroTextLineIndex >= gTextSettings.IntroTextLineCount) {
            gTextSettings.IntroTextLineIndex = 0;
        }
    }
}


void IntroDisplayFrame() {

    if (gIntro.IsStart) {
        SoundPlayLoop(gIntroSound);
        gIntro.IsStart = FALSE;
    }

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    if(gIntro.State == IntroStatePreIntro) IntroPart1();
    if(gIntro.State == IntroStateIntro) IntroPart2();

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);


    // Exit the Intro!
    if (InputCrossPressed() && !gInput.FingerOnCross && gIntro.State == IntroStateIntro) {

        //IntroInitialise();
        BackgroundInitialise();
        gGame.State = GameStateLevelStart;
        gInput.FingerOnCross = TRUE;
        gIntro.BackGroundFrames = 0;
        SoundPlayStop(gIntroSound);
    }

    // Flag to enforce repeated fire button presses
    if (!(InputCrossPressed())) gInput.FingerOnCross = FALSE;   
}