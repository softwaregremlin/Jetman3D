void SoundPlay(vitaWav *wav) {
	vitaWavPlay(wav);
}

void SoundPlayLoop(vitaWav *wav) {
	vitaWavLoop(wav, 1);
	vitaWavPlay(wav);
}

void SoundPlayStop(vitaWav *wav) {
	vitaWavStop(wav);
}