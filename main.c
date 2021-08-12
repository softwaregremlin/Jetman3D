#include "platformSpecific/includeFiles.c"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <stdlib.h>
#include <stdio.h>

#include "rand.c"

#include "platformSpecific/globals.c"

#include "globals.c"

#include "modelLoader.c"
#include "verticeArrayHelper.c"
#include "colourArrayHelper.c"
#include "collisionsHelper.c"

#include "loadTexture.c"
#include "billboard.c"
#include "background.c"
#include "platforms.c"

#include "platformSpecific/createFolder.c"
#include "platformSpecific/input.c"
#include "platformSpecific/time.c"

#include "saveData.c"

#include "explosions.c"
#include "particles.c"
#include "jetman.c"

#include "aliens.c"

#include "rocketGas.c"
#include "rockets.c"

#include "trinkets.c"

#include "text.c"
#include "intro.c"
#include "gameOver.c"

#include "displayFrame.c"
#include "initialise.c"
#include "stateChange.c"

#include "platformSpecific/main.c"

int main(int argc, char** argv) {	
	return mainPlatFormSpecific(argc, argv);
}