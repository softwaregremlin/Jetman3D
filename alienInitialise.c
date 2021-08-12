//////////////////////////////////////////
// Initialisation Functions

// definitions found in alienEyeAnimation.c
void AlienInitialiseEyeTextureCoordinates();
void AlienSetEyeTextureFrame(unsigned int frame);

///////////////////////////////////////////////////////////////////////////////////////

unsigned int AlienSpeciesIndex() {
	return  gGame.Levels[gGame.Level - 1].AlienIndex;
}
//////////////////////////////////////////////
void AlienUpDirectionSetRandom(unsigned int index) {
	randMinMax(0, 2, &gAliens[index].MovingUp);
}

void AlienSidewaysDelaySetRandom(unsigned int index) {
	randMinMax(gAlienSettingsGame.MinSidewaysFrame, gAlienSettingsGame.MaxSidewaysFrames, &gAliens[index].SidewaysFrames);
	// gAliens[index].SidewaysFrames = 60;
	gAliens[index].SidewaysFrame = gAliens[index].SidewaysFrames;
}

///////////////////////////////////////////////////////
// Randomly set alien to be tilted downwards
void AlienDownwardRotationSetRandom(unsigned int index) {
	unsigned int downwardRotationProbability = 0;
	
	gAliens[index].DownwardRotationEnabled = FALSE;
	randMinMax(0, gAlienSettingsSpecies[AlienSpeciesIndex()].DownwardRotationProability + 1, &downwardRotationProbability);
	if (downwardRotationProbability == gAlienSettingsSpecies[AlienSpeciesIndex()].DownwardRotationProability) {
		gAliens[index].DownwardRotationEnabled = TRUE;
	}
}

// Adjust co-ordinates to deal with Downward Rotation
void AlienDownwardRotationSetCoordinates(unsigned int index) {
	gAliens[index].YOffset = -sinf((PI / 180) * gAlienSettingsGame.DownwardRotationAngle) * gAlienSettingsGame.RightLimit;

	gAliens[index].XOffset =
		(gAlienSettingsGame.RightLimit / cosf((PI / 180) * gAlienSettingsGame.DownwardRotationAngle)) -
		gAlienSettingsGame.RightLimit;

	gAliens[index].XPos += (gAliens[index].FacingRight ? -1 : 1) * gAliens[index].XOffset;

	gAliens[index].XCollisionMultiplier = cosf((PI / 180) * gAlienSettingsGame.DownwardRotationAngle);
	gAliens[index].YCollisionMultiplier = sinf((PI / 180) * gAlienSettingsGame.DownwardRotationAngle);
	gAliens[index].CollisionYPos += gAliens[index].YCollisionMultiplier;
	gAliens[index].CollisionYPos += gAlienSettingsSpecies[AlienSpeciesIndex()].CollisionRectangleYOffsetDownwardRotation;
}


//////////////////////////////////////////////////////////
void AlienInitialise(unsigned int index) {
	
	if (gGame.State == GameStateLevelComplete) return;


	// reset vertices!
	for (unsigned int vv = 0; vv < 1000; vv++) {
		gAliens[index].Vertices[vv] = gAlienSettingsSpecies[AlienSpeciesIndex()].InitialVertices[vv];
	}

	// Set random y position
	randMinMaxFloat(gAlienSettingsGame.BottomLimit, gAlienSettingsGame.TopLimit, &gAliens[index].YPos);

	// Random facing left / right
	if (gGame.State != GameStateModelView) randMinMax(0, 2, &gAliens[index].FacingRight);

	// flip if we are facing left
	if (gAliens[index].FacingRight) VerticeArrayMirrorY(gAliens[index].Vertices, gAlienSettingsGame.VerticeCount * 3);
	
	// Diagonal movement - randomly select up/down direction
	gAliens[index].MovingUp = FALSE;
	if (gAlienSettingsSpecies[AlienSpeciesIndex()].MovesDiagonally) AlienUpDirectionSetRandom(index);

	// Random Downward Rotation
	gAliens[index].DownwardRotationEnabled = FALSE;	
	if (gAlienSettingsSpecies[AlienSpeciesIndex()].DownwardRotationEnabled) AlienDownwardRotationSetRandom(index);	

	// Random Sideways Movement
	gAliens[index].MovingSideways = FALSE;
	if (gAlienSettingsSpecies[AlienSpeciesIndex()].SidewaysMovementEnabled) AlienSidewaysDelaySetRandom(index);

	// Set alpha channel back to solid	
	for (unsigned int aa = 0; aa < gAlienSettingsGame.VerticeCount; aa++) gAliens[index].ColourIndexes[(aa * 4) + 3] = 1.0f;
	gAliens[index].Alpha = 1.0f;

	// Set random colour
	if (gGame.State != GameStateModelView) {
		gAliens[index].Colour = ColorArraySetRandom(gAliens[index].ColourIndexes, gAlienSettingsGame.VerticeCount * 4);
	}

	// YRotationDelayCounter
	if (gAlienSettingsSpecies[AlienSpeciesIndex()].YRotationEnabled && gAlienSettingsSpecies[AlienSpeciesIndex()].YRotationInterval > 0) {
		randMinMax(0, gAlienSettingsSpecies[AlienSpeciesIndex()].YRotationInterval, &gAliens[index].YRotationDelayCounter);
	}

	// Set position to far left / right
	gAliens[index].XPos = gAliens[index].FacingRight ? gAlienSettingsGame.LeftLimit : gAlienSettingsGame.RightLimit;

	// printf("%.2f\n", gAliens[index].XPos);

	// Exception! - Jump Jets
	gAliens[index].JumpJetStarting = FALSE;
	if (gAlienSettingsSpecies[AlienSpeciesIndex()].IsJumpJet) {
		gAliens[index].JumpJetStarting = TRUE,
		gAliens[index].XPos = gAlienSettingsGame.JumpJetXPos;
		if (gAliens[index].YPos < gAlienSettingsGame.JumpJetStartingYBottom) gAliens[index].YPos = gAlienSettingsGame.JumpJetStartingYBottom;
	}

	// Variables used to set the collision Rectangle to the same place as the Alien
	gAliens[index].XCollisionMultiplier = 1.0f;
	gAliens[index].YCollisionMultiplier = gAlienSettingsSpecies[AlienSpeciesIndex()].MovesDiagonally ? 1.0f : 0;

	// Collision Rectangle Positions
	gAliens[index].CollisionXPos = gAliens[index].XPos +
		(gAliens[index].FacingRight ? 1 : -1) * gAlienSettingsSpecies[AlienSpeciesIndex()].CollisionRectangleXOffset;
	gAliens[index].CollisionYPos = gAliens[index].YPos;

	// Reset Offsets!
	gAliens[index].XOffset = gAliens[index].YOffset = 0;




	// Offsets if we are rotating downward
	if (gAliens[index].DownwardRotationEnabled) AlienDownwardRotationSetCoordinates(index);

	// Initialise our Explosion settings
	ExplosionInitialise(&gAlienExplosions[index]);

	// Deformation ("Kina" levels only)
	if (gAlienSettingsSpecies[AlienSpeciesIndex()].DeformationEnabled) AlienDeformationInitialise(index);

	// Bubble Deformation (Bubble levels only)
	if (gAlienSettingsSpecies[AlienSpeciesIndex()].BubbleDeformationEnabled) AlienDeformBubbleDimensionInitialise(index);

	gAliens[index].State = AlienStateOff;


};

