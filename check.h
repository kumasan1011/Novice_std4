#ifndef _CHECK_H_
#define _CHECK_H_ 


int is_check_from_bishop(struct Position *pos, int dir,Board sq);
int is_check_from_rook(struct Position *pos, int dir,Board sq);
int is_check_from_lance(struct Position *pos, int dir,Board sq);
int is_check_from_normal(struct Position *pos, Board sq);
int is_in_check(struct Position*);

#endif //_CHECK_H_