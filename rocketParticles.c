structParticles gRocketParticles = {

    .ParticleCount = 15,
    .TextureCoordinateArraySource = BILLBOARD_TEXTURE_ARRAY,

    .XOffset = -0.15f, .YOffset = -2.0f, 
    .XPerspectiveCorrectionFactor = -0.03f, .YPerspectiveCorrectionFactor = -0.09f,
    .Speed = 0.035f, .MaxYMovement = 0.4f, .SpaceBetween = 0.0f,

    .Colours = {.Red =   {.Start = 1.0f, .Step = 0.0f },
                .Green = {.Start = 0.0f, .Step = 0.05f},
                .Blue =  {.Start = 0.0f, .Step = 0.0f } },

    .Particle = {{.Z = -0.457f, .Size = 0.33f,                  .MaxYMovement = 0.8f },
                 {.Z = -0.456f, .Size = 0.30f, .XOffset = 0.05, .MaxYMovement = 0.6f },
                 {.Z = -0.455f, .Size = 0.30f, .XOffset = -0.05, .MaxYMovement = 0.6f },
                 {.Z = -0.454f, .Size = 0.30f, .XOffset =  0.12, .MaxYMovement = 0.6f },
                 {.Z = -0.453f, .Size = 0.30f, .XOffset = -0.12, .MaxYMovement = 0.6f },
                 {.Z = -0.452f, .Size = 0.2f,  .XOffset =  0.15, .MaxYMovement = 0.5f },
                 {.Z = -0.451f, .Size = 0.18f, .XOffset = -0.15, .MaxYMovement = 0.5f },

                 {.Z = -0.45f, .Size = 0.25f, .XOffset =  0.18,  .MaxYMovement = 0.4f },
                 {.Z = -0.449f, .Size = 0.22f, .XOffset = -0.18,  .MaxYMovement = 0.4f },
                 {.Z = -0.448f, .Size = 0.2f,  .XOffset =  0.25,  .MaxYMovement = 0.3f },
                 {.Z = -0.447f, .Size = 0.18f, .XOffset = -0.25,  .MaxYMovement = 0.3f },

                 {.Z = -0.446f, .Size = 0.25f, .XOffset =  0.3,  .MaxYMovement = 0.2f },
                 {.Z = -0.445f, .Size = 0.22f, .XOffset = -0.3,  .MaxYMovement = 0.2f },
                 {.Z = -0.444f, .Size = 0.2f,  .XOffset =  0.4,  .MaxYMovement = 0.1f },
                 {.Z = -0.443f, .Size = 0.18f, .XOffset = -0.4,  .MaxYMovement = 0.1f }
                }
    
};

///////////////////////

void RocketParticlesInitialise() {

    // Texture is already loaded
    //TextureLoad(TEXTURE_PARTICLE, gParticleSettings.TextureIndex);
    ParticlesInitialise(&gRocketParticles);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void RocketParticlesStart() { ParticlesStartOrStop(&gRocketParticles, TRUE); }
void RocketParticlesStop()  { ParticlesStartOrStop(&gRocketParticles, FALSE); }

//////////////////////////////////////////
void RocketParticlesMove() {

    float particleX = gRocketSettingsGame.AssembledXPos + gRocketParticles.XOffset +
        (gRockets[RocketIndex()].YPos * gRocketParticles.XPerspectiveCorrectionFactor),
        particleY = gRockets[RocketIndex()].YPos + gRocketParticles.YOffset +
        (gRockets[RocketIndex()].YPos * gRocketParticles.YPerspectiveCorrectionFactor);

    // Shoot the particles downward in a stream
    for (unsigned int pp = 0; pp < gRocketParticles.ParticleCount; pp++) {

        float randomSpeedAdjust;
        randMinMaxFloat(-0.025f, 0.025f, &randomSpeedAdjust);

        gRocketParticles.Particle[pp].Y = particleY - (gRocketParticles.SpaceBetween * pp);
        gRocketParticles.Particle[pp].X = particleX + gRocketParticles.Particle[pp].XOffset;

        if (gRocketParticles.Particle[pp].On) {
            gRocketParticles.Particle[pp].YMovement += gRocketParticles.Speed + randomSpeedAdjust;
            gRocketParticles.Particle[pp].Y -= gRocketParticles.Particle[pp].YMovement;
            // loop back to the origin
            if (gRocketParticles.Particle[pp].YMovement >= gRocketParticles.Particle[pp].MaxYMovement) gRocketParticles.Particle[pp].YMovement = 0;
        }
    }
}


void RocketParticlesMoveAndDraw() {

    // Only have particles when we're taking off or landing
    if(!(gRockets[RocketIndex()].State == RocketStateTakeOff ||
         gRockets[RocketIndex()].State == RocketStateLanding)) return;

    RocketParticlesMove();
    ParticlesSetVerticesAndColours(&gRocketParticles);

    drawTriangles(gRocketParticles.VertexArray, gRocketParticles.ColorArray,
        gRocketParticles.TextureCoordinateArray, gRocketParticles.IndiceArray, gRocketParticles.ParticleCount * BILLBOARD_INDICE_COUNT);

}