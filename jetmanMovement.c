
unsigned int JetManTurnCheck(unsigned int isFacingOtherWay, unsigned int faceRight) {

	// Check if we need to turn
	if (!isFacingOtherWay) return FALSE;

	// Turn
	glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
	gJetman.FacingRight = faceRight;
	return TRUE;
}

void JetManMoveLeftOrRight(unsigned int isMovingRight) {

	// Blocked by platform
	if (JetManCollidesWithPlatform()) return;

	// Face the other way	
	if (JetManTurnCheck(isMovingRight ? !gJetman.FacingRight : gJetman.FacingRight, isMovingRight)) return;

	// Screen wrap!!
	if ( (!isMovingRight && gJetman.XPos <= gJetman.LeftLimit) || 
		 ( isMovingRight && gJetman.XPos >= gJetman.RightLimit)) {
		glTranslatef(-gJetman.WrapXShift, 0.0f, 0.0f);
	}

	// Move
	if (gJetman.Standing) gJetman.Walking = TRUE;
	glTranslatef(gJetman.Walking ? gJetman.WalkingSpeed : gJetman.LeftRightSpeed, 0.0f, 0.0f);
}

void JetManMoveUpOrDown(unsigned int isMovingUp, float speed) {

	// Taking off or falling from standing - start the jet pac particles
	if (gJetman.Standing) {
		JetPacParticlesStart();
		//if (isMovingUp) 
	    JetPacSmokePuffStart(isMovingUp);
	}

	// Move up/down
	gJetman.Standing = FALSE;
	glTranslatef(0.0f, speed, 0.0f);
	gJetman.YPos += speed;

	// Scroll screen up / down if we're above a certain height
	if (gJetman.YPos >= gJetman.YScrollThreshold) {
		gGame.LookAtY -= speed;
		glTranslatef(0.0f, -speed, 0.0f);
		return;
	}

	// Otherwise move up/down the screen
	glGetFloatv(GL_MODELVIEW_MATRIX, gJetman.ModelViewMatrix);
	gJetman.YPos = gJetman.ModelViewMatrix[13];
	gGame.LookAtY = 0;
}

void JetManMoveLeft()  { JetManMoveLeftOrRight(FALSE); }
void JetManMoveRight() { JetManMoveLeftOrRight(TRUE); }

void JetManMoveUp() {


	// gJetman.Standing = FALSE;

	// Hit a Platform - Bump head
	if (gJetman.Bumping) return;
	if (JetManCollidesWithPlatformBottom()) {
		gJetman.Bumping = TRUE;
		// Fall for a shorter distance each bump, creating an oscillating effect
		if (gJetman.Bump.Count <= gJetman.Bump.MaxBumps) {			
			gJetman.Bump.Count++;
			gJetman.Bump.FrameCount = gJetman.Bump.FrameCount - gJetman.Bump.BumpStepSize;
		}

		return;
	}

	// Hit the Top Limit
	if (gJetman.YPos >= gJetman.TopLimit) {
		glTranslatef(0.0f, gJetman.TopLimit - gJetman.YPos, 0.0f);
		gJetman.YPos = gJetman.TopLimit;
		return;
	}

	// Move Up
	JetManMoveUpOrDown(TRUE, gJetman.JumpingSpeed);
}

void JetManFall() {

	// Hit a Platform
	if (JetManCollidesWithPlatformTop()) {
		JetPacParticlesStop();
		gJetman.Standing = TRUE;
		return;
	}

	// Hit the floor
	if (gJetman.YPos <= gJetman.BottomLimit) {
		glTranslatef(0.0f, gJetman.BottomLimit - gJetman.YPos, 0.0f);
		gJetman.YPos = gJetman.BottomLimit;
		JetPacParticlesStop();
		gJetman.Standing = TRUE;
		return;
	}

	// Fall down
	JetManMoveUpOrDown(FALSE, -gJetman.FallingSpeed);
	return;
}

void JetManBumpCheckFall() {

	// Fall for a few frames if we hid our head on a platform
	if (!gJetman.Bumping) return;

	// Increase frame count
	gJetman.Bump.Frame++;
	if (gJetman.Bump.Frame < gJetman.Bump.FrameCount) return;

	// End of the fall
	gJetman.Bumping = FALSE;
	gJetman.Bump.Frame = 0;

	// Now start a timer so we can re-set after a delay
	gJetman.Bump.FramesSinceBump = 1;
}

void JetManBumpCheckDelayAfter() {
	// Delay after the last bump to reset the oscillation
	if (gJetman.Bump.FramesSinceBump == 0) return;

	// Increment the delay counter
	gJetman.Bump.FramesSinceBump++;
	if (gJetman.Bump.FramesSinceBump <= gJetman.Bump.FramesSinceBumpDelay) return;

	// At the end, reset the oscillation
	gJetman.Bump.FrameCount = gJetman.Bump.FrameCountMax;
	gJetman.Bump.Count = 0;
	gJetman.Bump.FramesSinceBump = 0;
}

void JetManBumpCheckMovement() {
	JetManBumpCheckFall();
	JetManBumpCheckDelayAfter();
}

void JetManMove() {

	// Freeze if hit
	if (gJetman.Exploding) return;

	// Stop walking animation (will start if we move)
	gJetman.Walking = FALSE;

	// Bouncing after hitting head on platform ("Bump")
	JetManBumpCheckMovement();

	// Directional movement
	if (gGame.JetManMovementDisabled) return;
	if (InputLeft())  JetManMoveLeft();
	if (InputRight()) JetManMoveRight();
	if (!InputUp() || gJetman.Bumping) JetManFall();
	if (InputUp())    JetManMoveUp();
}