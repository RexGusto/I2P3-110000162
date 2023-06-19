#include <cstdlib>

#include "../state/state.hpp"
#include "./minimax.hpp"


/**
 * @brief Randomly get a legal action
 *
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move
 */
int MinMax::Minmax(State* state, int depth, int alpha, int beta, bool maxPlayer) {
	if (depth == 0)
		return state->evaluate();
	else if (maxPlayer) {
		int maximum = -1000000000;
		for (auto& it : state->legal_actions) {
			State* st = state->next_state(it);
			maximum = std::max(maximum, Minmax(st, depth - 1, alpha, beta, false));
			alpha = std::max(alpha, maximum);
			if (beta <= alpha)
				break;
		}
		return maximum;
	}
	else {
		int minimum = 1000000000;
		for (auto& it : state->legal_actions) {
			State* st = state->next_state(it);
			minimum = std::min(minimum, Minmax(st, depth - 1, alpha, beta, true));
			beta = std::min(beta, minimum);
			if (beta <= alpha)
				break;
		}
		return minimum;
	}
}
