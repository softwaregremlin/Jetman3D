void AlienScreenWrap(unsigned int index, float directionX) {

	// Not moving horizontally - do nothing
	if (directionX == 0) return;

	float xLimit = (gAlienSettingsGame.XWrapLimit + gAliens[index].XOffset) * directionX;
	if (fabs(gAliens[index].XPos) < fabs(xLimit)) return; //AlienScreenWrap(index, xLimit, directionX);

	// Go to the opposite side
	gAliens[index].XPos = -xLimit;

	// Correct Yposition for downward rotation
	if (gAliens[index].DownwardRotationEnabled) {
		gAliens[index].YPos = gAliens[index].CollisionYPos;
	}

	// Reset the co-ordinates of the collision rectangle
	gAliens[index].CollisionXPos = -(gAlienSettingsGame.XWrapLimit * directionX) +
		(gAlienSettingsSpecies[AlienSpeciesIndex()].CollisionRectangleXOffset * directionX);

	//gAliens[index].CollisionYPos = gAliens[index].YPos - gAliens[index].YCollisionMultiplier;
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