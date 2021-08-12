#define ROCKET_COUNT 4
#define ROCKET_SECTION_COUNT 3
#define ROCKET_FUEL_LEVEL_COUNT 6
#define ROCKET_MODEL_INDEX_COUNT 1000

enum {
	RocketStatePieces, RocketStateAssembled, RocketStateFuelled, RocketStateTakeOff, RocketStateLanding
};

enum {
	RocketSectionStateResting, RocketSectionStateRestingCollectable, RocketSectionStateCollected,
	RocketSectionStateFalling, RocketSectionStateFallingToAssembly, RocketSectionStateAssembled,
};

typedef struct {

	char ModelPath[50], TexturePath[50];

	unsigned int TextureIndex, TextureLoaded, CollisionRectangleDraw, BaseSectionIndex,
		ColorPulsateFrameCount, SectionPickupScore;

	float Scale, AssembledXPos, AssembledYPos, AssembledZPos,
		CarryingZOffset, CarryingYOffset, CarryingAlpha, HiddenZOffset,
		FallSpeed, PlatformCollisionYOffset,
		TakeOffLandingSpeed, TakeOffToLandingHeight, MaxHeight;

} structRocketSettingsGame;


typedef struct {
	unsigned int State, VerticeStartIndex, VerticeEndIndex, 
				 IndiceStartIndex, IndiceEndIndex;
	float XPos, YPos, XPosOriginal, YPosOriginal,
		  CollisionRecYOffset, CollisionRecHeight, CollisionRecWidth, Alpha;
	float GroundCollisionY;
} structRocketSection;

typedef struct {

	float VerticesOriginal[ROCKET_MODEL_INDEX_COUNT];
	float Vertices[ROCKET_MODEL_INDEX_COUNT], ColourIndexes[ROCKET_MODEL_INDEX_COUNT], TextureIndexes[ROCKET_MODEL_INDEX_COUNT];
	GLUINT_ Indices[ROCKET_MODEL_INDEX_COUNT];

	unsigned int VerticeCount, IndiceCount, TextureVerticeCount;
	unsigned int State, FuelLevel, FuelLevelVerticeNumbers[ROCKET_FUEL_LEVEL_COUNT][2];
	unsigned int ColorPulsateDirection, ColorPulsateFrame;

	float YPos;
	float CollisionXPos, CollisionYPos;
	float Alpha, Scale;

	structRocketSection Sections[ROCKET_SECTION_COUNT];

} structRocket;

//////////////
// Instances
//////////////

structRocketSettingsGame gRocketSettingsGame = {
	.ModelPath = "/models/rockets/",
	.TexturePath = "/textures/rockets.png",
	.TextureIndex = 8, 
	.BaseSectionIndex = 2,
	.SectionPickupScore = 100,
	/////////////////////////////////
	// .CollisionRectangleDraw = TRUE,
	////////////////////////////////
	.Scale = 0.75f,
	.AssembledXPos = 1.4f, .AssembledYPos = 0.57f, .AssembledZPos = -0.45f,
	.CarryingZOffset = 0.4f,
	.CarryingYOffset = 0.4f,
	.CarryingAlpha = 0.5f,

	.ColorPulsateFrameCount = 30,

	.HiddenZOffset = -1000.0f,
	.FallSpeed = 0.025f,
	.PlatformCollisionYOffset = 0.05f,
	.TakeOffLandingSpeed = 0.0125f,
	.TakeOffToLandingHeight = 6.25f,
	.MaxHeight = 7.0f
};

