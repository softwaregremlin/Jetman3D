
void ModelLoaderCreatePath(char* subPath, unsigned int number) {
	char modelNo[10];
	sprintf(modelNo, "%d.bin", number);

	strncpy(gGame.DataPath, gPlatformSpecific.DataPath, 50);
	strcat(gGame.DataPath, subPath);
	strcat(gGame.DataPath, modelNo);
}

/////////////////////////////////////////////////////////
void ModelLoadHeaderCounts(unsigned int* verticeCount, 
						   unsigned int* indiceCount, 
						   unsigned int* textureVerticeCount,
						   FILE* file) {

	fread(&*verticeCount, sizeof(int), 1, file);
	fread(&*indiceCount, sizeof(int), 1, file);
	fread(&*textureVerticeCount, sizeof(int), 1, file);
}

////////////////////////////////
void ModelLoadFloatFromFile(unsigned int index, float targetArray[], float targetArray2[], FILE* file) {
	float floatValue;
	fread(&floatValue, sizeof(float), 1, file);
	targetArray[index] = floatValue;
	targetArray2[index] = floatValue;
}

void ModelLoadFloatsFromFile(unsigned int countAll, unsigned int countSubset, 
							 float targetArray[], float targetArray2[], FILE* file) {
	
	for (unsigned int ff = 0; ff < countAll; ff++) {
		targetArray[ff] = 0; targetArray2[ff] = 0;
		if (ff < countSubset) {
			ModelLoadFloatFromFile(ff, targetArray, targetArray2, file);
		}
	}
}

void ModelLoadVerticesFromFile(unsigned int verticeCount, float vertices[], float originalVertices[], FILE* file) {
	ModelLoadFloatsFromFile(verticeCount * 3, verticeCount * 3, vertices, originalVertices, file);
}

void ModelLoadColourIndexesFromFile(unsigned int verticeCount, float colourIndexes[], FILE* file) {
	ModelLoadFloatsFromFile(verticeCount * 4, verticeCount * 4, colourIndexes, colourIndexes, file);
}

void ModelLoadTextureIndexesFromFile(unsigned int verticeCount, unsigned int textureVerticeCount, float textureIndexes[], FILE* file) {
	ModelLoadFloatsFromFile(verticeCount * 2, textureVerticeCount * 2, textureIndexes, textureIndexes, file);
}
/////////////////////////////////

void ModelLoadIndicesFromFile(unsigned int indiceCount, GLUINT_ indices[], FILE* file) {
	int indInt;
	for (unsigned int gg = 0; gg < indiceCount; gg++) {
		fread(&indInt, sizeof(int), 1, file);
		indices[gg] = (GLUINT_)indInt;
	}
}

/////////////////////////////////
void ModelLoad( char* subPath, unsigned int modelNumber,
			    unsigned int* verticeCount, unsigned int* indiceCount, unsigned int* textureVerticeCount,
				float vertices[], float originalVertices[],
				float colourIndexes[], GLUINT_ indices[], float textureIndexes[]) {

	ModelLoaderCreatePath(subPath, modelNumber);

	// Open binary file
	FILE* file = fopen(gGame.DataPath, "rb");

	// Header contains the counts
	ModelLoadHeaderCounts(&*verticeCount, &*indiceCount, &*textureVerticeCount, file);

	// Vertices
	ModelLoadVerticesFromFile(*verticeCount, vertices, originalVertices, file);

	// Colours
	ModelLoadColourIndexesFromFile(*verticeCount, colourIndexes, file);

	// Indices
	ModelLoadIndicesFromFile(*indiceCount, indices, file);

	// Textures - set all to blank except the first values found
	ModelLoadTextureIndexesFromFile(*verticeCount, *textureVerticeCount, textureIndexes, file);	

	// Close the file
	fclose(file);
}