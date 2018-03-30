/************************************************************
 * Title: The Blocks Problem
 * Language: C++11
 * Author: 林煜凱 (Lin, Yu-Kai)
 * Solved Date:
 ************************************************************/

#include <cstdio>
#include <cstring>
#include <cinttypes>
#include <vector>

using ::std::vector;

class Block {
    public:
        Block(): _num(0), prev(NULL), next(NULL) {}
        Block(uint8_t i, Block *p, Block *n): _num(i), prev(p), next(n) {}

        uint8_t num() { return _num; }

        Block *prev;
        Block *next;

    private:
        uint8_t _num;
};

class Chain {
    public:
        Chain() {}
        Chain(size_t s): _chain(s, NULL), _pos(s, 0) {}

        void moveOnto(uint8_t a, uint8_t b);
        void moveOver(uint8_t a, uint8_t b);
        void pileOnto(uint8_t a, uint8_t b);
        void pileOver(uint8_t a, uint8_t b);
        void insertAfter(uint8_t num, Block* blk);
        void append(uint8_t pos, Block *blk);
        void print();

    private:
        vector<Block *> _chain;
        vector<uint8_t> _pos;
};

int main() {
    size_t size = 0;
    uint8_t a = 0, b = 0;
    char verb[5], prep[5];

    scanf("%lu", &size);
    Chain chain(size);

    while (1) {
        scanf("%s", verb);

        if (strcmp(verb, "move") == 0) {
            scanf("%" SCNu8 " %s %" SCNu8, &a, prep, &b);
        } else if (strcmp(verb, "pile") == 0) {
            scanf("%" SCNu8 " %s %" SCNu8, &a, prep, &b);
        } else
            break;
    }

    chain.print();

    return 0;
}