structRocket gRockets[ROCKET_COUNT] = {
	// Levels 1-4: Apollo
	{
		.State = RocketStatePieces,
		.FuelLevelVerticeNumbers = { {113,150}, {80,112}, {54,79}, {34,53}, {9,33}, {0,8} },
		.Sections = {
			{ .VerticeStartIndex = 0,   .VerticeEndIndex = 33,
			  .XPos = -2.55f, .YPos = 2.38f, .Alpha = 1.0f, 
			  .CollisionRecYOffset = -0.55f,
			  .CollisionRecHeight = 0.55f, .CollisionRecWidth = 0.4f, .Alpha = 1.0f,
			  .GroundCollisionY = -0.75f,
			  .State = RocketSectionStateResting },

			{ .VerticeStartIndex = 34, .VerticeEndIndex = 79,
			  .XPos = -0.02f, .YPos = 2.45f,
			  .CollisionRecYOffset = -1.20f,
			  .CollisionRecHeight = 0.65f, .CollisionRecWidth = 0.4f, .Alpha = 1.0f,
			  .GroundCollisionY = -0.15f,
			  .State = RocketSectionStateRestingCollectable},

			{ .VerticeStartIndex = 80, .VerticeEndIndex = 150,
			  .IndiceStartIndex = 180, .IndiceEndIndex = 374,
			  .XPos = 1.4f,   .YPos = 0.57f, .Alpha = 1.0f,
			  .CollisionRecYOffset = -1.85f,
			  .CollisionRecHeight = 0.65f, .CollisionRecWidth = 0.3f,
			  .State = RocketSectionStateAssembled }
		}
	},

	// Levels 5-8: Space Shuttle
	{
		.State = RocketStatePieces,
		.FuelLevelVerticeNumbers = { {131,171}, {96,130}, {72,95}, {48,71}, {24,47}, {0,23} },
		.Sections = {
			{.VerticeStartIndex = 0,   .VerticeEndIndex = 47,
			  .XPos = -2.55f, .YPos = 2.38f, .Alpha = 1.0f,
			  .CollisionRecYOffset = -0.55f,
			  .CollisionRecHeight = 0.55f, .CollisionRecWidth = 0.4f, .Alpha = 1.0f,
			  .GroundCollisionY = -0.75f,
			  .State = RocketSectionStateResting },

			{.VerticeStartIndex = 48, .VerticeEndIndex = 95,
			  .XPos = -0.02f, .YPos = 2.45f,
			  .CollisionRecYOffset = -1.20f,
			  .CollisionRecHeight = 0.65f, .CollisionRecWidth = 0.4f, .Alpha = 1.0f,
			  .GroundCollisionY = -0.15f,
			  .State = RocketSectionStateRestingCollectable},

			{.VerticeStartIndex = 96, .VerticeEndIndex = 171,
			  
			  .XPos = 1.4f,   .YPos = 0.57f, .Alpha = 1.0f,
			  .CollisionRecYOffset = -1.85f,
			  .CollisionRecHeight = 0.65f, .CollisionRecWidth = 0.3f,
			  .State = RocketSectionStateAssembled }
		}
	},

	// Levels 9-12: Lunar Lander
	{
		.State = RocketStatePieces,
		.FuelLevelVerticeNumbers = { {172,212}, {128,172}, {100,127}, {72,99}, {28,71}, {0,27} },
		.Sections = {
			{.VerticeStartIndex = 0,   .VerticeEndIndex = 71,
			  .XPos = -2.55f, .YPos = 2.38f, .Alpha = 1.0f,
			  .CollisionRecYOffset = -0.55f,
			  .CollisionRecHeight = 0.55f, .CollisionRecWidth = 0.4f, .Alpha = 1.0f,
			  .GroundCollisionY = -0.75f,
			  .State = RocketSectionStateResting },

			{.VerticeStartIndex = 72, .VerticeEndIndex = 127,
			  .XPos = -0.02f, .YPos = 2.45f,
			  .CollisionRecYOffset = -1.20f,
			  .CollisionRecHeight = 0.65f, .CollisionRecWidth = 0.4f, .Alpha = 1.0f,
			  .GroundCollisionY = -0.15f,
			  .State = RocketSectionStateRestingCollectable},

			{.VerticeStartIndex = 128, .VerticeEndIndex = 212,

			  .XPos = 1.4f,   .YPos = 0.57f, .Alpha = 1.0f,
			  .CollisionRecYOffset = -1.85f,
			  .CollisionRecHeight = 0.65f, .CollisionRecWidth = 0.3f,
			  .State = RocketSectionStateAssembled }
		}
	}, 

	// Levels 13-16: Sci-Fi Vessel
	{
		.State = RocketStatePieces,
		.FuelLevelVerticeNumbers = { {105,138}, {77,104}, {51,76}, {37,50}, {13,36}, {0,12} },
		.Sections = {
			{.VerticeStartIndex = 0,   .VerticeEndIndex = 36,
			  .XPos = -2.55f, .YPos = 2.38f, .Alpha = 1.0f,
			  .CollisionRecYOffset = -0.55f,
			  .CollisionRecHeight = 0.55f, .CollisionRecWidth = 0.4f, .Alpha = 1.0f,
			  .GroundCollisionY = -0.75f,
			  .State = RocketSectionStateResting },

			{.VerticeStartIndex = 37, .VerticeEndIndex = 76,
			  .XPos = -0.02f, .YPos = 2.45f,
			  .CollisionRecYOffset = -1.20f,
			  .CollisionRecHeight = 0.65f, .CollisionRecWidth = 0.4f, .Alpha = 1.0f,
			  .GroundCollisionY = -0.15f,
			  .State = RocketSectionStateRestingCollectable},

			{.VerticeStartIndex = 77, .VerticeEndIndex = 138,

			  .XPos = 1.4f,   .YPos = 0.57f, .Alpha = 1.0f,
			  .CollisionRecYOffset = -1.85f,
			  .CollisionRecHeight = 0.65f, .CollisionRecWidth = 0.3f,
			  .State = RocketSectionStateAssembled }
		}
	},
};

/////////////////////
// Helper Functions
/////////////////////
unsigned int RocketIndex() { return gGame.Levels[gGame.Level - 1].RocketIndex; }

int RocketSectionCollectedIndex() {
	for (unsigned int ss = 0; ss < ROCKET_SECTION_COUNT - 1; ss++) {
		if (gRockets[RocketIndex()].Sections[ss].State == RocketSectionStateCollected) return ss;
	}
	return -1;
}

unsigned int RocketSectionIsCollected() { return RocketSectionCollectedIndex() >=0; }

unsigned int RocketIsLastLevel() {
	unsigned int nextLevelIndex = gGame.Level >= LEVEL_COUNT ? 0 : gGame.Level;
	return gGame.Levels[nextLevelIndex].RocketInPieces;
}

