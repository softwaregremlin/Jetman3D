void TrinketPulsateColours(unsigned int trinketIndex) {

    ColorArrayPulsateSectionSequence(
        gTrinket.ColourIndexes,
        gTrinketSettingsGame.Settings[trinketIndex].OriginalColorArray,
        0, 0,
        gTrinketSettingsGame.Settings[trinketIndex].VerticeCount - 1,
        &gTrinket.ColorPulsateFrame,
        &gTrinket.ColorPulsateDirection,
        gTrinketSettingsGame.Settings[trinketIndex].ColorPulsateFrameCount,
        &gTrinket.ColorSequenceNumber,
        gTrinketSettingsGame.Settings[trinketIndex].PulsateSequences,
        gTrinketSettingsGame.Settings[trinketIndex].PulsateSequenceLength);
}