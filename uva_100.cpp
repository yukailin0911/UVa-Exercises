/************************************************************
 * Title: The 3n + 1 Problem
 * Language: C++11
 * Author: 林煜凱 (Lin, Yu-Kai)
 * Solved Date: Mar. 27, 2018
 ************************************************************/

#include <cstdio>
#include <cinttypes>
#include <unordered_map>
#include <algorithm>

using ::std::unordered_map;
using ::std::max;
using ::std::min;

uint32_t cycleLen(uint32_t n, unordered_map<uint32_t, uint32_t> &table);

int main() {
    uint32_t i = 0, j = 0, maxLen = 0;
    unordered_map<uint32_t, uint32_t> table = {{1, 1}};

    while (scanf("%" SCNu32 " %" SCNu32, &i, &j) != EOF) {
        uint32_t s = min(i, j), t = max(i, j);

        for (; s <= t; ++s)
            maxLen = max(maxLen, cycleLen(s, table));

        printf("%" PRIu32 " %" PRIu32 " %" PRIu32 "\n", i, j, maxLen);
        maxLen = 0;
    }
            
    return 0;
}

uint32_t cycleLen(uint32_t n, unordered_map<uint32_t, uint32_t> &table) {
    if (table.find(n) == table.end())
        table[n] = (n & 1) ?
            (2 + cycleLen((3 * n + 1) >> 1, table)) :
            (1 + cycleLen(n >> 1, table));

    return table[n];
}
