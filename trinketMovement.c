// Go back to 0,0,0 by transforming to -ve of the current position
void TrinketResetToOrigin() {

	glTranslatef(0, 0, 0);

	//VerticeArrayTransform(-gTrinket.XPos, -gTrinket.YPos, -gTrinket.ZPos, gTrinket.Vertices, 
	//	gTrinketSettingsGame.Settings[gTrinket.TrinketType - 1].VerticeCount * 3);
}

// Falling
void TrinketMoveFalling() {
    gTrinket.YPos -= gTrinketSettingsGame.FallSpeed;

	gTrinket.CollisionYPos = gTrinket.YPos + 
		gTrinketSettingsGame.Settings[gTrinket.TrinketType - 1].CollisionRectangleYOffset;

    //VerticeArrayTransform(0, -gTrinketSettingsGame.FallSpeed, 0, gTrinket.Vertices, 
    //    gTrinketSettingsGame.Settings[gTrinket.TrinketType - 1].VerticeCount * 3);

	glTranslatef(gTrinket.XPos, gTrinket.YPos, 0);

}

void TrinketMoveResting() {
	glTranslatef(gTrinket.XPos, gTrinket.YPos, 0);
}

// Start of the Fall
void TrinketMovePausedToFalling() {

	// Random position anywhere except above the rocket
	float noDropRange = gTrinketSettingsGame.NoDropZone[1] - gTrinketSettingsGame.NoDropZone[0],
		randomMax = gTrinketSettingsGame.XMinMax - noDropRange, dropPos;

	randMinMaxFloat(-gTrinketSettingsGame.XMinMax, randomMax, &dropPos);
	if (dropPos > gTrinketSettingsGame.NoDropZone[0] && dropPos < gTrinketSettingsGame.NoDropZone[1]) dropPos += noDropRange;

	gTrinket.State = TrinketStateFalling;
	TrinketResetToOrigin();

	// Drop between the platforms - increased chance
	float groundDropPointProbabilityFound;
	randMinMaxFloat(0, 1.0f, &groundDropPointProbabilityFound);
	if (groundDropPointProbabilityFound <= gRocketGas.GroundDropPointProbability) {
		unsigned int groundDropPointIndex = 0;
		randMinMax(0, ROCKET_GAS_GROUND_DROP_POINT_COUNT, &groundDropPointIndex);
		dropPos = gTrinketSettingsGame.GroundDropPoints[groundDropPointIndex];
	}

	///////////
	gTrinket.YPos = gTrinketSettingsGame.TopPos;
	gTrinket.XPos = dropPos;

	gTrinket.CollisionXPos = gTrinket.XPos;
	gTrinket.CollisionYPos = gTrinket.YPos;

	glTranslatef(gTrinket.XPos, gTrinket.YPos, 0);

	//VerticeArrayTransform(gTrinket.XPos, gTrinket.YPos, 0, gTrinket.Vertices, 
	//	gTrinketSettingsGame.Settings[gTrinket.TrinketType - 1].VerticeCount * 3);
}

// Collected!
void TrinketMoveToPaused() {
	gTrinket.State = TrinketStatePaused;
	randMinMax(gTrinketSettingsGame.PauseFramesMinMax[0], gTrinketSettingsGame.PauseFramesMinMax[1], &gTrinket.PauseFrames);
	gTrinket.PauseFrame = 0;

	gGame.Score += gTrinketSettingsGame.PickupScore;
	SoundPlay(gTrinketPickupSound);

	TrinketInitialise();
}

void TrinketRotate() {
	if (!gTrinketSettingsGame.Settings[gTrinket.TrinketType - 1].RotationEnabled) return;

	glRotatef(gTrinket.RotationAngle,
		gTrinketSettingsGame.Settings[gTrinket.TrinketType - 1].RotationDirection[0],
		gTrinketSettingsGame.Settings[gTrinket.TrinketType - 1].RotationDirection[1],
		gTrinketSettingsGame.Settings[gTrinket.TrinketType - 1].RotationDirection[2]);

	gTrinket.RotationAngle += gTrinketSettingsGame.Settings[gTrinket.TrinketType - 1].RotationSpeed;
	if (gTrinket.RotationAngle > 360.0f) gTrinket.RotationAngle = 0;
}

void TrinketMove() {

	// Paused
	if (gTrinket.State == TrinketStatePaused) gTrinket.PauseFrame++;

	// Paused -> Falling
	if (gTrinket.State == TrinketStatePaused &&
		gTrinket.PauseFrame >= gTrinket.PauseFrames) TrinketMovePausedToFalling();

	// Falling
	if (gTrinket.State == TrinketStateFalling) TrinketMoveFalling();

	// Falling -> hit Ground or Platform
	if (gTrinket.State == TrinketStateFalling &&
		(TrinketCollidesWithGround() || TrinketLandsOnPlatform())) {
		gTrinket.State = TrinketStateRestingCollectable;
		return;
	}

	// Resting / Collectable
	if (gTrinket.State == TrinketStateRestingCollectable) TrinketMoveResting();

	// Resting or Falling -> Collected 
	if ((gTrinket.State == TrinketStateRestingCollectable || gTrinket.State == TrinketStateFalling) &&
		TrinketCollidesWithJetman() && !gJetman.Exploding) TrinketMoveToPaused();

}