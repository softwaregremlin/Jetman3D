
void AlienInitialiseEyeTextureCoordinates() {
	unsigned int i, rr, cc, tv, tileCount = 0,
		rows = gAlienSettingsGame.EyeTileRows, cols = gAlienSettingsGame.EyeTileColumns;

	// Tiles are in a grid
	for (rr = 0; rr < rows; rr++) {
		for (cc = 0; cc < cols; cc++) {
			if (tileCount < ALIEN_EYE_TILE_COUNT) {
				gAlienSettingsGame.EyeTextureVertices[rr * cols + cc][0] = (float)cc / (float)cols;
				gAlienSettingsGame.EyeTextureVertices[rr * cols + cc][1] = 1.0f - ((float)rr / (float)rows);

				gAlienSettingsGame.EyeTextureVertices[rr * cols + cc][2] = (float)(cc + 1) / (float)cols;
				gAlienSettingsGame.EyeTextureVertices[rr * cols + cc][3] = 1.0f - ((float)(rr + 1) / (float)rows);

				gAlienSettingsGame.EyeTextureVertices[rr * cols + cc][4] = (float)cc / (float)cols;
				gAlienSettingsGame.EyeTextureVertices[rr * cols + cc][5] = 1.0f - ((float)(rr + 1) / (float)rows);

				gAlienSettingsGame.EyeTextureVertices[rr * cols + cc][6] = (float)(cc + 1) / (float)cols;
				gAlienSettingsGame.EyeTextureVertices[rr * cols + cc][7] = 1.0f - ((float)rr / (float)rows);
			}
			tileCount++;
		}
	}

	// Mirror the left eye movements to the right
	for (i = 0; i < ALIEN_EYE_TILE_MIRROR_COUNT; i++) {
		for (tv = 0; tv < BILLBOARD_VERTICE_COUNT; tv++) {
			// reverse the order of the x,y pairs
			gAlienSettingsGame.EyeTextureVertices[ALIEN_EYE_TILE_COUNT + i][tv * 2] =
				gAlienSettingsGame.EyeTextureVertices
				[gAlienSettingsGame.EyeTileMirrorFrom + i][((BILLBOARD_VERTICE_COUNT * 2) - 2) - (tv * 2)];
			gAlienSettingsGame.EyeTextureVertices[ALIEN_EYE_TILE_COUNT + i][tv * 2 + 1] =
				gAlienSettingsGame.EyeTextureVertices
				[gAlienSettingsGame.EyeTileMirrorFrom + i][((BILLBOARD_VERTICE_COUNT * 2) - 1) - (tv * 2)];

		}
	}
}



unsigned int AlienEyeGetMirroredFrame(unsigned int frame) {

	// Right Eye - we swap the pupil movement frames so we don't go cross-eyed
	unsigned int rightFrame = frame;
	for (unsigned int mm = 0; mm < ALIEN_EYE_PUPIL_FRAMES_COUNT; mm++) {
		if (frame == gAlienSettingsGame.PupilMovementFramesLeft[mm]) {
			return gAlienSettingsGame.PupilMovementFramesRight[mm];
		}
		if (frame == gAlienSettingsGame.PupilMovementFramesRight[mm]) {
			return gAlienSettingsGame.PupilMovementFramesLeft[mm];
		}
	}
	return frame;
}

void AlienSetEyeTextureFrame(unsigned int frame) {
	for (unsigned int i = 0; i < BILLBOARD_VERTICE_COUNT * 2; i++) {
		for (unsigned int aa = 0; aa < ALIEN_MAX_COUNT; aa++) {

			// Left Eye
			gAliens[aa].TextureIndexes[(gAlienSettingsGame.VerticeCount * 2) - (BILLBOARD_VERTICE_COUNT * 4) + i] =
				gAlienSettingsGame.EyeTextureVertices[frame][i];

			// Right Eye
			unsigned int rightFrame = AlienEyeGetMirroredFrame(frame);
			gAliens[aa].TextureIndexes[(gAlienSettingsGame.VerticeCount * 2) - (BILLBOARD_VERTICE_COUNT * 2) + i] =
				gAlienSettingsGame.EyeTextureVertices[rightFrame][i];

		}
	}
}