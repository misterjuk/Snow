#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/euler_angles.hpp>

#include <common/config.h>
#include <common/camera.h>
#include <common/renderer.h>

Renderer::Renderer()
{
	// We get the camera from the scene later
	_camera = nullptr;

	// Create window with OpenGL context
	this->init();
}

Renderer::~Renderer()
{
	// Cleanup VBO and shader
	glDeleteProgram(_programID);
	// Close OpenGL window and terminate GLFW
	glfwTerminate();
}

int Renderer::init()
{
	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		return -1;
	}

	// Set OpenGL version (2.1)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_SAMPLES, 4);

	// Open a window and create its OpenGL context
	_window = glfwCreateWindow( WIDTH, HEIGHT, "Demo", NULL, NULL);
	if( _window == NULL ){
		fprintf( stderr, "Failed to open GLFW window.\n" );
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(_window);

	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(_window, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

	// Create and compile our GLSL program from the shaders
	_programID = this->loadShaders("shaders/sprite.vert", "shaders/sprite.frag");

	// Use our shader
	glUseProgram(_programID);

	return 0;
}

float Renderer::updateDeltaTime() {
	// lastTime is initialised only the first time this function is called
	static double lastTime = glfwGetTime();
	// get the current time
	double currentTime = glfwGetTime();

	// Compute time difference between current and last time
	float deltaTime = float(currentTime - lastTime);

	// For the next frame, the "last time" will be "now"
	lastTime = currentTime;
	return deltaTime;
}

void Renderer::renderScene(Scene* scene)
{
	// get camera from scene and update
	_camera = scene->camera();

	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Render all the gameobjects(sprites)
	for (GameObject* go : scene->gameobjects())
	{
		this->renderGameObject(go);
	
	}
	// Swap buffers
	glfwSwapBuffers(this->window());
	glfwPollEvents();
}

void Renderer::renderGameObject(GameObject* gameObject)
{
	// get view + projectionmatrix from camera
	glm::mat4 viewMatrix = _camera->getViewMatrix();
	glm::mat4 projectionMatrix = _camera->getProjectionMatrix();

	//calculating sprite position in the world with relation to an gameobject
	//gives abillity to set sprite offset 
	glm::vec3 pos = gameObject->sprite->position + gameObject->position;
	float rotation = gameObject->sprite->rotation + gameObject->rotation;
	glm::vec3 scale = gameObject->sprite->scale * gameObject->scale;
	// Build the Model matrix from Sprite transform
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(pos.x, pos.y, 0.0f));
	glm::mat4 rotationMatrix    = glm::eulerAngleYXZ(0.0f, 0.0f, rotation);
	glm::mat4 scalingMatrix     = glm::scale(glm::mat4(1.0f), glm::vec3(scale.x, scale.y, 1.0f));

	glm::mat4 modelMatrix = translationMatrix * rotationMatrix * scalingMatrix;

	// Build MVP matrix
	glm::mat4 MVP = projectionMatrix * viewMatrix * modelMatrix;



	// Send our transformation to the currently bound shader, in the "MVP" uniform
	GLuint matrixID = glGetUniformLocation(_programID, "MVP");
	glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);

	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gameObject->sprite->texture());
	// Set our "textureSampler" sampler to use Texture Unit 0
	GLuint textureID  = glGetUniformLocation(_programID, "textureSampler");
	glUniform1i(textureID, 0);

	// 1st attribute buffer : vertices
	GLuint vertexPositionID = glGetAttribLocation(_programID, "vertexPosition");
	glEnableVertexAttribArray(vertexPositionID);
	glBindBuffer(GL_ARRAY_BUFFER, gameObject->sprite->vertexbuffer());
	glVertexAttribPointer(
		vertexPositionID, // The attribute we want to configure
		3,          // size : x,y,z => 3
		GL_FLOAT,   // type
		GL_FALSE,   // normalized?
		0,          // stride
		(void*)0    // array buffer offset
	);

	// 2nd attribute buffer : UVs
	GLuint vertexUVID = glGetAttribLocation(_programID, "vertexUV");
	glEnableVertexAttribArray(vertexUVID);
	glBindBuffer(GL_ARRAY_BUFFER, gameObject->sprite->uvbuffer());
	glVertexAttribPointer(
		vertexUVID, // The attribute we want to configure
		2,          // size : U,V => 2
		GL_FLOAT,   // type
		GL_FALSE,   // normalized?
		0,          // stride
		(void*)0    // array buffer offset
	);

	// Draw the triangles
	glDrawArrays(GL_TRIANGLES, 0, 2*3); // 2*3 indices starting at 0 -> 2 triangles

	// cleanup
	glDisableVertexAttribArray(vertexPositionID);
	glDisableVertexAttribArray(vertexUVID);
}

