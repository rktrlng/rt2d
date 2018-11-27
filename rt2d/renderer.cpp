/**
 * This file is part of RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *   - Initial commit
 *   - [meruiden] scaling of window
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
	_window = nullptr;
	_defaultShader = nullptr;

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
		_window = glfwCreateWindow( SWIDTH, SHEIGHT, WINDOWNAME, primary, nullptr);
	} else {
		_window = glfwCreateWindow( SWIDTH, SHEIGHT, WINDOWNAME, nullptr, nullptr);
	}

	if( _window == nullptr ) {
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
	//glEnable(GL_CULL_FACE);

	_defaultShader =_resman.getShader(SPRITEVERTEXSHADER, SPRITEFRAGMENTSHADER);
	printf("Renderer using uberShader as fallback\n");

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
	// Our Projection Matrix (orthographic or perspective camera)
	_projectionMatrix = scene->camera()->projectionMatrix();

	// 'root' scene node has identity Matrix
	glm::mat4 modelMatrix = glm::mat4(1.0f);

	// start rendering everything, starting from the scene 'rootnode'
	this->_renderEntity(modelMatrix, scene, scene->camera());

	// Swap buffers
	glfwSwapBuffers(_window);
}

void Renderer::_renderEntity(glm::mat4 modelMatrix, Entity* entity, Camera* camera)
{
	/*
	  All steps to take:

	  - build model matrix for this entity
	  - multiply that with model matrix of parent
	  - update real world coordinates of entity (we calculate it here anyway)

	  - render sprite (if any)
	  - render line (if any)
	  - render spritebatch (if any)

	  Do this recursively for all children of this entity.
	*/

	// OpenGL doesn't understand our Point3. Make it glm::vec3 compatible.
	glm::vec3 position = glm::vec3(entity->position.x, entity->position.y, entity->position.z);
	glm::vec3 rotation = glm::vec3(entity->rotation.x, entity->rotation.y, entity->rotation.z);
	glm::vec3 scale = glm::vec3(entity->scale.x, entity->scale.y, entity->scale.z);

	// Build the Model matrix
	glm::mat4 translationMatrix	= glm::translate(glm::mat4(1.0f), position);
	glm::mat4 rotationMatrix	= glm::eulerAngleYXZ(rotation.y, rotation.x, rotation.z);
	glm::mat4 scalingMatrix		= glm::scale(glm::mat4(1.0f), scale);

	glm::mat4 mm = translationMatrix * rotationMatrix * scalingMatrix;

	// multiply ModelMatrix for this entity with the ModelMatrix of its parent (the caller of this method)
	// the first time we do this (for the root-parent), modelMatrix is identity.
	modelMatrix *= mm;

	// #######################################################
	//glm::vec4 realpos = modelMatrix * glm::vec4(0,0,0,1);
	//entity->_worldposition = Vector3(realpos.x, realpos.y, realpos.z);

	// send the real world transforms back to Entity (glm::decompose is experimental)
	glm::vec3 realscale;
	glm::quat realrot;
	glm::vec3 realpos;
	glm::vec3 skew;
	glm::vec4 perspective;
	glm::decompose(modelMatrix, realscale, realrot, realpos, skew, perspective);

	entity->_worldposition = Point3(realpos.x, realpos.y, realpos.z);
	entity->_worldrotation = Point3(realrot.x, realrot.y, realrot.z);
	entity->_worldscale = Point3(realscale.x, realscale.y, realscale.z);
	// #######################################################

	// Check for Sprites to see if we need to render anything
	Sprite* sprite = entity->sprite();
	if (sprite != nullptr) {
		// render the Sprite. Just use the model matrix for the entity since this is a single sprite.
		if (sprite->dynamic()) {
			this->_renderSprite(modelMatrix, sprite, true); // dynamic Sprite from PixelBuffer
		} else {
			this->_renderSprite(modelMatrix, sprite, false); // static Sprite from ResourceManager
		}
	}

	// Check for Spritebatch to see if we need to render anything
	if (entity->_spritebatch.size() > 0) {
		// render the Spritebatch
		this->_renderSpriteBatch(modelMatrix, entity->_spritebatch, camera);
	}

	// Check for Lines to see if we need to render anything
	Line* line = entity->line();
	if (line != nullptr) {
		// render the Line.
		this->_renderLine(modelMatrix, line);
	}

	// Check for Linebatch to see if we need to render anything
	size_t s = entity->_linebatch.size();
	if (s > 0) { // render the Linebatch
		for (size_t i = 0; i < s; i++) {
			this->_renderLine(modelMatrix, &entity->_linebatch[i]);
		}
	}

	// Render all Children (recursively)
	std::vector<Entity*> children = entity->children();
	std::vector<Entity*>::iterator child;
	for (child = children.begin(); child != children.end(); child++) {
		this->_renderEntity(modelMatrix, *child, camera);
	}
}

