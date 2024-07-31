
// TODO: handle bug where pawn considered to be able to move twice distance on diagonal
// Promote pawn
// Checkmate

#include "chess.h"
#include "raylib.h"
#include <assert.h>
#include <stdio.h>

#define CHESS_BOARD_HEIGHT 8
#define CHESS_BOARD_WIDTH 8

void addPiece(Board *board, Piece new_piece) {
  if (board->current_piece_total + 1 >= MAX_CHESS_PIECE) {
    return;
  }

  (*board->pieces)[board->current_piece_total] = new_piece;
  board->current_piece_total++;
}

unsigned char pieceId(ChessPlayer player, PieceType type) {
  return (player << 3) | type;
}

Board initBoard(Piece (*initial_chess_pieces)[MAX_CHESS_PIECE], PieceMovement (*movements)[TOTAL_PIECES]) {

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
    .max_diff = 7, 
    .total_movement = 4,
    .movements = {{-1, 1}, {1, 1}, {-1, -1}, {1, -1}}
  };
  PieceMovement rook_movement = {
    .max_diff = 7, 
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
  (*movements)[ROOK] = rook_movement;
  (*movements)[KNIGHT] = knight_movement;

  Board board = {
    .current_player = WHITE_P,
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
      .piece_owner = BLACK_P,
      .piece_type = PAWN,
      .taken = false
    }; 
    Piece white_piece = {
      .x = 1,
      .y = i,
      .piece_owner = WHITE_P,
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
    .piece_owner = BLACK_P,
    .piece_type = KING,
    .taken = false,
    .last_movement = {-1, -1}
  };
  addPiece(&board, black_king);
  Piece black_queen = {
    .x = 7,
    .y = 3, 
    .piece_owner = BLACK_P, 
    .piece_type = QUEEN,
    .taken = false
  };
  addPiece(&board, black_queen);
  Piece black_bishop_left = {
    .x = 7,
    .y = 2,
    .piece_owner = BLACK_P,
    .piece_type = BISHOP,
    .taken = false
  };
  addPiece(&board, black_bishop_left);
  Piece black_knight_left = {
    .x = 7,
    .y = 1,
    .piece_owner = BLACK_P,
    .piece_type = KNIGHT,
    .taken = false
  };
  addPiece(&board, black_knight_left);
  Piece black_rook_left = {
    .x = 7,
    .y = 0,
    .piece_owner = BLACK_P,
    .piece_type = ROOK,
    .taken = false
  };
  addPiece(&board, black_rook_left);
  Piece black_bishop_right = {
    .x = 7,
    .y = 5,
    .piece_owner = BLACK_P,
    .piece_type = BISHOP,
    .taken = false
  };
  addPiece(&board, black_bishop_right);
  Piece black_knight_right = {
    .x = 7,
    .y = 6,
    .piece_owner = BLACK_P,
    .piece_type = KNIGHT,
    .taken = false
  };
  addPiece(&board, black_knight_right);
  Piece black_rook_right = {
    .x = 7,
    .y = 7,
    .piece_owner = BLACK_P,
    .piece_type = ROOK,
    .taken = false
  };
  addPiece(&board, black_rook_right);

  // complete the white pieces
  Piece white_king = {
    .x = 0,
    .y = 4,
    .piece_owner = WHITE_P,
    .piece_type = KING,
    .taken = false,
    .last_movement = {-1, -1}
  };
  addPiece(&board, white_king);
  Piece white_queen = {
    .x = 0,
    .y = 3,
    .piece_owner = WHITE_P,
    .piece_type = QUEEN,
    .taken = false
  };
  addPiece(&board, white_queen);
  Piece white_bishop_left = {
    .x = 0,
    .y = 2,
    .piece_owner = WHITE_P,
    .piece_type = BISHOP,
    .taken = false
  };
  addPiece(&board, white_bishop_left);
  Piece white_knight_left = {
    .x = 0,
    .y = 1,
    .piece_owner = WHITE_P,
    .piece_type = KNIGHT,
    .taken = false
  };
  addPiece(&board, white_knight_left);
  Piece white_rook_left = {
    .x = 0,
    .y = 0,
    .piece_owner = WHITE_P,
    .piece_type = ROOK,
    .taken = false,
    .last_movement = {-1, -1}
  };
  addPiece(&board, white_rook_left);
  Piece white_bishop_right = {
    .x = 0,
    .y = 5,
    .piece_owner = WHITE_P,
    .piece_type = BISHOP,
    .taken = false
  };
  addPiece(&board, white_bishop_right);
  Piece white_knight_right = {
    .x = 0,
    .y = 6,
    .piece_owner = WHITE_P,
    .piece_type = KNIGHT,
    .taken = false
  };
  addPiece(&board, white_knight_right);
  Piece white_rook_right = {
    .x = 0,
    .y = 7,
    .piece_owner = WHITE_P,
    .piece_type = ROOK,
    .taken = false,
    .last_movement = {-1, -1}

  };
  addPiece(&board, white_rook_right);

  return board;
}

