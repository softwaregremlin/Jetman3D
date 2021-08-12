
unsigned int AlienCollidesWithGround(unsigned int index, float collGroundYOffset) {
	return gAliens[index].CollisionYPos <= (gModelGround.YPos + collGroundYOffset);
}

unsigned int AlienCollidesWithRoof(unsigned int index, float collRecHeight) {
	return gAliens[index].CollisionYPos + collRecHeight / 2 >= gJetman.TopLimit;
}

unsigned int AlienCollidesWithPlatformTopOrBottom(unsigned int alienIndex, unsigned int platFormIndex, float collRecHeight) {
	return ((gAliens[alienIndex].CollisionYPos - collRecHeight / 2) <= gPlatforms[platFormIndex].Y) &&
		((gAliens[alienIndex].CollisionYPos + collRecHeight / 2) >= gPlatforms[platFormIndex].Y - gPlatforms[platFormIndex].Height);
}


unsigned int AlienCollidesWithPlatformSides(unsigned int alienIndex, unsigned int platFormIndex, float collRecWidth) {

	return  ((gAliens[alienIndex].CollisionXPos + collRecWidth / 2) >= gPlatforms[platFormIndex].X &&
		     (gAliens[alienIndex].CollisionXPos - collRecWidth / 2) <= (gPlatforms[platFormIndex].X + gPlatforms[platFormIndex].Width));
}


int gHits = 1;
unsigned int AlienCollidesWithPlatform(unsigned int index, float collRecWidth, float collRecHeight) {

	for (int pp = 0; pp < PLATFORM_COUNT; pp++) {

		if (AlienCollidesWithPlatformSides(index, pp, collRecWidth) &&
			AlienCollidesWithPlatformTopOrBottom(index, pp, collRecHeight)) {
			return TRUE;
		}
	}
	return FALSE;
}

//////////////// "Bounce" Logic /////////////////////////////////////////////////////////////////////////////////////

unsigned int AlienBouncesOffPlatformTopOrBottom(unsigned int alienIndex, float collRecWidth, float collRecHeight) {

	for (int pp = 0; pp < PLATFORM_COUNT; pp++) {

		if (AlienCollidesWithPlatformTopOrBottom(alienIndex, pp, collRecHeight) &&
			(gAliens[alienIndex].CollisionXPos  >= gPlatforms[pp].X &&
				gAliens[alienIndex].CollisionXPos <= (gPlatforms[pp].X + gPlatforms[pp].Width))) {

			return TRUE;
		}
	}
	return FALSE;
}

unsigned int AlienBouncesOffPlatformBottom(unsigned int alienIndex, float collRecWidth, float collRecHeight) {

	//if (gAliens[alienIndex].ReBounceFrameCounter > 0) return FALSE;

	for (int pp = 0; pp < PLATFORM_COUNT; pp++) {

		if (((gAliens[alienIndex].CollisionYPos + collRecHeight / 2) <= gPlatforms[pp].Y) &&
			((gAliens[alienIndex].CollisionYPos + collRecHeight / 2) >= gPlatforms[pp].Y - gPlatforms[pp].Height) && 

			(gAliens[alienIndex].CollisionXPos >= gPlatforms[pp].X &&
				gAliens[alienIndex].CollisionXPos <= (gPlatforms[pp].X + gPlatforms[pp].Width))) {

			return TRUE;
		}
	}
	return FALSE;
}

unsigned int AlienBouncesOffPlatformTop(unsigned int alienIndex, float collRecWidth, float collRecHeight) {

	for (int pp = 0; pp < PLATFORM_COUNT; pp++) {

		if (((gAliens[alienIndex].CollisionYPos - collRecHeight / 2) <= gPlatforms[pp].Y) &&
			((gAliens[alienIndex].CollisionYPos - collRecHeight / 2) >= gPlatforms[pp].Y - gPlatforms[pp].Height) &&

			(gAliens[alienIndex].CollisionXPos >= gPlatforms[pp].X &&
				gAliens[alienIndex].CollisionXPos <= (gPlatforms[pp].X + gPlatforms[pp].Width))) {

			return TRUE;
		}
	}
	return FALSE;
}



