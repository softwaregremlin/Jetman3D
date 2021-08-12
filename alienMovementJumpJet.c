void AlienMovementJumpJetStarting(unsigned int index, float *directionX) {
	
	*directionX = 0;
	gAliens[index].JumpJetStartingBounceFrame++;
	gAliens[index].JumpJetStartingFrameCount++;

	// Bounce up and down
	if (gAliens[index].JumpJetStartingBounceFrame >= gAlienSettingsGame.JumpJetStartingBounceFrames ||
		(gAliens[index].YPos < gAlienSettingsGame.JumpJetStartingYBottom && !gAliens[index].MovingUp)) {
		gAliens[index].MovingUp = !gAliens[index].MovingUp;

		gAliens[index].JumpJetStartingBounceFrame = 0;

	}

	// Launching in the X direction
	if (gAliens[index].JumpJetStartingFrameCount >= gAlienSettingsGame.JumpJetStartingFrameCount) {
		gAliens[index].JumpJetStarting = FALSE;
		gAliens[index].JumpJetStartingFrameCount = 0;
		
		// Turn White
		ColorArrayToBW(gAliens[index].ColourIndexes, gAlienSettingsGame.VerticeCount * 4);
	}
}