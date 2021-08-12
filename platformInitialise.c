void PlatformsLoadModel() {

	// ModelLoaderAddPath(gModelPlatforms.ModelPath, 1);

	ModelLoad(
		gModelPlatforms.ModelPath, 1,
		&gModelPlatforms.VerticeCount,
		&gModelPlatforms.IndiceCount,
		&gModelPlatforms.TextureVerticeCount,
		gModelPlatforms.Vertices,
		gModelPlatforms.Vertices,
		gModelPlatforms.ColourIndexes,
		gModelPlatforms.Indices,
		gModelPlatforms.TextureIndexes
	);
}

void GroundLoadModel() {

	ModelLoad(
		gModelGround.ModelPath, 1,
		&gModelGround.VerticeCount,
		&gModelGround.IndiceCount,
		&gModelGround.TextureVerticeCount,
		gModelGround.Vertices,
		gModelGround.Vertices,
		gModelGround.ColourIndexes,
		gModelGround.Indices,
		gModelGround.TextureIndexes
	);
}



void PlatformsInitialise() {

	TextureLoad(gModelPlatforms.TexturePath, gModelPlatforms.TextureIndex);
	PlatformsLoadModel();
	GroundLoadModel();
}
