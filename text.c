
#define TEXT_ASCII_ZERO 48
#define TEXT_ASCII_NINE 57
#define TEXT_ASCII_BLANK -1
#define TEXT_ASCII_A 65
#define TEXT_ASCII_Z 90
#define TEXT_WIDE_CHAR_COUNT 2
#define TEXT_MAX_CHARS 100

// Settings for all Text
typedef struct {
    char TexturePath[50];
    unsigned int TextureIndex, TextureTilesPerRowColumn, TextureSpaceRow, TextureSpaceColumn;
    unsigned int IntroTextLineIndex, IntroTextLineCount;
    float IntroTextRotation, IntroTextRotationSpeed;
    float IntroXLimits[2];
    float TextureCharacterSpacing, TextureCharacterWidth, TextureCharacterWidthWide, TextureCharacterHeight;    
    float LifeCharTextureCoordinates[BILLBOARD_VERTICE_COUNT * 2];
    char WideChars[TEXT_WIDE_CHAR_COUNT];
} structTextSettings;

// Global Text Settings
structTextSettings gTextSettings = {
    .TextureIndex = 1,
    .TexturePath = "/textures/spectrumChars.png",
    .IntroXLimits = { -7.0f, 3.0f}, .IntroTextLineCount = 10,
    .IntroTextRotationSpeed = 0.5f,
    .TextureTilesPerRowColumn = 6, .TextureSpaceRow = 0, .TextureSpaceColumn = 6,
    .TextureCharacterSpacing = 9.0f / 64.0f, .TextureCharacterWidth = 8.0f / 64.0f, .TextureCharacterWidthWide = 9.0f / 64.0f,
    .TextureCharacterHeight = 8.0f / 64.0f,
    .WideChars = {'T','Y'},
    .LifeCharTextureCoordinates = {0.83, 0, 1.0, 0, 0.83, 0.17, 1.0, 0.17 }
};

typedef struct {
    float VertexArray[TEXT_MAX_CHARS * BILLBOARD_VERTICE_COUNT * 3];
    float ColourArray[TEXT_MAX_CHARS * BILLBOARD_VERTICE_COUNT * 4];
    float TextureCoordinateArray[TEXT_MAX_CHARS * BILLBOARD_VERTICE_COUNT * 2];
    GLUINT_ IndiceArray[TEXT_MAX_CHARS * BILLBOARD_INDICE_COUNT];
    unsigned int CharacterCount;
} structTextGLArrays;

// Line of Text!
typedef struct {
    char Text[TEXT_MAX_CHARS];
    unsigned int CharacterCount;
    float X, Y, Z, CharacterWidth, CharacterHeight;
    float ScrollLimits[2];
    float Colour[4];
} structTextLine;

typedef struct {
    structTextLine OneUp, Score, HiScoreLabel, HiScore, Lives, GameOver, StartGame, LifeSymbol;
}
structTextLines;

structTextLines gTextLines = {
    .OneUp = {.Text = "1UP", .CharacterCount = 3, .X = -3.1f, .Y = 1.4f, .Z = -4.0f,
              .CharacterWidth = 0.2f, .CharacterHeight = 0.2f, .Colour = {1.0f, 1.0f, 1.0f, 0.7f}},
    .Score = {.CharacterCount = 6, .X = -2.4f, .Y = 1.4f, .Z = -4.0f,
              .CharacterWidth = 0.2f, .CharacterHeight = 0.2f, .Colour = {1.0f, 1.0f, 0.0f, 0.7f}},
    .HiScoreLabel = {.Text = "HI", .CharacterCount = 2, .X = 0.9f, .Y = 1.4f, .Z = -4.0f,
              .CharacterWidth = 0.2f, .CharacterHeight = 0.2f, .Colour = {0.0f, 1.0f, 1.0f, 0.7f}},
    .HiScore = {.CharacterCount = 6, .X = 1.45f, .Y = 1.4f, .Z = -4.0f,
              .CharacterWidth = 0.2f, .CharacterHeight = 0.2f, .Colour = {1.0f, 1.0f, 0.0f, 0.7f}},
    .Lives = {.Text = "4", .CharacterCount = 1, .X = -0.3f, .Y = 1.4f, .Z = -4.0f,
              .CharacterWidth = 0.2f, .CharacterHeight = 0.2f, .Colour = {1.0f, 1.0f, 1.0f, 0.7f}},
    .LifeSymbol = {.Text = "L", .CharacterCount = 1, .X = -0.1f, .Y = 1.4f, .Z = -4.0f,
              .CharacterWidth = 0.2f, .CharacterHeight = 0.2f, .Colour = {1.0f, 1.0f, 1.0f, 0.7f}},
    .GameOver = {.Text = "GAME OVER PLAYER 1", .CharacterCount = 18, .X = -1.9f, .Y = 0, .Z = -4.0f,
              .CharacterWidth = 0.2f, .CharacterHeight = 0.2f, .Colour = {1.0f, 1.0f, 1.0f, 1.0f}}
};

