#include <stdio.h>
#include <stdlib.h> 

int mySqrt(int x) {
    int l = 0, r = x, ans = -1;
    while(l <= r) {
        int mid = l + (r - l) / 2; //这里没有用(l+r)/2是为了防止越界；
        if (mid * mid <= x){
            ans = mid;
            l = mid + 1;
        } 
        else r = mid - 1;
    }
    return ans;
}

void main() {
    printf("%d", mySqrt(8));
}