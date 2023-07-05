#include <iostream>

#include "chess_board.hpp"

bool copyDataIfBoardSame(ChessBoard compareToBoard, ChessBoard* returnBoard){
    for (int j = 0; j < 8; j++)
    {
        for (int i = 0; i < 8; i++)
        {
            if (!chessPieceCompare(compareToBoard.board[i][j], returnBoard->board[i][j]))
            {
                return false;
            }
        }
    }

    returnBoard->en_passant = compareToBoard.en_passant;
    returnBoard->en_passant_tile.first = compareToBoard.en_passant_tile.first;
    returnBoard->en_passant_tile.second = compareToBoard.en_passant_tile.second;
    returnBoard->whiteOnMove = compareToBoard.whiteOnMove;
    returnBoard->kingsideCastleW = compareToBoard.kingsideCastleW;
    returnBoard->kingsideCastleB = compareToBoard.kingsideCastleB;
    returnBoard->queensideCastleW = compareToBoard.queensideCastleW;
    returnBoard->queensideCastleB = compareToBoard.queensideCastleB;
    returnBoard->halfmoves = compareToBoard.halfmoves;
    returnBoard->fullmoves = compareToBoard.fullmoves;
    returnBoard->last_move_end = compareToBoard.last_move_end;
    returnBoard->last_move_start = compareToBoard.last_move_start;

    return true;
}

bool odigrajPotez(std::pair<int, int> tile1, std::pair<int, int> tile2, ChessBoard currentBoard, ChessBoard* returnBoard){
    
    if (tile1.first < 0 && tile1.first > 7 &&
        tile2.first < 0 && tile2.first > 7 &&
        tile1.second < 0 && tile1.second > 7 &&
        tile2.second < 0 && tile2.second > 7)
    {
        return false;
    }

    for (int j = 0; j < 8; j++)
    {
        for (int i = 0; i < 8; i++)
        {
            returnBoard->board[i][j] = currentBoard.board[i][j];
        }
    }
    

    returnBoard->board[tile1.first][tile1.second] = {EMPTY_TILE, NO_COLOR};
    returnBoard->board[tile2.first][tile2.second] = {currentBoard.board[tile1.first][tile1.second]};

    //en passant
    if (currentBoard.board[tile1.first][tile1.second].type == PAWN && currentBoard.en_passant == true && currentBoard.en_passant_tile.first == tile2.first && currentBoard.en_passant_tile.second == tile2.second)
    {
        returnBoard->board[tile2.first][tile1.second] = {EMPTY_TILE, NO_COLOR};
    }

    //rokada
    if (currentBoard.board[tile1.first][tile1.second].type == KING)
    {
        if (tile2.first == tile1.first - 2 && tile2.second == tile1.second)
        {
            returnBoard->board[0][tile1.second] = {EMPTY_TILE, NO_COLOR};
            returnBoard->board[tile1.first - 1][tile1.second] = {ROOK, currentBoard.board[tile1.first][tile1.second].color};

        } else if (tile2.first == tile1.first + 2 && tile2.second == tile1.second)
        {
            returnBoard->board[7][tile1.second] = {EMPTY_TILE, NO_COLOR};
            returnBoard->board[tile1.first + 1][tile1.second] = {ROOK, currentBoard.board[tile1.first][tile1.second].color};
        }
    }

    //promocija
    if (currentBoard.board[tile1.first][tile1.second].type == PAWN && (tile2.second == 0 || tile2.second == 7))
    {
        returnBoard->board[tile1.first][tile1.second] = {EMPTY_TILE, NO_COLOR};
        returnBoard->board[tile2.first][tile2.second] = {QUEEN, currentBoard.board[tile1.first][tile1.second].color};
    }

    std::vector<ChessBoard> possible_moves = possibleMoves( currentBoard );
    bool legit = false;
    for (unsigned long long i = 0; i < possible_moves.size(); i++)
    {
        //print_chess_board(possible_moves[i]);
        if (copyDataIfBoardSame(possible_moves[i], returnBoard))
        {
            legit = true;
            break;
        }
    }

    if (legit)
    {
        return true;
    }
    
    return false;
}

bool chessBoardCompare(ChessBoard cb1, ChessBoard cb2){

    if (cb1.en_passant == cb2.en_passant &&
        cb1.en_passant_tile.first == cb2.en_passant_tile.first &&
        cb1.en_passant_tile.second == cb2.en_passant_tile.second &&
        cb1.whiteOnMove == cb2.whiteOnMove &&
        cb1.kingsideCastleW == cb2.kingsideCastleW &&
        cb1.kingsideCastleB == cb2.kingsideCastleB &&
        cb1.queensideCastleW == cb2.queensideCastleW &&
        cb1.queensideCastleB == cb2.queensideCastleB &&
        cb1.halfmoves == cb2.halfmoves &&
        cb1.fullmoves == cb2.fullmoves)
    {
        for (int j = 0; j < 8; j++)
        {
            for (int i = 0; i < 8; i++)
            {
                if (!chessPieceCompare(cb1.board[i][j], cb2.board[i][j]))
                {
                    return false;
                }
            }
        }
        
    } else {
        return false;
    }

    return true;
}

void print_chess_board( ChessBoard cb ){
    std::cout << "  abcdefgh" << std::endl;
    for (int j = 0; j < 8; j++)
    {
        std::cout << char('8' - j) << " ";
        
        for (int i = 0; i < 8; i++)
        {
            std::cout << getCharByPiece(cb.board[i][j]);
        }

        std::cout << std::endl;
    
    }
}

void print_struct_info( ChessBoard cb ){
    std::cout << "En passant: " << cb.en_passant << std::endl;
    std::cout << "En passant polje: " << cb.en_passant_tile.first << " " << cb.en_passant_tile.second << std::endl;
    std::cout << "Halfmoves: " << cb.halfmoves << std::endl;
    std::cout << "Fullmoves: " << cb.fullmoves << std::endl;
    std::cout << "kingsideCastleB: " << cb.kingsideCastleB << std::endl;
    std::cout << "queensideCastleB: " << cb.queensideCastleB << std::endl;
    std::cout << "kingsideCastleW: " << cb.kingsideCastleW << std::endl;
    std::cout << "queensideCastleW: " << cb.queensideCastleW << std::endl;
    std::cout << "whiteOnMove: " << cb.whiteOnMove << std::endl;
}

std::vector<ChessBoard> possibleMoves( ChessBoard board ){
    std::vector<ChessBoard> moves;


    if (board.whiteOnMove == true)
    {
        for (int j = 0; j < 8; j++)
        {
            for (int i = 0; i < 8; i++)
            {
                if (board.board[i][j].color == WHITE)
                {
                    std::vector<ChessBoard> temp = piecePossibleMoves(board, i, j);
                    for (long long unsigned int i = 0; i < temp.size(); i++)
                    {
                        if (whiteKingCheck(temp[i]))
                        {
                            continue;
                        } else {
                            temp[i].whiteOnMove = false;
                            temp[i].halfmoves++;
                            moves.push_back(temp[i]);
                        }
                    }
                }
            }
        }

    } else {
        for (int j = 0; j < 8; j++)
        {
            for (int i = 0; i < 8; i++)
            {
                if (board.board[i][j].color == BLACK)
                {
                    std::vector<ChessBoard> temp = piecePossibleMoves(board, i, j);
                    for (long long unsigned int i = 0; i < temp.size(); i++)
                    {
                        if (blackKingCheck(temp[i]))
                        {
                            continue;
                        } else {
                            temp[i].whiteOnMove = true;
                            temp[i].halfmoves++;
                            temp[i].fullmoves++;
                            moves.push_back(temp[i]);
                        }
                    }
                }
            }
        }
    }

    return moves;
}

std::vector<ChessBoard> piecePossibleMoves( ChessBoard board, int x, int y ){
    std::vector<ChessBoard> moves;
    std::vector<ChessBoard> temp;

    if (board.board[x][y].color == WHITE)
    {
        switch (board.board[x][y].type)
        {
            case PAWN:
                temp = whitePawnMoves( board, x, y );
                for (int i = 0; i < (int)temp.size(); i++)
                    moves.push_back( temp[i] );
                break;
            
            case KNIGHT:
                temp = whiteKnightMoves( board, x, y );
                for (int i = 0; i < (int)temp.size(); i++)
                    moves.push_back( temp[i] );
                break;

            case BISHOP:
                temp = whiteBishopMoves( board, x, y );
                for (int i = 0; i < (int)temp.size(); i++)
                    moves.push_back( temp[i] );
                break;

            case ROOK:
                temp = whiteRookMoves( board, x, y );
                for (int i = 0; i < (int)temp.size(); i++)
                    moves.push_back( temp[i] );
                break;

            case QUEEN:
                temp = whiteQueenMoves( board, x, y );
                for (int i = 0; i < (int)temp.size(); i++)
                    moves.push_back( temp[i] );
                break;

            case KING:
                temp = whiteKingMoves( board, x, y );
                for (int i = 0; i < (int)temp.size(); i++)
                    moves.push_back( temp[i] );
                break;
            
            default:
                break;
        }
    } else if (board.board[x][y].color == BLACK)
    {
        switch (board.board[x][y].type)
        {
            case PAWN:
                temp = blackPawnMoves( board, x, y );
                for (int i = 0; i < (int)temp.size(); i++)
                    moves.push_back( temp[i] );
                break;
            
            case KNIGHT:
                temp = blackKnightMoves( board, x, y );
                for (int i = 0; i < (int)temp.size(); i++)
                    moves.push_back( temp[i] );
                break;

            case BISHOP:
                temp = blackBishopMoves( board, x, y );
                for (int i = 0; i < (int)temp.size(); i++)
                    moves.push_back( temp[i] );
                break;

            case ROOK:
                temp = blackRookMoves( board, x, y );
                for (int i = 0; i < (int)temp.size(); i++)
                    moves.push_back( temp[i] );
                break;

            case QUEEN:
                temp = blackQueenMoves( board, x, y );
                for (int i = 0; i < (int)temp.size(); i++)
                    moves.push_back( temp[i] );
                break;

            case KING:
                temp = blackKingMoves( board, x, y );
                for (int i = 0; i < (int)temp.size(); i++)
                    moves.push_back( temp[i] );
                break;
            
            default:
                break;
        }
    }
    
    return moves;    
}

