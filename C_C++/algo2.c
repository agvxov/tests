// @BAKE gcc -o $*.out $@ -std=c2x -ldictate -lm
#include <dictate.h>

int myArray[]     = { 34, 23, 78, 41,  7, 87, 52, 36, 29, 42 };
int myArray2[]    = { 23, 12, 31, 76, 41, 43, 71, 23, 36, 91, 92, 42 };
int sortedArray[] = {  1,  2,  3,  6,  8, 10, 13, 14, 17, 20 };

#define len(x) (sizeof(x)/sizeof(*x))

int linearSearch(int array[], int n, int target) {
    for (int i = 0; i < n; i++) {
        if (array[i] == target) {
            return i;
        }
    }
    return -1;
}

int mySentineledArray[] = { 34, 23, 78, 41, 7, 87, 52, 36, 29, 42, 0 };

int sentinelSearch(int array[], int n, int target) {
    int i = 0;
    while (array[i] != target) {
        ++i;
    }
    return i;
}

// proc jumpSearch(a : varargs<int>; n : int; q : int) : int =
//  var j = (int)sqrt((float)n)
//  var i = j - 1
//  while i < n and a[i] < q:
//   i = i + j
//  i = i - j
//  for h in countup(i, i + b):
//   if a[h] == q:
//    return h
//  return -1
/// called as
// jumpSearch(sortedArray, len(sortedArray), 10)

#include <iso646.h>
#include <math.h>
int jumpSearch(int array[], int n, int target) {
    int step = (int)sqrt(n); // NOTE: automatically rounded down
    int i = step - 1;
    // jump until we run over
    while (i < n and array[i] < target) {
        i = i + step;
    }
    // jump back one
    i = i - step;
    // linear search the differene
    for (int h = i; h < i + step; h++) {
        if (array[h] == target) {
            return h;
        }
    }
    return -1;
}

/*
        proc binarySrc(a : var seq<int>, n : int, q : int) : int =
         var l = 0
         var r = n - 1
         while l <= r:
          let i = (int)( (l + r) / 2 )
          if a[i] < q:
           l = i + 1
          elif a[i] > q:
           r = i - 1
          else:
           return i
         return -1
      // called as
        binarySearch(sortedArray, len(sortedArray), 6)
      // returns
        3
*/

int binarySearch(int array[], int n, int target) {
    int left = 0;
    int right = n - 1;
    while (left <= right) {
        int i = (int)( (left + right) / 2 );
        if (array[i] < target) {
            left = i + 1;
        } else if (array[i] > target) {
            right = i - 1;
        } else {
            return i;
        }
    }
    return -1;
}

signed main(void) {
    //dictate(linearSearch(myArray, len(myArray), 23));
    /*
    int myTarget = 29;
    mySentineledArray[len(mySentineledArray)-1] = myTarget;
    dictate(sentinelSearch(mySentineledArray, len(mySentineledArray), myTarget));
    */
    dictate(binarySearch(sortedArray, len(sortedArray), 13), "\n");
    return 0;
}