Piece *getPiece(Board *board, int x, int y) {
  for (int i = 0; i < board->current_piece_total; i++) {
    if ((*board->pieces)[i].x == x && (*board->pieces)[i].y == y && !(*board->pieces)[i].taken) {
      return &(*board->pieces)[i];
    }
  }
  return NULL;
}

bool positionOutofBound(int x, int y) {
  return x < 0 || x >= 8 || y < 0 || y >= 8;
}

bool blockedByNonTargetPiece(Board *board, int max_offset, int st_x, int st_y, int dx, int dy, int tx, int ty) {

  //TODO: inline this function only called once anyway
  // check if pawn can go to the direction if there is no other pawn blocking the way
  // except the target not so efficient because we checked every possible direction

  // printf("starting position\n");
  // printf("%d %d\n", st_x, st_y);
  //
  // printf("max offset\n");
  // printf("%d\n", max_offset);
  //
  // printf("dx %d dy %d\n", dx, dy);

  for (int i = 1; i <= max_offset; i++) {
    int x_offset = st_x + dx * i;
    int y_offset = st_y + dy * i;

    printf("x_offset %d , y_offset %d\n", x_offset, y_offset);
  
    if (x_offset == tx && y_offset == ty) {
      break;
    }

    Piece *piece = getPiece(board, x_offset, y_offset);
    if (piece != NULL && !piece->taken) {
      return true;
    }
  }

  return false;
}


void validDirection(PieceMovement *movement, char dx, char dy, PieceType type, ChessPlayer player, char (*valid_direction)[2]) {
  
  int direction = type == PAWN && player == BLACK_P ? -1 : 1;

  dx = dx * direction;

  // check if direction is valid
  for (char j = 1; j <= movement->max_diff; j++) {
    for (int i = 0; i < movement->total_movement; i++) {

      char valid_dx = movement->movements[i][0];
      char valid_dy = movement->movements[i][1];

      if (j * valid_dx == dx && j * valid_dy == dy) {
        (*valid_direction)[0] = valid_dx * direction;
        (*valid_direction)[1] = valid_dy;
        break;
      }
    }

  }
}

/*
 * Returns 11 : checkmated
 * Returns 10 : in check
 * Return 00 : save
*/

bool positionUnderAttackByPlayer(Board *board, unsigned char x, unsigned char y, ChessPlayer current_player) {
  PieceMovement (*movements)[TOTAL_PIECES] = board->movements;
  bool position_under_attack = false;

  for (int i = 0; i < board->current_piece_total;i++) {
    Piece piece = (*board->pieces)[i];

    if (piece.piece_owner == current_player || piece.taken) {
      continue;
    }

    PieceMovement piece_movement = (*movements)[piece.piece_type];

    int dx_k = x - piece.x;
    int dy_k = y - piece.y;

    char king_valid_direction[2] = {0};
    validDirection(&piece_movement, dx_k, dy_k, piece.piece_type, piece.piece_owner, &king_valid_direction);

    if (!(king_valid_direction[0] == 0 && king_valid_direction[1] == 0))  {

      position_under_attack = position_under_attack || !blockedByNonTargetPiece(
        board, 
        piece_movement.max_diff, 
        piece.x, 
        piece.y,
        king_valid_direction[0], 
        king_valid_direction[1],
        x,
        y 
      );
    }
  }

  return position_under_attack;
}

