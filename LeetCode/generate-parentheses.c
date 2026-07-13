// https://leetcode.com/problems/generate-parentheses

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

void dfs(
    char * cur,
    int pos,
    char *** ans,
    int * returnSize,
    int * capacity,
    int lft,
    int rgt
) {
    if (!lft && !rgt) {
        cur[pos] = '\0';
        if (*returnSize >= *capacity) {
            *capacity <<= 1;
            *ans = (char**)realloc(*ans, (*capacity) * sizeof(char*));
        }
        (*ans)[*returnSize] = (char*)malloc((pos+1)* sizeof(char));
        strcpy((*ans)[*returnSize], cur);
        (*returnSize) ++;
        return;
    }
    if (lft > 0) {
        cur[pos] = '(';
        dfs(cur, pos+1, ans, returnSize, capacity, lft-1, rgt);
    }
    if (lft < rgt) {
        cur[pos] = ')';
        dfs(cur, pos+1, ans, returnSize, capacity, lft, rgt - 1);
    }
}

char** generateParenthesis(int n, int* returnSize) {
    *returnSize = 0;
    int capacity = 16;
    char ** ans = (char **)malloc(capacity * sizeof(char*));
    char * cur = (char *)malloc((2*n + 1) * sizeof(char));
    dfs(cur, 0, &ans, returnSize, &capacity, n, n);
    free(cur);
    return ans;
}
