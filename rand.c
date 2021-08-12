
void randMinMax(unsigned int min, unsigned int max, unsigned int* randNum) {
	int range = max - min;
	*randNum = rand() % range + min;
}

void randMinMaxFloat(float min, float max, float* randNum) {
	int range = (int)(max * 100) - (int)(min * 100);
	*randNum = (float)(rand() % range + (min * 100))/ 100.0f;
}