typedef struct {
    float ZPos, ZIncrementLevel1, ZIncrementLevel2;
} structAlienParticleSettings;

structParticles gAlienParticlesTemplate = {

    .ParticleCount = 5,
    .TextureCoordinateArraySource = BILLBOARD_TEXTURE_ARRAY,

    .MaxFrames = 8,

    .YOffset = -0.1f, .XOffsetLeft = 0.5f, .XOffsetRight = -0.5f, .Speed = 0.001f,

    .Particle = {{ .Size = 0.27f,  .StartFrame = -8 },
                 { .Size = 0.225f, .StartFrame = -6 },
                 { .Size = 0.18f,  .StartFrame = -4 },
                 { .Size = 0.15f,  .StartFrame = -2 },
                 { .Size = 0.12f,  .StartFrame = -0 }
    } 
};

structAlienParticleSettings gAlienParticleSettings = { .ZPos = 0.2f, .ZIncrementLevel1 = 0.001f, .ZIncrementLevel2 = 0.0001f };

structParticleColours
gParticleGreen = {
    .Red = {.Start = 0.5f, .Step = 0.05f },
    .Green = {.Start = 1.0f, .Step = 0.05f},
    .Blue = {.Start = 0.5f, .Step = 0.0f }
},
gParticleRed = {
    .Red = {.Start = 1.0f, .Step = 0.1f },
    .Green = {.Start = 0.5f, .Step = 0.05f},
    .Blue = {.Start = 0.5f, .Step = 0.0f }
},
gParticleMagenta = {
    .Red = {.Start = 1.0f, .Step = 0.1f },
    .Green = {.Start = 0.5f, .Step = 0.05f},
    .Blue = {.Start = 1.0f, .Step = 0.0f }
},
gParticleCyan = {
    .Red = {.Start = 0.5f, .Step = 0.1f },
    .Green = {.Start = 1.0f, .Step = 0.05f},
    .Blue = {.Start = 1.0f, .Step = 0.0f }
};

structParticles gAlienParticles[ALIEN_MAX_COUNT];

void AlienParticleCopyColour(structParticleColours* source, structParticleColours* destination) {
    destination->Red.Start   = source->Red.Start;
    destination->Red.Step    = source->Red.Step;
    destination->Green.Start = source->Green.Start;
    destination->Green.Step  = source->Green.Step;
    destination->Blue.Start  = source->Blue.Start;
    destination->Blue.Step   = source->Blue.Step;
}

void AlienParticlesSetColour(structParticles* particles, unsigned int colour) {
    if (colour == AlienColourGreen)   AlienParticleCopyColour(&gParticleGreen,   &particles->Colours);
    if (colour == AlienColourRed)     AlienParticleCopyColour(&gParticleRed,     &particles->Colours);
    if (colour == AlienColourMagenta) AlienParticleCopyColour(&gParticleMagenta, &particles->Colours);
    if (colour == AlienColourCyan)    AlienParticleCopyColour(&gParticleCyan,    &particles->Colours);
}

void AlienParticlesCopyFromTemplate(structParticles* particles, unsigned int index) {
    unsigned int i;
    for (i = 0; i < (BILLBOARD_VERTICE_COUNT * 2); i++) {
        particles->TextureCoordinateArraySource[i] = gAlienParticlesTemplate.TextureCoordinateArraySource[i];
    }

    particles->ParticleCount = gAlienParticlesTemplate.ParticleCount;
    particles->MaxFrames = gAlienParticlesTemplate.MaxFrames;

    particles->YOffset = gAlienParticlesTemplate.YOffset;
    particles->XOffsetLeft = gAlienParticlesTemplate.XOffsetLeft;
    particles->XOffsetRight = gAlienParticlesTemplate.XOffsetRight;
    particles->Speed = gAlienParticlesTemplate.Speed;

    
    particles->Colours.Red.Start = gAlienParticlesTemplate.Colours.Red.Start;
    particles->Colours.Red.Step = gAlienParticlesTemplate.Colours.Red.Step;
    particles->Colours.Green.Start = gAlienParticlesTemplate.Colours.Green.Start;
    particles->Colours.Green.Step = gAlienParticlesTemplate.Colours.Green.Step;
    particles->Colours.Blue.Start = gAlienParticlesTemplate.Colours.Blue.Start;
    particles->Colours.Blue.Step = gAlienParticlesTemplate.Colours.Blue.Step;

    AlienParticlesSetColour(particles, gAliens[index].Colour);

    for (i = 0; i < particles->ParticleCount; i++) {
        particles->Particle[i].Size = gAlienParticlesTemplate.Particle[i].Size;
        particles->Particle[i].StartFrame = gAlienParticlesTemplate.Particle[i].StartFrame;
    }

}