int getKingCondition(Board *board, ChessPlayer player) {
  // TODO: 
  // 1. handle when the king is in check or not for the current player 
  // just loop and find the king, once we find it we check for every enemy piece whether it attacks the king or not.
  // 2. handle whether the king is on checkmate or not
  // this needs to know whether the king is on check or not. but the idea is to see every possible direction the king can go
  // then check whether it's possible to move to certain position if it's not attacked and not occupied. checkmate happens only if 
  // the king is on check with nowhere to go.

  Piece *opponent_king;
  PieceMovement (*movements)[TOTAL_PIECES] = board->movements; 

  for (int i = 0; i < board->current_piece_total; i++) {
    if ((*board->pieces)[i].piece_owner == player && (*board->pieces)[i].piece_type == KING) {
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

  bool king_in_check = positionUnderAttackByPlayer(board, kx, ky, player);
  bool checkmated = false;

  int king_condition = 0;
  king_condition = king_condition | (king_in_check << 1) | checkmated;

  return king_condition;
}

bool movePiece(Board *board, int sp_x, int sp_y, int t_x, int t_y) {

  printf("%d, %d, %d, %d\n", sp_x, sp_y, t_x, t_y);

  if (board->promoted_pawn != NULL) {
    printf("Cannot move the pieces as the pawn should be promoted\n");
    return false;
  }

  if (sp_x == t_x && sp_y == t_y) {
    printf("Cannot move back to the same position\n");
    return false;
  }

  if (board->checkmated) {
    printf("Cannot move the piece as the king is checkmated\n");
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
    printf("Cannot move empty piece, not found position %d %d\n", sp_x, sp_y);
    return false;
  }

  // cannot move piece if it's not the ownership of the player
  if (sp_piece->piece_owner != board->current_player) {
    printf("Cannot move opponent piece\n");
    return false;
  }

  // Indication that the player might want to castle
  if (sp_piece->piece_type == KING && t_piece != NULL && t_piece->piece_owner == sp_piece->piece_owner && t_piece->piece_type == ROOK) {

    if (board->king_in_check) {
      printf("Cannot castle as the king is under attack\n");
      return false;
    }

    if (!(sp_piece->last_movement[0] == -1 && sp_piece->last_movement[1] == -1) && !(t_piece->last_movement[0] == -1 && t_piece->last_movement[1] == -1)) {
      printf("%d %d %d %d\n", sp_piece->last_movement[0], sp_piece->last_movement[1], t_piece->last_movement[0], t_piece->last_movement[1]);
      printf("Cannot castle because one of the piece already moved");
      return false;
    }

    // the king position should be valid assuming that last movement is always assigned
    // TODO: handle when a pawn promotes to a rook

    //  check whether the rook is on the king side or the queen side of the king.
    //  king side would be that the rook has a bigger value in y coordinate

    //  
    int diff = t_piece->y - sp_piece->y;
    bool king_side = diff > 0;
  
    // need to check whether two blocks is attacked by other pieces.
    if (king_side) {
      assert(sp_piece->y + 2 < 8);

      Piece *bishop = getPiece(board, sp_piece->x, sp_piece->y + 1);
      Piece *knight = getPiece(board, sp_piece->x, sp_piece->y + 2);
      bool bishop_square_attacked = positionUnderAttackByPlayer(board, sp_piece->x, sp_piece->y + 1, sp_piece->piece_owner);
      bool knight_square_attacked = positionUnderAttackByPlayer(board, sp_piece->x, sp_piece->y + 2, sp_piece->piece_owner);

      if (bishop != NULL || knight != NULL) {
        printf("Cannot castle because there is a piece on the way\n");
        return false;
      }

      if (bishop_square_attacked || knight_square_attacked) {
        printf("Cannot castle because the position was attacked \n");
        return false;
      }

      sp_piece->y = sp_piece->y + 1;
      t_piece->y = t_piece->y - 1;

      board->current_player = (board -> current_player + 1) % 2;

      return true;
    } else {
      assert(sp_piece->y - 3 < 8);

      Piece *queen = getPiece(board, sp_piece->x, sp_piece->y - 1);
      Piece *knight = getPiece(board, sp_piece->x, sp_piece->y - 2);
      Piece *bishop = getPiece(board, sp_piece->x, sp_piece->y - 3);
      
      bool queen_square_attacked = positionUnderAttackByPlayer(board, sp_piece->x, sp_piece->y - 1, sp_piece->piece_owner);
      bool bishop_square_attacked = positionUnderAttackByPlayer(board, sp_piece->x, sp_piece->y - 3, sp_piece->piece_owner);

      if (queen != NULL || bishop != NULL || knight != NULL) {
        printf("Cannot castle because there is a piece on the way\n");
        return false;
      }

      if (queen_square_attacked || bishop_square_attacked) {
        printf("Cannot castle because the position was attacked \n");
        return false;
      }

      sp_piece->y = sp_piece->y - 2;
      t_piece->y = t_piece->y + 3;

      board->current_player = (board -> current_player + 1) % 2;

      return true;
    } 
  }

  if (t_piece != NULL && t_piece->piece_owner == sp_piece->piece_owner) {
    printf("Cannot attack your own piece\n");
    return false;
  }

  PieceMovement (*movements)[TOTAL_PIECES] = board->movements;

  int dx = t_x - sp_x;
  int dy = t_y - sp_y;

  PieceMovement movement = (*movements)[sp_piece->piece_type];

  unsigned char max_diff = movement.max_diff;
  char valid_direction[2] = {0};

  validDirection(&movement, dx, dy, sp_piece->piece_type, sp_piece->piece_owner, &valid_direction);

  if (valid_direction[0] == 0 && valid_direction[1] == 0) {
    printf("Cannot move piece to direction %d %d\n", dx, dy);
    return false;
  }

  printf("valid direction x : %d y : %d\n", valid_direction[0], valid_direction[1]);

  bool blocked = blockedByNonTargetPiece(
    board, 
    max_diff, 
    sp_x, 
    sp_y,
    valid_direction[0], 
    valid_direction[1],
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

    if ((dy == 1 || dy == -1) && t_piece == NULL) {
      printf("Cannot move diagonally as there is no piece to attack\n");
      return false;
    }

    // if 2 step but already move then we cant take this step
    int direction = sp_piece->piece_owner == BLACK_P ? -1 : 1;
    if (dx == 2 * direction && !(sp_piece->last_movement[0] == 0 && sp_piece->last_movement[1] == 0)) {
      printf("Cannot move piece 2 step due to already moved previously\n");
      return false;
    }

    printf("%d %d\n", dx,  direction);
    if (dx ==  direction && dy == 0 && t_piece != NULL) {
      printf("Pawn cannot move forward when there is a piece blocking the way\n");
      return false;
    }

    // if diagonal steps are taken
    // it's either en passant or taking piece from the diagonal side
    
    Piece *sp_beside_piece = getPiece(board, sp_x, sp_y + dy);

    if (dx == 1 * direction && (dy == 1 || dy == -1) && sp_beside_piece != NULL && sp_beside_piece->piece_owner != sp_piece->piece_owner) {

      if (t_piece != NULL) {
        printf("Cannot do en passant if the target position is not empty\n");
        return false;
      }

      if (sp_beside_piece == NULL) {
        printf("Cannot do en passant no piece on the direction\n");
        return false;
      }
      printf("%d\n", sp_beside_piece->last_movement[0]);

      if (!(sp_beside_piece->last_movement[0] == 2 && sp_beside_piece->last_movement[1] == 0)) {
        printf("Cannot do en passant if two steps are not taken\n");
        return false;
      }
      t_piece = sp_beside_piece;
    }

    if (t_x == 0 || t_x == 7) {
      board->promoted_pawn = sp_piece;
    }

  } 
  // update this to make sure that it accounts for the piece that has moved as well.
  sp_piece->x = t_x;
  sp_piece->y = t_y;

  // eat the piece
  bool t_piece_eaten = false;

  if (t_piece != NULL && !t_piece->taken) {
    t_piece_eaten = t_piece->taken;
    t_piece->taken = true;
  } 

  int white_king_condition = getKingCondition(board, WHITE_P);
  int black_king_condition = getKingCondition(board, BLACK_P);

  bool w_king_in_check = white_king_condition & 2; 
  bool w_checkmated = white_king_condition & 1; 

  bool b_king_in_check = black_king_condition & 2; 
  bool b_checkmated = black_king_condition & 1; 

  bool undo = false;

  assert(!(w_king_in_check && b_king_in_check));
  assert(!(w_checkmated && b_checkmated));

  // case where the current plyaer is getting checked by upcoming attack on the blocking piece
  undo = ((board->current_player == BLACK_P && b_king_in_check) || (board->current_player == WHITE_P && w_king_in_check));
  
  board->king_in_check = w_king_in_check || b_king_in_check;
  board->checkmated = w_checkmated || b_checkmated;

  if (undo) {
    printf("Cannot move the piece as the king is still on check\n");

    sp_piece->x = sp_x;
    sp_piece->y = sp_y;

    if (t_piece != NULL) {
      t_piece->taken = t_piece_eaten;
    }

    return false;
  } 

  // update last taken movement
  sp_piece->last_movement[0] = dx;
  sp_piece->last_movement[1] = dy;

  board->current_player = (board->current_player + 1) % 2;

  // eat the piece
  if (t_piece != NULL && !t_piece->taken) {
    t_piece->taken = true;
  } 

  return true;
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

Vector2 getNormalizedPosition(int x_offset, int y_offset, int curr_x, int curr_y, int block_size) {
  int pos_x_diff = curr_x - x_offset; 
  int pos_y_diff = curr_y - y_offset; 

  // inverted because array and coordinate axis is fucked up
  Vector2 result = {.x = pos_y_diff/block_size, .y=pos_x_diff/block_size};
  return result;
}

void initPieceSymbols(Texture2D (*piece_symbols)[16]) {

  Image white_pawn_image = LoadImage("assets/w-pawn.png");
  Image white_queen_image = LoadImage("assets/w-queen.png");
  Image white_king_image = LoadImage("assets/w-king.png");
  Image white_bishop_image = LoadImage("assets/w-bishop.png");
  Image white_knight_image = LoadImage("assets/w-knight.png");
  Image white_rook_image = LoadImage("assets/w-rook.png");

  Image black_pawn_image = LoadImage("assets/b-pawn.png");
  Image black_queen_image = LoadImage("assets/b-queen.png");
  Image black_king_image = LoadImage("assets/b-king.png");
  Image black_bishop_image = LoadImage("assets/b-bishop.png");
  Image black_knight_image = LoadImage("assets/b-knight.png");
  Image black_rook_image = LoadImage("assets/b-rook.png");

  ImageResize(&white_pawn_image, 50, 50);
  ImageResize(&white_queen_image, 50, 50);
  ImageResize(&white_king_image, 50, 50);
  ImageResize(&white_bishop_image, 50, 50);
  ImageResize(&white_knight_image, 50, 50);
  ImageResize(&white_rook_image, 50, 50);

  ImageResize(&black_pawn_image, 50, 50);
  ImageResize(&black_queen_image, 50, 50);
  ImageResize(&black_king_image, 50, 50);
  ImageResize(&black_bishop_image, 50, 50);
  ImageResize(&black_knight_image, 50, 50);
  ImageResize(&black_rook_image, 50, 50);


  (*piece_symbols)[pieceId(WHITE_P, PAWN)] = LoadTextureFromImage(white_pawn_image);
  (*piece_symbols)[pieceId(WHITE_P, KING)] = LoadTextureFromImage(white_king_image);
  (*piece_symbols)[pieceId(WHITE_P, QUEEN)] = LoadTextureFromImage(white_queen_image);
  (*piece_symbols)[pieceId(WHITE_P, KNIGHT)] = LoadTextureFromImage(white_knight_image);
  (*piece_symbols)[pieceId(WHITE_P, ROOK)] =  LoadTextureFromImage(white_rook_image);
  (*piece_symbols)[pieceId(WHITE_P, BISHOP)] = LoadTextureFromImage(white_bishop_image);

  (*piece_symbols)[pieceId(BLACK_P, PAWN)] = LoadTextureFromImage(black_pawn_image);
  (*piece_symbols)[pieceId(BLACK_P, KING)] = LoadTextureFromImage(black_king_image);
  (*piece_symbols)[pieceId(BLACK_P, QUEEN)] = LoadTextureFromImage(black_queen_image);
  (*piece_symbols)[pieceId(BLACK_P, KNIGHT)] = LoadTextureFromImage(black_knight_image);
  (*piece_symbols)[pieceId(BLACK_P, ROOK)] = LoadTextureFromImage(black_rook_image);
  (*piece_symbols)[pieceId(BLACK_P, BISHOP)] = LoadTextureFromImage(black_bishop_image);


  UnloadImage(white_pawn_image);
  UnloadImage(white_queen_image);
  UnloadImage(white_king_image);
  UnloadImage(white_bishop_image);
  UnloadImage(white_knight_image);
  UnloadImage(white_rook_image);

  UnloadImage(black_pawn_image);
  UnloadImage(black_queen_image);
  UnloadImage(black_king_image);
  UnloadImage(black_bishop_image);
  UnloadImage(black_knight_image);
  UnloadImage(black_rook_image);

}
void PlayChess() {
  printf("Running Game\n");

  Piece pieces[MAX_CHESS_PIECE] = {0};
  PieceMovement movements[TOTAL_PIECES] = {0};
  Texture2D piece_symbols[16] = {0};
  unsigned char taken_move[4] = {0};

  Board board = initBoard(&pieces, &movements);

  int width = 800;
  int height = 600;

  int rectangle_size = 50;
  int padding_size = 5;
  int block_size = rectangle_size + padding_size;

  int offset_x_mid = width/2 - CHESS_BOARD_WIDTH * (block_size/2);
  int offset_y_mid = height/2 - CHESS_BOARD_HEIGHT * (block_size/2);

  bool initial_color_white = true;
  bool mouse_pressed = false;

  Vector2 mouse_clicked_pos;

  InitWindow(width, height, "Chess Game");
  initPieceSymbols(&piece_symbols);


  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    // drawing the tiles
    for (int y = 0; y < CHESS_BOARD_HEIGHT; y++) {
      bool current_tile_black = !initial_color_white;
      for (int x = 0; x < CHESS_BOARD_WIDTH; x++) {
        DrawRectangle(x * block_size + offset_x_mid, y * block_size + offset_y_mid, rectangle_size, rectangle_size, current_tile_black ? BLACK : WHITE);
        current_tile_black = !current_tile_black;
      }
      initial_color_white = !initial_color_white;
    }

    for (int i = 0; i < board.current_piece_total; i++) {

      if (pieces[i].taken) {
        continue;
      }

      int pos_x = offset_x_mid + pieces[i].y * block_size;
      int pos_y = offset_y_mid + pieces[i].x * block_size;

      DrawTexture(piece_symbols[pieceId(pieces[i].piece_owner, pieces[i].piece_type)], pos_x, pos_y , WHITE);
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
      Vector2 mouse_pressed_pos = GetMousePosition();
      Vector2 normalized_clicked = getNormalizedPosition(offset_x_mid, offset_y_mid, mouse_pressed_pos.x, mouse_pressed_pos.y, block_size);

      Piece *piece = getPiece(&board, normalized_clicked.x, normalized_clicked.y);

      if (!mouse_pressed) {
        mouse_clicked_pos = normalized_clicked;
      } else {
        printf("%f, %f, %f, %f\n", mouse_clicked_pos.y, mouse_clicked_pos.x, normalized_clicked.y, normalized_clicked.x);
        movePiece(&board, mouse_clicked_pos.x, mouse_clicked_pos.y, normalized_clicked.x, normalized_clicked.y);
      }

      if (piece != NULL && mouse_pressed == false) {
        mouse_pressed = true;
      } else {
        mouse_pressed = false;
      }
      
    }

    EndDrawing();
  }

  for (int i = 0; i < 16; i++) {
    UnloadTexture(piece_symbols[i]);
  }

  CloseWindow();
}
