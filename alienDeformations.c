#define ALIEN_DEFORMATION_MAX_VERTICES 16

enum { AlienDeformDirectionForward, AlienDeformDirectionBackwards};

typedef struct {
	unsigned int Frame, Frames, Direction;
	float OriginalPosition[3], DeformedPosition[3];
} structAlienDeformationPoint;


typedef struct {	
	unsigned int VerticeIndexes[ALIEN_DEFORMATION_MAX_VERTICES], MinFrames, MaxFrames, VerticeCount;
	float MinDistance, MaxDistance;
	structAlienDeformationPoint DeformationPoints[ALIEN_MAX_COUNT][ALIEN_DEFORMATION_MAX_VERTICES];
} structAlienDeformation;

///////////////////////////////////////////////////////////////////////

structAlienDeformation gKinaDeformation = {
	.VerticeIndexes = { 7,8,9,10, 20,21,22,23, 33,34,35,36, 46,47,48,49},
	.VerticeCount = 16,
	.MinDistance = -0.25f, .MaxDistance = 0.25f,
	.MinFrames = 10, .MaxFrames = 20
};

///////////////////////////////////////////////////////////////

void AlienDeformationReset(unsigned int deformationIndex, unsigned int alienIndex) {

	// Set random offset on the Vertice
	for (unsigned int xyz = 0; xyz < 3; xyz++) {
		float delta;
		randMinMaxFloat(gKinaDeformation.MinDistance, gKinaDeformation.MaxDistance, &delta);
		gKinaDeformation.DeformationPoints[alienIndex][deformationIndex].DeformedPosition[xyz] =
			gKinaDeformation.DeformationPoints[alienIndex][deformationIndex].OriginalPosition[xyz] + delta;
	}

	// Set the time to a random value
	randMinMax(gKinaDeformation.MinFrames, gKinaDeformation.MaxFrames, &gKinaDeformation.DeformationPoints[alienIndex][deformationIndex].Frames);
	gKinaDeformation.DeformationPoints[alienIndex][deformationIndex].Frame = 0;
	gKinaDeformation.DeformationPoints[alienIndex][deformationIndex].Direction = AlienDeformDirectionForward;

}

void AlienDeformationPointInitialise(unsigned int deformationIndex, unsigned int alienIndex) {
	
	for (unsigned int xyz = 0; xyz < 3; xyz++) {
		gKinaDeformation.DeformationPoints[alienIndex][deformationIndex].OriginalPosition[xyz] =
			gAliens[alienIndex].Vertices[(gKinaDeformation.VerticeIndexes[deformationIndex] * 3) + xyz];
	}		

	AlienDeformationReset(deformationIndex, alienIndex);
}

void AlienDeformationInitialise(unsigned int alienIndex) {
	
	for (unsigned int dd = 0; dd < gKinaDeformation.VerticeCount; dd++) {
		AlienDeformationPointInitialise(dd, alienIndex);
	}
	
	// gAliens[alienIndex].DeformationOriginalPointsSet = TRUE;
	
}

////////////////////////////////////////

void AlienDeformPoint(unsigned int deformationIndex, unsigned int alienIndex) {

	float deltaRatio =
		(float)gKinaDeformation.DeformationPoints[alienIndex][deformationIndex].Frame /
		(float)gKinaDeformation.DeformationPoints[alienIndex][deformationIndex].Frames;

	for (unsigned int xyz = 0; xyz < 3; xyz++) {
		float originalPos = gKinaDeformation.DeformationPoints[alienIndex][deformationIndex].OriginalPosition[xyz],
			delta = (gKinaDeformation.DeformationPoints[alienIndex][deformationIndex].DeformedPosition[xyz] - originalPos) * deltaRatio;

		gAliens[alienIndex].Vertices[(gKinaDeformation.VerticeIndexes[deformationIndex] * 3) + xyz] = originalPos + delta;

	}

	// Ping pong effect
	gKinaDeformation.DeformationPoints[alienIndex][deformationIndex].Frame +=
		(gKinaDeformation.DeformationPoints[alienIndex][deformationIndex].Direction == AlienDeformDirectionForward) ? 1 : -1;

	if (gKinaDeformation.DeformationPoints[alienIndex][deformationIndex].Frame == gKinaDeformation.DeformationPoints[alienIndex][deformationIndex].Frames) {
		gKinaDeformation.DeformationPoints[alienIndex][deformationIndex].Direction = AlienDeformDirectionBackwards;
	}

	if (gKinaDeformation.DeformationPoints[alienIndex][deformationIndex].Frame == 0 &&
		gKinaDeformation.DeformationPoints[alienIndex][deformationIndex].Direction == AlienDeformDirectionBackwards) {
		AlienDeformationReset(deformationIndex, alienIndex);
	}

}

void AlienDeform(unsigned int alienIndex) {
	for (unsigned int dd = 0; dd < gKinaDeformation.VerticeCount; dd++) {
		AlienDeformPoint(dd, alienIndex);
	}
}