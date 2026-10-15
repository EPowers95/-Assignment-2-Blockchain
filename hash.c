#include "hash.h"

unsigned char* SSHA(const unsigned char* msg, size_t length) {
    unsigned char A, B, C, D, E; //Initial Seed Value
    A = 56;
    B = 99;
    C = 102;
    D = 67;
    E = 76;

    for (int i = 0; i < length; i++) {
        for (int round = 0; round < 8; round++) {
            unsigned char new_A;
            unsigned char new_B;
            unsigned char new_C;
            unsigned char new_D;
            unsigned char new_E;
            new_A = E;
            new_B = A;
            new_C = (A >> 2) + E;
            new_D = (A >> 2) ^ (B >> 1);
            new_E = (B >> 1) + (msg[i]) + ((C & B) | (C & D)); 
            A = new_A;
            B = new_B;
            C = new_C;
            D = new_D;
            E = new_E;
        }
    }
    unsigned char* digest = (unsigned char*)malloc(DIGEST_SIZE * sizeof(unsigned char));
    digest[0] = A;
    digest[1] = B;
    digest[2] = C;
    digest[3] = D;
    digest[4] = E;
    return digest;
}

#include <cstddef>

unsigned char* SSHA2(const unsigned char* msg, size_t length)
{
    unsigned char A = 56;
    unsigned char B = 99;
    unsigned char C = 102;
    unsigned char D = 67;
    unsigned char E = 76;

    for (size_t i = 0; i < length; i++)
    {
        unsigned char shiftA2 = A >> 2;                    // A -> >>2
        unsigned char shiftB1 = B >> 1;                    // B -> >>1
        unsigned char andBC   = B & C;                     // left  &
        unsigned char andCD   = C & D;                     // right &
        unsigned char orOut   = andBC | andCD;             // |

        unsigned char newA = E;                            // E wraps around to A
        unsigned char newB = A;                            // A moves down to B
        unsigned char newC = shiftA2 + E;                  // middle +
        unsigned char newD = shiftA2 ^ shiftB1;            // ^
        unsigned char newE = shiftB1 + orOut + msg[i];     // right +

        A = newA;
        B = newB;
        C = newC;
        D = newD;
        E = newE;
    }

    unsigned char* result = (unsigned char*)malloc(DIGEST_SIZE * sizeof(unsigned char));
    result[0] = A;
    result[1] = B;
    result[2] = C;
    result[3] = D;
    result[4] = E;

    return result;
}

int digest_equal(struct Digest digest1, struct Digest digest2) {
    return ((digest1.hash0 == digest2.hash0) &&
        (digest1.hash1 == digest2.hash1) &&
        (digest1.hash2 == digest2.hash2) &&
        (digest1.hash3 == digest2.hash3) &&
        (digest1.hash4 == digest2.hash4));
}

void printDigest(struct Digest digest) {
    printf("%d %d %d %d %d\n", digest.hash0, digest.hash1, digest.hash2, digest.hash3, digest.hash4);
}