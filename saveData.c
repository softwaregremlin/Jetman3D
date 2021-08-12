void SaveHighScore() {

	// No need to save!
	if (gGame.Score < gGame.HiScore) return;

	gGame.HiScore = gGame.Score;
	// gGame.NewHighScore = true;

	// Save hi

	// Small delay when ceating the folder - moved to start of game
	// CreateDataFolderIfNotExists();
	FILE* dataFile;
	if ((dataFile = fopen(DATA_HISCORE, "w"))) {
		fprintf(dataFile, "%d", gGame.HiScore);
		fclose(dataFile);
	}
}