std::vector<ChessBoard> blackPawnMoves( ChessBoard board, int x, int y ){
    std::vector<ChessBoard> moves;

    board.last_move_start = {x, y};

    //en passant
    if ( board.en_passant == true && board.en_passant_tile.second == y + 1 && ( board.en_passant_tile.first == x - 1 || board.en_passant_tile.first == x + 1 ) )
    {
        ChessBoard temp = board;
        temp.board[x][y].color = NO_COLOR;
        temp.board[x][y].type = EMPTY_TILE;
        temp.board[board.en_passant_tile.first][y].color = NO_COLOR;
        temp.board[board.en_passant_tile.first][y].type = EMPTY_TILE;
        temp.board[board.en_passant_tile.first][board.en_passant_tile.second].color = BLACK;
        temp.board[board.en_passant_tile.first][board.en_passant_tile.second].type = PAWN;
        temp.en_passant = false;
        temp.last_move_end = {board.en_passant_tile.first, board.en_passant_tile.second};
        moves.push_back(temp);
    }
    
    board.en_passant = false;

    //7 dupli pomak
    if ( y == 1 && board.board[x][y + 1].color == NO_COLOR && board.board[x][y + 2].color == NO_COLOR )
    {
        ChessBoard temp = board;
        temp.board[x][y + 2].color = BLACK;
        temp.board[x][y + 2].type = PAWN;
        temp.board[x][y].color = NO_COLOR;
        temp.board[x][y].type = EMPTY_TILE;
        temp.en_passant = true;
        temp.en_passant_tile = {x, y + 1};
        temp.last_move_end = {x, y + 2};
        moves.push_back(temp);
    }

    //8-3 pocetna pozicija, pomicanje
    if ( board.board[x][y + 1].color == NO_COLOR && y < 6 )
    {
        ChessBoard temp = board;
        temp.board[x][y + 1].color = BLACK;
        temp.board[x][y + 1].type = PAWN;
        temp.board[x][y].color = NO_COLOR;
        temp.board[x][y].type = EMPTY_TILE;
        temp.last_move_end = {x, y + 1};
        moves.push_back(temp);
    }
    
    //8-3 jedenje lijevo
    if ( x != 0 && board.board[x - 1][y + 1].color == WHITE && y < 6 )
    {
        ChessBoard temp = board;
        temp.board[x - 1][y + 1].color = BLACK;
        temp.board[x - 1][y + 1].type = PAWN;
        temp.board[x][y].color = NO_COLOR;
        temp.board[x][y].type = EMPTY_TILE;
        temp.last_move_end = {x - 1, y + 1};
        moves.push_back(temp);
    }

    //8-3 jedenje desno
    if ( x != 7 && board.board[x + 1][y + 1].color == WHITE && y < 6 )
    {
        ChessBoard temp = board;
        temp.board[x + 1][y + 1].color = BLACK;
        temp.board[x + 1][y + 1].type = PAWN;
        temp.board[x][y].color = NO_COLOR;
        temp.board[x][y].type = EMPTY_TILE;
        temp.last_move_end = {x + 1, y + 1};
        moves.push_back(temp);
    }

    //2 pomicanje
    if ( y == 6 && board.board[x][y + 1].color == NO_COLOR )
    {
        ChessBoard temp = board;
        temp.board[x][y].color = NO_COLOR;
        temp.board[x][y].type = EMPTY_TILE;
        temp.board[x][y + 1].color = BLACK;
        temp.board[x][y + 1].type = KNIGHT;
        temp.last_move_end = {x, y + 1};
        moves.push_back(temp);
        temp.board[x][y + 1].type = BISHOP;
        moves.push_back(temp);
        temp.board[x][y + 1].type = ROOK;
        moves.push_back(temp);
        temp.board[x][y + 1].type = QUEEN;
        moves.push_back(temp);
    }
    

    //2 jedenje lijevo
    if ( x != 0 && y == 6 && board.board[x - 1][y + 1].color == WHITE )
    {
        ChessBoard temp = board;
        temp.board[x][y].color = NO_COLOR;
        temp.board[x][y].type = EMPTY_TILE;
        temp.board[x - 1][y + 1].color = BLACK;
        temp.board[x - 1][y + 1].type = KNIGHT;
        temp.last_move_end = {x - 1, y + 1};
        moves.push_back(temp);
        temp.board[x - 1][y + 1].type = BISHOP;
        moves.push_back(temp);
        temp.board[x - 1][y + 1].type = ROOK;
        moves.push_back(temp);
        temp.board[x - 1][y + 1].type = QUEEN;
        moves.push_back(temp);
    }

    //2 jedenje desno
    if ( x != 7 && y == 6 && board.board[x + 1][y + 1].color == WHITE )
    {
        ChessBoard temp = board;
        temp.board[x][y].color = NO_COLOR;
        temp.board[x][y].type = EMPTY_TILE;
        temp.board[x + 1][y + 1].color = BLACK;
        temp.board[x + 1][y + 1].type = KNIGHT;
        temp.last_move_end = {x + 1, y + 1};
        moves.push_back(temp);
        temp.board[x + 1][y + 1].type = BISHOP;
        moves.push_back(temp);
        temp.board[x + 1][y + 1].type = ROOK;
        moves.push_back(temp);
        temp.board[x + 1][y + 1].type = QUEEN;
        moves.push_back(temp);
    }

    return moves;
}

std::vector<ChessBoard> whitePawnMoves( ChessBoard board, int x, int y ){
    std::vector<ChessBoard> moves;

    //en passant
    if ( board.en_passant == true && board.en_passant_tile.second == y - 1 && ( board.en_passant_tile.first == x - 1 || board.en_passant_tile.first == x + 1 ) )
    {
        ChessBoard temp = board;
        temp.board[x][y].color = NO_COLOR;
        temp.board[x][y].type = EMPTY_TILE;
        temp.board[board.en_passant_tile.first][y].color = NO_COLOR;
        temp.board[board.en_passant_tile.first][y].type = EMPTY_TILE;
        temp.board[board.en_passant_tile.first][board.en_passant_tile.second].color = WHITE;
        temp.board[board.en_passant_tile.first][board.en_passant_tile.second].type = PAWN;
        temp.en_passant = false;
        moves.push_back(temp);
    }
    
    board.en_passant = false;

    //7 dupli pomak
    if ( y == 6 && board.board[x][y - 1].color == NO_COLOR && board.board[x][y - 2].color == NO_COLOR )
    {
        ChessBoard temp = board;
        temp.board[x][y - 2].color = WHITE;
        temp.board[x][y - 2].type = PAWN;
        temp.board[x][y].color = NO_COLOR;
        temp.board[x][y].type = EMPTY_TILE;
        temp.en_passant = true;
        temp.en_passant_tile = {x, y - 1};
        moves.push_back(temp);
    }

    //6-1 pocetna pozicija, pomicanje
    if ( board.board[x][y - 1].color == NO_COLOR && y > 1 )
    {
        ChessBoard temp = board;
        temp.board[x][y - 1].color = WHITE;
        temp.board[x][y - 1].type = PAWN;
        temp.board[x][y].color = NO_COLOR;
        temp.board[x][y].type = EMPTY_TILE;
        moves.push_back(temp);
    }
    
    //6-1 jedenje lijevo
    if ( x != 0 && board.board[x - 1][y - 1].color == BLACK && y > 1 )
    {
        ChessBoard temp = board;
        temp.board[x - 1][y - 1].color = WHITE;
        temp.board[x - 1][y - 1].type = PAWN;
        temp.board[x][y].color = NO_COLOR;
        temp.board[x][y].type = EMPTY_TILE;
        moves.push_back(temp);
    }

    //6-1 jedenje desno
    if ( x != 7 && board.board[x + 1][y - 1].color == BLACK && y > 1 )
    {
        ChessBoard temp = board;
        temp.board[x + 1][y - 1].color = WHITE;
        temp.board[x + 1][y - 1].type = PAWN;
        temp.board[x][y].color = NO_COLOR;
        temp.board[x][y].type = EMPTY_TILE;
        moves.push_back(temp);
    }

    //7 pomicanje
    if ( y == 1 && board.board[x][y - 1].color == NO_COLOR )
    {
        ChessBoard temp = board;
        temp.board[x][y].color = NO_COLOR;
        temp.board[x][y].type = EMPTY_TILE;
        temp.board[x][y - 1].color = WHITE;
        temp.board[x][y - 1].type = KNIGHT;
        moves.push_back(temp);
        temp.board[x][y - 1].type = BISHOP;
        moves.push_back(temp);
        temp.board[x][y - 1].type = ROOK;
        moves.push_back(temp);
        temp.board[x][y - 1].type = QUEEN;
        moves.push_back(temp);
    }
    

    //7 jedenje lijevo
    if ( x != 0 && y == 1 && board.board[x - 1][y - 1].color == BLACK )
    {
        ChessBoard temp = board;
        temp.board[x][y].color = NO_COLOR;
        temp.board[x][y].type = EMPTY_TILE;
        temp.board[x - 1][y - 1].color = WHITE;
        temp.board[x - 1][y - 1].type = KNIGHT;
        moves.push_back(temp);
        temp.board[x - 1][y - 1].type = BISHOP;
        moves.push_back(temp);
        temp.board[x - 1][y - 1].type = ROOK;
        moves.push_back(temp);
        temp.board[x - 1][y - 1].type = QUEEN;
        moves.push_back(temp);
    }

    //7 jedenje desno
    if ( x != 7 && y == 1 && board.board[x + 1][y - 1].color == BLACK )
    {
        ChessBoard temp = board;
        temp.board[x][y].color = NO_COLOR;
        temp.board[x][y].type = EMPTY_TILE;
        temp.board[x + 1][y - 1].color = WHITE;
        temp.board[x + 1][y - 1].type = KNIGHT;
        moves.push_back(temp);
        temp.board[x + 1][y - 1].type = BISHOP;
        moves.push_back(temp);
        temp.board[x + 1][y - 1].type = ROOK;
        moves.push_back(temp);
        temp.board[x + 1][y - 1].type = QUEEN;
        moves.push_back(temp);
    }

    return moves;
}

