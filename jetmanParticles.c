

structParticles gJetPacParticles = {

    .ParticleCount = 5,
    .TextureCoordinateArraySource = BILLBOARD_TEXTURE_ARRAY,


    .YOffset = 0.63f, .XOffsetLeft = 0.2f, .XOffsetRight = -0.32f,
    .Speed = 0.05f, .MaxYMovement = 0.3f, .SpaceBetween = 0.08f,

    .Colours = {.Red   = {.Start = 0.3f, .Step = 0.1f },
                .Green = {.Start = 0.5f, .Step = 0.05f},
                .Blue  = {.Start = 1.0f, .Step = 0.0f } },

    .Particle = {{ .Z = -5.95f, .Size = 0.18f,   },
                 { .Z = -5.94f, .Size = 0.15f, .XOffset =  0.05 },
                 { .Z = -5.93f, .Size = 0.12f, .XOffset = -0.05 },
                 { .Z = -5.92f, .Size = 0.1f,  .XOffset =  0.02 },
                 { .Z = -5.91f, .Size = 0.08f, .XOffset = -0.02 }
} };

///////////////////////////////////////////////////////////////////////////////////////////////////



void JetPacParticlesInitialise() {

    TextureLoad(gParticleSettings.TexturePath, gParticleSettings.TextureIndex);
    ParticlesInitialise(&gJetPacParticles);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void JetPacParticlesStart() { ParticlesStartOrStop(&gJetPacParticles, TRUE);  }
void JetPacParticlesStop()  { ParticlesStartOrStop(&gJetPacParticles, FALSE); }

//////////////////////////////////////////


void JetPacParticlesMove() {
    
    // Move the origin to be at the bottom of the Jetpac
    float jetmanScreenY = 
        gJetman.YPos >= gJetman.YScrollThreshold ? gJetman.YScrollThreshold : gJetman.YPos,
        jetManXOffset = gJetman.FacingRight ? gJetPacParticles.XOffsetRight : gJetPacParticles.XOffsetLeft;

    // Shoot the particles downward in a stream
    for (unsigned int pp = 0; pp < gJetPacParticles.ParticleCount; pp++) {
         
        gJetPacParticles.Particle[pp].Y = jetmanScreenY - gJetPacParticles.YOffset - (gJetPacParticles.SpaceBetween * pp);
        gJetPacParticles.Particle[pp].X = gJetman.XPos + jetManXOffset + gJetPacParticles.Particle[pp].XOffset;

        if (gJetPacParticles.Particle[pp].On) {
            gJetPacParticles.Particle[pp].YMovement += gJetPacParticles.Speed;
            gJetPacParticles.Particle[pp].Y -= gJetPacParticles.Particle[pp].YMovement;
            // loop back to the origin
            if (gJetPacParticles.Particle[pp].YMovement >= gJetPacParticles.MaxYMovement) gJetPacParticles.Particle[pp].YMovement = 0;
        }
    }
}

void JetPacParticlesDraw() {

    if (gJetman.InRocket) return;

    if (gJetman.Exploding) {
        // Apply Alpha
        for (unsigned int cc = 0; cc < 4 * gJetPacParticles.ParticleCount; cc++) {
            gJetPacParticles.ColorArray[(cc * 4) + 3] = gJetman.Alpha;
        }
    }

    glBindTexture(GL_TEXTURE_2D, gGame.Textures[gParticleSettings.TextureIndex]);

    drawTriangles(gJetPacParticles.VertexArray, gJetPacParticles.ColorArray,
        gJetPacParticles.TextureCoordinateArray, gJetPacParticles.IndiceArray, gJetPacParticles.ParticleCount * BILLBOARD_INDICE_COUNT);

}

void RocketParticlesMoveAndDraw();

void JetPacParticlesMoveAndDraw() {
    glPushMatrix();
        glLoadIdentity();
        JetPacParticlesMove();
        ParticlesSetVerticesAndColours(&gJetPacParticles);
        JetPacParticlesDraw();
    glPopMatrix();
}

