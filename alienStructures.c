#define ALIEN_MAX_COUNT 8

#define ALIEN_EYE_TILE_COUNT 5
#define ALIEN_EYE_TILE_MIRROR_COUNT 2
#define ALIEN_EYE_PUPIL_FRAMES_COUNT 2
#define ALIEN_SPECIES_COUNT 8

enum {AlienStateOn, AlienStateOff, AlienStateExploding};
enum {AlienColourRed, AlienColourGreen, AlienColourMagenta, AlienColourCyan, AlienColourWhite};
////////////
//unsigned int gAlienVerticeCount, gAlienIndiceCount, gAlienTextureVerticeCount;
//////////////////////////////////////////
// Structure Definitions

typedef struct {
	char ModelPath[50], TexturePath[50];
	unsigned int VerticeCount, IndiceCount, TextureVerticeCount;
	unsigned int TextureIndex, TextureLoaded;
	unsigned int EyeTileRows, EyeTileColumns, EyeTileMirrorFrom, EyeFramesPerFrame;
	unsigned int ShowCollisionRectangles;
	unsigned int MinSidewaysFrame, MaxSidewaysFrames;
	unsigned int JumpJetStartingFrameCount, JumpJetStartingBounceFrames;
	unsigned int PupilMovementFramesLeft[ALIEN_EYE_PUPIL_FRAMES_COUNT],
		PupilMovementFramesRight[ALIEN_EYE_PUPIL_FRAMES_COUNT];
	float EyeTextureVertices[ALIEN_EYE_TILE_COUNT + ALIEN_EYE_TILE_MIRROR_COUNT][BILLBOARD_VERTICE_COUNT * 2];
	int EyeAnimationSequence[50];

	float TopLimit, BottomLimit, XWrapLimit, LeftLimit, RightLimit, WrapXShift;
	float DownwardRotationAngle, ExplosionZIncrement, FadeSpeed;
	float ScaleFactorInGame;
	float JumpJetXPos, JumpJetStartingYBottom;

} structAlienSettingsGame;

typedef struct {
	unsigned int HasEyes, DownwardRotationEnabled, MovesDiagonally, ExplodesOnSceneryCollision,
		DownwardRotationProability, XRotationEnabled, 
		WrapLimit,
		YRotationEnabled, YRotationInterval,
		ParticlesEnabled, DeformationEnabled, BubbleDeformationEnabled, SidewaysMovementEnabled,
		YSpeedAlternateEnabled,
		IsJumpJet, IsGuided, IsGuidedX, IsGuidedY, GuidanceFrames,
		InitialDelayInterval,
		ScorePerAlien;
	float InitialVertices[1000];
	float Speed, XSpeed, 
		  YSpeedAlternate,
		  XRotationSpeed, YRotationSpeed;
	float CollisionRectangleHeight, CollisionRectangleWidth,
		CollisionRectangleXOffset, CollisionRectangleYOffset,
		CollisionRectangleYOffsetDownwardRotation,
		CollisionGroundYOffset, CollisionSceneryFactor;

} structAlienSettingsLevel;

typedef struct {
	unsigned int EyeFrame, EyeFrameCounter, State;
	unsigned int FacingRight, MovingUp, DownwardRotationEnabled, InitialDelay;
	unsigned int WrapCount;
	unsigned int MovingSideways, SidewaysFrame, SidewaysFrames;
	unsigned int YRotationDelayCounter, Colour;
	unsigned int JumpJetStarting, JumpJetStartingBounceFrame, JumpJetStartingFrameCount;
	unsigned int GuidanceFrame;
	unsigned int DeformationOriginalPointsSet;
	//float Vertices[1000], ColourIndexes[1000], TextureIndexes[2000];
	float Vertices[1000], ColourIndexes[1000], TextureIndexes[2000];
	GLUINT_ Indices[1000];
	float XPos, YPos, XOffset, YOffset, YSpeed,
		XRotationAngle, YRotationAngle,
		XCollisionMultiplier, YCollisionMultiplier;
	float CollisionXPos, CollisionYPos;
	float Alpha;
} structAlien;

//////////////////////////////////
// Instances

