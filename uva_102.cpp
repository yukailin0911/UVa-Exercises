/************************************************************
 * Title: Ecological Bin Packing
 * Language: C++11
 * Author: 林煜凱 (Lin, Yu-Kai)
 * Solved Date: Apr.3 2018
 ************************************************************/

#include <cstdio>
#include <cinttypes>
#include <vector>
#include <algorithm>
#include <utility>

using ::std::vector;
using ::std::next_permutation;
using ::std::swap;

const size_t N = 3;

void parse(uint32_t bottles[N][N], size_t n);
void init(vector<size_t> &order, vector<size_t> &choice);
void printChoice(vector<size_t> &choice);

int main() {
    uint32_t bottles[N][N];

    while (scanf("%" SCNu32, bottles[0]) != EOF) {
        uint32_t sum = 0, nonMove = 0;
        vector<size_t> order(N, 0), choice(N, 0);

        parse(bottles, N);
        init(order, choice);

        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < N; ++j)
                sum += bottles[i][j];
        }

        do {
            uint32_t tmp = 0;

            for (size_t i = 0; i < N; ++i)
                tmp += bottles[i][order[i]];

            if (tmp > nonMove) {
                nonMove = tmp;
                choice = order;
            }
        } while (next_permutation(order.begin(), order.end()));

        printChoice(choice);
        printf(" %" PRIu32 "\n", sum - nonMove);
    }

    return 0;
}

void parse(uint32_t bottles[N][N], size_t n) {
    for (size_t i = 1; i < n * n; ++i)
        scanf(" %" SCNu32, bottles[i / n] + (i % n));

    for (size_t i = 0; i < n; ++i)
        swap(bottles[i][1], bottles[i][2]);
}

void init(vector<size_t> &order, vector<size_t> &choice) {
    for (size_t i = 0; i < order.size(); ++i)
        order[i] = choice[i] = i;
}

void printChoice(vector<size_t> &choice) {
    for (vector<size_t>::const_iterator it = choice.cbegin();
            it != choice.cend(); ++it) {
        if (*it == 0) putchar('B');
        else if (*it == 1) putchar('C');
        else putchar('G');
    }
}
