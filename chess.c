
#include "chess.h"

void addPiece(Board *board, Piece new_piece) {
  if (board->current_piece_total + 1 >= MAX_CHESS_PIECE) {
    return;
  }

  (*board->pieces)[board->current_piece_total] = new_piece;
  board->current_piece_total++;
}

unsigned char pieceId(Player player, PieceType type) {
  return (player << 3) | type;
}

Board InitBoard(Piece (*initial_chess_pieces)[MAX_CHESS_PIECE], PieceMovement (*movements)[6]) {

  PieceMovement pawn_movement = {
    .max_diff = 2, 
    .total_movement = 3,
    .movements = {{1, 0}, {1, -1}, {1, 1}}
  };
  PieceMovement king_movement = {
    .max_diff = 1,
    .total_movement = 8,
    .movements = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}, {-1, 1}, {1, 1}, {-1, -1}, {1, -1}}
  };
  PieceMovement queen_movement = {
    .max_diff = 8, 
    .total_movement = 8,
    .movements = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}, {-1, 1}, {1, 1}, {-1, -1}, {1, -1}}
  };
  PieceMovement bishop_movement = {
    .max_diff = 8, 
    .total_movement = 4,
    .movements = {{-1, 1}, {1, 1}, {-1, -1}, {1, -1}}
  };
  PieceMovement rook_movement = {
    .max_diff = 8, 
    .total_movement = 4,
    .movements = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}}
  };
  PieceMovement knight_movement = {
    .max_diff = 1, 
    .total_movement = 8,
    .movements = {{-2,-1}, {-2, 1}, {2, -1}, {2,1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}}
  };

  (*movements)[PAWN] = pawn_movement;
  (*movements)[KING] = king_movement;
  (*movements)[QUEEN] = queen_movement;
  (*movements)[BISHOP] = bishop_movement;
  (*movements)[ROOK] = bishop_movement;
  (*movements)[KNIGHT] = knight_movement;

  Board board = {
    .current_player = WHITE,
    .king_in_check = false,
    .pieces = initial_chess_pieces,
    .current_piece_total = 0,
    .movements = movements
  };

  // add pawns
  for (unsigned char i=0; i < 8; i++) {
    Piece black_piece = {
      .x = 6,
      .y = i,
      .piece_owner = BLACK,
      .piece_type = PAWN
    }; 
    Piece white_piece = {
      .x = 1,
      .y = i,
      .piece_owner = WHITE,
      .piece_type = PAWN
    }; 

    addPiece(&board, black_piece);
    addPiece(&board, white_piece);
  }

  // complete the black pieces
  Piece black_king = {
    .x = 7,
    .y = 4,
    .piece_owner = BLACK,
    .piece_type = KING
  };
  addPiece(&board, black_king);
  Piece black_queen = {
    .x = 7,
    .y = 3, 
    .piece_owner = BLACK, 
    .piece_type = QUEEN
  };
  addPiece(&board, black_queen);
  Piece black_bishop_left = {
    .x = 7,
    .y = 2,
    .piece_owner = BLACK,
    .piece_type = BISHOP
  };
  addPiece(&board, black_bishop_left);
  Piece black_knight_left = {
    .x = 7,
    .y = 1,
    .piece_owner = BLACK,
    .piece_type = KNIGHT
  };
  addPiece(&board, black_knight_left);
  Piece black_rook_left = {
    .x = 7,
    .y = 0,
    .piece_owner = BLACK,
    .piece_type = ROOK
  };
  addPiece(&board, black_rook_left);
  Piece black_bishop_right = {
    .x = 7,
    .y = 5,
    .piece_owner = BLACK,
    .piece_type = BISHOP
  };
  addPiece(&board, black_bishop_right);
  Piece black_knight_right = {
    .x = 7,
    .y = 6,
    .piece_owner = BLACK,
    .piece_type = KNIGHT
  };
  addPiece(&board, black_knight_right);
  Piece black_rook_right = {
    .x = 7,
    .y = 7,
    .piece_owner = BLACK,
    .piece_type = ROOK
  };
  addPiece(&board, black_rook_right);

  // complete the white pieces
  Piece white_king = {
    .x = 0,
    .y = 4,
    .piece_owner = WHITE,
    .piece_type = KING
  };
  addPiece(&board, white_king);
  Piece white_queen = {
    .x = 0,
    .y = 3,
    .piece_owner = WHITE,
    .piece_type = QUEEN
  };
  addPiece(&board, white_queen);
  Piece white_bishop_left = {
    .x = 0,
    .y = 2,
    .piece_owner = WHITE,
    .piece_type = BISHOP
  };
  addPiece(&board, white_bishop_left);
  Piece white_knight_left = {
    .x = 0,
    .y = 1,
    .piece_owner = WHITE,
    .piece_type = KNIGHT
  };
  addPiece(&board, white_knight_left);
  Piece white_rook_left = {
    .x = 0,
    .y = 0,
    .piece_owner = WHITE,
    .piece_type = ROOK
  };
  addPiece(&board, white_rook_left);
  Piece white_bishop_right = {
    .x = 0,
    .y = 5,
    .piece_owner = WHITE,
    .piece_type = BISHOP
  };
  addPiece(&board, white_bishop_right);
  Piece white_knight_right = {
    .x = 0,
    .y = 6,
    .piece_owner = WHITE,
    .piece_type = KNIGHT
  };
  addPiece(&board, white_knight_right);
  Piece white_rook_right = {
    .x = 0,
    .y = 7,
    .piece_owner = WHITE,
    .piece_type = ROOK
  };
  addPiece(&board, white_rook_right);

  return board;
}