GLuint Renderer::loadShaders(const std::string& vertex_file_path, const std::string& fragment_file_path)
{
	// Create the shaders
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string vertexShaderCode;
	std::ifstream vertexShaderStream(vertex_file_path.c_str(), std::ios::in);
	if (vertexShaderStream.is_open()){
		std::string line = "";
		while (getline(vertexShaderStream, line)) {
			vertexShaderCode += "\n" + line;
		}
		vertexShaderStream.close();
	} else {
		printf("Can't to open %s.\n", vertex_file_path.c_str());
		return 0;
	}

	// Read the Fragment Shader code from the file
	std::string fragmentShaderCode;
	std::ifstream fragmentShaderStream(fragment_file_path.c_str(), std::ios::in);
	if (fragmentShaderStream.is_open()){
		std::string line = "";
		while (getline(fragmentShaderStream, line)) {
			fragmentShaderCode += "\n" + line;
		}
		fragmentShaderStream.close();
	} else {
		printf("Can't to open %s.\n", fragment_file_path.c_str());
		return 0;
	}

	GLint result = GL_FALSE;
	int infoLogLength;

	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path.c_str());
	char const * vertexSourcePointer = vertexShaderCode.c_str();
	glShaderSource(vertexShaderID, 1, &vertexSourcePointer , NULL);
	glCompileShader(vertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if ( infoLogLength > 0 ){
		std::vector<char> vertexShaderErrorMessage(infoLogLength+1);
		glGetShaderInfoLog(vertexShaderID, infoLogLength, NULL, &vertexShaderErrorMessage[0]);
		printf("%s\n", &vertexShaderErrorMessage[0]);
	}

	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path.c_str());
	char const * fragmentSourcePointer = fragmentShaderCode.c_str();
	glShaderSource(fragmentShaderID, 1, &fragmentSourcePointer , NULL);
	glCompileShader(fragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if ( infoLogLength > 0 ){
		std::vector<char> fragmentShaderErrorMessage(infoLogLength+1);
		glGetShaderInfoLog(fragmentShaderID, infoLogLength, NULL, &fragmentShaderErrorMessage[0]);
		printf("%s\n", &fragmentShaderErrorMessage[0]);
	}

	// Link the program
	printf("Linking program\n");
	GLuint programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);

	// Check the program
	glGetProgramiv(programID, GL_LINK_STATUS, &result);
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if ( infoLogLength > 0 ){
		std::vector<char> programErrorMessage(infoLogLength+1);
		glGetProgramInfoLog(programID, infoLogLength, NULL, &programErrorMessage[0]);
		printf("%s\n", &programErrorMessage[0]);
	}

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	return programID;
}
// void Renderer::_renderSpriteBatch(glm::mat4 modelMatrix, std::vector<Sprite*>& spritebatch, Camera* camera)
// {
// 	Sprite* spr = spritebatch[0];
// 	Shader* shader = _resman.getShader(spr->vertexshader().c_str(), spr->fragmentshader().c_str());
// 	// ask resourcemanager
// 	if (shader == nullptr) {
// 		shader = _defaultShader; // fallback to defaultshader
// 	}
// 	std::string texturename = spr->texturename();
// 	int filter = spr->filter();
// 	int wrap = spr->wrap();
// 	Texture* texture = _resman.getTexture(texturename, filter, wrap);

