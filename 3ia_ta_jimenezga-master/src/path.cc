#include "path.h"
#include "common_def.h"

Path::Path() {
	index_ = 0;
	current_point_ = 0;
}

void Path::init(MovementType mtype, PathLoopType ltype, glm::vec2 initial_pos ,int loops) {
	mov_type_ = mtype;
	loop_type_ = ltype;
	number_of_loops_ = loops;
	initial_position_ = initial_pos;
}

s16 Path::addPoint(glm::vec2 point) {
	if (index_ >= kMaxPoints) {
		return kErrorCode_StorageFull;
	}
	
	points_[index_] = point;
	index_++;
	return kErrorCode_Ok;
}

s16 Path::addPoint(PathDirections dir_type, float magnitude) {
	switch (dir_type)
	{
	case kNone:
		break;
	case kUp: 
		initial_position_ = { initial_position_.x, initial_position_.y - magnitude };
		addPoint(initial_position_);
		break;
	case kDown:
		initial_position_ = { initial_position_.x, initial_position_.y + magnitude };
		addPoint(initial_position_);
		break;
	case kLeft: 
		initial_position_ = { initial_position_.x - magnitude, initial_position_.y };
		addPoint(initial_position_);
		break;
	case kRight: 
		initial_position_ = { initial_position_.x + magnitude, initial_position_.y };
		addPoint(initial_position_);
		break;
	}

	return kErrorCode_Ok;
}


s16 Path::calculateRandomPoints(glm::vec2 min, glm::vec2 max, int number) {
	if (number > kMaxPoints) {
		return kErrorCode_StorageFull;
	}

	float r1 = 0;
	float r2 = 0;

	for (int i = 0; i < number; ++i) {
		do {
			r1 = min.x + (rand() % ((int)max.x));
		} while (r1 < min.x && r1 > max.x);

		do {
			r2 = min.y + (rand() % ((int)max.y));
		} while (r2 < min.y && r2 > max.y);

		addPoint({ r1, r2 });
	}
	return kErrorCode_Ok;
}

void Path::set_movement_type(MovementType mtype) {
	mov_type_ = mtype;
}

void Path::set_pathloop_type(PathLoopType ptype) {
	loop_type_ = ptype;
}

glm::vec2 Path::getNextPoint() {

	if (current_point_ == index_) {
		current_point_ = 0;
	}

	glm::vec2 temp = points_[current_point_];
	current_point_++;

	return temp;
}