/*
 * In-place implementation of QuickSort from
 * http://en.wikipedia.org/wiki/Quicksort#In-place_version
 */
int qs_partition(int *arr, int left, int right, int pivot_index) {
    int pivot_value = arr[pivot_index];

    int tmp = arr[pivot_index];
    arr[pivot_index] = arr[right];
    arr[right] = tmp;

    int store_index = left;
    int i;
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

void quicksort(int *arr, int left, int right) {
    int pivot_index, pivot_new_index;
    if (left < right) {
        pivot_index = (left + right) / 2;
        pivot_new_index = qs_partition(arr, left, right, pivot_index);
        quicksort(arr, left, pivot_new_index - 1);
        quicksort(arr, pivot_new_index + 1, right);
    }
}
