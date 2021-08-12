
void drawTriangles(float vertexArray[], float colourArray[], float textureArray[], 
                   GLUINT_ indiceArray[], unsigned int indicesCount) {
    glVertexPointer(3, GL_FLOAT, 0, vertexArray);
    glColorPointer(4, GL_FLOAT, 0, colourArray);
    glTexCoordPointer(2, GL_FLOAT, 0, textureArray);
    glDrawElements(GL_TRIANGLES, indicesCount, GL_DRAW_ELEMENTS_TYPE, indiceArray);
}

void drawGround() {
    drawTriangles(gModelGround.Vertices, gModelGround.ColourIndexes, gModelGround.TextureIndexes,
                  gModelGround.Indices, gModelGround.IndiceCount);
}

void drawPlatforms() {
    drawTriangles(gModelPlatforms.Vertices, gModelPlatforms.ColourIndexes, gModelPlatforms.TextureIndexes, 
                  gModelPlatforms.Indices, gModelPlatforms.IndiceCount);
}

void WorldAndAliensDraw() {
    

    glPushMatrix();
        glLoadIdentity();

        // Scroll the world up / down
        glTranslatef(0.0f, gGame.LookAtY, gGame.WorldZOffset);

        // Background ??


        //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

        glBindTexture(GL_TEXTURE_2D, gGame.Textures[gParticleSettings.TextureIndex]);

        drawTriangles(gBackground.Vertices, gBackground.ColourIndexes,
                      gBackground.TextureIndexes, gBackground.Indices, gBackground.IndiceCount);

        //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);


        glBindTexture(GL_TEXTURE_2D, gGame.Textures[gModelPlatforms.TextureIndex]);

        drawGround();
        drawPlatforms();

        RocketDrawBeforeJetman();
        AliensDraw();

    glPopMatrix();

    
}



void drawExplosionsAndLasers() {

    // Explosions and Lasers - these are in the "World" co-ordinates
    glPushMatrix();
        glLoadIdentity();

        // Scroll the world up / down
        glTranslatef(0.0f, gGame.LookAtY, -6.0f);

        AlienParticlesMoveAndDraw();
        
        RocketParticlesMoveAndDraw();


        LasersMoveAndDraw();

        // Explosions 
        gExplosions.ActiveCount = 0;
        JetManExplosionAndSmokePuffMoveAndDraw();

        // Alien Explosions
        AlienExplosionsDraw();

        ExplosionsDraw();

    glPopMatrix();
}




void displayFrame() {
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (gGame.State == GameStateIntro) {
        IntroDisplayFrame();
        return;
    }

    if (gGame.State == GameStateOver) {
        GameOverDisplayFrame();
        return;
    }


    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    TrinketMoveAndDraw();

    // World objects
    WorldAndAliensDraw();

    /////////
    JetmanDraw();


    RocketGasDrawIfCarrying();
    RocketDrawAfterJetman();

    // TrinketMoveAndDraw();

    /////////////////////////////////////
    /// 2D objects - "Billboard Sprites"
    ParticlesSetTexture();

    // Particle Trail coming from the JetPac
    // (Relative to JetMan's position)
    JetPacParticlesMoveAndDraw();

    // Explosions and Lasers are relative to the World position
    drawExplosionsAndLasers();

    // Text stays fixed
    TextDraw();

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);

    //////////////////////////////
    /*
    if (InputRTriggerPressed() && !gInput.RightTriggerHeld) {
        gGame.Level = gGame.Level == 0 ? 0 : ((gGame.Level == ALIEN_SPECIES_COUNT) ? 1 : gGame.Level + 1);
        AliensLoadAndInitialise();
        gInput.RightTriggerHeld = TRUE;
    }

    // Flag to enforce repeated fire button presses
    if (!(InputRTriggerPressed())) gInput.RightTriggerHeld = FALSE;
    */
    //////////////////////////////
}