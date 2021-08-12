void TrinketLoadModel(unsigned int index) {

	ModelLoad(
		gTrinketSettingsGame.ModelPath, index + 1,
		&gTrinketSettingsGame.Settings[index].VerticeCount,
		&gTrinketSettingsGame.Settings[index].IndiceCount,
		&gTrinketSettingsGame.Settings[index].TextureVerticeCount,
		gTrinketSettingsGame.Settings[index].InitialVertices,
		gTrinketSettingsGame.Settings[index].InitialVertices,
		gTrinketSettingsGame.Settings[index].InitialColourIndexes,
		gTrinketSettingsGame.Settings[index].Indices,
		gTrinketSettingsGame.Settings[index].TextureIndexes
	);
}

void TrinketInitialiseSettings(unsigned int index) {


	// Save the original colours to use for colour cycling later
	for (unsigned int cc = 0; cc < gTrinketSettingsGame.Settings[index].VerticeCount; cc++) {
		gTrinketSettingsGame.Settings[index].OriginalColorArray[cc] = gTrinketSettingsGame.Settings[index].InitialColourIndexes[(cc * 4)];
	}

	// Set the initial colour
	ColorArrayBWToColor(gTrinketSettingsGame.Settings[index].InitialColourIndexes,
		gTrinketSettingsGame.Settings[index].VerticeCount * 4, gTrinketSettingsGame.Settings[index].InitialColour);

	if (gGame.State == GameStateModelView) return;

	// Scale
	VerticeArrayScaleDimensions(gTrinketSettingsGame.Settings[index].Scale,
		gTrinketSettingsGame.Settings[index].InitialVertices, gTrinketSettingsGame.Settings[index].VerticeCount * 3);
}

// Initialise the instance
void TrinketInitialise() {

	// Randomly select the type of Trinket 
	randMinMax(1, TRINKET_COUNT + 1, &gTrinket.TrinketType);

	//TEMP
	// gTrinket.TrinketType = 3;

	// Copy down the vertices and Colours
	ArrayCopyFloat(gTrinketSettingsGame.Settings[gTrinket.TrinketType - 1].InitialVertices, gTrinket.Vertices,
		gTrinketSettingsGame.Settings[gTrinket.TrinketType - 1].VerticeCount * 3);
	ArrayCopyFloat(gTrinketSettingsGame.Settings[gTrinket.TrinketType - 1].InitialColourIndexes, gTrinket.ColourIndexes,
		gTrinketSettingsGame.Settings[gTrinket.TrinketType - 1].VerticeCount * 4);
	
	gTrinket.ColorPulsateFrame = 0;
	gTrinket.ColorPulsateDirection = ColorPulsateDirectionForward;
	gTrinket.ColorSequenceNumber = 0;

	gTrinket.State = TrinketStatePaused;
	gTrinket.PauseFrame = 0;

	randMinMax(gTrinketSettingsGame.PauseFramesMinMax[0], gTrinketSettingsGame.PauseFramesMinMax[1], &gTrinket.PauseFrames);

}

void TrinketsLoadAndInitialise() {

	for (unsigned int tt = 0; tt < TRINKET_COUNT; tt++) {
		TrinketLoadModel(tt);
		TrinketInitialiseSettings(tt);
	}

	TrinketInitialise();
}