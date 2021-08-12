void LoadSavedData() {
    // Load High Score and Level Data
    FILE* dataFile;
    if ((dataFile = fopen(DATA_HISCORE, "r"))) {
        fscanf(dataFile, "%d", &gGame.HiScore);
        fclose(dataFile);
    }

    if ((dataFile = fopen(DATA_LEVEL, "r"))) {
        fscanf(dataFile, "%d", &gGame.Level);
        fclose(dataFile);
        //if (g_Level > 0) g_Level--;
    }
}

void InitialiseGeneral(void)
{
    
    CreateDataFolderIfNotExists();
    LoadSavedData();


    glGenTextures(TEXTURE_COUNT, gGame.Textures);


    // Seed our random numbers
    srand(time(NULL));

    TextInitialise();
    JetPacParticlesInitialise();
    JetmanModelInitialise();

    PlatformsInitialise();
    ExplosionsInitialise();
    LasersInitialise();
    BackgroundInitialise();

    AliensLoadAndInitialise();
    AlienParticlesInitialise();

    RocketLoadAndInitialise();
    RocketGasLoadAndInitialise();
    RocketParticlesInitialise();
    RocketParticlesStart();

    TrinketsLoadAndInitialise();
    IntroInitialise();

    /*  select clearing (background) color       */
    glClearColor(0.0, 0.0, 0.0, 0.0);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_TEXTURE_2D);

    //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexEnvf(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    //glTexEnvf(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_REPLACE);
}


void InitialiseView(int w, int h) {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)w / (float)h, 0.01f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //////////////////////////////////
    glTranslatef(0.0f, 0.0f, gGame.WorldZOffset); // Centering the cube
    /////////////////////
}