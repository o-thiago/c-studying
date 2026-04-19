#include <stdio.h>
#include <stdlib.h>

unsigned bitcount(unsigned x) {
    unsigned b = 0;
    while (x) {
        x &= (x - 1);
        ++b;
    }
    return b;
}

// In a two’s complement number system, x &= (x−1) deletes the rightmost 1-bit
// in x. Explain why. Use this observation to write a faster version of
// bitcount.
//
// RESPONSE: This is because by subtracting by 1 we flip the lsb. Thus when we
// do a `&` operation on the resulting value as in `x & (x - 1)` we are always
// comparing two different lsb, either 0 or 1, which in turn always is 0. So all
// the values will end up unchanged except the lsb which will be 0, therefore
// deleted.
int main(void) {
    printf("%d", bitcount(0b10101));
    return EXIT_SUCCESS;
}