// 	if (spr->size.x == 0) { spr->size.x = texture->width() * spr->uvdim.x; }
// 	if (spr->size.y == 0) { spr->size.y = texture->height() * spr->uvdim.y; }

// 	Mesh* mesh = _resman.getSpriteMesh(spr->size.x, spr->size.y, spr->pivot.x, spr->pivot.y, spr->uvdim.x, spr->uvdim.y, spr->circlemesh(), spr->which());

// 	if (texture != nullptr) {
// 		// Bind the texture in Texture Unit 0
// 		glActiveTexture(GL_TEXTURE0);
// 		glBindTexture(GL_TEXTURE_2D, texture->getGLTexture());
// 		//glUniform1i(shader->textureID(), 0);

// 		// for every Sprite in the batch...
// 		int s = spritebatch.size();
// 		for (int i = 0; i < s; i++) {
// 			Sprite* sprite = spritebatch[i]; // a Sprite handle
// 			int culled = 0; // state that we need to draw it
// 			if (sprite->useCulling()) { // but maybe we don't
// 				int half_width = SWIDTH/2;
// 				int half_height = SHEIGHT/2;

// 				int left_edge = camera->position.x - half_width;
// 				int right_edge = camera->position.x + half_width;
// 				int top_edge = camera->position.y - half_height;
// 				int bottom_edge = camera->position.y + half_height;

// 				float posx = sprite->spriteposition.x;
// 				float posy = sprite->spriteposition.y;

// 				int debug = 0;
// 				if (debug) { // cull visibly within the frame
// 					if (posx - spr->size.x < left_edge) { culled = 1; }
// 					if (posx + spr->size.x > right_edge) { culled = 1; }
// 					if (posy + spr->size.y > bottom_edge) { culled = 1; }
// 					if (posy - spr->size.y < top_edge) { culled = 1; }
// 				} else {
// 					if (posx + spr->size.x < left_edge) { culled = 1; }
// 					if (posx - spr->size.x > right_edge) { culled = 1; }
// 					if (posy - spr->size.y > bottom_edge) { culled = 1; }
// 					if (posy + spr->size.y < top_edge) { culled = 1; }
// 				}
// 			}
// 			// this Sprite isn't culled and needs to be drawn
// 			if (!culled) {
// 				RGBAColor blendcolor = MAGENTA;
// 				if (texture->warranty()) {
// 					blendcolor = sprite->color;
// 				}

// 				// _uvOffsetID
// 				glUniform2f(shader->uvOffsetID(), sprite->uvoffset.x, sprite->uvoffset.y);

// 				// _customParamsID
// 				for (int i=0; i<8; i++) {
// 					if (shader->customParamsID(i) != -1) {
// 						glUniform3f(shader->customParamsID(i), sprite->customParams[i].x, sprite->customParams[i].y, sprite->customParams[i].z);
// 					}
// 				}

// 				// use sprite transform to build the model matrix.
// 				glm::vec3 position = glm::vec3(sprite->spriteposition.x, sprite->spriteposition.y, sprite->spriteposition.z);
// 				glm::vec3 rotation = glm::vec3(sprite->spriterotation.x, sprite->spriterotation.y, sprite->spriterotation.z);
// 				glm::vec3 scale = glm::vec3(sprite->spritescale.x, sprite->spritescale.y, sprite->spritescale.z);

// 				// Build the model matrix for this sprite.
// 				glm::mat4 translationMatrix	= glm::translate(modelMatrix, position);
// 				glm::mat4 rotationMatrix	= glm::eulerAngleYXZ(rotation.y, rotation.x, rotation.z);
// 				glm::mat4 scalingMatrix		= glm::scale(glm::mat4(1.0f), scale);

// 				glm::mat4 mm = translationMatrix * rotationMatrix * scalingMatrix;

// 				this->_renderMesh(mm, shader, mesh, mesh->numverts(), GL_TRIANGLES, blendcolor);
// 			}
// 		}
// 	}

// }