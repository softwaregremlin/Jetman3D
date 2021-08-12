void AlienSetGuidance(unsigned int index, float * directionX) {

	// Not applicable when the Jump Jet is starting
	if (gAliens[index].JumpJetStarting) return;

	// Delay before checking the guidance
	gAliens[index].GuidanceFrame++;
	if (gAliens[index].GuidanceFrame < gAlienSettingsSpecies[AlienSpeciesIndex()].GuidanceFrames) return;

	// Set the Guidance direction
	if (gAlienSettingsSpecies[AlienSpeciesIndex()].IsGuidedX) 
		*directionX = gAliens[index].CollisionXPos < gJetman.XPos ? 1.0f : -1.0f;

	if (gAlienSettingsSpecies[AlienSpeciesIndex()].IsGuidedY) gAliens[index].MovingUp = gAliens[index].CollisionYPos < gJetman.YPos;

	gAliens[index].GuidanceFrame = 0;
}