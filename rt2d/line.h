/**
 * @file line.h
 *
 * @brief The Line header file.
 *
 * This file is part of RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *   - Initial commit
 */
#ifndef LINE_H
#define LINE_H

#include <vector>
#include <string>
#include <cstring>
#include <stdio.h>

#include <glm/glm.hpp>

#include <rt2d/color.h>

/// @brief A Line is a collection of Points that make up a Line
class Line
{
public:
	Line(); ///< @brief Constructor of the Line
	Line(const std::string& filename); ///< @brief Custom constructor of the Line
	virtual ~Line(); ///< @brief Destructor of the Line

	RGBAColor color; ///< @brief blend Color of the Line

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
	/// @param z coordinate of the Point (default 0.0f)
	/// @return void
	void addPoint(float x, float y, float z = 0.0f);
	/// @brief Edit a Point on the Line
	/// @param id the Point to edit
	/// @param x coordinate of the Point
	/// @param y coordinate of the Point
	/// @param z coordinate of the Point (default 0.0f)
	/// @return void
	void editPoint(unsigned int id, float x, float y, float z = 0.0f);
	/// @brief Create a circle of points
	/// @param radius the radius of the circle
	/// @param segments the number of segments
	/// @param _x the optional x pos of the Circle
	/// @param _y the optional y pos of the Circle
	/// @return void
	void createCircle(int radius, int segments, float _x = 0.0f, float _y = 0.0f);
	/// @brief Create a box
	/// @param hw half the width of the box
	/// @param hh half the height of the box
	/// @return void
	void createBox(int hw, int hh);

	/// @brief Get the Points of this Line
	/// @return std::vector<glm::vec3> _points
	std::vector<glm::vec3>& points() { return _points; };

	/// @brief is this Line dynamic or not?
	/// @return bool _dynamic
	bool dynamic() { return _dynamic; };
	/// @brief set this Line to be dynamic or not
	/// @return void
	void dynamic(bool d) { _dynamic = d; };

	/// @brief is this Line closed or not?
	/// @return bool _closed
	bool closed() { return _closed; };
	/// @brief set this Line to be closed or not
	/// @return void
	void closed(bool c) { _closed = c; };

private:
	std::string _filename; ///< @brief _filename filename of the Line
	std::vector<glm::vec3> _points; ///< @brief _points points of the Line

	// identity for unique filename
	int _guid; ///< @brief The _guid property of this Line
	static int _nextGuid; ///< @brief The _nextGuid property of this Line

	bool _dynamic; ///< @brief The _dynamic property of this Line
	bool _closed; ///< @brief The _closed property of this Line
};

#endif /* LINE_H */
