void StateChangeCheck() {

	// Extra Life Score has been reasched
	if (gGame.Score >= gGame.ExtraLifeTargets[gGame.ExtraLifeTargetIndex]) {
		gGame.Lives++;
		gGame.ExtraLifeTargetIndex++;
	}

	// Restart - Game Over
	/////////////////////////////////////////////////////////////
	if (gGame.State == GameStateOver) {
		gGame.GameOverFrame++;

		// Game Over -> Intro
		if (gGame.GameOverFrame >= gGame.GameOverFrameCount) {
			gGame.GameOverFrame = 0;

			gGame.State = GameStateIntro;
			gIntro.IsStart = TRUE;
			gTextSettings.IntroTextLineIndex = 0;
			BackgroundInitialise();

			gGame.Lives = gGame.LivesInitial;
			gGame.Score = 0;
			gGame.Level = 1;
			gGame.ExtraLifeTargetIndex = 0;
			

			RocketLoadAndInitialise();
			AliensLoadAndInitialise();
			TrinketInitialise();
			gRocketGas.State = RocketGasStateOff;
			gRockets[RocketIndex()].FuelLevel = 0;
			return;
		}
	}

	// Restart - Level
	/////////////////////////////////////////////////////////////
	if (gGame.State == GameStateLevelReStart || 
		gGame.State == GameStateLevelStart) {

		AliensLoadAndInitialise();

		// Load a new rocket every 4 levels
		if(gGame.Levels[gGame.Level - 1].RocketInPieces && 
		   gGame.State == GameStateLevelStart) RocketLoadAndInitialise();

		gJetman.ResetPosition = TRUE;
		gJetman.InRocket = FALSE;

		gGame.LookAtY = 0;
		gGame.State = GameStateLevel;
	}
}