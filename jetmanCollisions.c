////////////////////////////////////////////////
// Collectible Objects (Rocket, Fuel, Trinkets)
////////////////////////////////////////////////
unsigned int JetmanCollidesWithObject(float xPos, float yPos, float collW, float collH, float collYOffset) {

	float collLeft = xPos - (collW / 2.0f),
		  collTop = yPos + collYOffset + (collH / 2.0f),
		  jetmanLeft = gJetman.XPos - (gJetman.CollisionRecWidth / 2.0f),
		  jetmanTop = gJetman.YPos + gJetman.CollisionRecHeightOffset + (gJetman.CollisionRecHeight / 2.0f);

	return RectanglesCollide(collLeft, collTop, collW, collH, jetmanLeft, jetmanTop, gJetman.CollisionRecWidth, gJetman.CollisionRecHeight);
}

/////////////////////////////////////////////////////
// Platforms (hit head on top, hit sides or landing)
/////////////////////////////////////////////////////
unsigned int JetManCollidesWithPlatformSides(int platFormIndex) {

	float jetManX = gJetman.XPos - (gJetman.Width / 2);

	return  (jetManX + gJetman.CollisionRecWidth >= gPlatforms[platFormIndex].X &&
		(jetManX + gJetman.Width - gJetman.CollisionRecWidth) <= gPlatforms[platFormIndex].X + gPlatforms[platFormIndex].Width);
}

unsigned int JetManCollidesWithPlatform() {
	float jetManY = gJetman.YPos + gJetman.YAbovePosition;

	for (int pp = 0; pp < PLATFORM_COUNT; pp++) {
		if (JetManCollidesWithPlatformSides(pp) &&

			// top on or above the platform
			(jetManY >= gPlatforms[pp].Y - (gPlatforms[pp].Height / 2) &&
				// bottom on or below the platform
				  jetManY - gJetman.Height <= gPlatforms[pp].Y - (gPlatforms[pp].Height))) {
			return TRUE;
		}
	}
	return FALSE;
}


unsigned int JetManCollidesWithPlatformBottom() {
	float jetManY = gJetman.YPos + gJetman.YAbovePosition;
	for (int pp = 0; pp < PLATFORM_COUNT; pp++) {
		if (JetManCollidesWithPlatformSides(pp) &&
			(jetManY >= gPlatforms[pp].Y - gPlatforms[pp].Height &&
				jetManY <= gPlatforms[pp].Y)) {
			return TRUE;
		}
	}
	return FALSE;
}


unsigned int JetManCollidesWithPlatformTop() {
	float jetManY = gJetman.YPos + gJetman.YAbovePosition;

	for (int pp = 0; pp < PLATFORM_COUNT; pp++) {

		if (JetManCollidesWithPlatformSides(pp) &&
			(jetManY - gJetman.Height <= gPlatforms[pp].Y) &&
			(jetManY - gJetman.Height >= gPlatforms[pp].Y - gPlatforms[pp].Height))
			return TRUE;
	}
	return FALSE;
}