unsigned int AlienBouncesOffPlatformLeft(unsigned int alienIndex, float collRecWidth, float collRecHeight) {

	for (int pp = 0; pp < PLATFORM_COUNT; pp++) {

		if (AlienCollidesWithPlatformTopOrBottom(alienIndex, pp, collRecHeight) &&
			// Left Edge
			((gAliens[alienIndex].CollisionXPos >= gPlatforms[pp].X - collRecWidth / 2 &&
				gAliens[alienIndex].CollisionXPos <= gPlatforms[pp].X))) {

			return TRUE;
		}
	}
	return FALSE;
}

unsigned int AlienBouncesOffPlatformRight(unsigned int alienIndex, float collRecWidth, float collRecHeight) {

	for (int pp = 0; pp < PLATFORM_COUNT; pp++) {

		if (AlienCollidesWithPlatformTopOrBottom(alienIndex, pp, collRecHeight) &&
			// Right Edge
			(gAliens[alienIndex].CollisionXPos >= gPlatforms[pp].X + gPlatforms[pp].Width &&
				gAliens[alienIndex].CollisionXPos <= gPlatforms[pp].X + gPlatforms[pp].Width + collRecWidth / 2)) {

			return TRUE;
		}
	}
	return FALSE;
}



unsigned int AlienBouncesOffPlatformSides(unsigned int alienIndex, float collRecWidth, float collRecHeight) {

	for (int pp = 0; pp < PLATFORM_COUNT; pp++) {

		if (AlienCollidesWithPlatformTopOrBottom(alienIndex, pp, collRecHeight) &&

			((gAliens[alienIndex].CollisionXPos >= gPlatforms[pp].X - collRecWidth / 2 &&
				gAliens[alienIndex].CollisionXPos <= gPlatforms[pp].X) ||
				// Right Edge
				(gAliens[alienIndex].CollisionXPos >= gPlatforms[pp].X + gPlatforms[pp].Width  &&
					gAliens[alienIndex].CollisionXPos <= gPlatforms[pp].X + gPlatforms[pp].Width + collRecWidth / 2)))	{

			return TRUE;
		}
	}
	return FALSE;
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned int AlienCollidesWithLaser(unsigned int alienIndex, unsigned int laserIndex, float collRecWidth, float collRecHeight) {
	if (!gLasers.Laser[laserIndex].On) return FALSE;

	float alienLeft = gAliens[alienIndex].CollisionXPos - collRecWidth  / 2,
		  alienTop  = gAliens[alienIndex].CollisionYPos + collRecHeight / 2;
	float laserWidth = gLasers.Width, laserHeight = gLasers.Height,
		  laserLeft = gLasers.Laser[laserIndex].X, laserTop = gLasers.Laser[laserIndex].Y + laserHeight;
	
	return RectanglesCollide(alienLeft, alienTop, collRecWidth, collRecHeight, laserLeft, laserTop, laserWidth, laserHeight);
}


unsigned int AlienCollidesWithJetman(unsigned int alienIndex, float collRecWidth, float collRecHeight) {

	// Already hit
	if (gJetman.Exploding) return FALSE;

	// In the Rocket
	if (gJetman.InRocket) return FALSE;

	float alienLeft = gAliens[alienIndex].CollisionXPos - collRecWidth / 2,
		alienTop = gAliens[alienIndex].CollisionYPos + collRecHeight / 2;
	float jetmanRecWidth = gJetman.CollisionRecWidth * gJetman.CollisionWidthAlienScaleFactor,
		jetmanRecHeight = gJetman.CollisionRecHeight,
		jetmanLeft = gJetman.XPos - (jetmanRecWidth / 2.0f),
		jetmanTop = gJetman.YPos + gJetman.CollisionRecHeightOffset + +(gJetman.CollisionRecHeight / 2.0f);

	unsigned int result = RectanglesCollide
		(alienLeft, alienTop, collRecWidth, collRecHeight, jetmanLeft, jetmanTop, jetmanRecWidth, jetmanRecHeight);
	
	// Decrement Lives
	if (result && !gGame.CheatInifinteLives) {
		gGame.Lives--;
	}

	return result;
}


unsigned int AlienCollidesWithLasers(unsigned int alienIndex, float collRecWidth, float collRecHeight) {
	for (unsigned int laserIndex = 0; laserIndex < LASER_COUNT; laserIndex++) {
		if (AlienCollidesWithLaser(alienIndex, laserIndex, collRecWidth, collRecHeight)) return TRUE;
	}
	return FALSE;
}



void AlienCollisionProcess(unsigned int index) {

	if (gAliens[index].State != AlienStateOn) return;

	// if (gAliens[index].ReBounceFrameCounter > 0) gAliens[index].ReBounceFrameCounter--;

	float collRecWidth = gAlienSettingsSpecies[AlienSpeciesIndex()].CollisionRectangleWidth,
		collRecHeight = gAlienSettingsSpecies[AlienSpeciesIndex()].CollisionRectangleHeight,
		collGroundYOffset = gAlienSettingsSpecies[AlienSpeciesIndex()].CollisionGroundYOffset;

	unsigned int collidesWithGround = AlienCollidesWithGround(index, collGroundYOffset),
		collidesWithRoof = AlienCollidesWithRoof(index, collRecHeight),
		collidesWithPlatform = AlienCollidesWithPlatform(index, collRecWidth, collRecHeight),
		collidesWithLasers = AlienCollidesWithLasers(index, collRecWidth, collRecHeight),
		collidesWithJetman = (gGame.JetManCollisionDisabled ? FALSE : AlienCollidesWithJetman(index, collRecWidth, collRecHeight)),
		hasCollision = collidesWithRoof || collidesWithGround || collidesWithPlatform || collidesWithLasers || collidesWithJetman;

	// Alien is set to explode on impact
	if (hasCollision && gAlienSettingsSpecies[AlienSpeciesIndex()].ExplodesOnSceneryCollision && !collidesWithRoof) {
		
		AlienExplosionStart(index, collidesWithGround, collidesWithPlatform, collidesWithLasers, collidesWithJetman);
		return;
	}

	// Alien not set to explode on impact, but has hit lasers or Jetman
	if (collidesWithLasers || collidesWithJetman) {
		AlienExplosionStart(index, collidesWithGround, collidesWithPlatform, collidesWithLasers, collidesWithJetman);
		return;
	}

	// Alien needs to bounce off world scenerey
	if (collidesWithGround) {
		gAliens[index].MovingUp = TRUE;
		return;
	}
			
	if (collidesWithRoof) {
		gAliens[index].MovingUp = FALSE;
		return;
	}


	float sceneryCollisionFactor = gAlienSettingsSpecies[AlienSpeciesIndex()].CollisionSceneryFactor;


	// Diagonal Bouncing Logic
	if (AlienBouncesOffPlatformLeft(index, collRecWidth * sceneryCollisionFactor, collRecHeight * sceneryCollisionFactor) && gAliens[index].FacingRight) {
		gAliens[index].FacingRight = FALSE; AlienRandomYSpeedAdjust(index);	return;
	}

	if (AlienBouncesOffPlatformRight(index, collRecWidth * sceneryCollisionFactor, collRecHeight * sceneryCollisionFactor) && !gAliens[index].FacingRight) {
		gAliens[index].FacingRight = TRUE; AlienRandomYSpeedAdjust(index);	return;
	}

	if (AlienBouncesOffPlatformBottom(index, collRecWidth * sceneryCollisionFactor, collRecHeight * sceneryCollisionFactor) && gAliens[index].MovingUp) {
		gAliens[index].MovingUp = FALSE; AlienRandomYSpeedAdjust(index);	return;
	}

	if (AlienBouncesOffPlatformTop(index, collRecWidth * sceneryCollisionFactor, collRecHeight * sceneryCollisionFactor) && !gAliens[index].MovingUp) {
		gAliens[index].MovingUp = TRUE; AlienRandomYSpeedAdjust(index);	return;
	}

}