#ifndef _FEATURES_H_
#define _FEATURES_H_

#include "types.h"

void cleanup(char *s);
double sim_score(struct features *s1, struct features *s2);
void compute_features(char *text, struct features *feat);

#endif
