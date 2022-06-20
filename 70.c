#include <stdio.h>
#include <stdlib.h>

//解法1：递归；
// 时间复杂度:O(2^n)；空间复杂度:O(n)。其中n为递归树的深度；
int climbStairs_recursion(int n) {
    if (n == 1) return 1; 
    if (n == 2) return 2; //递归终止条件；
    return (climbStairs_recursion(n-1)+climbStairs_recursion(n-2));
}


//解法2：记忆化递归
//时间复杂度:O(n)；空间复杂度:O(n)；
int climbStairsMemo(int n, int memo[]) {
    if(memo[n] > 0) return memo[n];
    if (n == 1) memo[n] = 1;
    else if (n == 2) memo[n] = 2;
    else memo[n] = climbStairsMemo(n - 1, memo) + climbStairsMemo(n - 2, memo);
    return memo[n];
}

int climbStairs_recursion2(int n) {
    int *memo;
    memo = (int *)malloc(sizeof(int) * (n + 1)); //memo[0]没有用，在memo[1]~memo[n]作为备忘录；
    for (int i = 0; i <= n; i++) memo[i] = 0;
    return climbStairsMemo(n, memo);
}


//解法3：动态规划
//时间复杂度:O(n)；空间复杂度:O(n)；
int climbStairs_dp(int n) {

    int *dp;
    dp = (int *)malloc(sizeof(int) * (n + 1)); //memo[0]没有用，在memo[1]~memo[n]作为备忘录；
    for (int i = 0; i <= n; i++) dp[i] = 0;
    
    dp[1] = 1;
    dp[2] = 2;
    for (int i = 3; i <= n; i++) dp[i] = dp[i-1] + dp[i-2];
    return dp[n];
}


//解法4：采用滚动数组法的动态规划；
//时间复杂度:O(n)；空间复杂度:O(1)；
int climbStairs_dp2(int n) { //爬到第n级台阶；
    int p = 0, q = 0, r = 1; //r是爬到第n级台阶的方法；
    for (int i = 1; i <= n; i++) {
        p = q;
        q = r;
        r = p + q;
    }
    return r;   
}


void main() {
    printf("%d", climbStairs_dp2(4));
}