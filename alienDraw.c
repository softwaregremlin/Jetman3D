
void AlienDrawCollisionRectangle(unsigned int index) {
    //float zOffset = 0.2f;
    float zOffset = 0.0f;
    float collisionRectangeVertices[12] = {
        gAliens[index].CollisionXPos - (gAlienSettingsSpecies[AlienSpeciesIndex()].CollisionRectangleWidth / 2.0f) ,
        gAliens[index].CollisionYPos + (gAlienSettingsSpecies[AlienSpeciesIndex()].CollisionRectangleHeight / 2.0f),zOffset,

        gAliens[index].CollisionXPos - (gAlienSettingsSpecies[AlienSpeciesIndex()].CollisionRectangleWidth / 2.0f),
        gAliens[index].CollisionYPos - (gAlienSettingsSpecies[AlienSpeciesIndex()].CollisionRectangleHeight / 2.0f),zOffset,

        gAliens[index].CollisionXPos + (gAlienSettingsSpecies[AlienSpeciesIndex()].CollisionRectangleWidth / 2.0f),
        gAliens[index].CollisionYPos - (gAlienSettingsSpecies[AlienSpeciesIndex()].CollisionRectangleHeight / 2.0f),zOffset,

        gAliens[index].CollisionXPos + (gAlienSettingsSpecies[AlienSpeciesIndex()].CollisionRectangleWidth / 2.0f),
        gAliens[index].CollisionYPos + (gAlienSettingsSpecies[AlienSpeciesIndex()].CollisionRectangleHeight / 2.0f),zOffset,

    };


    float collisionRectangeColours[16] = { 1.0f, 1.0f,1.0f,0.5f,1.0f,1.0f,1.0f,0.5f,1.0f,1.0f,1.0f,0.5f, 1.0f, 1.0f,1.0f,0.50f };
    float collisionRectangeTextures[24] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
    GLUINT_ collisionRectangeIndices[6] = { 0, 1, 2, 0, 2 , 3 };

    drawTriangles(collisionRectangeVertices, collisionRectangeColours,
        collisionRectangeTextures, collisionRectangeIndices, 6);
}


void AlienDraw(unsigned int index) {
    glPushMatrix();

    AlienCollisionProcess(index);
    AlienMove(index);

    if (gAliens[index].State != AlienStateOff) {

        
        drawTriangles(gAliens[index].Vertices,
            gAliens[index].ColourIndexes,
            gAliens[index].TextureIndexes,
            gAliens[index].Indices,
            gAlienSettingsGame.IndiceCount);
        
    }

    glPopMatrix();

    // Debugging - collision rectangle!
    if (gAlienSettingsGame.ShowCollisionRectangles) {
        AlienDrawCollisionRectangle(index);
    }
}

void AliensDraw() {


    glBindTexture(GL_TEXTURE_2D, gGame.Textures[gAlienSettingsGame.TextureIndex]);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    for (unsigned int aa = 0; aa < ALIEN_MAX_COUNT; aa++) {
        AlienDraw(aa);
    }


    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    //return;

    // Animation!
    if (gAlienSettingsSpecies[AlienSpeciesIndex()].HasEyes) {
        for (unsigned int aa = 0; aa < ALIEN_MAX_COUNT; aa++) {
            gAliens[aa].EyeFrameCounter++;
            if (gAliens[aa].EyeFrameCounter == gAlienSettingsGame.EyeFramesPerFrame) {
                gAliens[aa].EyeFrameCounter = 0;

                gAliens[aa].EyeFrame++;
                if (gAlienSettingsGame.EyeAnimationSequence[gAliens[aa].EyeFrame] == -1) gAliens[aa].EyeFrame = 0;
                AlienSetEyeTextureFrame(gAlienSettingsGame.EyeAnimationSequence[gAliens[aa].EyeFrame]);
            }
        }
    }
}