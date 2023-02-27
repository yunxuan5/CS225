#pragma once

#define PBSTR "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
#define PBWIDTH 60

#include <algorithm>
#include <set>
#include <stack>
#include <vector>
#include "graph.h"

using std::vector;

#ifndef INF
const double INF = 99999999;
#endif

vector<double> brandes(const Graph & g);

inline void printProgress2(double percentage) {
    int val = (int) (percentage * 100);
    int lpad = (int) (percentage * PBWIDTH);
    int rpad = PBWIDTH - lpad;
    printf("\r%3d%% [%.*s%*s]", val, lpad, PBSTR, rpad, "");
    fflush(stdout);
}