std::vector<ChessBoard> blackKnightMoves( ChessBoard board, int x, int y ){
    std::vector<ChessBoard> moves;

    board.en_passant = false;

    if ( x - 2 >= 0 && y - 1 >= 0 && board.board[x - 2][y - 1].color != BLACK )
    {
        ChessBoard temp = board;
        temp.board[x][y].color = NO_COLOR;
        temp.board[x][y].type = EMPTY_TILE;
        temp.board[x - 2][y - 1].color = BLACK;
        temp.board[x - 2][y - 1].type = KNIGHT;
        moves.push_back(temp);
    }

    if ( x - 2 >= 0 && y + 1 <= 7 && board.board[x - 2][y + 1].color != BLACK )
    {
        ChessBoard temp = board;
        temp.board[x][y].color = NO_COLOR;
        temp.board[x][y].type = EMPTY_TILE;
        temp.board[x - 2][y + 1].color = BLACK;
        temp.board[x - 2][y + 1].type = KNIGHT;
        moves.push_back(temp);
    }

    if ( x - 1 >= 0 && y - 2 >= 0 && board.board[x - 1][y - 2].color != BLACK )
    {
        ChessBoard temp = board;
        temp.board[x][y].color = NO_COLOR;
        temp.board[x][y].type = EMPTY_TILE;
        temp.board[x - 1][y - 2].color = BLACK;
        temp.board[x - 1][y - 2].type = KNIGHT;
        moves.push_back(temp);
    }

    if ( x - 1 >= 0 && y + 2 <= 7 && board.board[x - 1][y + 2].color != BLACK )
    {
        ChessBoard temp = board;
        temp.board[x][y].color = NO_COLOR;
        temp.board[x][y].type = EMPTY_TILE;
        temp.board[x - 1][y + 2].color = BLACK;
        temp.board[x - 1][y + 2].type = KNIGHT;
        moves.push_back(temp);
    }
    
    if ( x + 1 <= 7 && y - 2 >= 0 && board.board[x + 1][y - 2].color != BLACK )
    {
        ChessBoard temp = board;
        temp.board[x][y].color = NO_COLOR;
        temp.board[x][y].type = EMPTY_TILE;
        temp.board[x + 1][y - 2].color = BLACK;
        temp.board[x + 1][y - 2].type = KNIGHT;
        moves.push_back(temp);
    }

    if ( x + 1 <= 7 && y + 2 <= 7 && board.board[x + 1][y + 2].color != BLACK )
    {
        ChessBoard temp = board;
        temp.board[x][y].color = NO_COLOR;
        temp.board[x][y].type = EMPTY_TILE;
        temp.board[x + 1][y + 2].color = BLACK;
        temp.board[x + 1][y + 2].type = KNIGHT;
        moves.push_back(temp);
    }

    if ( x + 2 <= 7 && y - 1 >= 0 && board.board[x + 2][y - 1].color != BLACK )
    {
        ChessBoard temp = board;
        temp.board[x][y].color = NO_COLOR;
        temp.board[x][y].type = EMPTY_TILE;
        temp.board[x + 2][y - 1].color = BLACK;
        temp.board[x + 2][y - 1].type = KNIGHT;
        moves.push_back(temp);
    }

    if ( x + 2 <= 7 && y + 1 <= 7 && board.board[x + 2][y + 1].color != BLACK )
    {
        ChessBoard temp = board;
        temp.board[x][y].color = NO_COLOR;
        temp.board[x][y].type = EMPTY_TILE;
        temp.board[x + 2][y + 1].color = BLACK;
        temp.board[x + 2][y + 1].type = KNIGHT;
        moves.push_back(temp);
    }

    return moves;
}

std::vector<ChessBoard> whiteKnightMoves( ChessBoard board, int x, int y ){
    std::vector<ChessBoard> moves;

    board.en_passant = false;

    if ( x - 2 >= 0 && y - 1 >= 0 && board.board[x - 2][y - 1].color != WHITE )
    {
        ChessBoard temp = board;
        temp.board[x][y].color = NO_COLOR;
        temp.board[x][y].type = EMPTY_TILE;
        temp.board[x - 2][y - 1].color = WHITE;
        temp.board[x - 2][y - 1].type = KNIGHT;
        moves.push_back(temp);
    }

    if ( x - 2 >= 0 && y + 1 <= 7 && board.board[x - 2][y + 1].color != WHITE )
    {
        ChessBoard temp = board;
        temp.board[x][y].color = NO_COLOR;
        temp.board[x][y].type = EMPTY_TILE;
        temp.board[x - 2][y + 1].color = WHITE;
        temp.board[x - 2][y + 1].type = KNIGHT;
        moves.push_back(temp);
    }

    if ( x - 1 >= 0 && y - 2 >= 0 && board.board[x - 1][y - 2].color != WHITE )
    {
        ChessBoard temp = board;
        temp.board[x][y].color = NO_COLOR;
        temp.board[x][y].type = EMPTY_TILE;
        temp.board[x - 1][y - 2].color = WHITE;
        temp.board[x - 1][y - 2].type = KNIGHT;
        moves.push_back(temp);
    }

    if ( x - 1 >= 0 && y + 2 <= 7 && board.board[x - 1][y + 2].color != WHITE )
    {
        ChessBoard temp = board;
        temp.board[x][y].color = NO_COLOR;
        temp.board[x][y].type = EMPTY_TILE;
        temp.board[x - 1][y + 2].color = WHITE;
        temp.board[x - 1][y + 2].type = KNIGHT;
        moves.push_back(temp);
    }
    
    if ( x + 1 <= 7 && y - 2 >= 0 && board.board[x + 1][y - 2].color != WHITE )
    {
        ChessBoard temp = board;
        temp.board[x][y].color = NO_COLOR;
        temp.board[x][y].type = EMPTY_TILE;
        temp.board[x + 1][y - 2].color = WHITE;
        temp.board[x + 1][y - 2].type = KNIGHT;
        moves.push_back(temp);
    }

    if ( x + 1 <= 7 && y + 2 <= 7 && board.board[x + 1][y + 2].color != WHITE )
    {
        ChessBoard temp = board;
        temp.board[x][y].color = NO_COLOR;
        temp.board[x][y].type = EMPTY_TILE;
        temp.board[x + 1][y + 2].color = WHITE;
        temp.board[x + 1][y + 2].type = KNIGHT;
        moves.push_back(temp);
    }

    if ( x + 2 <= 7 && y - 1 >= 0 && board.board[x + 2][y - 1].color != WHITE )
    {
        ChessBoard temp = board;
        temp.board[x][y].color = NO_COLOR;
        temp.board[x][y].type = EMPTY_TILE;
        temp.board[x + 2][y - 1].color = WHITE;
        temp.board[x + 2][y - 1].type = KNIGHT;
        moves.push_back(temp);
    }

    if ( x + 2 <= 7 && y + 1 <= 7 && board.board[x + 2][y + 1].color != WHITE )
    {
        ChessBoard temp = board;
        temp.board[x][y].color = NO_COLOR;
        temp.board[x][y].type = EMPTY_TILE;
        temp.board[x + 2][y + 1].color = WHITE;
        temp.board[x + 2][y + 1].type = KNIGHT;
        moves.push_back(temp);
    }

    return moves;
}

