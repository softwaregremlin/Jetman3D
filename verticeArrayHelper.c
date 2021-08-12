#define CUBIOD_VERTICE_COUNT 8
#define CUBIOD_INDICE_COUNT  12

typedef struct { unsigned int X, Y, Z; } structModelViewMatrixIndexes;
structModelViewMatrixIndexes gModelViewMatrixIndexes = { .X = 12, .Y = 13, .Z = 14 };

enum VerticeScaleDimension { VerticeScaleDimensionX, VerticeScaleDimensionY, VerticeScaleDimensionZ };

// Scale all Vertices
void VerticeArrayScale(float scale, float * verticeArray, unsigned int arraySize) {
	for (unsigned int vv = 0; vv < arraySize; vv++) {
		verticeArray[vv] = verticeArray[vv] * scale;
	}
}

// Scale just one dimension
void VerticeArrayScaleDimension(float scale, float* verticeArray, unsigned int arraySize, unsigned int dimension ) {
	unsigned int verticeCount = arraySize / 3;
	for (unsigned int vv = 0; vv < verticeCount; vv++) {
		verticeArray[(vv * 3) + dimension] = verticeArray[(vv * 3) + dimension] * scale;
	}
}

// Scale various dimensions
void VerticeArrayScaleDimensions(float* scaleArray, float* verticeArray, unsigned int arraySize) {
	unsigned int verticeCount = arraySize / 3;
	for (unsigned int vv = 0; vv < verticeCount; vv++) {
		for (unsigned int dimension = 0; dimension < 3; dimension++) {
			verticeArray[(vv * 3) + dimension] = verticeArray[(vv * 3) + dimension] * scaleArray[dimension];
		}
	}
}



// Transform
void VerticeArrayTransformSection(float xMovement, float yMovement, float zMovement, float* verticeArray,
								  unsigned int arraySectionStart, unsigned int arraySectionEnd) {
	for (unsigned int vv = arraySectionStart / 3; vv <= arraySectionEnd / 3; vv++) {

		verticeArray[(vv * 3) + 0] += xMovement;
		verticeArray[(vv * 3) + 1] += yMovement;
		verticeArray[(vv * 3) + 2] += zMovement;
	}
}


void VerticeArrayTransform(float xMovement, float yMovement, float zMovement, float* verticeArray, unsigned int arraySize) {
	VerticeArrayTransformSection(xMovement, yMovement, zMovement, verticeArray, 0, arraySize - 1);
}

/////////////////////////////

// Snap To
void VerticeArraySnapToSection( float* verticeArray, float* verticeArrayOriginal,
								unsigned int arraySectionStart, unsigned int arraySectionEnd) {
	for (unsigned int vv = arraySectionStart / 3; vv <= arraySectionEnd / 3; vv++) {

		verticeArray[(vv * 3) + 0] = verticeArrayOriginal[(vv * 3) + 0];
		verticeArray[(vv * 3) + 1] = verticeArrayOriginal[(vv * 3) + 1];
		verticeArray[(vv * 3) + 2] = verticeArrayOriginal[(vv * 3) + 2];
	}
}


/////////////////////////////


void VerticeArrayRotate90(float * verticeArray, unsigned int arraySize) {
	float newZ, newX;
	for (unsigned int vv = 0; vv < arraySize / 3; vv++) {

		// Move z to x
		newX = verticeArray[(vv * 3) + 2];
		// y stays the same
		// Move x to z, and flip
		newZ = verticeArray[(vv * 3)] * -1;

		verticeArray[(vv * 3)]     = newX;
		verticeArray[(vv * 3) + 2] = newZ;
	}
}

void VerticeArrayMirrorZ(float* verticeArray, unsigned int arraySize) {
	for (unsigned int vv = 0; vv < arraySize / 3; vv++) {
		// Multiply z by -1
		verticeArray[(vv * 3) + 2] = verticeArray[(vv * 3) + 2] * -1;
	}
}

void VerticeArrayMirrorY(float* verticeArray, unsigned int arraySize) {
	for (unsigned int vv = 0; vv < arraySize / 3; vv++) {
		// Multiply x by -1
		verticeArray[(vv * 3) + 0] = verticeArray[(vv * 3) + 0] * -1;
	}
}



void VerticeArrayMirrorWithin(
	float* verticeArray, unsigned int* verticeCount, float* colourIndexArray,
	GLUINT_* indiceArray, unsigned int* indiceArraySize, float xScale, float yScale, float zScale) {

	unsigned int verticeArraySize = *verticeCount * 3;

	for (unsigned int vv = 0; vv < *verticeCount; vv++) {

		verticeArray[(vv * 3) + verticeArraySize] = verticeArray[(vv * 3)] * xScale;
		verticeArray[(vv * 3) + verticeArraySize + 1] = verticeArray[(vv * 3) + 1] * yScale;
		verticeArray[(vv * 3) + verticeArraySize + 2] = verticeArray[(vv * 3) + 2] * zScale;

		for (unsigned int cc = 0; cc < 4; cc++) {
			colourIndexArray[(vv * 4) + cc + (verticeArraySize * 4 / 3)] = colourIndexArray[(vv * 4) + cc];
		}
	}

	for (unsigned int ii = 0; ii < *indiceArraySize; ii++) {
		indiceArray[*indiceArraySize + ii] = indiceArray[ii] + (GLUINT_)*verticeCount;
	}

	*verticeCount = *verticeCount * 2;
	*indiceArraySize = *indiceArraySize * 2;

}



void VerticeArrayMirrorYWithin(float* verticeArray, unsigned int* verticeArraySize, float* colourIndexArray,
	GLUINT_* indiceArray, unsigned int* indiceArraySize) {

	VerticeArrayMirrorWithin(verticeArray, verticeArraySize, colourIndexArray, indiceArray, indiceArraySize, -1, 1, 1);
}


void VerticeArrayMirrorXWithin(float* verticeArray, unsigned int* verticeArraySize, float* colourIndexArray,
	GLUINT_* indiceArray, unsigned int* indiceArraySize) {

	VerticeArrayMirrorWithin(verticeArray, verticeArraySize, colourIndexArray, indiceArray, indiceArraySize, 1, -1, 1);
}

//////////////////////////////////////////////

void ArrayCopyFloat(float* arraySrc, float* arrayDest, unsigned int arraySize) {
	memcpy(arrayDest, arraySrc, arraySize * sizeof(float));
}

void ArrayAppendFloat(float* arraySrc, float* arrayDest, unsigned int startPos, unsigned int arraySize) {
	for (unsigned int ff = startPos; ff < startPos + arraySize; ff++) {
		arrayDest[ff] = arraySrc[ff - startPos];
	}
}

void ArrayCopyGluint(GLUINT_* arraySrc, GLUINT_* arrayDest, unsigned int arraySize) {
	memcpy(arrayDest, arraySrc, arraySize * sizeof(GLUINT_));
}

void ArrayAppendGluintWithOffset(GLUINT_* arraySrc, GLUINT_* arrayDest, GLUINT_ offset, unsigned int startPos, unsigned int arraySize) {
	for (unsigned int gg = startPos; gg < startPos + arraySize; gg++) {
		arrayDest[gg] = arraySrc[gg - startPos] + offset;
	}
}

//////////////////////////////////////////////