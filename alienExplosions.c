float AlienExplosionYPerspectiveCorrection(unsigned int collidesWithGround, unsigned int collidesWithPlatform, unsigned int collidesWithLasers) {
	float jetManYRange = gJetman.TopLimit - gJetman.BottomLimit,
		jetManZeroBasedYPos = gJetman.YPos - gJetman.BottomLimit,
		// Rules differ in relation to where the object is relative to the main Character
		jetManPercentYPos = collidesWithPlatform ? (jetManYRange - jetManZeroBasedYPos) / jetManYRange :
		jetManZeroBasedYPos / jetManYRange;



	if (collidesWithGround) return gExplosionSettings.YPerspectiveFactorGround * jetManPercentYPos;
	if (collidesWithPlatform) return gExplosionSettings.YPerspectiveFactorPlatform * jetManPercentYPos;
	if (collidesWithLasers) return gExplosionSettings.YPerspectiveFactorLaser * jetManPercentYPos;
	// Hit Jetman!
	return 0.0f;
}

void AlienExplosionStart(unsigned int index, unsigned int collidesWithGround, 
						 unsigned int collidesWithPlatform, 
						 unsigned int collidesWithLasers, unsigned int collidesWithJetman) {

	// Start the explosion
	SoundPlay(gExplosionSound);
	gAlienExplosions[index].On = TRUE;

	// Since we are bringing the Z position forward, introduce a correction to the X position
	gAlienExplosions[index].X = gAliens[index].CollisionXPos - (gAliens[index].CollisionXPos * gExplosionSettings.XPerspectiveFactor);
	gAlienExplosions[index].Y = gAliens[index].CollisionYPos;

	// Same with Y position - relative to our viewpoint
	gAlienExplosions[index].Y +=
		AlienExplosionYPerspectiveCorrection(collidesWithGround, collidesWithPlatform, collidesWithLasers);

	// Increase Score
	if (collidesWithLasers) {
		gGame.Score += gAlienSettingsSpecies[AlienSpeciesIndex()].ScorePerAlien;
		if (gGame.Score > gGame.HiScore) gGame.HiScore = gGame.Score;
	}

	// Hit Jetman!
	if (collidesWithJetman) {
		gGame.State = GameStateLifeLost;
		gJetman.Exploding = TRUE;
		JetManExplosionStart();
	}

	gAliens[index].State = AlienStateExploding;
}



void AlienExplosionDraw(unsigned int index) {

    if (!gAlienExplosions[index].On) return;

    // Animate - return if end of animation cycle
    unsigned int isEndOfExplosion = FALSE;

    ExplosionAnimate(&gAlienExplosions[index], &isEndOfExplosion);

    if (isEndOfExplosion) {
        // Now re-start the alien
		if (!gJetman.InRocket) {

			gAliens[index].InitialDelay = gAlienSettingsSpecies[AlienSpeciesIndex()].InitialDelayInterval;
			gAliens[index].State = AlienStateOff;
			AlienInitialise(index);
			AlienParticlesInitialiseInstance(index);
		}
        return;
    }

    // Set vertice array (size, positions)
    float zIncrement = gAlienSettingsGame.ExplosionZIncrement + (index * gAlienSettingsGame.ExplosionZIncrement);
    ExplosionDraw(&gAlienExplosions[index], zIncrement);
}

void AlienExplosionsDraw() {
    glBindTexture(GL_TEXTURE_2D, gGame.Textures[gExplosionSettings.TextureIndex]);
    for (unsigned int aa = 0; aa < ALIEN_MAX_COUNT; aa++) {
        AlienExplosionDraw(aa);
    }
}