void AlienParticlesInitialiseInstance(unsigned int aa) {
        AlienParticlesCopyFromTemplate(&gAlienParticles[aa], aa);
        ParticlesInitialise(&gAlienParticles[aa]);

        unsigned int isStart = TRUE;

        for (unsigned int pp = 0; pp < gAlienParticles[aa].ParticleCount; pp++) {
            gAlienParticles[aa].Particle[pp].Alpha = 0;
            gAlienParticles[aa].Particle[pp].Frame = gAlienParticles[aa].Particle[pp].StartFrame;
        }
}

void AlienParticlesInitialise() {
    for (unsigned int aa = 0; aa < ALIEN_MAX_COUNT; aa++) AlienParticlesInitialiseInstance(aa);
}


void AlienParticlesMove(unsigned int index) {

    float xOffset = gAliens[index].FacingRight ? gAlienParticles[index].XOffsetRight : gAlienParticles[index].XOffsetLeft;

    if (gAliens[index].FacingRight) gAlienParticles[index].Speed = gAlienParticles[index].Speed * -1.0f;

    for (unsigned int pp = 0; pp < gAlienParticles[index].ParticleCount; pp++) {

        if (gAlienParticles[index].Particle[pp].Frame == 0) {

            gAlienParticles[index].Particle[pp].Y = gAliens[index].CollisionYPos + gAlienParticles[index].YOffset;
            gAlienParticles[index].Particle[pp].X = gAliens[index].CollisionXPos + xOffset;            

            ParticleStartOrStop(&gAlienParticles[index].Particle[pp], TRUE);

        }
        else {
            if (gAlienParticles[index].Particle[pp].Frame > 0) {
                gAlienParticles[index].Particle[pp].X += gAlienParticles[index].Speed;                
            }
        }
        gAlienParticles[index].Particle[pp].Frame++;
        if (gAlienParticles[index].Particle[pp].Frame >= gAlienParticles[index].MaxFrames) {
            gAlienParticles[index].Particle[pp].Frame = gAlienParticles[index].Particle[pp].StartFrame;
        }
    }

}

void AlienParticlesDraw(unsigned int index) {

    if (gAliens[index].State == AlienStateOff) return;
    
    // Apply Alpha
    if (gAliens[index].State==AlienStateExploding) {
        
        for (unsigned int cc = 0; cc < 4 * gAlienParticles[index].ParticleCount; cc++) {
            gAlienParticles[index].ColorArray[(cc * 4) + 3] = gAliens[index].Alpha;
        }
    }

    // Stack the Z axis in order
    for (unsigned int zz = 0; zz < 3 * gAlienParticles[index].ParticleCount; zz++) {
        gAlienParticles[index].VertexArray[(zz * 3) + 2] = 
            gAlienParticleSettings.ZPos + (gAlienParticleSettings.ZIncrementLevel1 * index) + (gAlienParticleSettings.ZIncrementLevel2 * zz);
    }

    drawTriangles(gAlienParticles[index].VertexArray, gAlienParticles[index].ColorArray,
        gAlienParticles[index].TextureCoordinateArray, gAlienParticles[index].IndiceArray, gAlienParticles[index].ParticleCount * BILLBOARD_INDICE_COUNT);
}

void AlienParticlesMoveAndDraw() {

    if (!gAlienSettingsSpecies[AlienSpeciesIndex()].ParticlesEnabled) return;
    // if (gJetman.InRocket) return;

    for (unsigned int aa = 0; aa < ALIEN_MAX_COUNT; aa++) {
        AlienParticlesMove(aa);
        ParticlesSetVerticesAndColours(&gAlienParticles[aa]);
        AlienParticlesDraw(aa);
    }

}