#define TRINKET_COUNT 5
#define TRINKET_MODEL_MAX_VERTICES 200
#define TRINKET_MODEL_MAX_INDICES 600
#define TRINKET_GROUND_DROP_POINT_COUNT 3

// States
enum {	TrinketStatePaused, TrinketStateFalling, TrinketStateRestingCollectable };

// Settings per Trinket Type
typedef struct {
	unsigned int InitialColour, VerticeCount, IndiceCount,
		TextureVerticeCount, ColorPulsateFrameCount,				
		RotationEnabled;

	float InitialVertices[TRINKET_MODEL_MAX_VERTICES * 3],
		  InitialColourIndexes[TRINKET_MODEL_MAX_VERTICES * 4],
		  OriginalColorArray[TRINKET_MODEL_MAX_VERTICES],
		  TextureIndexes[TRINKET_MODEL_MAX_VERTICES * 2];

	float GroundCollisionOffset, 
		RotationSpeed, RotationDirection[3],
		CollisionRectangleWidth, CollisionRectangleHeight,
		CollisionRectangleYOffset, CollisionRecBottomSpace, GroundCollisionY;

	GLUINT_ Indices[TRINKET_MODEL_MAX_INDICES];

	int PulsateSequences[COLOR_PULSATE_MAX_LENGTH][RGB_LENGTH];
	unsigned int PulsateSequenceLength;

	float Scale[3];

} structTrinketSettings;


// Game Wide Settings
typedef struct {

	char ModelPath[50];

	unsigned int TextureIndex, CollisionRectangleDraw, PickupScore,
		PauseFramesMinMax[2];
	structTrinketSettings Settings[TRINKET_COUNT];
	float FallSpeed, TopPos,
		XMinMax, NoDropZone[2], AboveRocketZone[3];
	float GroundDropPoints[TRINKET_GROUND_DROP_POINT_COUNT], GroundDropPointProbability,
		GroundCollisionY;
} structTrinketSettingsGame;

// Instance Structure
typedef struct {
	float Vertices[TRINKET_MODEL_MAX_VERTICES * 3],
		ColourIndexes[TRINKET_MODEL_MAX_VERTICES * 4];
	
	unsigned int TrinketType,
		State, CollisionRectangleDraw,
		ColorPulsateDirection, ColorPulsateFrame,
		ColorSequenceNumber,
		PauseFrame, PauseFrames;

	float XPos, YPos, ZPos, TopPos, Alpha,
		CollisionXPos, CollisionYPos,
		RotationAngle;

} structTrinket;

///////////////////////////////////////////////////////////////////////

structTrinketSettingsGame gTrinketSettingsGame = {
	.ModelPath = "/models/trinkets/",
	.TextureIndex = 7,
	.FallSpeed = 0.025f,
	.TopPos = 5.5f,
	.PauseFramesMinMax = {60, 600},
	.PickupScore = 250,
	///
	.GroundCollisionY = -1.35f,
	.GroundDropPoints = {-3.75f, -1.2f, 3.75f},
	.GroundDropPointProbability = 0.3f,
	.NoDropZone = {0, 2.4f}, .AboveRocketZone = { 1.0f, 1.3f, 1.6f},
	.XMinMax = 3.75f,
	
	.Settings = {
		// Pebble
		{
			.InitialColour = ColorGreen, 
			//.InitialColour = ColorCyan, 
			.ColorPulsateFrameCount = 100,
			.Scale = {0.35f, 0.1775f, 0.35f},
			.PulsateSequences = { { 1, 0, 0 }, { -1, 0, 0 } },
			.PulsateSequenceLength = 2,
			.GroundCollisionOffset = -0.1f,
			.RotationEnabled = TRUE,
			.RotationSpeed = 1.0f,
			.RotationDirection = {0, 1.0f, 0 },
			.CollisionRectangleWidth = 0.6f,
			.CollisionRectangleHeight = 0.2f,
			//.CollisionRectangleYOffset = 0.2f,
			.CollisionRecBottomSpace = 0.1f
		},
		
		// Gemstone
		{
			.InitialColour = ColorRed, .ColorPulsateFrameCount = 20,
			.Scale = {0.35f, 0.35f, 0.35f},
			.PulsateSequences = { { -1, 1, 1 } , { 1, -1, -1 } , { 0, 1, 0} , { -1, -1, 1 }, { 1, 0, -1 } },
			.PulsateSequenceLength = 5,
			.GroundCollisionOffset = 0.1f,
			.RotationEnabled = TRUE,
			.RotationSpeed = 10.0f,
			.RotationDirection = {0, 1.0f, 0 },
			.CollisionRectangleWidth = 0.4f, 
			.CollisionRectangleHeight = 0.4f,
			.CollisionRectangleYOffset = -0.2f,
			.CollisionRecBottomSpace = 0.25f
		},

		// Mini Station
		{
			.InitialColour = ColorCyan, 
			.ColorPulsateFrameCount = 30,
			.Scale = {0.25f, 0.25f, 0.25f},
			.PulsateSequences = { { 1, 0, 0 }, { -1, 0, 0 } },
			.PulsateSequenceLength = 2,
			.GroundCollisionOffset = -0.1f,
			.RotationEnabled = TRUE,
			.RotationSpeed = 2.0f,
			//.RotationDirection = {0.25f, 0.25f, 0.25f },
			.RotationDirection = {1.0f, 1.0f, 1.0f },

			.CollisionRectangleWidth = 0.6f,
			.CollisionRectangleHeight = 0.2f,
			//.CollisionRectangleYOffset = 0.2f,
			.CollisionRecBottomSpace = 0.2f
		},

		// Nuclear Dish
		{
			.InitialColour = ColorCyan,
			.ColorPulsateFrameCount = 30,
			.Scale = {0.55f, 0.55f, 0.55f},
			.PulsateSequences = { { 0, -1, 0 }, { 0, 1, 0 } },
			.PulsateSequenceLength = 2,
			.GroundCollisionOffset = -0.1f,
			.RotationEnabled = TRUE,
			.RotationSpeed = 2.0f,
			.RotationDirection = {0.0f, 1.0f, 0.3f },
			.CollisionRectangleWidth = 0.6f,
			.CollisionRectangleHeight = 0.2f,
			//.CollisionRectangleYOffset = 0.2f,
			.CollisionRecBottomSpace = 0.25f
		},

		// Gold Bar
		{
			.InitialColour = ColorYellow,
			.ColorPulsateFrameCount = 10,
			.Scale = {0.25f, 0.25f, 0.25f},
			.PulsateSequences = { { -1, -1, 0}, {  1, 1, 0} },
			.PulsateSequenceLength = 2,
			.GroundCollisionOffset = -0.1f,
			.RotationEnabled = TRUE,
			.RotationSpeed = 1.0f,
			.RotationDirection = {0, 1.0f, 0 },
			.CollisionRectangleWidth = 0.6f,
			.CollisionRectangleHeight = 0.2f,
			.CollisionRecBottomSpace = 0.15f
		}
	}
};

structTrinket gTrinket = {
	.TrinketType = 3,
	.State = TrinketStatePaused
};