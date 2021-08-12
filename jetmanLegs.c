
// Set Left and Right legs to different frames
void JetManPrepareLegsLeftRight(unsigned int leftIndex, unsigned int rightIndex) {

	// Copy Right to Legs
	ArrayCopyFloat(gModelJetman.LegModels[rightIndex].Vertices, gModelJetman.VerticesLegs, JETMAN_LEG_VERTICE_COUNT);
	ArrayCopyFloat(gModelJetman.LegModels[rightIndex].ColourIndexes, gModelJetman.ColourIndexesLegs, JETMAN_LEG_FACE_COUNT * 16);

	// Copy right to left, mirror
	ArrayCopyFloat(gModelJetman.LegModels[leftIndex].Vertices, gModelJetman.VerticesLegLeft, JETMAN_LEG_VERTICE_COUNT);
	VerticeArrayMirrorZ(gModelJetman.VerticesLegLeft, JETMAN_LEG_VERTICE_COUNT);

	// Copy Left to Legs
	ArrayAppendFloat(gModelJetman.VerticesLegLeft, gModelJetman.VerticesLegs, JETMAN_LEG_VERTICE_COUNT, JETMAN_LEG_VERTICE_COUNT);
	ArrayAppendFloat(gModelJetman.LegModels[rightIndex].ColourIndexes, gModelJetman.ColourIndexesLegs, 
		JETMAN_LEG_FACE_COUNT * 16, JETMAN_LEG_FACE_COUNT * 16);
}


// Sitting 
void JetManPrepareLegsSitting() {	
	JetManPrepareLegsLeftRight(JetManLegFrameSitting, JetManLegFrameSitting);
}

void JetManPrepareLegsWalking() {	

	// If walking - take a step forward
	if (gJetman.Walking && !gJetman.Exploding) {
		gJetman.WalkingFrame++;
		if (gJetman.WalkingFrame == gJetman.WalkingFrameCount) {
			gJetman.WalkingFrame = 0;
			gJetman.WalkingStep++;
			if (gJetman.WalkingStep == gJetman.WalkingStepCount) gJetman.WalkingStep = 0;
		}
	}

	JetManPrepareLegsLeftRight(
		gModelJetman.WalkingFrames[gJetman.WalkingStep][0],
		gModelJetman.WalkingFrames[gJetman.WalkingStep][1]);
}

void JetManPrepareLegs() {

	// Standing upright or walking
	if (gJetman.Standing) {
		JetManPrepareLegsWalking();
		return;
	}
	
	// Jumping / falling
	JetManPrepareLegsSitting();
}