std::vector<ChessBoard> blackBishopMoves( ChessBoard board, int x, int y ){
    std::vector<ChessBoard> moves;

    board.en_passant = false;

    int temp_x = x - 1, temp_y = y - 1;

    //Gore lijevo
    while (temp_x >= 0 && temp_y >= 0)
    {
        if (board.board[temp_x][temp_y].color == BLACK)
        {
            break;
        } else if (board.board[temp_x][temp_y].color == WHITE)
        {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[temp_x][temp_y].color = BLACK;
            temp.board[temp_x][temp_y].type = BISHOP;
            moves.push_back(temp);
            break;
        } else {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[temp_x][temp_y].color = BLACK;
            temp.board[temp_x][temp_y].type = BISHOP;
            moves.push_back(temp);
            temp_x--;
            temp_y--;
        } 
    }
    
    //Gore desno
    temp_x = x + 1;
    temp_y = y - 1;
    while (temp_x <= 7 && temp_y >= 0)
    {
        if (board.board[temp_x][temp_y].color == BLACK)
        {
            break;
        } else if (board.board[temp_x][temp_y].color == WHITE)
        {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[temp_x][temp_y].color = BLACK;
            temp.board[temp_x][temp_y].type = BISHOP;
            moves.push_back(temp);
            break;
        } else {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[temp_x][temp_y].color = BLACK;
            temp.board[temp_x][temp_y].type = BISHOP;
            moves.push_back(temp);
            temp_x++;
            temp_y--;
        }
    }

    //Dolje lijevo
    temp_x = x - 1;
    temp_y = y + 1;
    while (temp_x >= 0 && temp_y <= 7)
    {
        if (board.board[temp_x][temp_y].color == BLACK)
        {
            break;
        } else if (board.board[temp_x][temp_y].color == WHITE)
        {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[temp_x][temp_y].color = BLACK;
            temp.board[temp_x][temp_y].type = BISHOP;
            moves.push_back(temp);
            break;
        } else {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[temp_x][temp_y].color = BLACK;
            temp.board[temp_x][temp_y].type = BISHOP;
            moves.push_back(temp);
            temp_x--;
            temp_y++;
        } 
    }

    //Dolje desno
    temp_x = x + 1;
    temp_y = y + 1;
    while (temp_x <= 7 && temp_y <= 7)
    {
        if (board.board[temp_x][temp_y].color == BLACK)
        {
            break;
        } else if (board.board[temp_x][temp_y].color == WHITE)
        {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[temp_x][temp_y].color = BLACK;
            temp.board[temp_x][temp_y].type = BISHOP;
            moves.push_back(temp);
            break;
        } else {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[temp_x][temp_y].color = BLACK;
            temp.board[temp_x][temp_y].type = BISHOP;
            moves.push_back(temp);
            temp_x++;
            temp_y++;
        } 
    }

    return moves;
}

std::vector<ChessBoard> whiteBishopMoves( ChessBoard board, int x, int y ){
    std::vector<ChessBoard> moves;

    board.en_passant = false;

    board.en_passant = false;

    int temp_x = x - 1, temp_y = y - 1;

    //Gore lijevo
    while (temp_x >= 0 && temp_y >= 0)
    {
        if (board.board[temp_x][temp_y].color == WHITE)
        {
            break;
        } else if (board.board[temp_x][temp_y].color == BLACK)
        {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[temp_x][temp_y].color = WHITE;
            temp.board[temp_x][temp_y].type = BISHOP;
            moves.push_back(temp);
            break;
        } else {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[temp_x][temp_y].color = WHITE;
            temp.board[temp_x][temp_y].type = BISHOP;
            moves.push_back(temp);
            temp_x--;
            temp_y--;
        } 
    }
    
    //Gore desno
    temp_x = x + 1;
    temp_y = y - 1;
    while (temp_x <= 7 && temp_y >= 0)
    {
        if (board.board[temp_x][temp_y].color == WHITE)
        {
            break;
        } else if (board.board[temp_x][temp_y].color == BLACK)
        {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[temp_x][temp_y].color = WHITE;
            temp.board[temp_x][temp_y].type = BISHOP;
            moves.push_back(temp);
            break;
        } else {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[temp_x][temp_y].color = WHITE;
            temp.board[temp_x][temp_y].type = BISHOP;
            moves.push_back(temp);
            temp_x++;
            temp_y--;
        }
    }

    //Dolje lijevo
    temp_x = x - 1;
    temp_y = y + 1;
    while (temp_x >= 0 && temp_y <= 7)
    {
        if (board.board[temp_x][temp_y].color == WHITE)
        {
            break;
        } else if (board.board[temp_x][temp_y].color == BLACK)
        {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[temp_x][temp_y].color = WHITE;
            temp.board[temp_x][temp_y].type = BISHOP;
            moves.push_back(temp);
            break;
        } else {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[temp_x][temp_y].color = WHITE;
            temp.board[temp_x][temp_y].type = BISHOP;
            moves.push_back(temp);
            temp_x--;
            temp_y++;
        } 
    }

    //Dolje desno
    temp_x = x + 1;
    temp_y = y + 1;
    while (temp_x <= 7 && temp_y <= 7)
    {
        if (board.board[temp_x][temp_y].color == WHITE)
        {
            break;
        } else if (board.board[temp_x][temp_y].color == BLACK)
        {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[temp_x][temp_y].color = WHITE;
            temp.board[temp_x][temp_y].type = BISHOP;
            moves.push_back(temp);
            break;
        } else {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[temp_x][temp_y].color = WHITE;
            temp.board[temp_x][temp_y].type = BISHOP;
            moves.push_back(temp);
            temp_x++;
            temp_y++;
        } 
    }

    return moves;
}

std::vector<ChessBoard> blackRookMoves( ChessBoard board, int x, int y ){
    std::vector<ChessBoard> moves;

    if (x == 0 && y == 0)
    {
        board.queensideCastleB = false;
    }

    if (x == 7 && y == 0)
    {
        board.kingsideCastleB = false;
    }

    board.en_passant = false;

    int temp_y = y - 1;

    //Gore
    while (temp_y >= 0)
    {
        if (board.board[x][temp_y].color == BLACK)
        {
            break;
        } else if (board.board[x][temp_y].color == WHITE)
        {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[x][temp_y].color = BLACK;
            temp.board[x][temp_y].type = ROOK;
            moves.push_back(temp);
            break;
        } else {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[x][temp_y].color = BLACK;
            temp.board[x][temp_y].type = ROOK;
            moves.push_back(temp);
            temp_y--;
        } 
    }

    //Dolje
    temp_y = y + 1;
    while (temp_y <= 7)
    {
        if (board.board[x][temp_y].color == BLACK)
        {
            break;
        } else if (board.board[x][temp_y].color == WHITE)
        {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[x][temp_y].color = BLACK;
            temp.board[x][temp_y].type = ROOK;
            moves.push_back(temp);
            break;
        } else {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[x][temp_y].color = BLACK;
            temp.board[x][temp_y].type = ROOK;
            moves.push_back(temp);
            temp_y++;
        } 
    }

    //Lijevo
    int temp_x = x - 1;
    while (temp_x >= 0)
    {
        if (board.board[temp_x][y].color == BLACK)
        {
            break;
        } else if (board.board[temp_x][y].color == WHITE)
        {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[temp_x][y].color = BLACK;
            temp.board[temp_x][y].type = ROOK;
            moves.push_back(temp);
            break;
        } else {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[temp_x][y].color = BLACK;
            temp.board[temp_x][y].type = ROOK;
            moves.push_back(temp);
            temp_x--;
        } 
    }

    //Desno
    temp_x = x + 1;
    while (temp_x <= 7)
    {
        if (board.board[temp_x][y].color == BLACK)
        {
            break;
        } else if (board.board[temp_x][y].color == WHITE)
        {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[temp_x][y].color = BLACK;
            temp.board[temp_x][y].type = ROOK;
            moves.push_back(temp);
            break;
        } else {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[temp_x][y].color = BLACK;
            temp.board[temp_x][y].type = ROOK;
            moves.push_back(temp);
            temp_x++;
        } 
    }

    return moves;
}

std::vector<ChessBoard> whiteRookMoves( ChessBoard board, int x, int y ){
    std::vector<ChessBoard> moves;

    board.en_passant = false;

    if (x == 0 && y == 7)
    {
        board.queensideCastleW = false;
    }

    if (x == 7 && y == 7)
    {
        board.kingsideCastleW = false;
    }
    
    

    int temp_y = y - 1;

    //Gore
    while (temp_y >= 0)
    {
        if (board.board[x][temp_y].color == WHITE)
        {
            break;
        } else if (board.board[x][temp_y].color == BLACK)
        {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[x][temp_y].color = WHITE;
            temp.board[x][temp_y].type = ROOK;
            moves.push_back(temp);
            break;
        } else {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[x][temp_y].color = WHITE;
            temp.board[x][temp_y].type = ROOK;
            moves.push_back(temp);
            temp_y--;
        } 
    }

    //Dolje
    temp_y = y + 1;
    while (temp_y <= 7)
    {
        if (board.board[x][temp_y].color == WHITE)
        {
            break;
        } else if (board.board[x][temp_y].color == BLACK)
        {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[x][temp_y].color = WHITE;
            temp.board[x][temp_y].type = ROOK;
            moves.push_back(temp);
            break;
        } else {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[x][temp_y].color = WHITE;
            temp.board[x][temp_y].type = ROOK;
            moves.push_back(temp);
            temp_y++;
        } 
    }

    //Lijevo
    int temp_x = x - 1;
    while (temp_x >= 0)
    {
        if (board.board[temp_x][y].color == WHITE)
        {
            break;
        } else if (board.board[temp_x][y].color == BLACK)
        {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[temp_x][y].color = WHITE;
            temp.board[temp_x][y].type = ROOK;
            moves.push_back(temp);
            break;
        } else {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[temp_x][y].color = WHITE;
            temp.board[temp_x][y].type = ROOK;
            moves.push_back(temp);
            temp_x--;
        } 
    }

    //Desno
    temp_x = x + 1;
    while (temp_x <= 7)
    {
        if (board.board[temp_x][y].color == WHITE)
        {
            break;
        } else if (board.board[temp_x][y].color == BLACK)
        {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[temp_x][y].color = WHITE;
            temp.board[temp_x][y].type = ROOK;
            moves.push_back(temp);
            break;
        } else {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[temp_x][y].color = WHITE;
            temp.board[temp_x][y].type = ROOK;
            moves.push_back(temp);
            temp_x++;
        } 
    }

    return moves;
}

