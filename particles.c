#define MAX_PARTICLE_COUNT 15

typedef struct {
    char TexturePath[50];
    unsigned int TextureIndex;
} structParticleSettings;

typedef struct {
    float X, Y, Z, Size, Alpha, XMovement, YMovement, MaxYMovement, XOffset;
    unsigned int On;
    int Frame, StartFrame;
} structParticle;

typedef struct {
    float Start, Step;
} structParticleColour;

typedef struct {
    structParticleColour Red, Green, Blue;
} structParticleColours;

typedef struct {
    float YOffset, XOffset, XOffsetLeft, XOffsetRight, Speed, MaxXMovement, MaxYMovement, SpaceBetween, ZPos;
    float XPerspectiveCorrectionFactor, YPerspectiveCorrectionFactor;
    unsigned int On;
    unsigned int ParticleCount;
    int MaxFrames, ActiveParticleCount;

    float ColorArraySource[BILLBOARD_VERTICE_COUNT * 4];
    float TextureCoordinateArraySource[BILLBOARD_VERTICE_COUNT * 2];

    float VertexArray[BILLBOARD_VERTICE_COUNT * 3 * MAX_PARTICLE_COUNT];
    GLUINT_ IndiceArray[BILLBOARD_INDICE_COUNT * MAX_PARTICLE_COUNT];
    float TextureCoordinateArray[BILLBOARD_VERTICE_COUNT * 2 * MAX_PARTICLE_COUNT];
    float ColorArray[BILLBOARD_VERTICE_COUNT * 4 * MAX_PARTICLE_COUNT];

    structParticleColours Colours;
    structParticle Particle[MAX_PARTICLE_COUNT];
} structParticles;

structParticleSettings gParticleSettings = 
    { .TextureIndex = 4, .TexturePath = "/textures/particle.png" };

/////////////////////////////////////////////////////////////////////////


void ParticlesInitialise(structParticles* particles) {

    unsigned int i;
    for (i = 0; i < BILLBOARD_VERTICE_COUNT * 4 * particles->ParticleCount; i++) { particles->ColorArray[i] = particles->ColorArraySource[i % (BILLBOARD_VERTICE_COUNT * 4)]; }
    for (i = 0; i < BILLBOARD_VERTICE_COUNT * 2 * particles->ParticleCount; i++) { particles->TextureCoordinateArray[i] = particles->TextureCoordinateArraySource[i % (BILLBOARD_VERTICE_COUNT * 2)]; }

    // Indices Array
    for (i = 0; i < particles->ParticleCount; i++) {
        particles->IndiceArray[(i * 6) + 0] = (i * 4) + 0;
        particles->IndiceArray[(i * 6) + 1] = (i * 4) + 1;
        particles->IndiceArray[(i * 6) + 2] = (i * 4) + 2;
        particles->IndiceArray[(i * 6) + 3] = (i * 4) + 1;
        particles->IndiceArray[(i * 6) + 4] = (i * 4) + 2;
        particles->IndiceArray[(i * 6) + 5] = (i * 4) + 3;
    }
}

// Same texture is used by all Particles and Lasers
void ParticlesSetTexture() {
    glBindTexture(GL_TEXTURE_2D, gGame.Textures[gParticleSettings.TextureIndex]);
}

void ParticleStartOrStop(structParticle* particle, unsigned int isStart) {
    particle->Alpha = isStart ? 1.0f : 0.0f;
    particle->On = isStart;
    particle->YMovement = 0;
}

void ParticlesStartOrStop(structParticles* particles, unsigned int isStart) {
    for (unsigned int pp = 0; pp < particles->ParticleCount; pp++) {
        ParticleStartOrStop(&particles->Particle[pp], isStart);
    }
    particles->On = isStart;
}

void ParticlesStart(structParticles* particles) { ParticlesStartOrStop(particles, TRUE); }
void ParticlesStop (structParticles* particles) { ParticlesStartOrStop(particles, FALSE); }

void ParticlesSetVerticesAndColours(structParticles* particles) {

    // Shift the vertices and set colours in the array for all particles
    for (unsigned int pp1 = 0; pp1 < particles->ParticleCount; pp1++) {

        for (unsigned int pp2 = 0; pp2 < 4; pp2++) {
            particles->VertexArray[(pp1 * 12) + 0 + (pp2 * 3)] = particles->Particle[pp1].X;
            particles->VertexArray[(pp1 * 12) + 1 + (pp2 * 3)] = particles->Particle[pp1].Y;
            particles->VertexArray[(pp1 * 12) + 2 + (pp2 * 3)] = particles->Particle[pp1].Z;

            // Alpha 1 or 0 to switch on or off
            particles->ColorArray[(pp1 * 16) + 3 + (pp2 * 4)] = particles->Particle[pp1].Alpha;
            // Vary the colours
            particles->ColorArray[(pp1 * 16) + 0 + (pp2 * 4)] =
                particles->Colours.Red.Start + (particles->Colours.Red.Step * (particles->ParticleCount - pp1));
            particles->ColorArray[(pp1 * 16) + 1 + (pp2 * 4)] =
                particles->Colours.Green.Start + (particles->Colours.Green.Step * (particles->ParticleCount - pp1));
            particles->ColorArray[(pp1 * 16) + 2 + (pp2 * 4)] =
                particles->Colours.Blue.Start + (particles->Colours.Blue.Step * (particles->ParticleCount - pp1));
        }

        particles->VertexArray[(pp1 * 12) + 3] += particles->Particle[pp1].Size;
        particles->VertexArray[(pp1 * 12) + 7] += particles->Particle[pp1].Size;
        particles->VertexArray[(pp1 * 12) + 9] += particles->Particle[pp1].Size;
        particles->VertexArray[(pp1 * 12) + 10] += particles->Particle[pp1].Size;
    }
}
