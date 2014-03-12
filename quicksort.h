#ifndef _QUICKSORT_H_
#define _QUICKSORT_H_

/*
 * In-place implementation of QuickSort from
 * http://en.wikipedia.org/wiki/Quicksort#In-place_version
 */
long qs_partition(long *arr, long left, long right, long pivot_index) {
    long pivot_value = arr[pivot_index];

    long tmp = arr[pivot_index];
    arr[pivot_index] = arr[right];
    arr[right] = tmp;

    long store_index = left;
    long i;
    for (i = left; i < right; i++)
        if (arr[i] <= pivot_value) {
            tmp = arr[i];
            arr[i] = arr[store_index];
            arr[store_index] = tmp;

            store_index++;
        }

    tmp = arr[store_index];
    arr[store_index] = arr[right];
    arr[right] = tmp;
    return store_index;
}

void quicksort(long *arr, long left, long right) {
    long pivot_index, pivot_new_index;
    if (left < right) {
        pivot_index = (left + right) / 2;
        pivot_new_index = qs_partition(arr, left, right, pivot_index);
        quicksort(arr, left, pivot_new_index - 1);
        quicksort(arr, pivot_new_index + 1, right);
    }
}

#endif