std::vector<ChessBoard> blackQueenMoves( ChessBoard board, int x, int y ){
    std::vector<ChessBoard> moves;

    board.en_passant = false;
    
    int temp_y = y - 1;

    //Gore
    while (temp_y >= 0)
    {
        if (board.board[x][temp_y].color == BLACK)
        {
            break;
        } else if (board.board[x][temp_y].color == WHITE)
        {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[x][temp_y].color = BLACK;
            temp.board[x][temp_y].type = QUEEN;
            moves.push_back(temp);
            break;
        } else {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[x][temp_y].color = BLACK;
            temp.board[x][temp_y].type = QUEEN;
            moves.push_back(temp);
            temp_y--;
        } 
    }

    //Dolje
    temp_y = y + 1;
    while (temp_y <= 7)
    {
        if (board.board[x][temp_y].color == BLACK)
        {
            break;
        } else if (board.board[x][temp_y].color == WHITE)
        {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[x][temp_y].color = BLACK;
            temp.board[x][temp_y].type = QUEEN;
            moves.push_back(temp);
            break;
        } else {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[x][temp_y].color = BLACK;
            temp.board[x][temp_y].type = QUEEN;
            moves.push_back(temp);
            temp_y++;
        } 
    }

    //Lijevo
    int temp_x = x - 1;
    while (temp_x >= 0)
    {
        if (board.board[temp_x][y].color == BLACK)
        {
            break;
        } else if (board.board[temp_x][y].color == WHITE)
        {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[temp_x][y].color = BLACK;
            temp.board[temp_x][y].type = QUEEN;
            moves.push_back(temp);
            break;
        } else {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[temp_x][y].color = BLACK;
            temp.board[temp_x][y].type = QUEEN;
            moves.push_back(temp);
            temp_x--;
        } 
    }

    //Desno
    temp_x = x + 1;
    while (temp_x <= 7)
    {
        if (board.board[temp_x][y].color == BLACK)
        {
            break;
        } else if (board.board[temp_x][y].color == WHITE)
        {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[temp_x][y].color = BLACK;
            temp.board[temp_x][y].type = QUEEN;
            moves.push_back(temp);
            break;
        } else {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[temp_x][y].color = BLACK;
            temp.board[temp_x][y].type = QUEEN;
            moves.push_back(temp);
            temp_x++;
        } 
    }

    temp_x = x - 1; 
    temp_y = y - 1;

    //Gore lijevo
    while (temp_x >= 0 && temp_y >= 0)
    {
        if (board.board[temp_x][temp_y].color == BLACK)
        {
            break;
        } else if (board.board[temp_x][temp_y].color == WHITE)
        {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[temp_x][temp_y].color = BLACK;
            temp.board[temp_x][temp_y].type = QUEEN;
            moves.push_back(temp);
            break;
        } else {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[temp_x][temp_y].color = BLACK;
            temp.board[temp_x][temp_y].type = QUEEN;
            moves.push_back(temp);
            temp_x--;
            temp_y--;
        } 
    }
    
    //Gore desno
    temp_x = x + 1;
    temp_y = y - 1;
    while (temp_x <= 7 && temp_y >= 0)
    {
        if (board.board[temp_x][temp_y].color == BLACK)
        {
            break;
        } else if (board.board[temp_x][temp_y].color == WHITE)
        {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[temp_x][temp_y].color = BLACK;
            temp.board[temp_x][temp_y].type = QUEEN;
            moves.push_back(temp);
            break;
        } else {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[temp_x][temp_y].color = BLACK;
            temp.board[temp_x][temp_y].type = QUEEN;
            moves.push_back(temp);
            temp_x++;
            temp_y--;
        }
    }

    //Dolje lijevo
    temp_x = x - 1;
    temp_y = y + 1;
    while (temp_x >= 0 && temp_y <= 7)
    {
        if (board.board[temp_x][temp_y].color == BLACK)
        {
            break;
        } else if (board.board[temp_x][temp_y].color == WHITE)
        {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[temp_x][temp_y].color = BLACK;
            temp.board[temp_x][temp_y].type = QUEEN;
            moves.push_back(temp);
            break;
        } else {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[temp_x][temp_y].color = BLACK;
            temp.board[temp_x][temp_y].type = QUEEN;
            moves.push_back(temp);
            temp_x--;
            temp_y++;
        } 
    }

    //Dolje desno
    temp_x = x + 1;
    temp_y = y + 1;
    while (temp_x <= 7 && temp_y <= 7)
    {
        if (board.board[temp_x][temp_y].color == BLACK)
        {
            break;
        } else if (board.board[temp_x][temp_y].color == WHITE)
        {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[temp_x][temp_y].color = BLACK;
            temp.board[temp_x][temp_y].type = QUEEN;
            moves.push_back(temp);
            break;
        } else {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[temp_x][temp_y].color = BLACK;
            temp.board[temp_x][temp_y].type = QUEEN;
            moves.push_back(temp);
            temp_x++;
            temp_y++;
        } 
    }


    return moves;
}

std::vector<ChessBoard> whiteQueenMoves( ChessBoard board, int x, int y ){
    std::vector<ChessBoard> moves;

    board.en_passant = false;

    int temp_y = y - 1;

    //Gore
    while (temp_y >= 0)
    {
        if (board.board[x][temp_y].color == WHITE)
        {
            break;
        } else if (board.board[x][temp_y].color == BLACK)
        {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[x][temp_y].color = WHITE;
            temp.board[x][temp_y].type = QUEEN;
            moves.push_back(temp);
            break;
        } else {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[x][temp_y].color = WHITE;
            temp.board[x][temp_y].type = QUEEN;
            moves.push_back(temp);
            temp_y--;
        } 
    }

    //Dolje
    temp_y = y + 1;
    while (temp_y <= 7)
    {
        if (board.board[x][temp_y].color == WHITE)
        {
            break;
        } else if (board.board[x][temp_y].color == BLACK)
        {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[x][temp_y].color = WHITE;
            temp.board[x][temp_y].type = QUEEN;
            moves.push_back(temp);
            break;
        } else {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[x][temp_y].color = WHITE;
            temp.board[x][temp_y].type = QUEEN;
            moves.push_back(temp);
            temp_y++;
        } 
    }

    //Lijevo
    int temp_x = x - 1;
    while (temp_x >= 0)
    {
        if (board.board[temp_x][y].color == WHITE)
        {
            break;
        } else if (board.board[temp_x][y].color == BLACK)
        {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[temp_x][y].color = WHITE;
            temp.board[temp_x][y].type = QUEEN;
            moves.push_back(temp);
            break;
        } else {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[temp_x][y].color = WHITE;
            temp.board[temp_x][y].type = QUEEN;
            moves.push_back(temp);
            temp_x--;
        } 
    }

    //Desno
    temp_x = x + 1;
    while (temp_x <= 7)
    {
        if (board.board[temp_x][y].color == WHITE)
        {
            break;
        } else if (board.board[temp_x][y].color == BLACK)
        {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[temp_x][y].color = WHITE;
            temp.board[temp_x][y].type = QUEEN;
            moves.push_back(temp);
            break;
        } else {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[temp_x][y].color = WHITE;
            temp.board[temp_x][y].type = QUEEN;
            moves.push_back(temp);
            temp_x++;
        } 
    }

    temp_x = x - 1; 
    temp_y = y - 1;

    //Gore lijevo
    while (temp_x >= 0 && temp_y >= 0)
    {
        if (board.board[temp_x][temp_y].color == WHITE)
        {
            break;
        } else if (board.board[temp_x][temp_y].color == BLACK)
        {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[temp_x][temp_y].color = WHITE;
            temp.board[temp_x][temp_y].type = QUEEN;
            moves.push_back(temp);
            break;
        } else {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[temp_x][temp_y].color = WHITE;
            temp.board[temp_x][temp_y].type = QUEEN;
            moves.push_back(temp);
            temp_x--;
            temp_y--;
        } 
    }
    
    //Gore desno
    temp_x = x + 1;
    temp_y = y - 1;
    while (temp_x <= 7 && temp_y >= 0)
    {
        if (board.board[temp_x][temp_y].color == WHITE)
        {
            break;
        } else if (board.board[temp_x][temp_y].color == BLACK)
        {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[temp_x][temp_y].color = WHITE;
            temp.board[temp_x][temp_y].type = QUEEN;
            moves.push_back(temp);
            break;
        } else {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[temp_x][temp_y].color = WHITE;
            temp.board[temp_x][temp_y].type = QUEEN;
            moves.push_back(temp);
            temp_x++;
            temp_y--;
        }
    }

    //Dolje lijevo
    temp_x = x - 1;
    temp_y = y + 1;
    while (temp_x >= 0 && temp_y <= 7)
    {
        if (board.board[temp_x][temp_y].color == WHITE)
        {
            break;
        } else if (board.board[temp_x][temp_y].color == BLACK)
        {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[temp_x][temp_y].color = WHITE;
            temp.board[temp_x][temp_y].type = QUEEN;
            moves.push_back(temp);
            break;
        } else {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[temp_x][temp_y].color = WHITE;
            temp.board[temp_x][temp_y].type = QUEEN;
            moves.push_back(temp);
            temp_x--;
            temp_y++;
        } 
    }

    //Dolje desno
    temp_x = x + 1;
    temp_y = y + 1;
    while (temp_x <= 7 && temp_y <= 7)
    {
        if (board.board[temp_x][temp_y].color == WHITE)
        {
            break;
        } else if (board.board[temp_x][temp_y].color == BLACK)
        {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[temp_x][temp_y].color = WHITE;
            temp.board[temp_x][temp_y].type = QUEEN;
            moves.push_back(temp);
            break;
        } else {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[temp_x][temp_y].color = WHITE;
            temp.board[temp_x][temp_y].type = QUEEN;
            moves.push_back(temp);
            temp_x++;
            temp_y++;
        } 
    }

    return moves;
}