//////////////////////////////////////////////////////////////////////////////

void AlienModelArraysClone() {
	for (unsigned int aa = 1; aa < ALIEN_MAX_COUNT; aa++) {
		ArrayCopyFloat( gAliens[0].Vertices,       gAliens[aa].Vertices,       gAlienSettingsGame.VerticeCount * 3);
		ArrayCopyFloat( gAliens[0].ColourIndexes,  gAliens[aa].ColourIndexes,  gAlienSettingsGame.VerticeCount * 4);
		ArrayCopyFloat( gAliens[0].TextureIndexes, gAliens[aa].TextureIndexes, gAlienSettingsGame.VerticeCount * 2);
		ArrayCopyGluint(gAliens[0].Indices,        gAliens[aa].Indices,        gAlienSettingsGame.IndiceCount);
	}
}

//////////////////////////////////////////////////////////////////////////////

void AlienLoadModel() {

	ModelLoad(
		gAlienSettingsGame.ModelPath,
		gGame.Levels[gGame.Level - 1].AlienIndex + 1,
		&gAlienSettingsGame.VerticeCount,
		&gAlienSettingsGame.IndiceCount,
		&gAlienSettingsGame.TextureVerticeCount,
		gAliens[0].Vertices,
		gAlienSettingsSpecies[AlienSpeciesIndex()].InitialVertices,
		gAliens[0].ColourIndexes,
		gAliens[0].Indices,
		gAliens[0].TextureIndexes
	);

	// Copy to the rest of them
	AlienModelArraysClone();

	// Shrink!
	if (gGame.State == GameStateModelView) return;
	for (unsigned int aa = 0; aa < ALIEN_MAX_COUNT; aa++) {
		VerticeArrayScale(gAlienSettingsGame.ScaleFactorInGame, gAliens[aa].Vertices, gAlienSettingsGame.VerticeCount * 3);
	}
	VerticeArrayScale(gAlienSettingsGame.ScaleFactorInGame, 
		gAlienSettingsSpecies[AlienSpeciesIndex()].InitialVertices, gAlienSettingsGame.VerticeCount * 3);
}

void AlienSetEyesAndTextures() {

	// Texture indices for eyes, if applicable
	if (gAlienSettingsSpecies[AlienSpeciesIndex()].HasEyes) {
		AlienInitialiseEyeTextureCoordinates();
		AlienSetEyeTextureFrame(0);
	}
}


void AliensInitialise() {

	for (unsigned int aa = 0; aa < ALIEN_MAX_COUNT; aa++) {

		// Set inital delay to stagger the x positions
		gAliens[aa].InitialDelay = aa * gAlienSettingsSpecies[AlienSpeciesIndex()].InitialDelayInterval;
		AlienInitialise(aa);
		AlienParticlesInitialiseInstance(aa);
	}
}

void AliensLoadAndInitialise() {

	// Avoid memory leak!
	if (!gAlienSettingsGame.TextureLoaded) {
		TextureLoad(gAlienSettingsGame.TexturePath, gAlienSettingsGame.TextureIndex);
		gAlienSettingsGame.TextureLoaded = TRUE;
	}

	AlienLoadModel();
	AlienSetEyesAndTextures();

	AliensInitialise();


}
