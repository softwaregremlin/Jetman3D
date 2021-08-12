int timeLastFrame = 0, msSinceLastFrame = 0, msCounter = 0;
uint64_t currentTickX =0, lastTick =0; 
SceRtcTick currentTick;

#define TICKS_PER_FRAME 1000000 / 58


////////////////////////////////////
void delay(unsigned int mseconds) {

	if(lastTick ==0) {
		sceRtcGetCurrentTick(&currentTick);
		lastTick = currentTick.tick;
	}
	
	int tickChange = 0;
	while(tickChange < TICKS_PER_FRAME) {
		sceRtcGetCurrentTick(&currentTick);
		tickChange = currentTick.tick - lastTick;
	}	
	
	lastTick = currentTick.tick;
	
	msSinceLastFrame = (int)(tickChange / 1000);
    msCounter += msSinceLastFrame;
	
    frameCounter++;
	
    if (msCounter >= 1000) {
	
		// Calculate FPS
        fps = frameCounter;
        if (fps >= 100) fps = 99;
        msCounter = 0;
        frameCounter = 0;

        // Periodically check for a High Score Save
        gGame.HiScoreSaveTimer += 1;
        if (gGame.HiScoreSaveTimer == gGame.HiScoreSaveInterval) {
            gGame.HiScoreSaveTimer = 0;
              SaveHighScore();
        }		
    }	
}