std::vector<ChessBoard> blackKingMoves( ChessBoard board, int x, int y ){
    std::vector<ChessBoard> moves;

    //Rokada
    if (board.kingsideCastleB && x == 4 && y == 0 && board.board[7][0].color == BLACK && board.board[7][0].type == ROOK && board.board[5][0].color == NO_COLOR && board.board[6][0].color == NO_COLOR && !tileIsAttackedByWhite(board, 4, 0) && !tileIsAttackedByWhite(board, 5, 0) && !tileIsAttackedByWhite(board, 6, 0))  
    {
        board.queensideCastleB = false;
        board.kingsideCastleB = false;

        ChessBoard temp = board;
        temp.board[7][0].color = NO_COLOR;
        temp.board[7][0].type = EMPTY_TILE;
        temp.board[4][0].color = NO_COLOR;
        temp.board[4][0].type = EMPTY_TILE;
        temp.board[5][0].color = BLACK;
        temp.board[5][0].type = ROOK;
        temp.board[6][0].color = BLACK;
        temp.board[6][0].type = KING;
        moves.push_back(temp);
    }
    
    if (board.queensideCastleB && x == 4 && y == 0 && board.board[0][0].color == BLACK && board.board[0][0].type == ROOK && board.board[3][0].color == NO_COLOR && board.board[2][0].color == NO_COLOR && board.board[1][0].color == NO_COLOR && !tileIsAttackedByWhite(board, 4, 0) && !tileIsAttackedByWhite(board, 3, 0) && !tileIsAttackedByWhite(board, 2, 0))
    {
        board.queensideCastleB = false;
        board.kingsideCastleB = false;

        ChessBoard temp = board;
        temp.board[0][0].color = NO_COLOR;
        temp.board[0][0].type = EMPTY_TILE;
        temp.board[4][0].color = NO_COLOR;
        temp.board[4][0].type = EMPTY_TILE;
        temp.board[3][0].color = BLACK;
        temp.board[3][0].type = ROOK;
        temp.board[2][0].color = BLACK;
        temp.board[2][0].type = KING;
        moves.push_back(temp);
    }
    
    board.queensideCastleB = false;
    board.kingsideCastleB = false;

    board.en_passant = false;

    if (x > 0)
    {
        //Lijevo
        if (board.board[x - 1][y].color != BLACK)
        {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[x - 1][y].color = BLACK;
            temp.board[x - 1][y].type = KING;
            moves.push_back(temp);
        }
        
        //Gore lijevo
        if (y > 0 && board.board[x - 1][y - 1].color != BLACK)
        {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[x - 1][y - 1].color = BLACK;
            temp.board[x - 1][y - 1].type = KING;
            moves.push_back(temp);
        } 
        
        //Dolje lijevo
        if (y < 7 && board.board[x - 1][y + 1].color != BLACK)
        {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[x - 1][y + 1].color = BLACK;
            temp.board[x - 1][y + 1].type = KING;
            moves.push_back(temp);
        }
    }
    
    if (x < 7)
    {
        //Desno
        if (board.board[x + 1][y].color != BLACK)
        {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[x + 1][y].color = BLACK;
            temp.board[x + 1][y].type = KING;
            moves.push_back(temp);
        }
        
        //Gore desno
        if (y > 0 && board.board[x + 1][y - 1].color != BLACK)
        {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[x + 1][y - 1].color = BLACK;
            temp.board[x + 1][y - 1].type = KING;
            moves.push_back(temp);
        } 
        
        //Dolje desno
        if (y < 7 && board.board[x + 1][y + 1].color != BLACK)
        {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[x + 1][y + 1].color = BLACK;
            temp.board[x + 1][y + 1].type = KING;
            moves.push_back(temp);
        }
    }
    
    //Gore
    if (y > 0 && board.board[x][y - 1].color != BLACK)
    {
        ChessBoard temp = board;
        temp.board[x][y].color = NO_COLOR;
        temp.board[x][y].type = EMPTY_TILE;
        temp.board[x][y - 1].color = BLACK;
        temp.board[x][y - 1].type = KING;
        moves.push_back(temp);
    }
    
    //Dolje
    if (y < 7 && board.board[x][y + 1].color != BLACK)
    {
        ChessBoard temp = board;
        temp.board[x][y].color = NO_COLOR;
        temp.board[x][y].type = EMPTY_TILE;
        temp.board[x][y + 1].color = BLACK;
        temp.board[x][y + 1].type = KING;
        moves.push_back(temp);
    }

    return moves;
}

std::vector<ChessBoard> whiteKingMoves( ChessBoard board, int x, int y ){
    std::vector<ChessBoard> moves;

    //Rokada
    if (board.kingsideCastleW && x == 4 && y == 7 && board.board[7][7].color == WHITE && board.board[7][7].type == ROOK && board.board[5][7].color == NO_COLOR && board.board[6][7].color == NO_COLOR && !tileIsAttackedByBlack(board, 4, 7) && !tileIsAttackedByBlack(board, 5, 7) && !tileIsAttackedByBlack(board, 6, 7))  
    {
        board.queensideCastleW = false;
        board.kingsideCastleW = false;

        ChessBoard temp = board;
        temp.board[7][7].color = NO_COLOR;
        temp.board[7][7].type = EMPTY_TILE;
        temp.board[4][7].color = NO_COLOR;
        temp.board[4][7].type = EMPTY_TILE;
        temp.board[5][7].color = WHITE;
        temp.board[5][7].type = ROOK;
        temp.board[6][7].color = WHITE;
        temp.board[6][7].type = KING;
        moves.push_back(temp);
    }
    
    if (board.queensideCastleW && x == 4 && y == 7 && board.board[0][7].color == WHITE && board.board[0][7].type == ROOK && board.board[3][7].color == NO_COLOR && board.board[2][7].color == NO_COLOR && board.board[1][7].color == NO_COLOR && !tileIsAttackedByBlack(board, 4, 7) && !tileIsAttackedByBlack(board, 3, 7) && !tileIsAttackedByBlack(board, 2, 7))
    {
        board.queensideCastleW = false;
        board.kingsideCastleW = false;

        ChessBoard temp = board;
        temp.board[0][7].color = NO_COLOR;
        temp.board[0][7].type = EMPTY_TILE;
        temp.board[4][7].color = NO_COLOR;
        temp.board[4][7].type = EMPTY_TILE;
        temp.board[3][7].color = WHITE;
        temp.board[3][7].type = ROOK;
        temp.board[2][7].color = WHITE;
        temp.board[2][7].type = KING;
        moves.push_back(temp);
    }
    
    board.queensideCastleW = false;
    board.kingsideCastleW = false;

    board.en_passant = false;

    if (x > 0)
    {
        //Lijevo
        if (board.board[x - 1][y].color != WHITE)
        {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[x - 1][y].color = WHITE;
            temp.board[x - 1][y].type = KING;
            moves.push_back(temp);
        }
        
        //Gore lijevo
        if (y > 0 && board.board[x - 1][y - 1].color != WHITE)
        {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[x - 1][y - 1].color = WHITE;
            temp.board[x - 1][y - 1].type = KING;
            moves.push_back(temp);
        } 
        
        //Dolje lijevo
        if (y < 7 && board.board[x - 1][y + 1].color != WHITE)
        {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[x - 1][y + 1].color = WHITE;
            temp.board[x - 1][y + 1].type = KING;
            moves.push_back(temp);
        }
    }
    
    if (x < 7)
    {
        //Desno
        if (board.board[x + 1][y].color != WHITE)
        {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[x + 1][y].color = WHITE;
            temp.board[x + 1][y].type = KING;
            moves.push_back(temp);
        }
        
        //Gore desno
        if (y > 0 && board.board[x + 1][y - 1].color != WHITE)
        {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[x + 1][y - 1].color = WHITE;
            temp.board[x + 1][y - 1].type = KING;
            moves.push_back(temp);
        } 
        
        //Dolje desno
        if (y < 7 && board.board[x + 1][y + 1].color != WHITE)
        {
            ChessBoard temp = board;
            temp.board[x][y].color = NO_COLOR;
            temp.board[x][y].type = EMPTY_TILE;
            temp.board[x + 1][y + 1].color = WHITE;
            temp.board[x + 1][y + 1].type = KING;
            moves.push_back(temp);
        }
    }
    
    //Gore
    if (y > 0 && board.board[x][y - 1].color != WHITE)
    {
        ChessBoard temp = board;
        temp.board[x][y].color = NO_COLOR;
        temp.board[x][y].type = EMPTY_TILE;
        temp.board[x][y - 1].color = WHITE;
        temp.board[x][y - 1].type = KING;
        moves.push_back(temp);
    }
    
    //Dolje
    if (y < 7 && board.board[x][y + 1].color != WHITE)
    {
        ChessBoard temp = board;
        temp.board[x][y].color = NO_COLOR;
        temp.board[x][y].type = EMPTY_TILE;
        temp.board[x][y + 1].color = WHITE;
        temp.board[x][y + 1].type = KING;
        moves.push_back(temp);
    }

    return moves;
}

