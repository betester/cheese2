
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
    .movements = movements,
    .promoted_pawn = NULL
  };

  // add pawns
  for (unsigned char i=0; i < 8; i++) {
    Piece black_piece = {
      .x = 6,
      .y = i,
      .piece_owner = BLACK,
      .piece_type = PAWN,
      .taken = false
    }; 
    Piece white_piece = {
      .x = 1,
      .y = i,
      .piece_owner = WHITE,
      .piece_type = PAWN,
      .taken = false
    }; 

    addPiece(&board, black_piece);
    addPiece(&board, white_piece);
  }

  // complete the black pieces
  Piece black_king = {
    .x = 7,
    .y = 4,
    .piece_owner = BLACK,
    .piece_type = KING,
    .taken = false
  };
  addPiece(&board, black_king);
  Piece black_queen = {
    .x = 7,
    .y = 3, 
    .piece_owner = BLACK, 
    .piece_type = QUEEN,
    .taken = false
  };
  addPiece(&board, black_queen);
  Piece black_bishop_left = {
    .x = 7,
    .y = 2,
    .piece_owner = BLACK,
    .piece_type = BISHOP,
    .taken = false
  };
  addPiece(&board, black_bishop_left);
  Piece black_knight_left = {
    .x = 7,
    .y = 1,
    .piece_owner = BLACK,
    .piece_type = KNIGHT,
    .taken = false
  };
  addPiece(&board, black_knight_left);
  Piece black_rook_left = {
    .x = 7,
    .y = 0,
    .piece_owner = BLACK,
    .piece_type = ROOK,
    .taken = false
  };
  addPiece(&board, black_rook_left);
  Piece black_bishop_right = {
    .x = 7,
    .y = 5,
    .piece_owner = BLACK,
    .piece_type = BISHOP,
    .taken = false
  };
  addPiece(&board, black_bishop_right);
  Piece black_knight_right = {
    .x = 7,
    .y = 6,
    .piece_owner = BLACK,
    .piece_type = KNIGHT,
    .taken = false
  };
  addPiece(&board, black_knight_right);
  Piece black_rook_right = {
    .x = 7,
    .y = 7,
    .piece_owner = BLACK,
    .piece_type = ROOK,
    .taken = false
  };
  addPiece(&board, black_rook_right);

  // complete the white pieces
  Piece white_king = {
    .x = 0,
    .y = 4,
    .piece_owner = WHITE,
    .piece_type = KING,
    .taken = false
  };
  addPiece(&board, white_king);
  Piece white_queen = {
    .x = 0,
    .y = 3,
    .piece_owner = WHITE,
    .piece_type = QUEEN,
    .taken = false
  };
  addPiece(&board, white_queen);
  Piece white_bishop_left = {
    .x = 0,
    .y = 2,
    .piece_owner = WHITE,
    .piece_type = BISHOP,
    .taken = false
  };
  addPiece(&board, white_bishop_left);
  Piece white_knight_left = {
    .x = 0,
    .y = 1,
    .piece_owner = WHITE,
    .piece_type = KNIGHT,
    .taken = false
  };
  addPiece(&board, white_knight_left);
  Piece white_rook_left = {
    .x = 0,
    .y = 0,
    .piece_owner = WHITE,
    .piece_type = ROOK,
    .taken = false
  };
  addPiece(&board, white_rook_left);
  Piece white_bishop_right = {
    .x = 0,
    .y = 5,
    .piece_owner = WHITE,
    .piece_type = BISHOP,
    .taken = false
  };
  addPiece(&board, white_bishop_right);
  Piece white_knight_right = {
    .x = 0,
    .y = 6,
    .piece_owner = WHITE,
    .piece_type = KNIGHT,
    .taken = false
  };
  addPiece(&board, white_knight_right);
  Piece white_rook_right = {
    .x = 0,
    .y = 7,
    .piece_owner = WHITE,
    .piece_type = ROOK,
    .taken = false
  };
  addPiece(&board, white_rook_right);

  return board;
}

Piece *getPiece(Board *board, int x, int y) {
  for (int i = 0; i < board->current_piece_total; i++) {
    if ((*board->pieces)[i].x == x && (*board->pieces)[i].y == y) {
      return &(*board->pieces)[i];
    }
  }
  return NULL;
}

bool positionOutofBound(int x, int y) {
  return x < 0 || x >= MAX_CHESS_PIECE || y < 0 || y >= MAX_CHESS_PIECE;
}

