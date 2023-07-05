#include "chess_piece.hpp"

char getCharByPiece( ChessPiece cp ){
    if (cp.type == EMPTY_TILE)
    {
        return ' ';
    }

    if (cp.color == WHITE)
    {
        switch (cp.type)
        {
        case PAWN:
            return 'P';
            break;
        
        case KNIGHT:
            return 'N';
            break;

        case BISHOP:
            return 'B';
            break;

        case ROOK:
            return 'R';
            break;

        case QUEEN:
            return 'Q';
            break;

        case KING:
            return 'K';
            break;

        default:
            return ' ';
            break;
        }
    } else if (cp.color == BLACK)
    {
        switch (cp.type)
        {
        case PAWN:
            return 'p';
            break;
        
        case KNIGHT:
            return 'n';
            break;

        case BISHOP:
            return 'b';
            break;

        case ROOK:
            return 'r';
            break;

        case QUEEN:
            return 'q';
            break;

        case KING:
            return 'k';
            break;

        default:
            return ' ';
            break;
        }
    }

    return '0';
}

bool chessPieceCompare(ChessPiece cp1, ChessPiece cp2){
    if (cp1.color == cp2.color && cp1.type == cp2.type)
    {
        return true;
    }

    return false;
}