structTextLine gIntroText[] = {
        {.Text = "JETMAN 3D GAME SELECTION", .CharacterCount = 24, .X = 5.0f, .Y = -1.55f, .Z = -4.0f,
              .ScrollLimits = {-10.0f, 3.0f}, .CharacterWidth = 0.2f, .CharacterHeight = 0.3f, .Colour = {1.0, 0.25f, 0.0f, 0.7f}},
        {.Text = PLATFORM_SPECIFIC_MSG1, .CharacterCount = 50, .X = 3.0f, .Y = -1.55f, .Z = -4.0f,
              .ScrollLimits = {-7.0f, 3.0f}, .CharacterWidth = 0.2f, .CharacterHeight = 0.3f, .Colour = {1.0, 0.25f, 0.0f, 0.7f}},
        {.Text = PLATFORM_SPECIFIC_MSG2, .CharacterCount = 50, .X = 3.0f, .Y = -1.55f, .Z = -4.0f,
              .ScrollLimits = {-12.0f, 3.0f}, .CharacterWidth = 0.2f, .CharacterHeight = 0.3f, .Colour = {1.0, 0.25f, 0.0f, 0.7f}},
        {.Text = "USE THE DIRECTIONAL PAD OR LEFT JOYSTICK TO CONTROL THE JETPACK",
              .ScrollLimits = {-15.0f, 3.0f}, .CharacterCount = 65, .X = 3.0f, .Y = -1.55f, .Z = -4.0f,
              .CharacterWidth = 0.2f, .CharacterHeight = 0.3f, .Colour = {1.0, 0.25f, 0.0f, 0.7f}},
        {.Text = "SHOOT ALIENS AND COLLECT PIECES OF YOUR SPACESHIP", .CharacterCount = 50, .X = 3.0f, .Y = -1.55f, .Z = -4.0f,
              .ScrollLimits = {-12.0f, 3.0f}, .CharacterWidth = 0.2f, .CharacterHeight = 0.3f, .Colour = {1.0, 0.25f, 0.0f, 0.7f}},
        {.Text = "THEN FUEL UP AND TAKE OFF", .CharacterCount = 25, .X = 3.0f, .Y = -1.55f, .Z = -4.0f,
              .ScrollLimits = {-7.0f, 3.0f}, .CharacterWidth = 0.2f, .CharacterHeight = 0.3f, .Colour = {1.0, 0.25f, 0.0f, 0.7f}},
        {.Text = "GAME BY GREMLIN SOFTWARE", .CharacterCount = 24, .X = 3.0f, .Y = -1.55f, .Z = -4.0f,
              .ScrollLimits = {-7.0f, 3.0f}, .CharacterWidth = 0.2f, .CharacterHeight = 0.3f, .Colour = {1.0, 0.25f, 0.0f, 0.7f}},
        {.Text = "BASED ON AN EARLY 80S ZX SPECTRUM CLASSIC", .CharacterCount = 42, .X = 3.0f, .Y = -1.55f, .Z = -4.0f,
              .ScrollLimits = {-12.0f, 3.0f}, .CharacterWidth = 0.2f, .CharacterHeight = 0.3f, .Colour = {1.0, 0.25f, 0.0f, 0.7f}},
        {.Text = PLATFORM_SPECIFIC_MSG3, .CharacterCount = 33, .X = 3.0f, .Y = -1.55f, .Z = -4.0f,
              .ScrollLimits = {-9.0f, 3.0f}, .CharacterWidth = 0.2f, .CharacterHeight = 0.3f, .Colour = {1.0, 0.25f, 0.0f, 0.7f}},
        {.Text = "ENJOY AND GOOD LUCK", .CharacterCount = 24, .X = 3.0f, .Y = -1.55f, .Z = -4.0f,
              .ScrollLimits = {-7.0f, 3.0f}, .CharacterWidth = 0.2f, .CharacterHeight = 0.3f, .Colour = {1.0, 0.25f, 0.0f, 0.7f}}
};