void Renderer::_renderSpriteBatch(glm::mat4 modelMatrix, std::vector<Sprite*>& spritebatch, Camera* camera)
{
	Sprite* spr = spritebatch[0];
	Shader* shader = _resman.getShader(spr->vertexshader().c_str(), spr->fragmentshader().c_str());
	// ask resourcemanager
	if (shader == nullptr) {
		shader = _defaultShader; // fallback to defaultshader
	}
	std::string texturename = spr->texturename();
	int filter = spr->filter();
	int wrap = spr->wrap();
	Texture* texture = _resman.getTexture(texturename, filter, wrap);

	if (spr->size.x == 0) { spr->size.x = texture->width() * spr->uvdim.x; }
	if (spr->size.y == 0) { spr->size.y = texture->height() * spr->uvdim.y; }

	Mesh* mesh = _resman.getSpriteMesh(spr->size.x, spr->size.y, spr->pivot.x, spr->pivot.y, spr->uvdim.x, spr->uvdim.y, spr->circlemesh(), spr->which());

	if (texture != nullptr) {
		// Bind the texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture->getGLTexture());
		//glUniform1i(shader->textureID(), 0);

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

				// _customParamsID
				for (int i=0; i<8; i++) {
					if (shader->customParamsID(i) != -1) {
						glUniform3f(shader->customParamsID(i), sprite->customParams[i].x, sprite->customParams[i].y, sprite->customParams[i].z);
					}
				}

				// use sprite transform to build the model matrix.
				glm::vec3 position = glm::vec3(sprite->spriteposition.x, sprite->spriteposition.y, sprite->spriteposition.z);
				glm::vec3 rotation = glm::vec3(sprite->spriterotation.x, sprite->spriterotation.y, sprite->spriterotation.z);
				glm::vec3 scale = glm::vec3(sprite->spritescale.x, sprite->spritescale.y, sprite->spritescale.z);

				// Build the model matrix for this sprite.
				glm::mat4 translationMatrix	= glm::translate(modelMatrix, position);
				glm::mat4 rotationMatrix	= glm::eulerAngleYXZ(rotation.y, rotation.x, rotation.z);
				glm::mat4 scalingMatrix		= glm::scale(glm::mat4(1.0f), scale);

				glm::mat4 mm = translationMatrix * rotationMatrix * scalingMatrix;

				this->_renderMesh(mm, shader, mesh, mesh->numverts(), GL_TRIANGLES, blendcolor);
			}
		}
	}

}

void Renderer::_renderSprite(const glm::mat4 modelMatrix, Sprite* sprite, bool dynamic)
{
	Shader* shader = _resman.getShader(sprite->vertexshader().c_str(), sprite->fragmentshader().c_str());
	if (shader == nullptr) {
		shader = _defaultShader; // fallback to defaultshader
	}

	Texture* texture = nullptr;
	if (dynamic) {
		if (sprite->texture() != nullptr) {
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

	// _customParamsID
	for (int i=0; i<8; i++) {
		if (shader->customParamsID(i) != -1) {
			glUniform3f(shader->customParamsID(i), sprite->customParams[i].x, sprite->customParams[i].y, sprite->customParams[i].z);
		}
	}

	if (texture != nullptr) {
		// Bind the texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0 + 0);
		glBindTexture(GL_TEXTURE_2D, texture->getGLTexture());
		//glUniform1i(shader->textureID(), 0);
	}

	if (sprite->palette() != nullptr) {
		// Bind the palette in Texture Unit 1
		glActiveTexture(GL_TEXTURE0 + 1);
		glBindTexture(GL_TEXTURE_1D, sprite->palette()->getGLTexture());
		//glUniform1i(shader->paletteID(), 1);
	}

	this->_renderMesh(modelMatrix, shader, mesh, mesh->numverts(), GL_TRIANGLES, blendcolor);

	if (dynamic && texture != nullptr) {
		delete texture;
	}
}

void Renderer::_renderLine(const glm::mat4 modelMatrix, Line* line)
{
	Shader* shader = _defaultShader;

	Texture* texture = _resman.getTexture(AUTOGENWHITE, 0, 1);
	Mesh* mesh = nullptr;
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

	// Bind the texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0 + 0);
	glBindTexture(GL_TEXTURE_2D, texture->getGLTexture());
	//glUniform1i(shader->textureID(), 0);

	this->_renderMesh(modelMatrix, shader, mesh, numpoints, GL_LINES, blendcolor);

	if (line->dynamic()) {
		delete mesh;
	}
}

void Renderer::_renderMesh(const glm::mat4 modelMatrix, Shader* shader,
	Mesh* mesh, int numverts, GLuint mode, RGBAColor blendcolor)
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

	// Set our "paletteSampler" sampler to user Texture Unit 1
	if (shader->paletteID() != -1) {
		glUniform1i(shader->paletteID(), 1);
	}

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