structAlienSettingsGame gAlienSettingsGame = {
	.ModelPath = "/models/aliens/",
	.TexturePath = "/textures/aliens.png",
	.TextureIndex = 7,
	.EyeTileRows = 3, .EyeTileColumns = 3, .EyeTileMirrorFrom = 1, .EyeFramesPerFrame = 5,
	.MinSidewaysFrame = 60, .MaxSidewaysFrames = 180,
	.PupilMovementFramesLeft = {1,2}, .PupilMovementFramesRight = {5,6},
	.EyeAnimationSequence = {0,0,0,0,0,1,2,1,0,5,6,5,0,0,0,0,3,4,3,-1},

	.JumpJetStartingFrameCount = 300, .JumpJetStartingBounceFrames = 120,

	.TopLimit = 3.5f, .BottomLimit = -1.05f,
	.XWrapLimit = 4.5f, .LeftLimit = -4.5f, .RightLimit = 4.5f, .WrapXShift = 8.5f,
	.DownwardRotationAngle = 15.0f,
	.ExplosionZIncrement = 0.001f,
	.FadeSpeed = 0.02f,
	.ScaleFactorInGame = 0.35f,
	.JumpJetXPos = -3.75f, .JumpJetStartingYBottom = -0.4f
    // , .ShowCollisionRectangles = TRUE
};

