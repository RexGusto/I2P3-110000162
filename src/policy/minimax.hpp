#pragma once
#include "../state/state.hpp"


/**
 * @brief Policy class for random policy,
 * your policy class should have get_move method
 */
class MinMax {
public:
	static int Minmax(State* state, int depth, int alpha, int beta, bool maxPlayer) ;
};