Piece *getPiece(Board *board, int x, int y) {
  for (int i=0; i < board->current_piece_total; i++) {
    if ((*board->pieces[i]).x == x && (*board->pieces[i]).y == y && !(*board->pieces[i]).taken) {
      return &(*board->pieces[i]);
    }
  }
  return NULL;
}

bool positionOutofBound(int x, int y) {
  return x < 0 || x >= MAX_CHESS_PIECE || y < 0 || y >= MAX_CHESS_PIECE;
}

unsigned char* getDirection(int x1, int y1, int x2, int y2) {
  // TODO: somehow get the normalized direction from 2 points
  // probably just the diff?
  static unsigned char base_direction[2];

  base_direction[0] = x2 - x1;
  base_direction[1] = y2 - y1;

  return base_direction;
}

bool blockedByNonTargetPiece(Board *board, int max_offset, int st_x, int st_y, int dx, int dy, int tx, int ty) {

  // check if pawn can go to the direction if there is no other pawn blocking the way
  // except the target not so efficient because we checked every possible direction

  for (int i = 1; i <= max_offset; i++) {
    int x_offset = st_x + dx * st_x;
    int y_offset = st_y + dy * st_y;

    if (x_offset == tx && y_offset == ty) {
      continue;
    }

    Piece *piece = getPiece(board, x_offset, y_offset);
    if (piece != NULL){
      return true;
    }
  }

  return false;
}

bool validDirection(PieceMovement *movement, unsigned char *base_direction, char x_dir, char y_dir) {
  bool valid_direction = false;

  // check if direction is valid
  for (int i = 0; i < movement->total_movement; i++) {
    int dx = x_dir * movement->movements[i][0];
    int dy = y_dir * movement->movements[i][1];

    if (base_direction[0] == dx && base_direction[1] == dy) {
      return true;
    }
  }

  return false;
}

void AttackPiece(Piece *sp_piece, Piece *t_piece, int t_x, int t_y, int dx, int dy) {

  // eat the piece
  if (t_piece != NULL && !t_piece->taken) {
    t_piece->taken = true;
    sp_piece->x = t_x;
    sp_piece->y = t_y;
  } 

  sp_piece->last_movement[0] = dx;
  sp_piece->last_movement[1] = dy;
}

