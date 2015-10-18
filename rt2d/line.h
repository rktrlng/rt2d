/**
 * @file line.h
 * 
 * @brief The Line header file.
 * 
 * This file is part of RT2D, a 2D OpenGL framework.
 * 
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *   - Initial commit
 * - Copyright [year] [your name] <you@yourhost.com>
 *   - [description]
 */
#ifndef LINE_H
#define LINE_H

#include <vector>
#include <string>
#include <cstring>

#include <glm/glm.hpp>

#include <rt2d/color.h>

/// @brief A Line is a collection of Points that make up a Line
class Line
{
	public:
		Line(); ///< @brief Constructor of the Line
		Line(const std::string& filename); ///< @brief Custom constructor of the Line
		virtual ~Line(); ///< @brief Destructor of the Line
		
		/// @brief get the filename (path to the file)
		/// @return std::string _filename
		std::string filename() { return _filename; };
		
		/// @brief get the filename (path to the file)
		/// @param filename path to the file
		/// @return bool
		bool loadLineFile(const std::string& filename);
		/// @brief Add a Point to the Line
		/// @param x coordinate of the Point
		/// @param y coordinate of the Point
		/// @return void
		void addPoint(float x, float y);
		
		/// @brief Get the Points of this Line
		/// @return std::vector<glm::vec3> _points
		const std::vector<glm::vec3>& points() { return _points; };
		/// @brief Get the UV's of this Line
		/// @return std::vector<glm::vec2> _uvs
		const std::vector<glm::vec2>& uvs() { return _uvs; };
		
		Color color;		///< @brief blend Color of the Line
	
	private:
		std::string _filename;	///< @brief _filename filename of the Line
		std::vector<glm::vec3> _points;	///< @brief _points points of the Line
		std::vector<glm::vec2> _uvs;	///< @brief _uvs UV's of the Line
		
		// identity
		int _guid;				///< @brief The _guid of this Line
		static int _nextGuid;	///< @brief The _nextGuid of this Line
};

#endif /* LINE_H */ 
