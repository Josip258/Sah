#include <vector>
#include <sstream>
#include <string>
#include <iostream>

#include "fen_load.hpp"

ChessBoard FEN_to_board( std::string FEN ){
    ChessBoard cb;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			cb.board[i]->color = NO_COLOR;
			cb.board[i]->type = EMPTY_TILE;
		}
	}
	

    //Podijeli FEN u 6 dijelova
    std::vector<std::string> parts;
    std::istringstream f(FEN);
    std::string part;
    while (getline(f, part, ' ')) {
        parts.push_back(part);
    }

    int row = 0, col = 0;
	for (char c : parts[0]) {
        if (c == '/') {
			row++;
            col = 0;
		} else if (isdigit(c)) {
			for(int i=0; i<((int)(c - '0')); i++){
				cb.board[col][row].type = EMPTY_TILE;
                cb.board[col][row].color = NO_COLOR;
				col++;
			}
		} else {
			switch (c) {
				case 'P':   cb.board[col][row].type = PAWN; cb.board[col][row].color = WHITE; break;
				case 'N':   cb.board[col][row].type = KNIGHT; cb.board[col][row].color = WHITE; break;
				case 'B':   cb.board[col][row].type = BISHOP; cb.board[col][row].color = WHITE; break;
				case 'R':   cb.board[col][row].type = ROOK; cb.board[col][row].color = WHITE; break;
				case 'Q':   cb.board[col][row].type = QUEEN; cb.board[col][row].color = WHITE; break;
				case 'K':   cb.board[col][row].type = KING; cb.board[col][row].color = WHITE; break;
				case 'p':   cb.board[col][row].type = PAWN; cb.board[col][row].color = BLACK; break;
				case 'n':   cb.board[col][row].type = KNIGHT; cb.board[col][row].color = BLACK; break;
				case 'b':   cb.board[col][row].type = BISHOP; cb.board[col][row].color = BLACK; break;
				case 'r':   cb.board[col][row].type = ROOK; cb.board[col][row].color = BLACK; break;
				case 'q':   cb.board[col][row].type = QUEEN; cb.board[col][row].color = BLACK; break;
				case 'k':   cb.board[col][row].type = KING; cb.board[col][row].color = BLACK; break;
				default :   cb.board[col][row].type = EMPTY_TILE; cb.board[col][row].color = NO_COLOR; break;
			}
            col++;
        }
    }

    cb.whiteOnMove = (parts[1] == "w");

    cb.kingsideCastleW = false;
	cb.kingsideCastleB = false;
	cb.queensideCastleW = false;
	cb.queensideCastleB = false;
	for(char c : parts[2]){
        switch (c) {
				case 'K':   cb.kingsideCastleW = true; break;
				case 'k':   cb.kingsideCastleB = true; break;
				case 'Q':   cb.queensideCastleW = true; break;
				case 'q':   cb.queensideCastleB = true; break;
			}
	}
    
    if(parts[3] == "-"){
        cb.en_passant = false;
	}else{
		cb.en_passant = true;
		cb.en_passant_tile = std::pair<int, int>(parts[3][0] - 'a', 8 - (int(parts[3][1]) - '0'));
    }

    cb.halfmoves = stoi(parts[4]);

    cb.fullmoves = stoi(parts[5]);

    return cb;
}