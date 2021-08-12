
void JetmanDrawCollisionRectangle() {
    
    if (!gJetman.CollisionRectangleDraw) return;

    float zOffset = 0.0f,
        yPos = gJetman.YPos + gJetman.CollisionRecHeightOffset,
        xPos = gJetman.XPos,
        w = gJetman.CollisionRecWidth,
        h = gJetman.CollisionRecHeight,
        collisionRectangeVertices[12] = {
            xPos - (w / 2.0f), yPos + (h / 2.0f), zOffset,
            xPos - (w / 2.0f), yPos - (h / 2.0f), zOffset,
            xPos + (w / 2.0f), yPos - (h / 2.0f), zOffset,
            xPos + (w / 2.0f), yPos + (h / 2.0f), zOffset,
    };

    float collisionRectangeColours[16] = { 1.0f, 1.0f,1.0f,0.5f,1.0f,1.0f,1.0f,0.5f,1.0f,1.0f,1.0f,0.5f, 1.0f, 1.0f,1.0f,0.50f };
    float collisionRectangeTextures[24] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
    GLUINT_ collisionRectangeIndices[6] = { 0, 1, 2, 0, 2 , 3 };


    drawTriangles(collisionRectangeVertices, collisionRectangeColours,
        collisionRectangeTextures, collisionRectangeIndices, 6);
}


void JetManSetInitialPosition() {
    glLoadIdentity();
    glTranslatef(0.0f, gJetman.BottomLimit, gGame.WorldZOffset);

    gJetman.FacingRight = TRUE;
    gJetman.Exploding = FALSE;
    gJetman.Alpha = 1.0f;

    gJetman.ResetPosition = FALSE;

    // Get the initial X,Y coordinates
    glGetFloatv(GL_MODELVIEW_MATRIX, gJetman.ModelViewMatrix);
    gJetman.XPos = gJetman.ModelViewMatrix[gModelViewMatrixIndexes.X];
    gJetman.YPos = gJetman.ModelViewMatrix[gModelViewMatrixIndexes.Y];
    gJetman.ZPos = gJetman.ModelViewMatrix[gModelViewMatrixIndexes.Z];

    SoundPlay(gLevelStartSound);
}


void JetManFadeIfExploding() {
    
    if (!gJetman.Exploding) return;

    gJetman.Alpha -= gJetman.Alpha <= 0 ? 0 : gJetman.FadeSpeed;
    gJetman.AfterExplosionPause--;

    // Pause after exploding
    if (gJetman.AfterExplosionPause <= 0) {
                
        if (gGame.Lives >= 0) {
            gGame.State = GameStateLevelReStart;
            return;
        }

        // GAME OVER!
        gGame.State = GameStateOver;        
    }   
}

void JetmanDraw() {
    
    
    if (gJetman.InRocket) return;

    glBindTexture(GL_TEXTURE_2D, gGame.Textures[gJetman.TextureIndex]);

    //JetmanDrawCollisionRectangle();

    if (gJetman.ResetPosition) JetManSetInitialPosition();

    glGetFloatv(GL_MODELVIEW_MATRIX, gJetman.ModelViewMatrix);
    gJetman.XPos = gJetman.ModelViewMatrix[gModelViewMatrixIndexes.X];

    // Check input - move
    JetManMove();

    // Exploding? - Fade out
    JetManFadeIfExploding();

    // Apply Alpha
    ColorArrayApplyAlpha(gModelJetman.ColourIndexes, JETMAN_TORSO_FACE_COUNT * 16, gJetman.Alpha);

    // Don't render if we're invisible
    if (gJetman.Alpha <= 0) return;

    // Draw the body from the waist up (stationary)
    drawTriangles(gModelJetman.VerticesTorso, gModelJetman.ColourIndexes, gModelJetman.TextureIndexes,
        gModelJetman.Indices, 6 * JETMAN_TORSO_FACE_COUNT);

    // Draw the legs (moving / animated)    
    JetManPrepareLegs();
    ColorArrayApplyAlpha(gModelJetman.ColourIndexesLegs, JETMAN_LEG_FACE_COUNT * 16 * 2, gJetman.Alpha);

    drawTriangles(gModelJetman.VerticesLegs, 
        //gModelJetman.ColourIndexes, 
        gModelJetman.ColourIndexesLegs,
        gModelJetman.TextureIndexesLegs,
        gModelJetman.Indices, 6 * 2 * JETMAN_LEG_FACE_COUNT);

}