structTextGLArrays gTextGLArrays = { .ColourArray = BILLBOARD_COLOUR_ARRAY, .IndiceArray = BILLBOARD_INDICE_ARRAY }; 
////////////////////////////////////////////////

int TextGetSequenceNumberFromChar(char ch) {
    // Digits 0-9
    if (ch >= TEXT_ASCII_ZERO && ch <= TEXT_ASCII_NINE) return ch - TEXT_ASCII_ZERO;
    // Letters A-Z
    if (ch >= TEXT_ASCII_A && ch <= TEXT_ASCII_Z) return ch - TEXT_ASCII_A + 10;
    // Anything else will be a space
    return TEXT_ASCII_BLANK;
}

void TextSetTextureCoordinatesFromChar(char ch, float textureCoordinateArray[], unsigned int arrayOffset) {
    int sequenceNumber = TextGetSequenceNumberFromChar(ch);
    unsigned row = sequenceNumber == TEXT_ASCII_BLANK ?
            gTextSettings.TextureSpaceRow : sequenceNumber / gTextSettings.TextureTilesPerRowColumn,
        column = sequenceNumber == TEXT_ASCII_BLANK ?
            gTextSettings.TextureSpaceColumn : sequenceNumber % gTextSettings.TextureTilesPerRowColumn;

    if (sequenceNumber == TEXT_ASCII_BLANK) {
        BillboardSetTextureCoordinates(textureCoordinateArray, arrayOffset, 0, 0, 0, 0);
        return;
    }

    BillboardSetTextureCoordinates(textureCoordinateArray, arrayOffset,
        column * gTextSettings.TextureCharacterSpacing, row * gTextSettings.TextureCharacterSpacing,
        gTextSettings.TextureCharacterWidth, gTextSettings.TextureCharacterHeight);
}

void TextAddLine(structTextLine textLine) {

    float xOffset = 0;
    
    for (unsigned int cc = 0; cc < textLine.CharacterCount; cc++) {
        // Offset in the global array
        unsigned int arrayCharPos = gTextGLArrays.CharacterCount + cc;
        
        // Set Texture coodinates for this Character
        TextSetTextureCoordinatesFromChar(
            textLine.Text[cc], gTextGLArrays.TextureCoordinateArray, arrayCharPos * BILLBOARD_VERTICE_COUNT * 2);

        // Set Vetices coodinates for this Character
        float widthToAdd = textLine.CharacterWidth / (textLine.Text[cc] == ' ' ? 2.0f : 1.0f);
        xOffset += widthToAdd;
        BillboardSetVerticePositionsByBottomLeft(
            gTextGLArrays.VertexArray, arrayCharPos * BILLBOARD_VERTICE_COUNT * 3,
            textLine.X + xOffset, textLine.Y, textLine.Z, textLine.CharacterWidth, textLine.CharacterHeight);

        // Set the colour
        unsigned int colourArrayOffet = arrayCharPos * BILLBOARD_VERTICE_COUNT * 4;
        for (unsigned int colour = 0; colour < BILLBOARD_VERTICE_COUNT; colour++) {
            for (unsigned int rgba = 0; rgba < 4; rgba++) {
                gTextGLArrays.ColourArray[(colour * 4) + colourArrayOffet + rgba] = textLine.Colour[rgba];
            }
        }

        // Set the indice sequence to the standard 2 triangles for a Billboard Sprite
        unsigned int indiceArrayOffet = arrayCharPos * BILLBOARD_INDICE_COUNT;
        for (unsigned int ii = 0; ii < BILLBOARD_INDICE_COUNT; ii++) {
            gTextGLArrays.IndiceArray[ii + indiceArrayOffet] = 
                gBillboardSettings.IndiceArray[ii] + (arrayCharPos * BILLBOARD_VERTICE_COUNT);
        }
    }
    gTextGLArrays.CharacterCount += textLine.CharacterCount;
}



