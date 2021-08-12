void JetmanDrawCollisionRectangle() {

    glPushMatrix();
    glLoadIdentity();    

    // Scroll the world up / down
    glTranslatef(0.0f, LookAtY, 0.0f);

    float zOffset = gJetman.ZPos,
        jetManY = gJetman.YPos + gJetman.CollisionRecHeightOffset,
        recWidth = gJetman.CollisionRecWidth * gJetman.CollisionWidthAlienScaleFactor;

    //printf("%.2f", LookAtY);

    float collisionRectangeVertices[12] = {
        gJetman.XPos - (recWidth / 2.0f),
        jetManY + (gJetman.CollisionRecHeight / 2.0f), zOffset,

        gJetman.XPos - (recWidth / 2.0f),
        jetManY - (gJetman.CollisionRecHeight / 2.0f), zOffset,

        gJetman.XPos + (recWidth / 2.0f),
        jetManY - (gJetman.CollisionRecHeight / 2.0f), zOffset,

        gJetman.XPos + (recWidth / 2.0f),
        jetManY + (gJetman.CollisionRecHeight / 2.0f), zOffset        
    };


    float collisionRectangeColours[16] = { 1.0f, 1.0f,0.0f,1.0f,1.0f,1.0f,0.0f,1.0f,1.0f,1.0f,0.0f,1.0f, 1.0f, 1.0f,0.0f,1.f };
    float collisionRectangeTextures[24] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
    GLUINT_ collisionRectangeIndices[6] = { 0, 1, 2, 0, 2 , 3 };

    drawTriangles(collisionRectangeVertices, collisionRectangeColours,
        collisionRectangeTextures, collisionRectangeIndices, 6);

    glPopMatrix();
}

