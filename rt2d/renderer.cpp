/**
 * This file is part of RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *   - Initial commit
 *   - <meruiden> scaling of window
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
	if( !glfwInit() ) {
		fprintf( stderr, "Failed to initialize GLFW\n" );
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // MacOS X

	GLFWmonitor* primary = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(primary);
	std::cout << "monitor: " << mode->width << "x"  << mode->height << std::endl;

	// Open a window and create its OpenGL context
	if (FULLSCREEN) {
		_window = glfwCreateWindow( SWIDTH, SHEIGHT, WINDOWNAME, primary, NULL);
	} else {
		_window = glfwCreateWindow( SWIDTH, SHEIGHT, WINDOWNAME, NULL, NULL);
	}

	if( _window == NULL ) {
		fprintf( stderr, "Failed to open GLFW window.\n" );
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(_window);

	// vsync (0=off, 1=on)
	glfwSwapInterval(VSYNC);

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
	glClearColor(CLEARCOLOR_RED, CLEARCOLOR_GREEN, CLEARCOLOR_BLUE, 1.0f);

	// Orthographic camera. We don't need these.
	// Enable depth test
	//glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	//glDepthFunc(GL_LESS);

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

	if (UBERSHADER) { // from config.h
		_uberShader =_resman.getShader(SPRITEVERTEXSHADER, SPRITEFRAGMENTSHADER);
		printf("Renderer using uberShader\n");
	}

	printf("Renderer::init() done\n");

	return 0;
}

void Renderer::renderScene(Scene* scene)
{
	// Since apple scales automatically, this will cause bugs where the viewport gets very small.
	#ifndef __APPLE__
		// Set the glViewport to the width and height of the window.
		glViewport(0, 0, scene->input()->getWindowWidth(), scene->input()->getWindowHeight());
	#endif

	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// get viewMatrix from Camera (Camera position and direction)
	_viewMatrix = scene->camera()->viewMatrix();
	// Our Projection Matrix (orthographic camera)
	_projectionMatrix = scene->camera()->projectionMatrix();

	// 'root' scene node has identity Matrix
	glm::mat4 modelMatrix = glm::mat4(1.0f);

	// start rendering everything, starting from the scene 'rootnode'
	this->_renderEntity(modelMatrix, scene, scene->camera());

	// Swap buffers
	glfwSwapBuffers(_window);
}

void Renderer::_renderEntity(glm::mat4& modelMatrix, Entity* entity, Camera* camera)
{
	// multiply ModelMatrix for this child with the ModelMatrix of the parent (the caller of this method)
	// the first time we do this (for the root-parent), modelMatrix is identity.
	modelMatrix *= this->_getModelMatrix(entity);

	// #######################################################
	// fill _worldpos in Entity
	glm::vec4 realpos = modelMatrix * glm::vec4(0,0,0,1);
	// send the real world position after these transforms back to Entity->worldpos
	entity->_worldpos = Vector2(realpos.x, realpos.y);
	// #######################################################

	// Check for Sprites to see if we need to render anything
	Sprite* sprite = entity->sprite();
	if (sprite != NULL) {
		// render the Sprite
		if (sprite->dynamic()) {
			this->_renderSprite(modelMatrix, sprite, true); // dynamic Sprite from PixelBuffer
		} else {
			this->_renderSprite(modelMatrix, sprite, false); // static Sprite from ResourceManager
		}
	}

	// Check for Lines to see if we need to render anything
	Line* line = entity->line();
	if (line != NULL) {
		// render the Line.
		this->_renderLine(modelMatrix, line);
	}

	// Check for Spritebatch to see if we need to render anything
	if (entity->_spritebatch.size() > 0) {
		// render the Spritebatch
		this->_renderSpriteBatch(modelMatrix, entity->_spritebatch, camera);
	}

	// Render all Children (recursively)
	std::vector<Entity*> children = entity->children();
	std::vector<Entity*>::iterator child;
	for (child = children.begin(); child != children.end(); child++) {
		// Transform child's children...
		this->_renderEntity(modelMatrix, *child, camera);
		// ...then reset modelMatrix for siblings to the modelMatrix of the parent.
		modelMatrix = this->_getModelMatrix( (*child)->parent() );
	}
}

glm::mat4 Renderer::_getModelMatrix(Entity* entity)
{
	// OpenGL doesn't understand our Vector2. Make it glm::vec3 compatible.
	glm::vec3 position = glm::vec3(entity->position.x, entity->position.y, 0.0f);
	glm::vec3 rotation = glm::vec3(0.0f, 0.0f, entity->rotation);
	glm::vec3 scale = glm::vec3(entity->scale.x, entity->scale.y, 1.0f);

	// Build the Model matrix
	glm::mat4 translationMatrix	= glm::translate(glm::mat4(1.0f), position);
	glm::mat4 rotationMatrix	= glm::eulerAngleYXZ(0.0f, 0.0f, rotation.z);
	glm::mat4 scalingMatrix		= glm::scale(glm::mat4(1.0f), scale);

	glm::mat4 mm = translationMatrix * rotationMatrix * scalingMatrix;

	return mm;
}

void Renderer::_renderSpriteBatch(glm::mat4& modelMatrix, std::vector<Sprite*>& spritebatch, Camera* camera)
{
	Sprite* spr = spritebatch[0];
	Shader* shader = _uberShader;
	// ask resourcemanager
	if (shader == NULL) {
		shader = _resman.getShader(spr->vertexshader().c_str(), spr->fragmentshader().c_str());
	}
	std::string texturename = spr->texturename();
	int filter = spr->filter();
	int wrap = spr->wrap();
	Texture* texture = _resman.getTexture(texturename, filter, wrap);

	if (spr->size.x == 0) { spr->size.x = texture->width() * spr->uvdim.x; }
	if (spr->size.y == 0) { spr->size.y = texture->height() * spr->uvdim.y; }

	Mesh* mesh = _resman.getSpriteMesh(spr->size.x, spr->size.y, spr->pivot.x, spr->pivot.y, spr->uvdim.x, spr->uvdim.y, spr->circlemesh(), spr->which());

	if (texture != NULL) {
		// Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture->getGLTexture());

		// for every Sprite in the batch...
		int s = spritebatch.size();
		for (int i = 0; i < s; i++) {
			Sprite* sprite = spritebatch[i]; // a Sprite handle
			int culled = 0; // state that we need to draw it
			if (sprite->useCulling()) { // but maybe we don't
				int half_width = SWIDTH/2;
				int half_height = SHEIGHT/2;

				int left_edge = camera->position.x - half_width;
				int right_edge = camera->position.x + half_width;
				int top_edge = camera->position.y - half_height;
				int bottom_edge = camera->position.y + half_height;
				float posx = sprite->spriteposition.x;
				float posy = sprite->spriteposition.y;

				int debug = 0;
				if (debug) { // cull visibly within the frame
					if (posx - spr->size.x < left_edge) { culled = 1; }
					if (posx + spr->size.x > right_edge) { culled = 1; }
					if (posy + spr->size.y > bottom_edge) { culled = 1; }
					if (posy - spr->size.y < top_edge) { culled = 1; }
				} else {
					if (posx + spr->size.x < left_edge) { culled = 1; }
					if (posx - spr->size.x > right_edge) { culled = 1; }
					if (posy - spr->size.y > bottom_edge) { culled = 1; }
					if (posy + spr->size.y < top_edge) { culled = 1; }
				}
			}
			// this Sprite isn't culled and needs to be drawn
			if (!culled) {
				RGBAColor blendcolor = MAGENTA;
				if (texture->warranty()) {
					blendcolor = sprite->color;
				}

				// _uvOffsetID
				glUniform2f(shader->uvOffsetID(), sprite->uvoffset.x, sprite->uvoffset.y);

				// use spritepos for position
				glm::vec3 position = glm::vec3(sprite->spriteposition.x, sprite->spriteposition.y, 0.0f);
				glm::vec3 rotation = glm::vec3(0.0f, 0.0f, sprite->spriterotation);
				glm::vec3 scale = glm::vec3(sprite->spritescale.x, sprite->spritescale.y, 0.0f);

				// Build the Model matrix
				glm::mat4 translationMatrix	= glm::translate(modelMatrix, position);
				glm::mat4 rotationMatrix	= glm::eulerAngleYXZ(0.0f, 0.0f, rotation.z);
				glm::mat4 scalingMatrix		= glm::scale(glm::mat4(1.0f), scale);
				glm::mat4 mm = translationMatrix * rotationMatrix * scalingMatrix;

				this->_renderMesh(mm, shader, texture, mesh, mesh->numverts(), GL_TRIANGLES, blendcolor);
			}
		}
	}

}

void Renderer::_renderSprite(const glm::mat4& modelMatrix, Sprite* sprite, bool dynamic)
{
	Shader* shader = _uberShader;
	// ask resourcemanager
	if (shader == NULL) {
		shader = _resman.getShader(sprite->vertexshader().c_str(), sprite->fragmentshader().c_str());
	}
	Texture* texture = NULL;
	if (dynamic) {
		if (sprite->texture() != NULL) {
			texture = new Texture();
			texture->createFromBuffer(sprite->texture()->pixels());
		}
	} else {
		texture = _resman.getTexture(sprite->texturename(), sprite->filter(), sprite->wrap());
	}

	if (sprite->size.x == 0) { sprite->size.x = texture->width() * sprite->uvdim.x; }
	if (sprite->size.y == 0) { sprite->size.y = texture->height() * sprite->uvdim.y; }

	Mesh* mesh = _resman.getSpriteMesh(sprite->size.x, sprite->size.y, sprite->pivot.x, sprite->pivot.y, sprite->uvdim.x, sprite->uvdim.y, sprite->circlemesh(), sprite->which());

	RGBAColor blendcolor = MAGENTA;
	if (texture->warranty()) {
		blendcolor = sprite->color;
	}

	// _uvOffsetID
	glUniform2f(shader->uvOffsetID(), sprite->uvoffset.x, sprite->uvoffset.y);

	if (texture != NULL) {
		// Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture->getGLTexture());

		this->_renderMesh(modelMatrix, shader, texture, mesh, mesh->numverts(), GL_TRIANGLES, blendcolor);
	}

	if (dynamic && texture != NULL) {
		delete texture;
	}
}

void Renderer::_renderLine(const glm::mat4& modelMatrix, Line* line)
{
	Shader* shader = _uberShader;
	// ask resourcemanager
	if (shader == NULL) {
		// only uberShader for now TODO fix
		//shader = _resman.getShader(sprite->vertexshader().c_str(), sprite->fragmentshader().c_str());
	}
	Texture* texture = _resman.getTexture(AUTOGENWHITE, 0, 1);
	Mesh* mesh = NULL;
	RGBAColor blendcolor = line->color;

	int numpoints = (line->points().size()*2) - 1;
	if (line->closed()) {
		numpoints += 1;
	}

	if (line->dynamic()) {
		mesh = new Mesh();
		mesh->generateLineMesh(line);
	} else {
		mesh = _resman.getLineMesh(line);
	}

	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->getGLTexture());

	this->_renderMesh(modelMatrix, shader, texture, mesh, numpoints, GL_LINES, blendcolor);

	if (line->dynamic()) {
		delete mesh;
	}
}

void Renderer::_renderMesh(const glm::mat4& modelMatrix, Shader* shader,
	Texture* texture, Mesh* mesh, int numverts,
	GLuint mode, RGBAColor blendcolor)
{
	// use our shader program
	glUseProgram(shader->programID());

	// generate the ModelMatrix
	glm::mat4 MVP = _projectionMatrix * _viewMatrix * modelMatrix;

	// ... and send our transformation to the currently bound shader, in the "MVP" uniform
	glUniformMatrix4fv(shader->matrixID(), 1, GL_FALSE, &MVP[0][0]);

	// _blendColorID
	glUniform4f(shader->blendColorID(), (float) blendcolor.r/255.0f, (float) blendcolor.g/255.0f, (float) blendcolor.b/255.0f, (float) blendcolor.a/255.0f);

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

	// Draw the triangles or lines
	glDrawArrays(mode, 0, numverts);

	glDisableVertexAttribArray(vertexPositionID);
	glDisableVertexAttribArray(vertexUVID);
}

void Renderer::cleanup()
{
	_resman.cleanup();
}
