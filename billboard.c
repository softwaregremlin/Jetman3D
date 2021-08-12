#define BILLBOARD_VERTICE_COUNT 4
#define BILLBOARD_INDICE_COUNT 6
#define BILLBOARD_INDICE_ARRAY {0, 1, 2, 1, 2, 3}
#define BILLBOARD_COLOUR_ARRAY {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f }
#define BILLBOARD_TEXTURE_ARRAY { 0, 0, 1.0f, 0, 0, 1.0f, 1.0f, 1.0f }

typedef struct {
    float ColourArray[BILLBOARD_VERTICE_COUNT * 4];
    GLUINT_ IndiceArray[BILLBOARD_INDICE_COUNT];
} structBillboardSettings;

structBillboardSettings gBillboardSettings = {
    .ColourArray = BILLBOARD_COLOUR_ARRAY,
    .IndiceArray = BILLBOARD_INDICE_ARRAY
};

/////////////////////////////////////////////////////////////////////

void BillboardSetVerticePositionsByBottomLeft(float vertexArray[], unsigned int arrayOffset, float x, float y, float z, float width, float height ) {

    // All indices
    for (unsigned int vv = 0; vv < 4; vv++) {
        vertexArray[0 + (vv * 3) + arrayOffset] = x;
        vertexArray[1 + (vv * 3) + arrayOffset] = y;
        vertexArray[2 + (vv * 3) + arrayOffset] = z;
    }

    // Indice 1 (bottom right)
    vertexArray[3 + arrayOffset] += width;
    // Indice 2 (top left)
    vertexArray[7 + arrayOffset] += height;
    // Indice 3 (top right_
    vertexArray[9 + arrayOffset] += width;
    vertexArray[10 + arrayOffset] += height;
}

void BillboardSetVerticePositionsByCenter(float vertexArray[], unsigned int arrayOffset, float x, float y, float z, float width, float height) {
    BillboardSetVerticePositionsByBottomLeft(vertexArray, arrayOffset, x - (width / 2), y - (height / 2), z, width, height);
}

void BillboardSetTextureCoordinates(
    float textureCoordinateArray[], unsigned int arrayOffset,
    float x, float y, float width, float height) {

    // All indices
    for (unsigned int tt = 0; tt < BILLBOARD_VERTICE_COUNT; tt++) {
        textureCoordinateArray[0 + (tt * 2) + arrayOffset] = x;
        textureCoordinateArray[1 + (tt * 2) + arrayOffset] = y;
    }

    // Indice 1 (bottom right)
    textureCoordinateArray[2 + arrayOffset] += width;
    // Indice 2 (top left)
    textureCoordinateArray[5 + arrayOffset] += height;
    // Indice 3 (top right_
    textureCoordinateArray[6 + arrayOffset] += width;
    textureCoordinateArray[7 + arrayOffset] += height;
}