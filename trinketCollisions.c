/// Jetman ////////////////
unsigned int TrinketCollidesWithJetman() {

	return JetmanCollidesWithObject(
		gTrinket.XPos, gTrinket.YPos,
		gTrinketSettingsGame.Settings[gTrinket.TrinketType - 1].CollisionRectangleWidth, 
		gTrinketSettingsGame.Settings[gTrinket.TrinketType - 1].CollisionRectangleWidth, 0);
}


// The Ground Plane /////////////////////
unsigned int TrinketCollidesWithGround() {
	return gTrinket.YPos <= gTrinketSettingsGame.GroundCollisionY + 
		gTrinketSettingsGame.Settings[gTrinket.TrinketType - 1].GroundCollisionOffset;
}

// Platforms /////////////////////
unsigned int TrinketLandsOnPlatform() {

	// Exception for far right of the screen
	if (gTrinket.XPos == gTrinketSettingsGame.XMinMax) return FALSE;

	for (int pp = 0; pp < PLATFORM_COUNT; pp++) {
		if (ObjectLandsOnPlatformInstance(pp,
			gTrinket.XPos, gTrinket.YPos,
			gTrinketSettingsGame.Settings[gTrinket.TrinketType - 1].CollisionRectangleWidth, 
			gTrinketSettingsGame.Settings[gTrinket.TrinketType - 1].CollisionRectangleHeight,
			-gTrinketSettingsGame.Settings[gTrinket.TrinketType - 1].CollisionRecBottomSpace)) return TRUE;
	}
	return FALSE;
}