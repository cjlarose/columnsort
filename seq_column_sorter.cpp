#include "seq_column_sorter.h"
#include "matrix.h"

SeqColumnSorter::SeqColumnSorter(long n)
    :ColumnSorter(n) {
}

void SeqColumnSorter::sort() {
    #if DEBUG
    std::cout << "r = " << r << ", s = " << s << std::endl;
    std::cout << "SORT\n";
    #endif

    long j;
    for (j = 0; j < s; j++)
        left.sort_column(j);

    #if DEBUG
    std::cout << left;
    std::cout << "TRANSPOSE\n";
    #endif

    for (j = 0; j < s; j++)
        left.transpose_column(right, j);

    #if DEBUG
    std::cout << right;
    std::cout << "SORT\n";
    #endif

    for (j = 0; j < s; j++)
        right.sort_column(j);

    #if DEBUG
    std::cout << right;
    std::cout << "REVERSE TRANSPOSE\n";
    #endif

    for (j = 0; j < s; j++)
        right.reverse_transpose_column(left, j);

    #if DEBUG
    std::cout << left;
    std::cout << "SORT\n";
    #endif

    for (j = 0; j < s; j++)
        left.sort_column(j);

    #if DEBUG
    std::cout << left;
    std::cout << "SHIFT SORT\n";
    #endif

    for (j = 0; j < s; j++)
        left.sort_column_shift(j, r / 2);

    #if DEBUG
    std::cout << left;
    #endif
}
