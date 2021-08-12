
void AlienSpinX(unsigned int index) {
	glRotatef(gAliens[index].XRotationAngle, 1.0f, 0, 0);
	gAliens[index].XRotationAngle += gAlienSettingsSpecies[AlienSpeciesIndex()].XRotationSpeed;
	if (gAliens[index].XRotationAngle > 360.0f) gAliens[index].XRotationAngle = 0;
}

void AlienSpinY(unsigned int index) {

	if (gAliens[index].YRotationDelayCounter > 0) {
		gAliens[index].YRotationDelayCounter--;
		return;
	}

	glRotatef(gAliens[index].YRotationAngle, 0, 1.0f, 0);
	gAliens[index].YRotationAngle += gAlienSettingsSpecies[AlienSpeciesIndex()].YRotationSpeed;
	if (gAliens[index].YRotationAngle <= 360.0f) return;
	gAliens[index].YRotationAngle = 0;
	gAliens[index].YRotationDelayCounter = gAlienSettingsSpecies[AlienSpeciesIndex()].YRotationInterval;
}