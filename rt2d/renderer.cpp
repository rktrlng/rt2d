/**
 * This file is part of RT2D, a 2D OpenGL framework.
 * 
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *   - Initial commit
 * - Copyright [year] [your name] <you@yourhost.com>
 *   - [description]
 */

#include <rt2d/renderer.h>
#include <rt2d/camera.h>
#include <rt2d/shader.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

using namespace glm;

Renderer::Renderer()
{
	_window = NULL;
	
	_uberShader = NULL;
	
	this->init();
}


Renderer::~Renderer()
{
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

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

	// Open a window and create its OpenGL context
	_window = glfwCreateWindow( SWIDTH, SHEIGHT, WINDOWNAME, NULL, NULL);
	if( _window == NULL ){
		fprintf( stderr, "Failed to open GLFW window.\n" );
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(_window);
	
	// vsync (0=off, 1=on)
	glfwSwapInterval(1);

	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	// Ensure we can capture keys being pressed
	glfwSetInputMode(_window, GLFW_STICKY_KEYS, GL_TRUE);
	
	// MS Windows only
	//glfwSetCursorPos(_window, SWIDTH/2, SHEIGHT/2);

	// Black background
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Orthographic camera. We don't need these.
	// Enable depth test
	//glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	//glDepthFunc(GL_LESS); 

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);
	
	if (UBERSHADER) { // from config.h
		_uberShader =_resman.getShader(VERTEXSHADER, FRAGMENTSHADER);
		printf("Renderer using uberShader\n");
	}

	printf("Renderer::init() done\n");
	
	return 0;
}

void Renderer::renderScene(Scene* scene)
{
	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// get viewMatrix from Camera (Camera position and direction)
	_viewMatrix = scene->camera()->viewMatrix();
	// Our Projection Matrix (orthographic camera)
	_projectionMatrix = scene->camera()->projectionMatrix();

	// 'root' scene node has identity Matrix
	glm::mat4 modelMatrix = glm::mat4(1.0f);

	// start rendering everything, starting from the scene 'rootnode'
	this->_renderEntity(modelMatrix, scene);

	// Swap buffers
	glfwSwapBuffers(_window);
}

void Renderer::_renderEntity(glm::mat4& modelMatrix, Entity* entity)
{
	// OpenGL doesn't understand our Vector2. Make it glm::vec3 compatible.
	glm::vec3 position = glm::vec3(entity->position.x, entity->position.y, 0.0f);
	glm::vec3 rotation = glm::vec3(0.0f, 0.0f, entity->rotation);
	glm::vec3 scale = glm::vec3(entity->scale.x, entity->scale.y, 1.0f);
	
	// Build the Model matrix
	glm::mat4 translationMatrix	= glm::translate(glm::mat4(1.0f), position);
	glm::mat4 rotationMatrix	= glm::eulerAngleYXZ(0.0f, 0.0f, rotation.z);
	glm::mat4 scalingMatrix		= glm::scale(glm::mat4(1.0f), scale);

	// multiply ModelMatrix of children with the ModelMatrix of the parent (the caller of this method)
	// the first time we do this (for the root-parent), modelMatrix is identity.
	modelMatrix *= translationMatrix * rotationMatrix * scalingMatrix;

	// Check for Sprites to see if we need to render anything
	Sprite* sprite = entity->sprite();
	if (sprite != NULL) {
		// Finally, generate our MVP...
		glm::mat4 MVP = _projectionMatrix * _viewMatrix * modelMatrix;
		// ... and render the Sprite.
		this->_renderSprite(MVP, sprite);
	}
	
	// Render all Children (recursively)
	std::vector<Entity*> children = entity->children();
	std::vector<Entity*>::iterator child;
	for (child = children.begin(); child != children.end(); child++) {
		// Transform child's children...
		this->_renderEntity(modelMatrix, *child);
		// ... then reset modelMatrix for siblings.
		modelMatrix = glm::mat4(1.0f);
	}
}

void Renderer::_renderSprite(const glm::mat4& MVP, Sprite* sprite)
{
	Shader* shader = _uberShader;
	// ask resourcemanager
	if (shader == NULL) {
		shader = _resman.getShader(sprite->vertexshader().c_str(), sprite->fragmentshader().c_str());
	}
	Texture* texture = _resman.getTexture(sprite->texturename());

	glm::vec2 uvdim = sprite->uvdim;
	glm::vec2 pivot = sprite->pivot;
	int width = texture->width() * uvdim.x;
	int height = texture->height() * uvdim.y;
	Mesh* mesh = _resman.getSpriteMesh(width, height, pivot.x, pivot.y, uvdim.x, uvdim.y);
	
	// use our shader program
	glUseProgram(shader->programID());

	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->getGLTexture());
	
	// ... and send our transformation to the currently bound shader, in the "MVP" uniform
	glUniformMatrix4fv(shader->matrixID(), 1, GL_FALSE, &MVP[0][0]);

	// _blendColorID
	Color blendcolor = sprite->color;
	glUniform4f(shader->blendColorID(), blendcolor.r, blendcolor.g, blendcolor.b, blendcolor.a);
	// _uvOffsetID
	glUniform2f(shader->uvOffsetID(), sprite->uvoffset.x, sprite->uvoffset.y);
	
	// Set our "textureSampler" sampler to user Texture Unit 0
	glUniform1i(shader->textureID(), 0);

	// Note: We generated vertices in the correct order, with normals facing the camera.
	// We can also get the normalbuffer from the Mesh, but that's ignored here.
	// Use the normalbuffer (with links to the Shader) if you want to use lighting on your Sprites.
	// TODO: implement
	GLuint vertexPositionID =  glGetAttribLocation(shader->programID(), "vertexPosition"); // Mesh::_vertexbuffer
	GLuint vertexUVID =        glGetAttribLocation(shader->programID(), "vertexUV"); // Mesh::_uvbuffer

	// 1st attribute buffer : vertices
	glEnableVertexAttribArray(vertexPositionID);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexbuffer());
	glVertexAttribPointer(
		vertexPositionID,             // The attribute we want to configure
		3,                            // size : x+y+z => 3
		GL_FLOAT,                     // type
		GL_FALSE,                     // normalized?
		0,                            // stride
		(void*)0                      // array buffer offset
	);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(vertexUVID);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->uvbuffer());
	glVertexAttribPointer(
		vertexUVID,                   // The attribute we want to configure
		2,                            // size : U+V => 2
		GL_FLOAT,                     // type
		GL_FALSE,                     // normalized?
		0,                            // stride
		(void*)0                      // array buffer offset
	);

	// Draw the triangles !
	glDrawArrays(GL_TRIANGLES, 0, 2*3); // 2*3 indices starting at 0 -> 2 triangles
	//glDrawArrays(GL_LINES, 0, numpoints); // draw lines

	glDisableVertexAttribArray(vertexPositionID);
	glDisableVertexAttribArray(vertexUVID);
}

void Renderer::cleanup()
{
	_resman.cleanup();
}
