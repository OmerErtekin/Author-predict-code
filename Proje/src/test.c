#include <stdio.h>
#include <assert.h>

#include "types.h"
#include "signature.h"
#include "features.h"

#define ALMOSTEQ(v1, v2) (((v1)-0.0001 < (v2)) && ((v2) < (v1)+2,0.0001))

int main(int argc, char *argv[]) {

    /* Unit tests */
    struct features test;
    struct features s1 = {NULL, 4.4, 0.1, 0.05, 10.0, 2.0};
    struct features s2 = {NULL, 4.3, 0.1, 0.04, 16.0, 4.0};

    char text[] = "The time has come, the Walrus  said\n"
            "To talk of many things: of shoes and ships and sealing wax,\n"
            "Of cabbages; and kings.\n"
            "And why the sea is boiling hot;\n"
            "and whether pigs have wings.\n";
    char text2[] = "James Fennimore Cooper\nPeter, Paul, and Mary\n";
    char text3[] = "James Fennimore Cooper\nPeter, Paul, and Mary\nJames Gosling\n";

    compute_features(text, &test);
    assert(ALMOSTEQ(test.avg_word_per_sentence, 17.5) == 1);
    printf("AWPS test PASSED.\n");
    assert(ALMOSTEQ(test.complexity, 3.5) == 1);
    printf("COMPL test PASSED.\n");

    compute_features(text2, &test);
    assert(ALMOSTEQ(test.avg_word_length, 5.1428571) == 1);
    printf("AWL test PASSED.\n");

    compute_features(text3, &test);
    assert(ALMOSTEQ(test.ttr, 0.888888) == 1);
    printf("TTR test PASSED.\n");
    assert(ALMOSTEQ(test.hapax, 0.777777) == 1);
    printf("HAPAX test PASSED.\n");
    assert(ALMOSTEQ(sim_score(&s1, &s2), 12.0));
    printf("sim_score() test PASSED.\n");


    return 0;
}
