#pragma once

#include <vector>
#include <string>

#include "chess_piece.hpp"

struct ChessBoard
{
    // 8x8 2D vector ploce, na poziciji board[0][0] se nalazi A8 polje, a na board[7][7] H1 polje
    ChessPiece board[8][8];

    bool en_passant;
    std::pair<int, int> en_passant_tile;

    bool whiteOnMove;

    bool kingsideCastleW;
	bool kingsideCastleB;
	bool queensideCastleW;
	bool queensideCastleB;

    unsigned int halfmoves = 0;
    unsigned int fullmoves = 0;

    //pomicanje figurice zadnjeg poteza
    std::pair<int, int> last_move_start;
    std::pair<int, int> last_move_end;
};


//Vraca true ako su ChessBoard.board vektori jednaki i popuni ostale podatke ploce
bool copyDataIfBoardSame(ChessBoard compareToBoard, ChessBoard* returnBoard);

//Vrati true ako je potez legalan, cb - pointer na koji se vraca potez
bool odigrajPotez(std::pair<int, int> tile1, std::pair<int, int> tile2, ChessBoard currentBoard, ChessBoard* returnBoard);

//vrati true ako su ChessBoard-ovi jednaki
bool chessBoardCompare(ChessBoard cb1, ChessBoard cb2);

void print_chess_board( ChessBoard cb );

void print_struct_info( ChessBoard cb );

//Da li je kralj u sahu
bool whiteKingCheck( ChessBoard cb );

bool blackKingCheck( ChessBoard cb );

//Da li je polje napadnutno od jedne strane
bool tileIsAttackedByWhite( ChessBoard cb, int x, int y );

bool tileIsAttackedByBlack( ChessBoard cb, int x, int y );

//Vraca listu ChessBoard-ova svih mogucih pozicija iz trenutne pozicije
std::vector<ChessBoard> possibleMoves( ChessBoard board );

//Svi moguci potezi za figuricu na lokaciji
std::vector<ChessBoard> piecePossibleMoves( ChessBoard board, int x, int y );

//funkcije koje racunaju moguce poteze figurica

std::vector<ChessBoard> blackPawnMoves( ChessBoard board, int x, int y );

std::vector<ChessBoard> whitePawnMoves( ChessBoard board, int x, int y );

std::vector<ChessBoard> blackKnightMoves( ChessBoard board, int x, int y );

std::vector<ChessBoard> whiteKnightMoves( ChessBoard board, int x, int y );

std::vector<ChessBoard> blackBishopMoves( ChessBoard board, int x, int y );

std::vector<ChessBoard> whiteBishopMoves( ChessBoard board, int x, int y );

std::vector<ChessBoard> blackRookMoves( ChessBoard board, int x, int y );

std::vector<ChessBoard> whiteRookMoves( ChessBoard board, int x, int y );

std::vector<ChessBoard> blackQueenMoves( ChessBoard board, int x, int y );

std::vector<ChessBoard> whiteQueenMoves( ChessBoard board, int x, int y );

std::vector<ChessBoard> blackKingMoves( ChessBoard board, int x, int y );

std::vector<ChessBoard> whiteKingMoves( ChessBoard board, int x, int y );