bool blockedByNonTargetPiece(Board *board, int max_offset, int st_x, int st_y, int dx, int dy, int tx, int ty) {

  //TODO: inline this function only called once anyway
  // check if pawn can go to the direction if there is no other pawn blocking the way
  // except the target not so efficient because we checked every possible direction

  for (int i = 1; i <= max_offset; i++) {
    int x_offset = st_x + dx * i;
    int y_offset = st_y + dy * i;

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

bool validDirection(PieceMovement *movement, unsigned char dx, unsigned char dy, char x_dir, char y_dir) {
  bool valid_direction = false;

  //TODO: inline this function only called once anyway
  
  // check if direction is valid
  for (int i = 0; i < movement->total_movement; i++) {
    int valid_dx = x_dir * movement->movements[i][0];
    int valid_dy = y_dir * movement->movements[i][1];

    if (valid_dx == dx && valid_dy == dy) {
      return true;
    }
  }

  return false;
}

bool movePiece(Board *board, int sp_x, int sp_y, int t_x, int t_y) {

  if (board->promoted_pawn != NULL) {
    printf("Cannot move the pieces as the pawn should be promoted\n");
    return false;
  }

  if (board->king_in_check) {
    printf("Cannot move piece as the king is in check\n");
    return false;
  }

  if (positionOutofBound(sp_x, sp_y) || positionOutofBound(t_x, t_y)) {
    printf("Invalid position due to out of board bound\n");
    return false;
  }


  Piece *sp_piece = getPiece(board, sp_x, sp_y);
  Piece *t_piece = getPiece(board, t_x, t_y);

  // moving non existent piece should return null
  if (sp_piece == NULL) {
    printf("Cannot move empty piece\n");
    return false;
  }

  // cannot move piece if it's not the ownership of the player
  if (sp_piece->piece_owner != board->current_player) {
    printf("Cannot move opponent piece\n");
    return false;
  }

  if (t_piece != NULL && t_piece->piece_owner == sp_piece->piece_owner) {
    printf("Cannot attack your own piece\n");
    return false;
  }

  PieceMovement (*movements)[6] = board->movements;

  int dx = t_x - sp_x;
  int dy = t_y - sp_y;

  PieceMovement pawn_movement = (*movements)[sp_piece->piece_type];
  int direction = (sp_piece->piece_type == PAWN && sp_piece->piece_owner == WHITE) ? 1 : -1;

  unsigned char max_diff = pawn_movement.max_diff;

  if (validDirection(&pawn_movement, dx, dy, direction, 1)) {
    return false;
  }

  bool blocked = blockedByNonTargetPiece(
    board, 
    max_diff, 
    sp_x, 
    sp_y,
    dx, 
    dy,
    t_x,
    t_y
  );

  if (blocked) {
    printf("Cannot move to target due to blocked by other piece\n");
    return false;
  }

  if (sp_piece->piece_type == PAWN) {
    // could either move it 2 steps or 1 step depending whether it has already taken step previously
    // en passant
    // 2 or 1 step ahead on initial start

    // if 2 step but already move then we cant take this step
    if (dx == 2 && !(sp_piece->last_movement[0] == 0 && sp_piece->last_movement[1] == 0)) {
      return false;
    }

    // if diagonal steps are taken

    if (dx == 1 && (dy == 1 || dy == -1)) {

      Piece *sp_beside_piece = getPiece(board, sp_x + dx, sp_y + dy);

      if (t_piece != NULL) {
        printf("Cannot do en passant if the target position is not empty%s\n");
        return false;
      }

      if (sp_beside_piece == NULL) {
        printf("Cannot do en passant no piece on the direction\n");
        return false;
      }

      if (!(sp_beside_piece->last_movement[0] == 2 && sp_beside_piece->last_movement[1] == 0)) {
        printf("Cannot do en passant if two steps are not taken\n");
        return false;
      }
    }

    // eat the piece
    if (t_piece != NULL && !t_piece->taken) {
      t_piece->taken = true;
      sp_piece->x = t_x;
      sp_piece->y = t_y;
    } 

    // update last taken movement
    sp_piece->last_movement[0] = dx;
    sp_piece->last_movement[1] = dy;

    if (t_x == 0 || t_x == 7) {
      board->promoted_pawn = sp_piece;
    }
  }

  // change the current allowed player to move
  board->current_player = (board -> current_player + 1) % 2;

  // TODO: 
  // 1. handle when the king is in check or not for the current player 
  // just loop and find the king, once we find it we check for every enemy piece whether it attacks the king or not.
  // 2. handle whether the king is on checkmate or not
  // this needs to know whether the king is on check or not. but the idea is to see every possible direction the king can go
  // then check whether it's possible to move to certain position if it's not attacked and not occupied. checkmate happens only if 
  // the king is on check with nowhere to go.

  // finding the king position
  Piece *opponent_king;

  for (int i = 0; i < board->current_piece_total; i++) {
    if ((*board->pieces)[i].piece_owner == board->current_player && (*board->pieces)[i].piece_type == KING) {
      opponent_king = &(*board->pieces)[i];
      break;
    }
  }

  unsigned char kx = opponent_king->x;
  unsigned char ky = opponent_king->y;

  PieceMovement king_movements = (*movements)[KING];

  int king_surrounding_loc[king_movements.total_movement][2];

  for (int i = 0; i < king_movements.total_movement; i++) {
    king_surrounding_loc[i][0] = kx + king_movements.movements[i][0];
    king_surrounding_loc[i][1] = ky + king_movements.movements[i][1];
  }

  bool king_in_check = false;

  for (int i = 0; i < board->current_piece_total;i++) {
    Piece piece = (*board->pieces)[i];

    if (piece.piece_owner == board->current_player || piece.taken) {
      continue;
    }
    PieceMovement piece_movement = (*movements)[piece.piece_type];

    int dx_k = kx - piece.x;
    int dy_k = ky - piece.y;

    if (validDirection(&piece_movement, dx_k, dy_k, kx, ky)) {

      king_in_check = king_in_check || blockedByNonTargetPiece(
        board, 
        piece_movement.max_diff, 
        piece.x, 
        piece.y,
        dx_k, 
        dy_k,
        kx,
        ky
      );
    }

    unsigned char total_surrounded = 0;
    unsigned char expected_surrounding_for_checkmate = king_movements.total_movement;

    for (int j = 0; j < king_movements.total_movement; j++) {
      if (positionOutofBound(king_surrounding_loc[j][0], king_surrounding_loc[j][1])) {
        expected_surrounding_for_checkmate--;
        continue;
      }
      int dx_ks = king_surrounding_loc[j][0] - piece.x;
      int dy_ks = king_surrounding_loc[j][1] - piece.y;

      bool piece_can_go_to_surrounding = validDirection(&piece_movement, dx_ks, dy_ks, king_surrounding_loc[j][0], king_surrounding_loc[j][1]);

      bool piece_attacked_the_surrounding = blockedByNonTargetPiece(
        board, 
        max_diff, 
        piece.x, 
        piece.y,
        dx_ks, 
        dy_ks,
        king_surrounding_loc[j][0],
        king_surrounding_loc[j][1]
      );

      if (piece_can_go_to_surrounding && piece_attacked_the_surrounding) {
        total_surrounded++;
      }
    }

    if (king_in_check) {
      board->king_in_check = true;
    }

    if (king_in_check && total_surrounded == expected_surrounding_for_checkmate) {
      board->checkmated = true;
    }
  }

  return true;
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

void promotePawn(Board *board, PieceType promotion_type) {
  Piece *piece = board->promoted_pawn;

  if (piece == NULL || piece->piece_type != PAWN) {
    printf("Can only promote pawn\n");
    return;
  }

  if (promotion_type == PAWN || promotion_type == KING) {
    printf("Cannot promote to pawn or king\n");
    return;
  }

  if (piece->taken) {
    printf("Cannot promote taken piece\n");
    return;
  }

  piece->piece_type = promotion_type;
  board->promoted_pawn = NULL;
}

void UpdateBoard(unsigned char (*board2d)[8][8], unsigned char (*taken_move)[4]) {
  int sp_x, sp_y, t_x, t_y;

  if ((*taken_move)[0] == 0 && (*taken_move)[1] == 0 && (*taken_move)[2] == 0 && (*taken_move)[3] == 0) {
    return;
  }

  sp_x = (*taken_move)[0];
  sp_y = (*taken_move)[1];
  t_x = (*taken_move)[2];
  t_y = (*taken_move)[3];

  unsigned char prev_id = (*board2d)[sp_x][sp_y];
  (*board2d)[sp_x][sp_y] = (*board2d)[t_x][t_y];
  (*board2d)[t_x][t_y] = prev_id;
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

void UserInput(Board *board, unsigned char (*taken_move)[4]) {

  if (board->promoted_pawn != NULL) {
    PieceType promotion_to;
    printf("Promote your pawn\n", board->current_player);
    scanf("%d" , promotion_to);
    promotePawn(board, promotion_to);
  } else {
  int sp_x, sp_y, t_x, t_y;
  printf("Player %d to make the move\n", board->current_player);
  scanf("%d %d %d %d", &sp_x, &sp_y, &t_x, &t_y);

  bool piece_moved = movePiece(board, sp_x, sp_y, t_x, t_y);

  if (piece_moved) {
    (*taken_move)[0] = sp_x;
    (*taken_move)[1] = sp_y;
    (*taken_move)[2] = t_x;
    (*taken_move)[3] = t_y;
  } else {
    (*taken_move)[0] = 0;
    (*taken_move)[1] = 0;
    (*taken_move)[2] = 0;
    (*taken_move)[3] = 0;
  }
  }
}
