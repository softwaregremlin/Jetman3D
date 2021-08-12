GLenum texture_format = GL_RGB;
GLuint myTextures[2];

// curl -T build/eboot.bin ftp://192.168.1.11:1337/ux0:/app/VITAGL005/

/*
float colors[] = {1.0, 0.0, 0.0, 0.3, 
				  0.0, 1.0, 0.0, 0.3, 
				  0.0, 0.0, 1.0, 0.3,
				  1.0, 1.0, 0.0, 0.3}; // Colors for a face
*/
float colors[] = { 1.0, 0.0, 0.0, 1,
                  0.0, 1.0, 0.0, 1,
                  0.0, 0.0, 1.0, 1,
                  1.0, 1.0, 0.0, 1 }; // Colors for a face				  

float vertices_front[] = {-0.5f, -0.5f, -0.5f, 0.5f, -0.5f, -0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f, -0.5f}; // Back Face
float vertices_back[] = {-0.5f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f}; // Front Face
float vertices_left[] = {-0.5f, -0.5f, -0.5f, -0.5f, 0.5f, -0.5f, -0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f}; // Left Face
float vertices_right[] = {0.5f, -0.5f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f, 0.5f, 0.5f}; // Right Face
float vertices_top[] = {-0.5f, -0.5f, -0.5f, 0.5f, -0.5f, -0.5f, -0.5f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f}; // Top Face
float vertices_bottom[] = {-0.5f, 0.5f, -0.5f, 0.5f, 0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f}; // Bottom Face

float textcoords[] = { 0.0,  0.0,   1.0, 0.0,    0.0, 1.0,  1.0, 1.0 };

uint16_t indices[] = {
	 0, 1, 2, 1, 2, 3, // Back
	 4, 5, 6, 5, 6, 7, // Front
	 8, 9,10, 9,10,11, // Left
	12,13,14,13,14,15, // Right
	16,17,18,17,18,19, // Top
	20,21,22,21,22,23  // Bottom
};

////////////////////////////
float vertex_array_bg[] = { -2.0f, -2.0f, -2.5f,
                            2.0f, -2.0f, -2.5f, 
                            -2.0f, 2.0f, -2.5f,
                             2.0f, 2.0f, -2.5f }; 
uint16_t indices_bg[] = { 0, 1, 2, 1, 2, 3 };
float color_array_bg[] = {  1.0, 0.0, 0.0, 1,
							0.0, 1.0, 0.0, 1,
							0.0, 0.0, 1.0, 1,
							1.0, 1.0, 0.0, 1 };
float texture_coord_array_bg[] = { 0.0,  0.0,  1.0, 0.0,  0.0, 1.0,  1.0, 1.0 };

// Display FPS!! /////////////////////////////////
float vertex_array_fps[] = {  2.5f, 1.5f, -2.5f,
                              3.0f, 1.5f, -2.5f,
                              2.5f, 2.0f, -2.5f,
                              3.0f, 2.0f, -2.5f,
                              3.0f, 1.5f, -2.5f,
                              3.5f, 1.5f, -2.5f,
                              3.0f, 2.0f, -2.5f,
                              3.5f, 2.0f, -2.5f,
                              3.5f, 1.5f, -2.5f,
                              4.0f, 1.5f, -2.5f,
                              3.5f, 2.0f, -2.5f,
                              4.0f, 2.0f, -2.5f };


uint16_t indices_fps[] = { 0, 1, 2, 1, 2, 3, 4, 5, 6, 5, 6, 7, 8, 9, 10, 9, 10, 11 };
float texture_coord_array_fps[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 
                                   0.5f, 0.25f, 1.0f, 0.25f, 0.5f, 0.5f, 1.0f, 0.5f };

float color_array_fps[] = { 1.0, 0.0, 0.0, 1,
							0.0, 1.0, 0.0, 1,
							0.0, 0.0, 1.0, 1,
							1.0, 1.0, 0.0, 1,
							
							1.0, 0.0, 0.0, 1,
							0.0, 1.0, 0.0, 1,
							0.0, 0.0, 1.0, 1,
							1.0, 1.0, 0.0, 1,
							
							1.0, 0.0, 0.0, 1,
							0.0, 1.0, 0.0, 1,
							0.0, 0.0, 1.0, 1,
							1.0, 1.0, 0.0, 1 };
							
/////////////////

int frameCounter = 0, fps = 0;