bool tileIsAttackedByWhite( ChessBoard cb, int x, int y ){

    //Lovac, top, kraljica
    int temp_y = y - 1;

    //Gore
    while (temp_y >= 0)
    {
        if (cb.board[x][temp_y].color == BLACK || (cb.board[x][temp_y].color == WHITE && !(cb.board[x][temp_y].type == QUEEN || cb.board[x][temp_y].type == ROOK)))
        {
            break;
        } else if (cb.board[x][temp_y].color == WHITE && (cb.board[x][temp_y].type == QUEEN || cb.board[x][temp_y].type == ROOK))
        {
            return true;
        } else {
            temp_y--;
        } 
    }

    //Dolje
    temp_y = y + 1;
    while (temp_y <= 7)
    {
        if (cb.board[x][temp_y].color == BLACK || (cb.board[x][temp_y].color == WHITE && !(cb.board[x][temp_y].type == QUEEN || cb.board[x][temp_y].type == ROOK)))
        {
            break;
        } else if (cb.board[x][temp_y].color == WHITE && (cb.board[x][temp_y].type == QUEEN || cb.board[x][temp_y].type == ROOK))
        {
            return true;
        } else {
            temp_y++;
        } 
    }

    //Lijevo
    int temp_x = x - 1;
    while (temp_x >= 0)
    {
        if (cb.board[temp_x][y].color == BLACK || (cb.board[temp_x][y].color == WHITE && !(cb.board[temp_x][y].type == QUEEN || cb.board[temp_x][y].type == ROOK)))
        {
            break;
        } else if (cb.board[temp_x][y].color == WHITE && (cb.board[temp_x][y].type == QUEEN || cb.board[temp_x][y].type == ROOK))
        {
            return true;
        } else {
            temp_x--;
        } 
    }

    //Desno
    temp_x = x + 1;
    while (temp_x <= 7)
    {
        if (cb.board[temp_x][y].color == BLACK || (cb.board[temp_x][y].color == WHITE && !(cb.board[temp_x][y].type == QUEEN || cb.board[temp_x][y].type == ROOK)))
        {
            break;
        } else if (cb.board[temp_x][y].color == WHITE && (cb.board[temp_x][y].type == QUEEN || cb.board[temp_x][y].type == ROOK))
        {
            return true;
        } else {
            temp_x++;
        } 
    }

    temp_x = x - 1; 
    temp_y = y - 1;

    //Gore lijevo
    while (temp_x >= 0 && temp_y >= 0)
    {
        if (cb.board[temp_x][temp_y].color == BLACK || (cb.board[temp_x][temp_y].color == WHITE && !(cb.board[temp_x][temp_y].type == QUEEN || cb.board[temp_x][temp_y].type == BISHOP)))
        {
            break;
        } else if (cb.board[temp_x][temp_y].color == WHITE && (cb.board[temp_x][temp_y].type == QUEEN || cb.board[temp_x][temp_y].type == BISHOP))
        {
            return true;
        } else {
            temp_x--;
            temp_y--;
        } 
    }
    
    //Gore desno
    temp_x = x + 1;
    temp_y = y - 1;
    while (temp_x <= 7 && temp_y >= 0)
    {
        if (cb.board[temp_x][temp_y].color == BLACK || (cb.board[temp_x][temp_y].color == WHITE && !(cb.board[temp_x][temp_y].type == QUEEN || cb.board[temp_x][temp_y].type == BISHOP)))
        {
            break;
        } else if (cb.board[temp_x][temp_y].color == WHITE && (cb.board[temp_x][temp_y].type == QUEEN || cb.board[temp_x][temp_y].type == BISHOP))
        {
            return true;
        } else {
            temp_x++;
            temp_y--;
        }
    }

    //Dolje lijevo
    temp_x = x - 1;
    temp_y = y + 1;
    while (temp_x >= 0 && temp_y <= 7)
    {
        if (cb.board[temp_x][temp_y].color == BLACK || (cb.board[temp_x][temp_y].color == WHITE && !(cb.board[temp_x][temp_y].type == QUEEN || cb.board[temp_x][temp_y].type == BISHOP)))
        {
            break;
        } else if (cb.board[temp_x][temp_y].color == WHITE && (cb.board[temp_x][temp_y].type == QUEEN || cb.board[temp_x][temp_y].type == BISHOP))
        {
            return true;
        } else {
            temp_x--;
            temp_y++;
        } 
    }

    //Dolje desno
    temp_x = x + 1;
    temp_y = y + 1;
    while (temp_x <= 7 && temp_y <= 7)
    {
        if (cb.board[temp_x][temp_y].color == BLACK || (cb.board[temp_x][temp_y].color == WHITE && !(cb.board[temp_x][temp_y].type == QUEEN || cb.board[temp_x][temp_y].type == BISHOP)))
        {
            break;
        } else if (cb.board[temp_x][temp_y].color == WHITE && (cb.board[temp_x][temp_y].type == QUEEN || cb.board[temp_x][temp_y].type == BISHOP))
        {
            return true;
        } else {
            temp_x++;
            temp_y++;
        } 
    }

    //Kralj i pijun
    if ((x - 1) >= 0 && (y + 1) <= 7 && cb.board[x - 1][y + 1].color == WHITE && (cb.board[x - 1][y + 1].type == PAWN || cb.board[x - 1][y + 1].type == KING))
    {
        return true;
    }

    if ((x + 1) <= 7 && (y + 1) <= 7 && cb.board[x + 1][y + 1].color == WHITE && (cb.board[x + 1][y + 1].type == PAWN || cb.board[x + 1][y + 1].type == KING))
    {
        return true;
    }

    if ((y + 1) <= 7 && cb.board[x][y + 1].color == WHITE && cb.board[x][y + 1].type == KING)
    {
        return true;
    }

    if ((y - 1) >= 0 && cb.board[x][y - 1].color == WHITE && cb.board[x][y - 1].type == KING)
    {
        return true;
    }

    if ((y - 1) >= 0 && (x - 1) >= 0 && cb.board[x - 1][y - 1].color == WHITE && cb.board[x - 1][y - 1].type == KING)
    {
        return true;
    }

    if ((y - 1) >= 0 && (x + 1) <= 7 && cb.board[x + 1][y - 1].color == WHITE && cb.board[x + 1][y - 1].type == KING)
    {
        return true;
    }

    if ((x - 1) >= 0 && cb.board[x - 1][y].color == WHITE && cb.board[x - 1][y].type == KING)
    {
        return true;
    }

    if ((x + 1) <= 7 && cb.board[x + 1][y].color == WHITE && cb.board[x + 1][y].type == KING)
    {
        return true;
    }
    
    //Skakac
    if ( x - 2 >= 0 && y - 1 >= 0 && cb.board[x - 2][y - 1].color == WHITE && cb.board[x - 2][y - 1].type == KNIGHT )
    {
        return true;
    }

    if ( x - 2 >= 0 && y + 1 <= 7 && cb.board[x - 2][y + 1].color == WHITE && cb.board[x - 2][y + 1].type == KNIGHT )
    {
        return true;
    }

    if ( x - 1 >= 0 && y - 2 >= 0 && cb.board[x - 1][y - 2].color == WHITE && cb.board[x - 1][y - 2].type == KNIGHT )
    {
        return true;
    }

    if ( x - 1 >= 0 && y + 2 <= 7 && cb.board[x - 1][y + 2].color == WHITE && cb.board[x - 1][y + 2].type == KNIGHT )
    {
        return true;
    }
    
    if ( x + 1 <= 7 && y - 2 >= 0 && cb.board[x + 1][y - 2].color == WHITE && cb.board[x + 1][y - 2].type == KNIGHT )
    {
        return true;
    }

    if ( x + 1 <= 7 && y + 2 <= 7 && cb.board[x + 1][y + 2].color == WHITE && cb.board[x + 1][y + 2].type == KNIGHT )
    {
        return true;
    }

    if ( x + 2 <= 7 && y - 1 >= 0 && cb.board[x + 2][y - 1].color == WHITE && cb.board[x + 2][y - 1].type == KNIGHT )
    {
        return true;
    }

    if ( x + 2 <= 7 && y + 1 <= 7 && cb.board[x + 2][y + 1].color == WHITE && cb.board[x + 2][y + 1].type == KNIGHT )
    {
        return true;
    }

    return false;
}

