#define COLOR_PULSATE_MAX_LENGTH 5
#define RGB_LENGTH 3


enum { ColorPulsateDirectionForward, ColorPulsateDirectionBackward };
enum { ColorRed, ColorGreen, ColorBlue, ColorYellow, ColorMagenta, ColorCyan, ColorWhite, ColorBlack };

///////////////////////////////////////////////////////////////////////////////////////////////////////////

void ColorArrayBWToCyanSection(float* colorArray, unsigned int arrayStart, unsigned int arrayEnd) {
	for (unsigned int cc = arrayStart; cc <= arrayEnd; cc++) {
		colorArray[cc * 4] = 0;
		// Tinge of red to accent highlights
		if (colorArray[(cc * 4) + 1] == 1.0f) colorArray[(cc * 4) + 0] = 0.75f;
	}
}

void ColorArrayBWToCyan(float* colorArray, unsigned int arraySize) {
	ColorArrayBWToCyanSection(colorArray, 0, (arraySize / 4) - 1);
}

void ColorArrayBWToMagentaSection(float* colorArray, unsigned int arrayStart, unsigned int arrayEnd) {	
	for (unsigned int cc = arrayStart; cc <= arrayEnd; cc++) {
		colorArray[(cc * 4) + 1] = 0;
		// Tinge of green to accent highlights
		if (colorArray[(cc * 4) + 0] == 1.0f) colorArray[(cc * 4) + 1] = 0.5f;
	}
}

void ColorArrayBWToMagenta(float* colorArray, unsigned int arraySize) {
	ColorArrayBWToMagentaSection(colorArray, 0, (arraySize / 4) - 1);
}

void ColorArrayBWToRed(float* colorArray, unsigned int arraySize) {
	for (unsigned int cc = 0; cc < arraySize / 4; cc++) {
		colorArray[(cc * 4) + 1] = 0;
		colorArray[(cc * 4) + 2] = 0;
		// Tinge of green to accent highlights
		if (colorArray[(cc * 4) + 0] == 1.0f) colorArray[(cc * 4) + 1] = 0.5f;
	}
}

void ColorArrayBWToGreen(float* colorArray, unsigned int arraySize) {
	for (unsigned int cc = 0; cc < arraySize / 4; cc++) {
		colorArray[cc * 4] = 0;
		colorArray[(cc * 4) + 2] = 0;
		// Tinge of red to accent highlights
		if (colorArray[(cc * 4) + 1] == 1.0f) colorArray[(cc * 4) + 0] = 0.5f;
	}
}

void ColorArrayBWToYellow(float* colorArray, unsigned int arraySize) {
	for (unsigned int cc = 0; cc < arraySize / 4; cc++) {
		colorArray[(cc * 4) + 2] = 0;
	}
}

