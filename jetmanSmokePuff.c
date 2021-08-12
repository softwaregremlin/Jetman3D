
void JetManExplosionOrSmokePuffStart(structExplosion *explosion, float yPos) {

    explosion->On = TRUE;

    // Since we are bringing the Z position forward, introduce a correction to the X position
    float xOffsetRight = gJetman.SmokePuffSettings.XOffsetRight - (gJetman.XPos * gExplosionSettings.XPerspectiveFactor),
        xOffsetLeft = gJetman.SmokePuffSettings.XOffsetLeft - (gJetman.XPos * gExplosionSettings.XPerspectiveFactor);

    explosion->X = gJetman.XPos +
        (gJetman.FacingRight ? xOffsetRight : xOffsetLeft);
    explosion->Y = yPos;

    ExplosionInitialise(explosion);
 }

void JetPacSmokePuffStart(unsigned int isMovingUp) {

    // If falling, make the smoke appear lower down
    float yPos = gJetman.YPos +
        (isMovingUp ? gJetman.SmokePuffSettings.YOffset : gJetman.SmokePuffSettings.YOffsetFalling);

    JetManExplosionOrSmokePuffStart(&gJetman.JetPackSmokePuff, yPos);

}

void JetManExplosionStart() {
   
    if (gJetman.Explosion.On) return;
    JetManExplosionOrSmokePuffStart(&gJetman.Explosion, gJetman.YPos);
    // Start a timer
    gJetman.AfterExplosionPause = gJetman.AfterExplosionPauseTime;
}


void JetManExplosionOrSmokePuffMoveAndDraw(structExplosion* explosion) {

    unsigned int isEndOfSmokePuff = FALSE;
    ExplosionAnimate(explosion, &isEndOfSmokePuff);
    // gJetman.Explosion.On = isEndOfSmokePuff;

    //ExplosionAnimate(&gJetman.JetPackSmokePuff, &isEndOfSmokePuff);
    
    ExplosionDraw(explosion,0);
    // ExplosionDraw(&gJetman.JetPackSmokePuff,0);
}


void JetManExplosionAndSmokePuffMoveAndDraw() {
    if (!gJetman.Explosion.On && !gJetman.JetPackSmokePuff.On) return;
    glBindTexture(GL_TEXTURE_2D, gGame.Textures[gExplosionSettings.TextureIndex]);
    JetManExplosionOrSmokePuffMoveAndDraw(&gJetman.JetPackSmokePuff);
    JetManExplosionOrSmokePuffMoveAndDraw(&gJetman.Explosion);
}