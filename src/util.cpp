

#include "util.h"

int min(int row, int row1) {
    if (row < row1) {
        return row;
    }
    return row1;
}

int max(int row, int row1) {
    if (row > row1) {
        return row;
    }
    return row1;
}
