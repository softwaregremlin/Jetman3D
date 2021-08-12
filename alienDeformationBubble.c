typedef struct {
	float Speed, MinScale, MaxScale, Scale, RelativeScale;
} structAlienDeformationBubbleDimension;

structAlienDeformationBubbleDimension gAlienDeformationBubbleTemplate[3] = {
	{.Scale = 1.0f,  .Speed = 0.05f,  .MinScale = 1.0f,  .MaxScale = 1.05f },
	{.Scale = 1.0f,  .Speed = -0.05f, .MinScale = 0.8f, .MaxScale = 1.05f  },
	{.Scale = 1.0f,  .Speed = 0.05f,  .MinScale = 1.0f,  .MaxScale = 1.05f }
};

structAlienDeformationBubbleDimension gAlienDeformationBubble[ALIEN_MAX_COUNT][3];

///////////////////////////////////////////////////////////
// Copy settings down to the individual instances
void AlienDeformBubbleDimensionInitialise(unsigned int alienIndex) {


	for (unsigned int dd = 0; dd < 3; dd++) {

		// Correct scale if already deformed
		//float relativeScale = gAlienDeformationBubble[alienIndex][dd].Scale == 0 ?
		//	gAlienDeformationBubbleTemplate[dd].Scale :
		//	gAlienDeformationBubbleTemplate[dd].Scale / gAlienDeformationBubble[alienIndex][dd].Scale;
		float relativeScale = 1.0f;

		gAlienDeformationBubble[alienIndex][dd].Scale    = gAlienDeformationBubbleTemplate[dd].Scale;
		gAlienDeformationBubble[alienIndex][dd].Speed    = gAlienDeformationBubbleTemplate[dd].Speed;
		gAlienDeformationBubble[alienIndex][dd].MinScale = gAlienDeformationBubbleTemplate[dd].MinScale;
		gAlienDeformationBubble[alienIndex][dd].MaxScale = gAlienDeformationBubbleTemplate[dd].MaxScale;


		VerticeArrayScaleDimension(
			relativeScale, gAliens[alienIndex].Vertices, gAlienSettingsGame.VerticeCount * 3, dd);
	}

}


void AlienDeformBubbleDimension(unsigned int alienIndex, unsigned int dimension) {
	gAlienDeformationBubble[alienIndex][dimension].Scale += gAlienDeformationBubble[alienIndex][dimension].Speed;

	float scale = gAlienDeformationBubble[alienIndex][dimension].Scale,
		speed = gAlienDeformationBubble[alienIndex][dimension].Speed;

	// Reverse direction of the deformation
	if (scale >= gAlienDeformationBubble[alienIndex][dimension].MaxScale ||
		scale <= gAlienDeformationBubble[alienIndex][dimension].MinScale) {
		gAlienDeformationBubble[alienIndex][dimension].Speed = speed * -1.0f;
	}

	gAlienDeformationBubble[alienIndex][dimension].RelativeScale = scale / (scale - speed);
	VerticeArrayScaleDimension(
		gAlienDeformationBubble[alienIndex][dimension].RelativeScale, gAliens[alienIndex].Vertices, gAlienSettingsGame.VerticeCount * 3, dimension);

}

void AlienDeformBubble(unsigned int alienIndex) {
	for (unsigned int dd = 0; dd < 3; dd++) AlienDeformBubbleDimension(alienIndex, dd);
}