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
        void clearTop(uint8_t n);
        void print();
        bool isTheSameStack(uint8_t a, uint8_t b);

    private:
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
        if ((a == b) || chain.isTheSameStack(a, b)) continue;

        if (strcmp(verb, "move") == 0) {
            if (strcmp(prep, "onto") == 0) chain.moveOnto(a, b);
            else chain.moveOver(a, b);
        } else if (strcmp(verb, "pile") == 0) {
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
    clearTop(b);
    moveOver(a, b);
}

void Chain::moveOver(uint8_t a, uint8_t b) {
    clearTop(a);

    _chain[_pos[a]].pop_back();
    _chain[_pos[b]].push_back(a);
    _pos[a] = _pos[b];
}

void Chain::pileOnto(uint8_t a, uint8_t b) {
    clearTop(b);
    pileOver(a, b);
}

void Chain::pileOver(uint8_t a, uint8_t b) {
    list<uint8_t> &from = _chain[_pos[a]], &to = _chain[_pos[b]];
    list<uint8_t>::iterator it = from.begin();

    while (*it != a) ++it;
    to.splice(to.end(), from, it, from.end());
    for (; it != to.end(); ++it) _pos[*it] = _pos[b];
}

void Chain::clearTop(uint8_t n) {
    list<uint8_t> &blocks = _chain[_pos[n]];
    uint8_t i = blocks.back();

    while (i != n) {
        _pos[i] = i;
        _chain[i].push_back(i);

        blocks.pop_back();
        i = blocks.back();
    }
}

void Chain::print() {
    size_t size = _chain.size();

    for (size_t i = 0; i < size; ++i) {
        printf("%lu:", i);

        list<uint8_t>::const_iterator cit = _chain[i].cbegin();
        list<uint8_t>::const_iterator end = _chain[i].cend();

        while (cit != end) {
            printf(" %" PRIu8, *cit);
            ++cit;
        }
        printf("\n");
    }
}

bool Chain::isTheSameStack(uint8_t a, uint8_t b) {
    return _pos[a] == _pos[b];
}