void MovePiece(Board *board, int sp_x, int sp_y, int t_x, int t_y) {

  if (board->king_in_check) {
    return;
  }

  if (positionOutofBound(sp_x, sp_y) || positionOutofBound(t_x, t_y)) {
    return;
  }

  Piece *sp_piece = getPiece(board, sp_x, sp_y);
  Piece *t_piece = getPiece(board, t_x, t_y);

  // moving non existent piece should return null
  if (sp_piece == NULL) {
    return;
  }

  // cannot move piece if it's not the ownership of the player
  if (sp_piece->piece_owner != board->current_player) {
    return;
  }

  if (t_piece != NULL && t_piece->piece_owner == sp_piece->piece_owner) {
    return;
  }

  PieceMovement (*movements)[6] = board->movements;

  int dx = t_x - sp_x;
  int dy = t_y - sp_y;

  PieceMovement pawn_movement = (*movements)[sp_piece->piece_type];
  int x_direction = (sp_piece->piece_type == PAWN && sp_piece->piece_owner == WHITE) ? -1 : 1;

  unsigned char *base_direction = getDirection(sp_x, sp_y, t_x, t_y);
  unsigned char max_diff = pawn_movement.max_diff;

  if (validDirection(&pawn_movement, base_direction, x_direction, 1)) {
    return;
  }

  bool blocked = blockedByNonTargetPiece(
    board, 
    max_diff, 
    sp_x, 
    sp_y,
    base_direction[0], 
    base_direction[1],
    t_x,
    t_y
  );

  if (blocked) {
    return;
  }

  if (sp_piece->piece_type == PAWN) {
    // could either move it 2 steps or 1 step depending whether it has already taken step previously
    // en passant
    // 2 or 1 step ahead on initial start

    // if 2 step but already move then we cant take this step
    if (base_direction[0] == 2 && !(sp_piece->last_movement[0] == 0 && sp_piece->last_movement[1] == 0)) {
      return;
    }

    AttackPiece(sp_piece, t_piece, t_x, t_y, dx, dy);
  }

  return;
}

void MapBoardTo2dBoard(Board *board, unsigned char (*board2d)[8][8]) {
  for (int i=0; i < board->current_piece_total; i++) {
    unsigned char x = (*board->pieces)[i].x;
    unsigned char y = (*board->pieces)[i].y;

    (*board2d)[x][y] = pieceId((*board->pieces)[i].piece_owner, (*board->pieces)[i].piece_type);
  }
}

void DisplayBoard(unsigned char (*board2d)[8][8], char (*piece_symbols)[16][5]) {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      printf("%s ", (*piece_symbols)[(*board2d)[i][j]]);
    }
    printf("\n");
  }
}

void InitPieceSymbols(char (*piece_symbols)[16][5]) {
    strcpy((*piece_symbols)[pieceId(WHITE, PAWN)], "P");
    strcpy((*piece_symbols)[pieceId(WHITE, KING)], "K");
    strcpy((*piece_symbols)[pieceId(WHITE, QUEEN)], "Q");
    strcpy((*piece_symbols)[pieceId(WHITE, KNIGHT)], "KN");
    strcpy((*piece_symbols)[pieceId(WHITE, ROOK)], "R");
    strcpy((*piece_symbols)[pieceId(WHITE, BISHOP)], "B");
    
    strcpy((*piece_symbols)[pieceId(BLACK, PAWN)], "p");
    strcpy((*piece_symbols)[pieceId(BLACK, KING)], "k");
    strcpy((*piece_symbols)[pieceId(BLACK, QUEEN)], "q");
    strcpy((*piece_symbols)[pieceId(BLACK, KNIGHT)], "kn");
    strcpy((*piece_symbols)[pieceId(BLACK, ROOK)], "r");
    strcpy((*piece_symbols)[pieceId(BLACK, BISHOP)], "b");
    
    // Initialize NEUTRAL pieces if needed
    strcpy((*piece_symbols)[pieceId(WHITE, NEUTRAL)], " ");
    strcpy((*piece_symbols)[pieceId(BLACK, NEUTRAL)], " ");
}

void UserInput(Board *board) {
  int sp_x, sp_y, t_x, t_y;
  printf("Player %d to make the move", board->current_player);
  scanf("%d %d %d %d", &sp_x, &sp_y, &t_x, &t_y);
  MovePiece(board, sp_x, sp_y, t_x, t_y);
}