// 
structAlienSettingsLevel gAlienSettingsSpecies[ALIEN_SPECIES_COUNT] = {
	// Comets
	{	.Speed = 0.05f,
		.ExplodesOnSceneryCollision = TRUE,
		.XRotationEnabled = TRUE, .XRotationSpeed = 1.5f,
		.YRotationEnabled = FALSE,
		.CollisionRectangleWidth = 0.45f, .CollisionRectangleHeight = 0.45f,
		.CollisionRectangleXOffset = -0.07f, .CollisionRectangleYOffsetDownwardRotation = -0.15f,
		.CollisionGroundYOffset = 0.25f,

		.MovesDiagonally = FALSE,
		.DownwardRotationEnabled = TRUE, .DownwardRotationProability = 1,
		.WrapLimit = 3,
		.ParticlesEnabled = TRUE,
		.DeformationEnabled = FALSE,

		.InitialDelayInterval = 60,
		.ScorePerAlien = 25
	},
	// "Kina"
	{	.Speed = 0.025f,
		.ExplodesOnSceneryCollision = FALSE,
		.XRotationEnabled = FALSE,
		.YRotationEnabled = TRUE, .YRotationSpeed = 1.5f, .YRotationInterval = 240,
		
		.CollisionRectangleWidth = 0.55f, .CollisionRectangleHeight = 0.55f,
		.CollisionRectangleXOffset = -0.07f, // .CollisionRectangleYOffsetDownwardRotation = -0.15f,
		.CollisionGroundYOffset = 0.25f,
		.CollisionSceneryFactor = 1.5f,
		
		.MovesDiagonally = TRUE,
		.DownwardRotationEnabled = FALSE, .DownwardRotationProability = 0,
		.ParticlesEnabled = FALSE,
		.DeformationEnabled = TRUE,

		.InitialDelayInterval = 60,
		.ScorePerAlien = 25,
		.HasEyes = TRUE
	},
	// Bubble
	{	.Speed = 0.025f,
		.YRotationEnabled = TRUE, .YRotationSpeed = 1.5f, .YRotationInterval = 240,
		.MovesDiagonally = TRUE, .SidewaysMovementEnabled = TRUE, .BubbleDeformationEnabled = TRUE,
		.CollisionRectangleWidth = 0.55f, .CollisionRectangleHeight = 0.55f,
		.CollisionRectangleXOffset = -0.07f,
		.CollisionGroundYOffset = 0.25f,
		.CollisionSceneryFactor = 1.5f,
		.InitialDelayInterval = 60,
		.ScorePerAlien = 25,
	},
	// Jump Jet
	{	.Speed = 0.025f, .XSpeed = 0.05f,
		.ExplodesOnSceneryCollision = TRUE,
		.MovesDiagonally = TRUE, .SidewaysMovementEnabled = FALSE, .BubbleDeformationEnabled = FALSE,
		.CollisionRectangleWidth = 0.75f, .CollisionRectangleHeight = 0.3f,
		.CollisionRectangleXOffset = -0.05f, 
		.CollisionGroundYOffset = 0.25f,
		.IsJumpJet = TRUE,
		.IsGuided = TRUE, .IsGuidedY = TRUE,
		.GuidanceFrames = 30,
		.ScorePerAlien = 25
	},
	// Saucer
	{	.Speed = 0.025f, 
		.YRotationEnabled = TRUE, .YRotationSpeed = 3.0f, .YRotationInterval = 0,
		.MovesDiagonally = TRUE,  .SidewaysMovementEnabled = TRUE, 
		.CollisionRectangleWidth = 0.6f, .CollisionRectangleHeight = 0.40f,
		.CollisionRectangleXOffset = -0.07f,
		.CollisionGroundYOffset = 0.25f,
		.CollisionSceneryFactor = 1.5f,
		.IsJumpJet = FALSE,
		.IsGuided = TRUE, .IsGuidedX = TRUE, .IsGuidedY = TRUE, .GuidanceFrames = 30,
		.InitialDelayInterval = 60,
		.ScorePerAlien = 25,
	},
	// Station
	{	.Speed = 0.025f, .YSpeedAlternate = 0.005f, .YSpeedAlternateEnabled = TRUE,
		.ExplodesOnSceneryCollision = FALSE,
		.YRotationEnabled = TRUE, .YRotationSpeed = 4.0f, .YRotationInterval = 0,
		.MovesDiagonally = TRUE, .SidewaysMovementEnabled = FALSE,
		.CollisionRectangleWidth = 0.55f, .CollisionRectangleHeight = 0.55f,
		.CollisionRectangleXOffset = -0.07f, 
		.CollisionGroundYOffset = 0.25f,
		.CollisionSceneryFactor = 1.5f,
		
		.IsGuided = FALSE, .IsGuidedX = FALSE, .IsGuidedY = FALSE, .GuidanceFrames = 0,
		// .DeformationEnabled = TRUE,
		.InitialDelayInterval = 60,
		.ScorePerAlien = 25
		//.HasEyes = TRUE
	},
	// Falcon
	{	.Speed = 0.05f,  .YSpeedAlternate = 0.0f, .YSpeedAlternateEnabled = FALSE,
		.ExplodesOnSceneryCollision = TRUE,
		.XRotationEnabled = TRUE, .XRotationSpeed = 1.5f,
		.YRotationEnabled = FALSE,
		.MovesDiagonally = FALSE, .SidewaysMovementEnabled = FALSE,

		.CollisionRectangleWidth = 0.45f, .CollisionRectangleHeight = 0.45f,
		.CollisionRectangleXOffset = -0.07f, .CollisionRectangleYOffsetDownwardRotation = -0.15f,
		.CollisionGroundYOffset = 0.25f,
		.CollisionSceneryFactor = 0,
		.DownwardRotationEnabled = TRUE,
		.DownwardRotationProability = 1,

		.IsGuided = FALSE, .IsGuidedX = FALSE, .IsGuidedY = FALSE, .GuidanceFrames = 0,

		//.ParticlesEnabled = TRUE,
		.InitialDelayInterval = 60,
		.ScorePerAlien = 25
	},
	// Owl
	{	.Speed = 0.025f,
		.YRotationEnabled = TRUE, .YRotationSpeed = 1.5f, .YRotationInterval = 240,
		.MovesDiagonally = TRUE,
		.CollisionRectangleWidth = 0.55f, .CollisionRectangleHeight = 0.55f,
		.CollisionRectangleXOffset = -0.07f, // .CollisionRectangleYOffsetDownwardRotation = -0.15f,
		.CollisionGroundYOffset = 0.25f,
		.CollisionSceneryFactor = 1.5f,
		.IsGuided = TRUE, .IsGuidedX = TRUE, .IsGuidedY = TRUE, .GuidanceFrames = 30,
		// .DeformationEnabled = TRUE,
		.InitialDelayInterval = 60,
		.ScorePerAlien = 25,
		.HasEyes = TRUE
	}
};

structAlien gAliens[ALIEN_MAX_COUNT];
structExplosion gAlienExplosions[ALIEN_MAX_COUNT];

float gAlienVerticesTEMP[1000];

void AlienParticlesInitialiseInstance(unsigned int index);