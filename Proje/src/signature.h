#ifndef _SIGNATURE_H_

#include "types.h"

struct features** read_signatures(int *nr_author);
void free_signatures(struct features **authors);

#endif
