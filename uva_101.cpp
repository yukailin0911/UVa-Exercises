/************************************************************
 * Title: The Blocks Problem
 * Language: C++11
 * Author: 林煜凱 (Lin, Yu-Kai)
 * Solved Date: Mar. 30, 2018
 ************************************************************/

#include <cstdio>
#include <cstring>
#include <cinttypes>
#include <algorithm>
#include <vector>
#include <list>

using ::std::vector;
using ::std::list;

class Chain {
    public:
        Chain() {}
        Chain(uint8_t s);

        void moveOnto(uint8_t a, uint8_t b);
        void moveOver(uint8_t a, uint8_t b);
        void pileOnto(uint8_t a, uint8_t b);
        void pileOver(uint8_t a, uint8_t b);
        void print();
        bool isOnSameStack(uint8_t a, uint8_t b);

    private:
        void _clearAbove(uint8_t n);

        vector<list<uint8_t> > _chain;
        vector<uint8_t> _pos;
};

int main() {
    uint8_t size = 0, a = 0, b = 0;
    char verb[5], prep[5];

    scanf("%" SCNu8, &size);
    Chain chain(size);

    while (1) {
        scanf("%s", verb);

        if (strcmp(verb, "quit") == 0) break;

        scanf("%" SCNu8 " %s %" SCNu8, &a, prep, &b);
        if ((a == b) || chain.isOnSameStack(a, b)) continue;

        if (strcmp(verb, "move") == 0) {
            if (strcmp(prep, "onto") == 0) chain.moveOnto(a, b);
            else chain.moveOver(a, b);
        } else {
            if (strcmp(prep, "onto") == 0) chain.pileOnto(a, b);
            else chain.pileOver(a, b);
        }
    }

    chain.print();

    return 0;
}

Chain::Chain(uint8_t s): _chain(s), _pos(s, 0) {
    for (uint8_t i = 0; i < s; ++i) {
        _chain[i].push_back(i);
        _pos[i] = i;
    }
}

void Chain::moveOnto(uint8_t a, uint8_t b) {
    _clearAbove(b);
    moveOver(a, b);
}

void Chain::moveOver(uint8_t a, uint8_t b) {
    _clearAbove(a);
    pileOver(a, b);
}

void Chain::pileOnto(uint8_t a, uint8_t b) {
    _clearAbove(b);
    pileOver(a, b);
}

void Chain::pileOver(uint8_t a, uint8_t b) {
    list<uint8_t> &fromBlocks = _chain[_pos[a]];
    list<uint8_t> &toBlocks = _chain[_pos[b]];
    list<uint8_t>::iterator it =
        std::find(fromBlocks.begin(), fromBlocks.end(), a);

    toBlocks.splice(toBlocks.end(), fromBlocks, it, fromBlocks.end());
    for (; it != toBlocks.end(); ++it) _pos[*it] = _pos[b];
}

void Chain::print() {
    for (size_t i = 0; i < _chain.size(); ++i) {
        printf("%lu:", i);

        list<uint8_t>::const_iterator cit = _chain[i].cbegin();

        while (cit != _chain[i].cend()) {
            printf(" %" PRIu8, *cit);
            ++cit;
        }
        putchar('\n');
    }
}

bool Chain::isOnSameStack(uint8_t a, uint8_t b) {
    return _pos[a] == _pos[b];
}

void Chain::_clearAbove(uint8_t n) {
    list<uint8_t> &blocks = _chain[_pos[n]];

    while (blocks.back() != n) {
        uint8_t i = blocks.back();

        _pos[i] = i;
        _chain[i].push_back(i);
        blocks.pop_back();
    }
}
