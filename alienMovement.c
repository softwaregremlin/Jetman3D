void AlienMove(unsigned int index) {

	if (gAliens[index].State == AlienStateOff) {
		// Delay before appearing to stagger the x positions
		if (gAliens[index].InitialDelay > 0) {
			gAliens[index].InitialDelay--;
			return;
		}
		gAliens[index].State = AlienStateOn;
	}
	
	// variable to set left/right direction
	float directionX = gAliens[index].FacingRight ? 1.0f : -1.0f,
		  directionY = gAliens[index].MovingSideways ? 0 : (gAliens[index].MovingUp ? 1.0f : -1.0f);

	// Specific logic for Jump Jets starting off
	if (gAliens[index].JumpJetStarting) AlienMovementJumpJetStarting(index, &directionX);

	// Set Current y Position
	glTranslatef(0, gAliens[index].YPos + gAliens[index].YOffset, 0);

	// Downward Rotation - Rotate on the Z (really y) axis if applicable
	if (gAliens[index].DownwardRotationEnabled) {
		glRotatef(directionX * -gAlienSettingsGame.DownwardRotationAngle, 0, 0, 1.0f);
	}

	// Spin around the x axis if applicable
	if (gAlienSettingsSpecies[AlienSpeciesIndex()].XRotationEnabled) AlienSpinX(index);

	// Set Current x Position
	glTranslatef(gAliens[index].XPos, 0, 0);

	// Spin around the Y axis if applicable
	if (gAlienSettingsSpecies[AlienSpeciesIndex()].YRotationEnabled) AlienSpinY(index);

	// Exploding - stay still and fade out
	if (gAliens[index].State == AlienStateExploding) {
		gAliens[index].Alpha -= gAlienSettingsGame.FadeSpeed;

		for (unsigned int aa = 0; aa < gAlienSettingsGame.VerticeCount; aa++) {
			gAliens[index].ColourIndexes[(aa * 4) + 3] = gAliens[index].Alpha;
		}
		return;
	}

	// Guided Missile logic!
	if (gAlienSettingsSpecies[AlienSpeciesIndex()].IsGuided) AlienSetGuidance(index, &directionX);

	// Move left/right	
	float xSpeed = gAlienSettingsSpecies[AlienSpeciesIndex()].XSpeed != 0 ?
		gAlienSettingsSpecies[AlienSpeciesIndex()].XSpeed : gAlienSettingsSpecies[AlienSpeciesIndex()].Speed;
	gAliens[index].XPos += xSpeed * directionX;

	// Up/down if applicable
	float ySpeed = gAlienSettingsSpecies[AlienSpeciesIndex()].Speed;
	if (gAlienSettingsSpecies[AlienSpeciesIndex()].MovesDiagonally || 
			gAlienSettingsSpecies[AlienSpeciesIndex()].IsJumpJet) {
		ySpeed = gAliens[index].YSpeed != 0 ?
			gAliens[index].YSpeed : gAlienSettingsSpecies[AlienSpeciesIndex()].Speed;
		gAliens[index].YPos += ySpeed * directionY;
	}

	// Screen wrap
	AlienScreenWrap(index, directionX);	

	// Deform!
	if (gAlienSettingsSpecies[AlienSpeciesIndex()].DeformationEnabled) AlienDeform(index);
	if (gAlienSettingsSpecies[AlienSpeciesIndex()].BubbleDeformationEnabled) AlienDeformBubble(index);

	// Randomly change from diagonal to sideways movement and vice-versa
	if (gAlienSettingsSpecies[AlienSpeciesIndex()].SidewaysMovementEnabled) AlienRandomSidewaysMovement(index);

	// Adjust the co-ordinates of the collision rectangle
	gAliens[index].CollisionXPos += xSpeed * directionX * gAliens[index].XCollisionMultiplier;
	gAliens[index].CollisionYPos += ySpeed * directionY * gAliens[index].YCollisionMultiplier;
	if (directionY > 0) {
		int test123 = 0;
	}
}