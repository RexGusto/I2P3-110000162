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
Move Minimax::get_move(State* state, int depth){
    if (!state->legal_actions.size()) state->get_legal_actions();

    auto action = state->legal_actions;
    long unsigned int best_move = 0;
	int val; 
    int second_max = -1000000000;
    int maximum = -1000000000, minimum = 1000000000;
    for (long unsigned int i = 0; i < action.size(); i++) {
        State* temp = state->next_state(action[i]);

        val =Minmax(temp, depth-1, maximum, minimum, false);
        if (val > second_max) {
            second_max = val;
           best_move = i;

        }
        if (second_max > maximum) maximum = second_max;
    }
	int final_move = (int)best_move;
    return action[(int)best_move];
}

int Minimax::Minmax(State* state, int depth, int alpha, int beta, bool maxPlayer) {
	if (!state->legal_actions.size()) state->get_legal_actions();
    if (maxPlayer) {
        if (depth == 0) return state->evaluate();
        if (state->game_state == WIN) return state->evaluate() + 100;
        
        auto action = state->legal_actions;
        int maximum = -1000000000;
		int val;

        for (long unsigned int i = 0; i < action.size(); i++) {
            State* temp = state->next_state(action[i]);
            val = Minmax(temp, depth-1, alpha, beta, false);
            if (val > maximum) maximum = val;
            if (maximum > alpha) alpha = maximum;


            if (alpha >= beta) break;
        }
        return maximum;
    }
    else {
        State* second_st = new State(state->board, !state->player);

        if (depth == 0) return second_st->evaluate();
        if (state->game_state == WIN) return second_st->evaluate() - 100;
        
        auto action = state->legal_actions;

        int minimum = 1000000000;
		int val;

        for (long unsigned int i = 0; i < action.size(); i++) {
            State* temp = state->next_state(action[i]);
            val = Minmax(temp, depth-1, alpha, beta, true);
            if (val < minimum) minimum = val;
            if (minimum < beta) beta = minimum;


            if (beta <= alpha) break;
        }
        return minimum;
    }
}
