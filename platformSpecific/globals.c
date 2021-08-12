
#define GLUINT uint16_t
#define GLUINT_ uint16_t
#define GL_DRAW_ELEMENTS_TYPE GL_UNSIGNED_SHORT

typedef struct {
	char DataPath[50];
	char IntroLines[3][50];	
} structPlatformSpecific;

structPlatformSpecific gPlatformSpecific = { .DataPath = "app0:data" };

// Saved data paths
#define DATA_FOLDER   "ux0:data/vitaGLJetPac"
#define DATA_HISCORE  "ux0:data/vitaGLJetPac/hi"
#define DATA_LEVEL    "ux0:data/vitaGLJetPac/lev"
#define DATA_MAXLEVEL "ux0:data/vitaGLJetPac/maxlev"

// Parts of the Intro Text
#define PLATFORM_SPECIFIC_MSG1 "PRESS X TO BEGIN"
#define PLATFORM_SPECIFIC_MSG2 "X IS ALSO THE FIRE BUTTON"
#define PLATFORM_SPECIFIC_MSG3 "VITA GL LIBRARY BY RINNEGATAMANTE"

GLenum texture_format = GL_RGB;
vitaWav *gFireSound;
vitaWav *gExplosionSound;
vitaWav *gLevelStartSound;
vitaWav *gRocketPickupSound;
vitaWav *gRocketAssembleSound;
vitaWav *gTrinketPickupSound;
vitaWav *gRocketSound;
vitaWav *gRocketDescSound;
vitaWav *gIntroSound;
