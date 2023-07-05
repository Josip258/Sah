#pragma once

#include <vector>

#include "chess_board.hpp"

float minimax( ChessBoard node, int depth, float a, float b );

float evaluation( ChessBoard board );

//ChessBoard izaberiPotez( std::vector<ChessBoard> potezi );