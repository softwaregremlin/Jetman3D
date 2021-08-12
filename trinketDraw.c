void TrinketDrawCollisionRectangle() {

    if (gTrinket.State == TrinketStatePaused) return;
    unsigned int trinketIndex = gTrinket.TrinketType - 1;

    //float zOffset = 0.2f;
    float zOffset = 0.0f;
    float collisionRectangeVertices[12] = {
        gTrinket.CollisionXPos - (gTrinketSettingsGame.Settings[trinketIndex].CollisionRectangleWidth / 2.0f) ,
        gTrinket.CollisionYPos + (gTrinketSettingsGame.Settings[trinketIndex].CollisionRectangleHeight / 2.0f),zOffset,

        gTrinket.CollisionXPos - (gTrinketSettingsGame.Settings[trinketIndex].CollisionRectangleWidth / 2.0f),
        gTrinket.CollisionYPos - (gTrinketSettingsGame.Settings[trinketIndex].CollisionRectangleHeight / 2.0f),zOffset,

        gTrinket.CollisionXPos + (gTrinketSettingsGame.Settings[trinketIndex].CollisionRectangleWidth / 2.0f),
        gTrinket.CollisionYPos - (gTrinketSettingsGame.Settings[trinketIndex].CollisionRectangleHeight / 2.0f),zOffset,

        gTrinket.CollisionXPos + (gTrinketSettingsGame.Settings[trinketIndex].CollisionRectangleWidth / 2.0f),
        gTrinket.CollisionYPos + (gTrinketSettingsGame.Settings[trinketIndex].CollisionRectangleHeight / 2.0f),zOffset,

    };


    //float collisionRectangeColours[16] = { 1.0f, 1.0f,1.0f,0.5f,1.0f,1.0f,1.0f,0.5f,1.0f,1.0f,1.0f,0.5f, 1.0f, 1.0f,1.0f,0.50f };
    float collisionRectangeColours[16] = { 1.0f, 1.0f,0.0f,0.75f,1.0f,1.0f,0.0f,0.75f,1.0f,1.0f,0.0f,0.75f, 1.0f, 1.0f,0.0f,0.750f };
    float collisionRectangeTextures[24] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
    GLUINT_ collisionRectangeIndices[6] = { 0, 1, 2, 0, 2 , 3 };

    drawTriangles(collisionRectangeVertices, collisionRectangeColours,
        collisionRectangeTextures, collisionRectangeIndices, 6);
}



void TrinketDraw() {

    if (gTrinket.State == TrinketStatePaused) return;

    unsigned int trinketIndex = gTrinket.TrinketType - 1;

    TrinketPulsateColours(trinketIndex);

    // ColorArrayApplyAlpha(gTrinket.ColourIndexes, gTrinketSettingsGame.Settings[trinketIndex].VerticeCount * 4, 0.2);

    drawTriangles(
        gTrinket.Vertices,
        gTrinket.ColourIndexes,
        gTrinketSettingsGame.Settings[trinketIndex].TextureIndexes,
        gTrinketSettingsGame.Settings[trinketIndex].Indices,
        gTrinketSettingsGame.Settings[trinketIndex].IndiceCount);
}

void TrinketMoveAndDraw() {
    glBindTexture(GL_TEXTURE_2D, gGame.Textures[gTrinketSettingsGame.TextureIndex]);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    glPushMatrix();
        glLoadIdentity();

        // Scroll the world up / down
        glTranslatef(0.0f, gGame.LookAtY, gGame.WorldZOffset);

        glPushMatrix();

            TrinketMove();
            TrinketRotate();
            TrinketDraw();  

        glPopMatrix();

        // TrinketDrawCollisionRectangle();

    glPopMatrix();

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

}