void TextInitialise() {
    TextureLoad(gTextSettings.TexturePath, gTextSettings.TextureIndex);
}

void TextSetLifeCharTextureCoordinates() {
    // Special case / character symbol for lives
    unsigned int startPos = (gTextGLArrays.CharacterCount * BILLBOARD_VERTICE_COUNT * 2) - BILLBOARD_VERTICE_COUNT * 2;
    for (unsigned int ll = startPos; ll < startPos + BILLBOARD_VERTICE_COUNT * 2; ll++) {
        gTextGLArrays.TextureCoordinateArray[ll] = gTextSettings.LifeCharTextureCoordinates[ll - startPos];
    }
}


void TextAddLinesLives() {
    if (gGame.Lives < 0) return;
    TextAddLine(gTextLines.Lives);
    TextAddLine(gTextLines.LifeSymbol);
    TextSetLifeCharTextureCoordinates();    
}

void TextAddLinesGame() {
    TextAddLine(gTextLines.OneUp);
    TextAddLine(gTextLines.Score);
    TextAddLine(gTextLines.HiScoreLabel);
    TextAddLine(gTextLines.HiScore);
    TextAddLinesLives();
}

void TextAddLinesGameOver() {
    TextAddLine(gTextLines.GameOver);
}

void TextAddLinesIntro() {
    TextAddLine(gIntroText[gTextSettings.IntroTextLineIndex]);
}

void TextDraw() {
    
    sprintf(gTextLines.Score.Text, "%06d", gGame.Score);
    sprintf(gTextLines.HiScore.Text, "%06d", gGame.HiScore);
    sprintf(gTextLines.Lives.Text, "%d", gGame.Lives);
    //sprintf(gTextLines.HiScore.Text, "%06d", fps);

    gTextGLArrays.CharacterCount = 0;

    if (gGame.State != GameStateOver && gGame.State != GameStateIntro)  TextAddLinesGame();
    if (gGame.State == GameStateOver)  TextAddLinesGameOver();
    if (gGame.State == GameStateIntro) TextAddLinesIntro();
    
    glPushMatrix();
        glLoadIdentity();
    
        glBindTexture(GL_TEXTURE_2D, gGame.Textures[gTextSettings.TextureIndex]);

        // Rotation - Intro Only!
        if (gGame.State == GameStateIntro) {
            gTextSettings.IntroTextRotation += gTextSettings.IntroTextRotationSpeed;
            glRotatef(gTextSettings.IntroTextRotation, 0, 0, 1.0f);
            if (gTextSettings.IntroTextRotation > 360.0f) gTextSettings.IntroTextRotation = 0;
        }


        drawTriangles(
            gTextGLArrays.VertexArray,
            gTextGLArrays.ColourArray,
            gTextGLArrays.TextureCoordinateArray,
            gTextGLArrays.IndiceArray,
            BILLBOARD_INDICE_COUNT * gTextGLArrays.CharacterCount);
    
    glPopMatrix();
    
}