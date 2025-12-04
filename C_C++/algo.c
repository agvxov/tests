// @BAKE gcc -o $*.out $@ -std=c2x -ldictate
#include <dictate.h>

int myArray[]     = { 34, 23, 78, 41,  7, 87, 52, 36, 29, 42 };
int myArray2[]    = { 23, 12, 31, 76, 41, 43, 71, 23, 36, 91, 92, 42 };
int sortedArray[] = {  1,  2,  3,  6,  8, 10, 13, 14, 17, 20 };

#define len(x) (sizeof(x)/sizeof(*x))

int summary(int* a, int n){
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum = sum + a[i];
    }
    return sum;
}

bool any(int * array, int n, int target) {
    for (int i = 0; i < n; i++) {
        if (array[i] == target) {
            // NOTE: if this weren't a function and we were setting
            //        a result variable directly,
            //        it would be crucial to `break` to avoid redundant checks
            return true;
        }
    }
    return false;
}

int count_equals(int * array, int n, int target) {
    int result = 0;
    for (int i = 0; i < n; i++) {
        if (array[i] == target) {
            ++result;
        }
    }
    return result;
}

int count_lesser(int * array, int n, int target) {
    int result = 0;
    for (int i = 0; i < n; i++) {
        if (array[i] < target) {
            ++result;
        }
    }
    return result;
}

bool equals(int a, int b)      { return a == b; }
bool lesser_than(int a, int b) { return a < b; }

int count(int * array, int n, int target, bool (*callback)(int,int)) {
    int result = 0;
    for (int i = 0; i < n; i++) {
        if (callback(array[i], target)) {
            ++result;
        }
    }
    return result;
}

void select_lesser(int * source, int n, int target, int * destination) {
    for (int i = 0, h = 0; i < n; i++) {
        if (source[i] < target) {
            destination[h] = source[i];
            ++h;
        }
    }
}

#include <limits.h>
int min(int * array, int n) {
    int result = INT_MAX;
    for (int i = 0; i < n; i++) {
        if (array[i] < result) {
            result = array[i];
        }
    }
    return result;
}

int intersection(int * array1, int n1, int * array2, int n2, int * destination) {
    int d = 0;
    for (int i = 0; i < n1; i++) {
        for (int h = 0; h < n2; h++) {
            if (array1[i] == array2[h]) {
                destination[d] = array1[i];
                ++d;
                break;
            }
        }
    }
    return d;
}

void merge(int * array1, int n1, int * array2, int n2, int * destination) {
    int d = 0;
    for (int i = 0; i < n1; i++) {
        destination[d] = array1[i];
        ++d;
    }
    for (int i = 0; i < n2; i++) {
        destination[d] = array2[i];
        ++d;
    }
}

int union_f(int array1[], int n1, int array2[], int n2, int destination[]) {
    int d = 0;
    for (int i = 0; i < n1; i++) {
        if (any(destination, d, array1[i])) { continue; }
        destination[d] = array1[i];
        ++d;
    }
    for (int i = 0; i < n2; i++) {
        if (any(destination, d, array2[i])) { continue; }
        destination[d] = array2[i];
        ++d;
    }
    return d;
}

signed main(void) {
    //dictate(count_lesser(myArray, len(myArray), 40), "\n");
    /*
    int myTarget = 40;
    int n = count_lesser(myArray, len(myArray), myTarget);
    int destination[n];
    select_lesser(myArray, len(myArray), myTarget, destination);
    for (int i = 0; i < n; i++) {
        dictate(destination[i], ", ");
    }
    */
    /*
    int destination[len(myArray2)];
    int n = intersection(myArray, len(myArray), myArray2, len(myArray2), destination);
    for (int i = 0; i < n; i++) {
        dictate(destination[i], ", ");
    }
    */
    /*
    int destination[len(myArray) + len(myArray2)];
    merge(myArray, len(myArray), myArray2, len(myArray2), destination);
    for (int i = 0; i < len(myArray) + len(myArray2); i++) {
        dictate(destination[i], ", ");
    }
    */
    int destination[len(myArray) + len(myArray2)];
    int n = union_f(myArray, len(myArray), myArray2, len(myArray2), destination);
    for (int i = 0; i < n; i++) {
        dictate(destination[i], ", ");
    }
    return 0;
}
