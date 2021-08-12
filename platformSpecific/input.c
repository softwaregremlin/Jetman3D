/*

typedef struct {
	unsigned int FacingRight, Jumping, Falling, Walking, Standing, Firing;
	float LeftRightSpeed, WalkingSpeed, JumpingSpeed, FallingSpeed;
	float XPos, YPos, YScrollThreshold, TopLimit, BottomLimit, LeftLimit, RightLimit, WrapXShift, Scale;
	float YAbovePosition, Height, Width, CollisionRecWidth;
	GLfloat ModelViewMatrix[16];
} structJetman;


typedef struct{
	unsigned int Left, Right, Up, Fire;

} structInput;
structInput gInput;

structInput gInput;
structJetman gJetman = {
	.XPos = 5.0f,
	//.FacingRight = TRUE, .LeftRightSpeed = 0.5f, .JumpingSpeed = 0.5f, .FallingSpeed = 0.25f,
	.FacingRight = TRUE, .LeftRightSpeed = 0.0625f, .JumpingSpeed = 0.0625f, .FallingSpeed = 0.03125f,
	.Scale = 0.125f,
	//.TopLimit = 2.0f, .BottomLimit = -1.05f, .LeftLimit = -4.0f, .RightLimit = 4.0f, .WrapXShift = 8.5,
	.TopLimit = 3.0f, .BottomLimit = -1.05f, .LeftLimit = -4.0f, .RightLimit = 4.0f, .WrapXShift = 8.5,
	.YScrollThreshold = 1.5,
	.YAbovePosition = 0.42f, .Height = 1.25f,.Width = 0.6f, .CollisionRecWidth = 0.55f
	//.YAbovePosition = 0.85f, .Height = 1.77f,.Width = 0.625f, .CollisionRecWidth = 0.475f
}; // 68.0 };


unsigned int JetManCollidesWithPlatformSides(int platFormIndex) {

	float jetManX = gJetman.XPos - (gJetman.Width / 2);

	return  (jetManX + gJetman.CollisionRecWidth >= gPlatforms[platFormIndex].X &&
		    (jetManX + gJetman.Width - gJetman.CollisionRecWidth) <= gPlatforms[platFormIndex].X + gPlatforms[platFormIndex].Width);
}

unsigned int JetManCollidesWithPlatform() {
	float jetManY = gJetman.YPos + gJetman.YAbovePosition;

	for (int pp = 0; pp < 2; pp++) {
		if (JetManCollidesWithPlatformSides(pp) &&

			// top on or above the platform
			(jetManY >= gPlatforms[pp].Y - (gPlatforms[pp].Height / 2) &&
				// bottom on or below the platform
				jetManY - gJetman.Height <= gPlatforms[pp].Y - (gPlatforms[pp].Height / 2))) {

			// printf("%.2f, %.2f, %.2f\n", jetManY, jetManY - gJetman.Height, gPlatforms[1].Y);
			return TRUE;
		}
	}
	return FALSE;
}


unsigned int JetManCollidesWithPlatformBottom() {
	float jetManY = gJetman.YPos + gJetman.YAbovePosition;
	for (int pp = 0; pp < 2; pp++) {
		if (JetManCollidesWithPlatformSides(pp) &&
			(jetManY >= gPlatforms[pp].Y - gPlatforms[pp].Height &&
				jetManY <= gPlatforms[pp].Y)) {

			//printf("%.2f, %.2f\n", jetManY, gPlatforms[1].Y - gPlatforms[1].Height);
			// printf("%.2f, %.2f\n", jetManY, gPlatforms[1].Y);
			return TRUE;
		}
	}
	return FALSE;
}


unsigned int JetManCollidesWithPlatformTop() {
	float jetManY = gJetman.YPos + gJetman.YAbovePosition;

	for (int pp = 0; pp < 2; pp++) {

		if (JetManCollidesWithPlatformSides(pp) &&
			(jetManY - gJetman.Height <= gPlatforms[pp].Y) && 
			(jetManY - gJetman.Height >= gPlatforms[pp].Y - gPlatforms[pp].Height))
			return TRUE;
	}
	return FALSE;
}

*/

// Input
SceCtrlData g_VitaPad;
#define MIN_ANALOG_STICK_THRESHOLD 50
#define MAX_ANALOG_STICK_THRESHOLD 205


void InitialiseInput() {
	memset(&g_VitaPad, 0, sizeof(g_VitaPad));
	sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG);
}

unsigned int InputStartPressed() {
	sceCtrlPeekBufferPositive(0, &g_VitaPad, 1);
	return g_VitaPad.buttons & SCE_CTRL_START;
}

unsigned int InputCrossPressed() {
	sceCtrlPeekBufferPositive(0, &g_VitaPad, 1);
	return g_VitaPad.buttons & SCE_CTRL_CROSS;
}

unsigned int InputTrianglePressed() {
	sceCtrlPeekBufferPositive(0, &g_VitaPad, 1);
	return g_VitaPad.buttons & SCE_CTRL_TRIANGLE;
}

unsigned int InputCirclePressed() {
	sceCtrlPeekBufferPositive(0, &g_VitaPad, 1);
	return g_VitaPad.buttons & SCE_CTRL_CIRCLE;
}

unsigned int InputLTriggerPressed() {
	sceCtrlPeekBufferPositive(0, &g_VitaPad, 1);
	return g_VitaPad.buttons & SCE_CTRL_LTRIGGER;
}

unsigned int InputRTriggerPressed() {
	sceCtrlPeekBufferPositive(0, &g_VitaPad, 1);
	return g_VitaPad.buttons & SCE_CTRL_RTRIGGER;
}

unsigned int InputLeft() {
	sceCtrlPeekBufferPositive(0, &g_VitaPad, 1);
	return (g_VitaPad.lx < MIN_ANALOG_STICK_THRESHOLD) || (g_VitaPad.buttons & SCE_CTRL_LEFT);
}

unsigned int InputRight() {
	sceCtrlPeekBufferPositive(0, &g_VitaPad, 1);
	return (g_VitaPad.lx > MAX_ANALOG_STICK_THRESHOLD) || (g_VitaPad.buttons & SCE_CTRL_RIGHT);
}

unsigned int InputUp() {
	sceCtrlPeekBufferPositive(0, &g_VitaPad, 1);
	return (g_VitaPad.ly < MIN_ANALOG_STICK_THRESHOLD) || (g_VitaPad.buttons & SCE_CTRL_UP);
}

unsigned int InputDown() {
	sceCtrlPeekBufferPositive(0, &g_VitaPad, 1);
	return (g_VitaPad.ly > MAX_ANALOG_STICK_THRESHOLD) || (g_VitaPad.buttons & SCE_CTRL_DOWN);
}

/*
void keyboard(unsigned char key, int x, int y)
{
	
	
    //if (key == 'x') {
    //    glutFullScreen();
    //}

	if (key == 'z') gInput.Left = TRUE;
	if (key == 'x') gInput.Right = TRUE;
	if (key == 'w') gInput.Up = TRUE;


}

void keyboardUp(unsigned char key, int x, int y)
{


	//if (key == 'x') {
	//    glutFullScreen();
	//}

	if (key == 'z') gInput.Left = FALSE;
	if (key == 'x') gInput.Right = FALSE;
	if (key == 'w') gInput.Up = FALSE;

}
*/