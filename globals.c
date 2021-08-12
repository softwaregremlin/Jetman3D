
#define TRUE 1
#define FALSE 0
#define PI 3.14159265f
#define RADIAN_TO_DEGREES = PI / 180.0f
#define TEXTURE_COUNT 9
#define LEVEL_COUNT 16
#define EXTRA_LIFE_TARGET_COUNT 20

enum { GameStateIntro,
       GameStateModelView,
       GameStateLevelStart, GameStateLevelReStart, GameStateLevel, GameStateLevelComplete, 
       GameStateLifeLost,
       GameStateOver};

typedef struct {
    unsigned int AlienIndex, RocketIndex, RocketInPieces;
} structLevel;

typedef struct {
    unsigned int Score, HiScore, Level,
        HiScoreSaveTimer, HiScoreSaveInterval,
        State, GameOverFrame, GameOverFrameCount,
        // InputFingerOnCross,
        JetManCollisionDisabled, JetManMovementDisabled,
        CheatInifinteLives,
        CheatSingleGas,
        ExtraLifeTargetIndex,
        ExtraLifeTargets[EXTRA_LIFE_TARGET_COUNT];
  
    int Lives, LivesInitial;
                   
    float WorldZOffset, OriginalWorldZOffset, LookAtY,
          LevelCompleteZoomOutSpeed;

    char DataPath[50];
    GLuint Textures[TEXTURE_COUNT];

    structLevel Levels[LEVEL_COUNT];
} structGame;


typedef struct {
    unsigned int Left, Right, Up, Down, Fire, In, Out, 
        FingerOnCross,
        LeftTriggerHeld, RightTriggerHeld;
} structInput;

structInput gInput, gInputTest;

typedef struct {
    float X, Y, Z, Width, Height, Depth;
} structCuboid;

typedef struct {
    char Folder[30], HighScore[30], Level[30], MaxLevel[30];
} structDataPaths;

//////////////////////////////////////////////
//******************************************//
//////////////////////////////////////////////
structGame gGame = {
    .HiScoreSaveInterval = 5,
    .WorldZOffset = -6.0f, .OriginalWorldZOffset = -6.0f,
    .LevelCompleteZoomOutSpeed = -0.0025f,
    .GameOverFrameCount = 120,

    //.State = GameStateModelView,
    .State = GameStateIntro,
    //.State = GameStateLevelStart,

    //.State = GameStateOver, 
    .Level = 1,

    .Lives = 4, .LivesInitial = 4,

    //.CheatInifinteLives = TRUE,
    // .CheatSingleGas = TRUE,

    //.JetManCollisionDisabled = TRUE,
    //.JetManMovementDisabled = TRUE,
    
    .ExtraLifeTargets =
        {  5000, 10000, 20000, 30000, 50000, 70000, 100000, 150000, 200000, 250000, 300000, 400000, 500000 },

    // 16 Levels, but the aliens repeat themselves after #8. Rocket changes every 4 levels
    .Levels =  {
        {.AlienIndex=0, .RocketIndex=0, .RocketInPieces=TRUE}, {.AlienIndex=1, .RocketIndex=0}, {.AlienIndex=2, .RocketIndex=0}, {.AlienIndex=3, .RocketIndex=0},
        {.AlienIndex=4, .RocketIndex=1, .RocketInPieces=TRUE}, {.AlienIndex=5, .RocketIndex=1}, {.AlienIndex=6, .RocketIndex=1}, {.AlienIndex=7, .RocketIndex=1},
        {.AlienIndex=0, .RocketIndex=2, .RocketInPieces=TRUE}, {.AlienIndex=1, .RocketIndex=2}, {.AlienIndex=2, .RocketIndex=2}, {.AlienIndex=3, .RocketIndex=2},
        {.AlienIndex=4, .RocketIndex=3, .RocketInPieces=TRUE}, {.AlienIndex=5, .RocketIndex=3}, {.AlienIndex=6, .RocketIndex=3}, {.AlienIndex=7, .RocketIndex=3}
    }
};

//////////////////////////////////////////////
//******************************************//
//////////////////////////////////////////////


// static GLuint myTextures[TEXTURE_COUNT];

int frameCounter = 0, fps = 0, target_fps = 60;
// int isFirstFrame = 0;


// Function headers
void drawTriangles(float vertexArray[], float colourArray[], float textureArray[],
    GLUINT_ indiceArray[], unsigned int indicesCount);

void SaveHighScore();
