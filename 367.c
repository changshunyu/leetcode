#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


bool isPerfectSquare(int num) {
    if (num == 1) return true;
    int left = 2, right = (num / 2) + 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if ((mid * mid) < num) {
            left = mid + 1;
        }
        else if ((mid * mid) > num) right = mid - 1;
        else return true;
    }
    return false;
}

void main() {
    printf("%d", isPerfectSquare(4));
}
