unsigned int ObjectCollidesWithPlatformInstanceSides(unsigned int platformIndex, float xPos, float collisionRecWidth) {

	float left  = xPos - collisionRecWidth / 2.0f,
		  right = xPos + collisionRecWidth / 2.0f,
		  platformLeft  = gPlatforms[platformIndex].X,
		  platformRight = gPlatforms[platformIndex].X + gPlatforms[platformIndex].Width;

	return right >= platformLeft && left <= platformRight;
}

unsigned int ObjectLandsOnPlatformInstance(unsigned int platformIndex, float xPos, float yPos,
										   float collisionRecWidth, float collisionRecHeight, float collisionYOffSet) {

	float bottom = yPos - (collisionRecHeight / 2.0f) + collisionYOffSet,

		platformTop = gPlatforms[platformIndex].Y,
		platformBottom = platformTop - gPlatforms[platformIndex].Height;

	return ObjectCollidesWithPlatformInstanceSides(platformIndex, xPos, collisionRecWidth) &&
		bottom <= platformTop && bottom >= platformBottom;
}