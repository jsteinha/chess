#include "attack.h"
#include "book.h"
#include "hash.h"
#include "move_do.h"
#include "option.h"
#include "pawn.h"
#include "piece.h"
#include "protocol.h"
#include "random.h"
#include "square.h"
#include "trans.h"
#include "util.h"
#include "value.h"
#include "vector.h"
#include "fen.h"
#include "eval.h"
#include "material.h"
#include "pst.h"

using namespace engine;

static bool has_init = false;

int gnuchess_eval(const char* fen) {
  board_t bd;

  if(!has_init) {
     my_random_init(); // for opening book
     option_init();

     square_init();
     piece_init();
     pawn_init_bit();
     value_init();
     vector_init();
     attack_init();
     move_do_init();

     random_init();
     hash_init();

     trans_init(Trans);
     book_init();

/*
      if (option_get_bool("OwnBook")) {
         book_open(option_get_string("BookFile"));
      }
*/

     trans_alloc(Trans);

     pawn_init();
     pawn_alloc();

     material_init();
     material_alloc();

     pst_init();
     eval_init();
  }

  board_from_fen(&bd, fen);
  return eval(&bd);
}
