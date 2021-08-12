void drawDigit(int digit, int powerOf10) {

    float numberSize = 8.0f / 32.0f,
        numberLeft = (float)(digit % 4) * numberSize,
        numberBottom = (float)(3 - (digit / 4)) * numberSize;

    int arrayOffset = powerOf10 == 0 ? 8 : 0;

    texture_coord_array_fps[0 + arrayOffset] = numberLeft;
    texture_coord_array_fps[1 + arrayOffset] = numberBottom;
    texture_coord_array_fps[2 + arrayOffset] = numberLeft + numberSize;
    texture_coord_array_fps[3 + arrayOffset] = numberBottom;
    texture_coord_array_fps[4 + arrayOffset] = numberLeft;
    texture_coord_array_fps[5 + arrayOffset] = numberBottom + numberSize;
    texture_coord_array_fps[6 + arrayOffset] = numberLeft + numberSize;
    texture_coord_array_fps[7 + arrayOffset] = numberBottom + numberSize;
}

void drawNumber(int number) {


    drawDigit(number / 10, 1);
    drawDigit(number % 10, 0);

    glBindTexture(GL_TEXTURE_2D, myTextures[1]);
    glVertexPointer(3, GL_FLOAT, 0, vertex_array_fps);
    glColorPointer(4, GL_FLOAT, 0, color_array_fps);
    glTexCoordPointer(2, GL_FLOAT, 0, texture_coord_array_fps);
    glDrawElements(GL_TRIANGLES, 3 * 6, GL_DRAW_ELEMENTS_TYPE, indices_fps);

}