/**
 * @defgroup   PATH path
 *
 * @brief      This file implements path.
 *
 * @author     jimenezga
 * @date       2019
 */
#ifndef __PATH_H__
#define __PATH_H__ 1

#include "glm/vec2.hpp"
#include "platform_types.h"

#include "app_manager.h"

const int kMaxPoints = 256;

enum MovementType {
	kStop = -1,
	kDeterm = 0,
	kRandom = 1,
	kTracker = 2,
	kPattern = 3
};

enum PathDirections {
	kNone = 0,
	kUp = 1,
	kDown = 2,
	kRight = 3,
	kLeft = 4
};

enum PathLoopType {
	kNoLoop = 0,
	kSingleLoop = 1,
	kMultipleLoop = 2,
	kInfiniteLoop = 3,
};


class Path {
public:
	Path();
	/**
	 * @brief      Initialize the path
	 *
	 * @param[in]  mtype        The MovementType
	 * @param[in]  ltype        The LoopType Does nothing
	 * @param[in]  initial_pos  The initial position
	 * @param[in]  loops        The loops
	 */
	void init(MovementType mtype, PathLoopType ltype, glm::vec2 initial_pos, int loops = 1);

	/**
	 * @brief      Add a basic point and moves the index
	 *
	 * @param[in]  point  The point
	 *
	 * @return     { Ok if all goes well }
	 */
	s16 addPoint(glm::vec2 point);

	/**
	 * @brief      Add a point depending on the Direction and Magnite passed
	 *
	 * @param[in]  dir_type   The dir type
	 * @param[in]  magnitude  The magnitude
	 *
	 * @return     { Ok if all goes well }
	 */
	s16 addPoint(PathDirections dir_type, float magnitude);

	/**
	 * @brief      Generates a number of ramdon points with a maximun and a
	 *             minimun range
	 *
	 * @param[in]  min     The minimum
	 * @param[in]  max     The maximum
	 * @param[in]  number  The number
	 *
	 * @return     { Ok if all goes well }
	 */
	s16 calculateRandomPoints(glm::vec2 min, glm::vec2 max, int number);

	/**
	 * @brief      Sets the movement type.
	 *
	 * @param[in]  mtype  The mtype
	 */
	void set_movement_type(MovementType mtype);
	
	/**
	 * @brief      Sets the pathloop type.
	 *
	 * @param[in]  ptype  The ptype
	 */
	void set_pathloop_type(PathLoopType ptype);

	/**
	 * @brief      Gets the next point.
	 *
	 * @return     The next point.
	 */
	glm::vec2 getNextPoint();

private:
	int index_;
	glm::vec2 points_[kMaxPoints];
	glm::vec2 initial_position_;

	MovementType mov_type_;
	PathLoopType loop_type_;

	

	int current_point_;
	int number_of_loops_;
};

#endif//__PATH_H__