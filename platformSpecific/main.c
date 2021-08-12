


int mainPlatFormSpecific(int argc, char** argv){
	

	
	// Initializing graphics device
	vglInit(0x800000);
	vglWaitVblankStart(GL_TRUE);
	
	///////////////
	vitaWavInit();
	gFireSound           = vitaWavLoadVorbis("app0:data/sounds/Laser.ogg");
	gExplosionSound      = vitaWavLoadVorbis("app0:data/sounds/Explosion.ogg");
	gLevelStartSound     = vitaWavLoadVorbis("app0:data/sounds/LevelStart.ogg");
	gRocketPickupSound   = vitaWavLoadVorbis("app0:data/sounds/RocketPickup.ogg");
	gRocketAssembleSound = vitaWavLoadVorbis("app0:data/sounds/RocketAssemble.ogg");
	gTrinketPickupSound  = vitaWavLoadVorbis("app0:data/sounds/TrinketPickup.ogg");
	gRocketSound         = vitaWavLoadVorbis("app0:data/sounds/Rocket.ogg");
	gRocketDescSound     = vitaWavLoadVorbis("app0:data/sounds/RocketDesc.ogg");
	gIntroSound		     = vitaWavLoadVorbis("app0:data/sounds/Intro.ogg");
	//////////////////	
	
	InitialiseGeneral();
	InitialiseView(960.0f, 544.0f);
	InitialiseInput();
	
	for (;;){
		vglStartRendering();
		displayFrame();	
		StateChangeCheck();		
		vglStopRendering();
		delay(0);		
	}
	
	vglEnd();
	return 0;
}