bool tileIsAttackedByBlack( ChessBoard cb, int x, int y ){
    //Lovac, top, kraljica
    int temp_y = y - 1;

    //Gore
    while (temp_y >= 0)
    {
        if (cb.board[x][temp_y].color == WHITE || (cb.board[x][temp_y].color == BLACK && !(cb.board[x][temp_y].type == QUEEN || cb.board[x][temp_y].type == ROOK)))
        {
            break;
        } else if (cb.board[x][temp_y].color == BLACK && (cb.board[x][temp_y].type == QUEEN || cb.board[x][temp_y].type == ROOK))
        {
            return true;
        } else {
            temp_y--;
        } 
    }

    //Dolje
    temp_y = y + 1;
    while (temp_y <= 7)
    {
        if (cb.board[x][temp_y].color == WHITE || (cb.board[x][temp_y].color == BLACK && !(cb.board[x][temp_y].type == QUEEN || cb.board[x][temp_y].type == ROOK)))
        {
            break;
        } else if (cb.board[x][temp_y].color == BLACK && (cb.board[x][temp_y].type == QUEEN || cb.board[x][temp_y].type == ROOK))
        {
            return true;
        } else {
            temp_y++;
        } 
    }

    //Lijevo
    int temp_x = x - 1;
    while (temp_x >= 0)
    {
        if (cb.board[temp_x][y].color == WHITE || (cb.board[temp_x][y].color == BLACK && !(cb.board[temp_x][y].type == QUEEN || cb.board[temp_x][y].type == ROOK)))
        {
            break;
        } else if (cb.board[temp_x][y].color == BLACK && (cb.board[temp_x][y].type == QUEEN || cb.board[temp_x][y].type == ROOK))
        {
            return true;
        } else {
            temp_x--;
        } 
    }

    //Desno
    temp_x = x + 1;
    while (temp_x <= 7)
    {
        if (cb.board[temp_x][y].color == WHITE || (cb.board[temp_x][y].color == BLACK && !(cb.board[temp_x][y].type == QUEEN || cb.board[temp_x][y].type == ROOK)))
        {
            break;
        } else if (cb.board[temp_x][y].color == BLACK && (cb.board[temp_x][y].type == QUEEN || cb.board[temp_x][y].type == ROOK))
        {
            return true;
        } else {
            temp_x++;
        } 
    }

    temp_x = x - 1; 
    temp_y = y - 1;

    //Gore lijevo
    while (temp_x >= 0 && temp_y >= 0)
    {
        if (cb.board[temp_x][temp_y].color == WHITE || (cb.board[temp_x][temp_y].color == BLACK && !(cb.board[temp_x][temp_y].type == QUEEN || cb.board[temp_x][temp_y].type == BISHOP)))
        {
            break;
        } else if (cb.board[temp_x][temp_y].color == BLACK && (cb.board[temp_x][temp_y].type == QUEEN || cb.board[temp_x][temp_y].type == BISHOP))
        {
            return true;
        } else {
            temp_x--;
            temp_y--;
        } 
    }
    
    //Gore desno
    temp_x = x + 1;
    temp_y = y - 1;
    while (temp_x <= 7 && temp_y >= 0)
    {
        if (cb.board[temp_x][temp_y].color == WHITE || (cb.board[temp_x][temp_y].color == BLACK && !(cb.board[temp_x][temp_y].type == QUEEN || cb.board[temp_x][temp_y].type == BISHOP)))
        {
            break;
        } else if (cb.board[temp_x][temp_y].color == BLACK && (cb.board[temp_x][temp_y].type == QUEEN || cb.board[temp_x][temp_y].type == BISHOP))
        {
            return true;
        } else {
            temp_x++;
            temp_y--;
        }
    }

    //Dolje lijevo
    temp_x = x - 1;
    temp_y = y + 1;
    while (temp_x >= 0 && temp_y <= 7)
    {
        if (cb.board[temp_x][temp_y].color == WHITE || (cb.board[temp_x][temp_y].color == BLACK && !(cb.board[temp_x][temp_y].type == QUEEN || cb.board[temp_x][temp_y].type == BISHOP)))
        {
            break;
        } else if (cb.board[temp_x][temp_y].color == BLACK && (cb.board[temp_x][temp_y].type == QUEEN || cb.board[temp_x][temp_y].type == BISHOP))
        {
            return true;
        } else {
            temp_x--;
            temp_y++;
        } 
    }

    //Dolje desno
    temp_x = x + 1;
    temp_y = y + 1;
    while (temp_x <= 7 && temp_y <= 7)
    {
        if (cb.board[temp_x][temp_y].color == WHITE || (cb.board[temp_x][temp_y].color == BLACK && !(cb.board[temp_x][temp_y].type == QUEEN || cb.board[temp_x][temp_y].type == BISHOP)))
        {
            break;
        } else if (cb.board[temp_x][temp_y].color == BLACK && (cb.board[temp_x][temp_y].type == QUEEN || cb.board[temp_x][temp_y].type == BISHOP))
        {
            return true;
        } else {
            temp_x++;
            temp_y++;
        } 
    }

    //Kralj i pijun
    if ((x - 1) >= 0 && (y + 1) <= 7 && cb.board[x - 1][y + 1].color == BLACK && cb.board[x - 1][y + 1].type == KING)
    {
        return true;
    }

    if ((x + 1) <= 7 && (y + 1) <= 7 && cb.board[x + 1][y + 1].color == BLACK && cb.board[x + 1][y + 1].type == KING)
    {
        return true;
    }

    if ((y + 1) <= 7 && cb.board[x][y + 1].color == BLACK && cb.board[x][y + 1].type == KING)
    {
        return true;
    }

    if ((y - 1) >= 0 && cb.board[x][y - 1].color == BLACK && cb.board[x][y - 1].type == KING)
    {
        return true;
    }

    if ((y - 1) >= 0 && (x - 1) >= 0 && cb.board[x - 1][y - 1].color == BLACK && (cb.board[x - 1][y - 1].type == PAWN || cb.board[x - 1][y - 1].type == KING))
    {
        return true;
    }

    if ((y - 1) >= 0 && (x + 1) <= 7 && cb.board[x + 1][y - 1].color == BLACK && (cb.board[x + 1][y - 1].type == PAWN || cb.board[x + 1][y - 1].type == KING))
    {
        return true;
    }

    if ((x - 1) >= 0 && cb.board[x - 1][y].color == BLACK && cb.board[x - 1][y].type == KING)
    {
        return true;
    }

    if ((x + 1) <= 7 && cb.board[x + 1][y].color == BLACK && cb.board[x + 1][y].type == KING)
    {
        return true;
    }
    
    //Skakac
    if ( x - 2 >= 0 && y - 1 >= 0 && cb.board[x - 2][y - 1].color == BLACK && cb.board[x - 2][y - 1].type == KNIGHT )
    {
        return true;
    }

    if ( x - 2 >= 0 && y + 1 <= 7 && cb.board[x - 2][y + 1].color == BLACK && cb.board[x - 2][y + 1].type == KNIGHT )
    {
        return true;
    }

    if ( x - 1 >= 0 && y - 2 >= 0 && cb.board[x - 1][y - 2].color == BLACK && cb.board[x - 1][y - 2].type == KNIGHT )
    {
        return true;
    }

    if ( x - 1 >= 0 && y + 2 <= 7 && cb.board[x - 1][y + 2].color == BLACK && cb.board[x - 1][y + 2].type == KNIGHT )
    {
        return true;
    }
    
    if ( x + 1 <= 7 && y - 2 >= 0 && cb.board[x + 1][y - 2].color == BLACK && cb.board[x + 1][y - 2].type == KNIGHT )
    {
        return true;
    }

    if ( x + 1 <= 7 && y + 2 <= 7 && cb.board[x + 1][y + 2].color == BLACK && cb.board[x + 1][y + 2].type == KNIGHT )
    {
        return true;
    }

    if ( x + 2 <= 7 && y - 1 >= 0 && cb.board[x + 2][y - 1].color == BLACK && cb.board[x + 2][y - 1].type == KNIGHT )
    {
        return true;
    }

    if ( x + 2 <= 7 && y + 1 <= 7 && cb.board[x + 2][y + 1].color == BLACK && cb.board[x + 2][y + 1].type == KNIGHT )
    {
        return true;
    }

    return false;
}

bool whiteKingCheck( ChessBoard cb ){
    for (int j = 7; j >= 0; j--)
    {
        for (int i = 7; i >= 0; i--)
        {
            if (cb.board[i][j].type == KING && cb.board[i][j].color == WHITE)
            {
                if (tileIsAttackedByBlack(cb, i, j))
                {
                    return true;
                } else {
                    return false;
                }
            }
        }
    }
    
    return false;
}

bool blackKingCheck( ChessBoard cb ){
    for (int j = 0; j < 8; j++)
    {
        for (int i = 0; i < 8; i++)
        {
            if (cb.board[i][j].type == KING && cb.board[i][j].color == BLACK)
            {
                if (tileIsAttackedByWhite(cb, i, j))
                {
                    return true;
                } else {
                    return false;
                }
            }
        }
    }
    
    return false;
}