void ColorArrayBWToBlack(float* colorArray, unsigned int arraySize) {
	for (unsigned int cc = 0; cc < arraySize / 4; cc++) {
		for (unsigned int cc2 = 0; cc < 3; cc++) {
			colorArray[(cc * 4) + cc2] = 0;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////

void ColorArrayBWToColor(float* colorArray, unsigned int arraySize, unsigned int color) {
	if (color == ColorRed)    ColorArrayBWToRed(colorArray, arraySize);
	if (color == ColorGreen)  ColorArrayBWToGreen(colorArray, arraySize);
	if (color == ColorCyan)   ColorArrayBWToCyan(colorArray, arraySize);
	if (color == ColorYellow) ColorArrayBWToYellow(colorArray, arraySize);
	if (color == ColorBlack)  ColorArrayBWToBlack(colorArray, arraySize);
}

/////////////////////////////////////////////////////////


// Convert from colours back to black and white
void ColorArrayToBWSection(float* colorArray, unsigned int arrayStart, unsigned int arrayEnd) {
	unsigned int ccOffset;
	for (unsigned int cc = arrayStart; cc <= arrayEnd; cc++) {
		float maxColor = 0;
		for (ccOffset = 0; ccOffset < 3; ccOffset++) {
			float color = colorArray[(cc * 4) + ccOffset];
			maxColor = color > maxColor ? color : maxColor;
		}
		for (ccOffset = 0; ccOffset < 3; ccOffset++) {
			colorArray[(cc * 4) + ccOffset] = maxColor;
		}
	}
}


void ColorArrayToBW(float* colorArray, unsigned int arraySize) {
	ColorArrayToBWSection(colorArray, 0, (arraySize / 4) - 1);
}

unsigned int ColorArraySetRandom(float* colorArray, unsigned int arraySize) {

	enum { Red, Green, Magenta, Cyan, White };

	ColorArrayToBW(colorArray, arraySize);
	unsigned int colour = 0;
	randMinMax(0, 4, &colour);

	if(colour==Red) ColorArrayBWToRed(colorArray, arraySize);
	if(colour==Green) ColorArrayBWToGreen(colorArray, arraySize);
	if(colour==Magenta) ColorArrayBWToMagenta(colorArray, arraySize);
	if(colour==Cyan) ColorArrayBWToCyan(colorArray, arraySize);

	return colour;
}

void ColorArrayApplyAlphaSection(float* colorArray, unsigned int arrayStart, unsigned int arrayEnd, float alphaValue) {
	for (unsigned int cc = arrayStart; cc <= arrayEnd; cc++) {
		colorArray[(cc * 4) + 3] = alphaValue;
	}
}


void ColorArrayApplyAlpha(float* colorArray, unsigned int arraySize, float alphaValue) {
	ColorArrayApplyAlphaSection(colorArray, 0, (arraySize / 4) - 1, alphaValue);
}

/////////////////////////////////////////////////////////////////////////


void ColorArrayPulsateSection(float* colorArray, 
	unsigned int hasReferenceColorArray,
	float* referenceColorArray, unsigned int sourceColorIndex,
	unsigned int arrayStart, unsigned int arrayEnd,
	unsigned int* colorPulsateFrame, unsigned int* colorPulsateDirection,
	unsigned int colorPulsateFrameCount,
	int* rgbDirections) {

	*colorPulsateFrame += *colorPulsateDirection == ColorPulsateDirectionForward ? 1 : -1;
	if (*colorPulsateFrame == colorPulsateFrameCount) *colorPulsateDirection = ColorPulsateDirectionBackward;
	if (*colorPulsateFrame == 0) *colorPulsateDirection = ColorPulsateDirectionForward;

	float colorPulsatePercent = (float)*colorPulsateFrame / (float)colorPulsateFrameCount;

	for (unsigned int cc = arrayStart; cc <= arrayEnd; cc++) {
		float copyColorFrom = hasReferenceColorArray ?
			referenceColorArray[cc] : colorArray[(cc * 4) + sourceColorIndex];
		float colorDest = copyColorFrom * colorPulsatePercent,
			  colorMinusDest = copyColorFrom * (1.0f - colorPulsatePercent);

		int destR = rgbDirections[ColorRed], destG = rgbDirections[ColorGreen], destB = rgbDirections[ColorBlue];		

		if (destR != 0) colorArray[(cc * 4) + ColorRed]   = (destR == 1 ? colorDest : colorMinusDest);
		if (destG != 0) colorArray[(cc * 4) + ColorGreen] = (destG == 1 ? colorDest : colorMinusDest);
		if (destB != 0) colorArray[(cc * 4) + ColorBlue]  = (destB == 1 ? colorDest : colorMinusDest);
		// colorArray[(cc * 4) + ColorBlue] = 0;
	}
}

/////////////////////////////////////////////////////////////////////////////


void ColorArrayPulsateMagentaToWhite(float* colorArray, unsigned int arraySize,
	unsigned int* colorPulsateFrame, unsigned int* colorPulsateDirection,
	unsigned int colorPulsateFrameCount) {

	int rgbDirections[3] = { 0, 1, 0 };
	float nullColorArray[] = { 0 };
	ColorArrayPulsateSection(colorArray, FALSE, nullColorArray, ColorBlue, 0, (arraySize / 4) - 1,
		&*colorPulsateFrame, &*colorPulsateDirection, colorPulsateFrameCount, rgbDirections); // 0, 1, 0);
}


void ColorArrayPulsateCyanToWhiteSection(float* colorArray, unsigned int arrayStart, unsigned int arrayEnd,
										 unsigned int* colorPulsateFrame, unsigned int* colorPulsateDirection,
										 unsigned int colorPulsateFrameCount) {
	
	int rgbDirections[3] = { 1, 0, 0 };
	float nullColorArray[] = { 0 };
	ColorArrayPulsateSection(colorArray, FALSE, nullColorArray, ColorBlue, arrayStart, arrayEnd,
		&*colorPulsateFrame, &*colorPulsateDirection, colorPulsateFrameCount, rgbDirections);
}



/////////////////////////////////////////////////////////
void ColorArrayPulsateSectionSequence(float* colorArray, float* referenceColorArray, unsigned int sourceColorIndex,
	unsigned int arrayStart, unsigned int arrayEnd,
	unsigned int* colorPulsateFrame, 
	unsigned int* colorPulsateDirection,
	unsigned int colorPulsateFrameCount,
	unsigned int* pulsateSequenceNumber,
	int pulsateSequences[COLOR_PULSATE_MAX_LENGTH][RGB_LENGTH],
	unsigned int pulsateSequenceLength) {

	ColorArrayPulsateSection(colorArray, TRUE, referenceColorArray, sourceColorIndex, arrayStart, arrayEnd,
		&*colorPulsateFrame, &*colorPulsateDirection, colorPulsateFrameCount, pulsateSequences[*pulsateSequenceNumber]);

	if (*colorPulsateFrame == colorPulsateFrameCount) {
		*pulsateSequenceNumber+=1;
		*colorPulsateFrame = 0;
		*colorPulsateDirection = 0;
	}
	if (*pulsateSequenceNumber >= pulsateSequenceLength) *pulsateSequenceNumber = 0;

}
