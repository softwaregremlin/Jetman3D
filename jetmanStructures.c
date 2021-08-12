typedef struct {
	unsigned int Count, Frame, FrameCount, FrameCountMax, FramesSinceBump, FramesSinceBumpDelay,
		MaxBumps, BumpStepSize;
} structBump;

typedef struct {
	float XOffsetRight, XOffsetLeft, YOffset, YOffsetFalling;
} structSmokePuffSettings;

typedef struct {
	unsigned int TextureIndex;
	unsigned int ResetPosition;
	unsigned int FacingRight, Jumping, Falling, Walking, Standing, Firing, Bumping, Exploding, InRocket;
	unsigned int WalkingFrame, WalkingFrameCount, WalkingStep, WalkingStepCount;
	unsigned int CollisionRectangleDraw;
	structBump Bump;
	structSmokePuffSettings SmokePuffSettings;
	float LeftRightSpeed, WalkingSpeed, JumpingSpeed, FallingSpeed;
	float XPos, YPos, ZPos, YScrollThreshold, TopLimit, BottomLimit, LeftLimit, RightLimit, WrapXShift, Scale;
	float YAbovePosition, Height, Width,
		CollisionRecWidth, CollisionRecHeight, CollisionRecHeightOffset, CollisionWidthAlienScaleFactor;
	float Alpha, FadeSpeed, AfterExplosionPause, AfterExplosionPauseTime;
	GLfloat ModelViewMatrix[16];
	structExplosion JetPackSmokePuff, Explosion;
} structJetman;


structJetman gJetman = {

	.TextureIndex = 3,
	.ResetPosition = TRUE,
	.XPos = 5.0f,

	.FacingRight = TRUE,
	//////////////////////////////////
	// .CollisionRectangleDraw = TRUE,
	//////////////////////////////////

	.LeftRightSpeed = 0.0625f, .JumpingSpeed = 0.0625f, .FallingSpeed = 0.03125f, .WalkingSpeed = 0.03125f,

	.WalkingFrame = 0, .WalkingFrameCount = 7, .WalkingStep = 0, .WalkingStepCount = 8,

	.Bump = {.Frame = 0, .FrameCount = 15, .FrameCountMax = 15, .FramesSinceBump = 0, .FramesSinceBumpDelay = 18,
			 .MaxBumps = 4, .BumpStepSize = 3},

	.SmokePuffSettings = {.XOffsetRight = -0.3f, .XOffsetLeft = 0.15f, .YOffset = -0.4f, .YOffsetFalling = -0.9f },

	.Scale = 0.125f,

	// For studying the model in detail...
	//.Scale = 0.5f,

	.TopLimit = 3.5f, .BottomLimit = -1.05f, .LeftLimit = -4.0f, .RightLimit = 4.0f, .WrapXShift = 8.5f,
	.YScrollThreshold = 1.3,
	.YAbovePosition = 0.42f, .Height = 1.25f,.Width = 0.6f,
	.CollisionRecWidth = 0.55f, .CollisionRecHeight = 0.85, .CollisionRecHeightOffset = -0.1f,
	.CollisionWidthAlienScaleFactor = 0.6,
	.Alpha = 1.0f, 
	.FadeSpeed = 0.02f, .AfterExplosionPauseTime = 240.0f,

	.Explosion = { .InitialSize = 1.0f, .Z = 1.0005f}
}; 

//structExplosion gJetPackSmokePuff;
