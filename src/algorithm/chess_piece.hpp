#pragma once

enum PieceType {
    EMPTY_TILE,
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING
};

enum PieceColor {
    NO_COLOR,
    WHITE,
    BLACK
};

struct ChessPiece
{
    PieceType type;
    PieceColor color;
};

//Vraca char kojim je figurica predstavljena u FEN-u
char getCharByPiece( ChessPiece cp );

//vraca true ako su figurice iste
bool chessPieceCompare(ChessPiece cp1, ChessPiece cp2);