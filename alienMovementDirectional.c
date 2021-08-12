void AlienScreenWrap(unsigned int index, float directionX) {

	// End of level - keep going
	if (gGame.State == GameStateLevelComplete) return;

	// Not moving horizontally - do nothing
	if (directionX == 0) return;

	// Must have gone past the wrap point!
	float xLimit = (gAlienSettingsGame.XWrapLimit + gAliens[index].XOffset) * directionX;
	if (fabs(gAliens[index].XPos) < fabs(xLimit)) return; 

	// Reset if we have wrapped x time to increase the difficulty 
	gAliens[index].WrapCount++;
	if (gAliens[index].WrapCount >= gAlienSettingsSpecies[AlienSpeciesIndex()].WrapLimit) {
		gAliens[index].WrapCount = 0;
		AlienInitialise(index);
		AlienParticlesInitialiseInstance(index);
		return;
	}


	// Go to the opposite side
	gAliens[index].XPos = -xLimit;

	// Correct Yposition for downward rotation
	if (gAliens[index].DownwardRotationEnabled) {
		gAliens[index].YPos = gAliens[index].CollisionYPos;
	}

	// Reset the co-ordinates of the collision rectangle
	gAliens[index].CollisionXPos = -(gAlienSettingsGame.XWrapLimit * directionX) +
		(gAlienSettingsSpecies[AlienSpeciesIndex()].CollisionRectangleXOffset * directionX);

	// gAliens[index].CollisionYPos = gAliens[index].YPos - gAliens[index].YCollisionMultiplier;
	if (gAliens[index].DownwardRotationEnabled) {
		gAliens[index].CollisionYPos -= gAlienSettingsSpecies[AlienSpeciesIndex()].CollisionRectangleYOffsetDownwardRotation;
	}
}

void AlienRandomSidewaysMovement(unsigned int index) {
	
	if (gAliens[index].SidewaysFrame > 0) {
		gAliens[index].SidewaysFrame--;
		return;
	}
	gAliens[index].MovingSideways = !gAliens[index].MovingSideways;
	AlienSidewaysDelaySetRandom(index);
}

void AlienRandomYSpeedAdjust(unsigned int index) {
	if (!gAlienSettingsSpecies[AlienSpeciesIndex()].YSpeedAlternateEnabled) return;
	unsigned int yAdjustmentProbability = 0;
	randMinMax(0, 2, &yAdjustmentProbability);

	gAliens[index].YSpeed = yAdjustmentProbability == 0 ? 0 :
		gAlienSettingsSpecies[AlienSpeciesIndex()].YSpeedAlternate;
}