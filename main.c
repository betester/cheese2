
#include "chess.h"

int main(void) {

  printf("Running Game\n");

  Piece pieces[MAX_CHESS_PIECE] = {0};
  PieceMovement movements[6] = {0};
  unsigned char board2d[8][8] = {0};
  char piece_symbols[16][5] = {0};
  unsigned char taken_move[4] = {0};

  Board board = InitBoard(&pieces, &movements);
  MapBoardTo2dBoard(&board, &board2d);
  InitPieceSymbols(&piece_symbols);
  
  while (true) {
    DisplayBoard(&board2d, &piece_symbols);
    UserInput(&board, &taken_move);
    UpdateBoard(&board2d, &taken_move);
  }

  return 0;
}
