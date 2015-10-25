/**
 * @file renderer.h
 * 
 * @brief The Renderer header file.
 * 
 * This file is part of RT2D, a 2D OpenGL framework.
 * 
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *   - Initial commit
 * - Copyright [year] [your name] <you@yourhost.com>
 *   - [description]
 */

#ifndef RENDERER_H
#define RENDERER_H

// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include <rt2d/resourcemanager.h>
#include <rt2d/entity.h>
#include <rt2d/scene.h>
#include <rt2d/shader.h>
#include <rt2d/config.h>

/// @brief The Renderer class renders meshes (vertices, normals, UV coordinates) from Sprites.
class Renderer
{
	public:
		Renderer();				///< @brief Constructor of the Renderer
		virtual ~Renderer();	///< @brief Destructor of the Renderer
		
		/// @brief Initialise the Renderer. Create a Window with OpenGL Context.
		/// @return int (0 when successful, -1 when errors occurred)
		int init();
		/// @brief Renders a Scene with all its children.
		/// @param scene The Scene that needs to be rendered
		/// @return void
		void renderScene(Scene* scene);
		
		/// @brief access the GLFWwindow.
		/// @return GLFWwindow* _window
		GLFWwindow* window() { return _window; };
		
		/// @brief cleanup (_resman)
		/// @return void
		void cleanup();
		
	private:
		// Only renderer needs access to the ResourceManager
		ResourceManager _resman;	///< @brief The ResourceManager of the Renderer
		
		// Our GLFW window with OpenGL context
		GLFWwindow* _window;		///< @brief The GLFWwindow of the Renderer
		
		/// @brief Recursive function that renders an Entity which is a child of the Scene or parent Entity.
		/// @param modelMatrix The modelMatrix of the parent
		/// @param entity The Entity that needs rendering
		/// @return void
		void _renderEntity(glm::mat4& modelMatrix, Entity* entity);
		
		/// @brief get the modelMatrix from an Entity
		/// @param entity The Entity we need the modelMatrix from.
		/// @return glm::mat4
		inline glm::mat4 _getModelMatrix(Entity* entity);
		
		/// @brief Renders the Sprite 'component' of an Entity.
		/// @param MVP The ModelViewProjection Matrix of the Entity
		/// @param sprite The Sprite 'component' of the Entity
		/// @param dynamic Render what we get from ResourceManager or PixelBuffer
		/// @return void
		void _renderSprite(const glm::mat4& MVP, Sprite* sprite, bool dynamic);
		
		/// @brief Renders the Line 'component' of an Entity.
		/// @param MVP The ModelViewProjection Matrix of the Entity
		/// @param line The Line 'component' of the Entity
		/// @return void
		void _renderLine(const glm::mat4& MVP, Line* line);
		
		/// @brief Renders the Mesh 'component' of a Sprite or Line.
		/// @param MVP The ModelViewProjection Matrix of the Mesh
		/// @param shader The Shader
		/// @param texture The Texture
		/// @param mesh The Mesh
		/// @param numverts The number of vertices to render
		/// @param mode The mode: GL_LINES or GL_TRIANGLES
		/// @param blendcolor The Color to use for blending
		/// @return void
		inline void _renderMesh(const glm::mat4& MVP, Shader* shader, 
			Texture* texture, Mesh* mesh, int numverts,
			GLuint mode, Color blendcolor);
		
		/// @brief Culls a Scene with all its children.
		/// @param scene The Scene that needs to be culled
		/// @return void
		void _cullScene(Scene* scene);
		/// @brief Culls an Entity with all its children.
		/// @param campos The position of the Camera
		/// @param entity The Entity that needs to be culled
		/// @return void
		void _cullEntity(Vector2 campos, Entity* entity);
		
		// temp 'local' variables.
		glm::mat4 _projectionMatrix;	///< @brief The _projectionMatrix we get from the Camera. We only get the ProjectionMatrix from the orthographic camera once
		glm::mat4 _viewMatrix;			///< @brief The _viewMatrix we get from the Camera once per frame.
		
		Shader* _uberShader;			///< @brief We can choose to use an 'ubershader', or get the Shader from the Sprite.
};

#endif /* RENDERER_H */ 
