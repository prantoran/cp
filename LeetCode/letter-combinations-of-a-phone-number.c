//https://leetcode.com/problems/letter-combinations-of-a-phone-number

// hashmap, hashing using HASH_ADD, HASH_FIND and UT_hash_handle

struct letters {
    char id;
    const char* value;
    UT_hash_handle hh;
};

void dfs(
        struct letters** letterHashHead,
        const char* digits,
        const int n,
        int i,
        char* path,
        int pathLen,
        char** ans,
        int* returnSize
    ) {
    if (pathLen == n) {
        path[n] = '\0';
        ans[*returnSize] = (char*)malloc((pathLen+1)*sizeof(char));
        strncpy(ans[*returnSize], path, pathLen + 1);
        (*returnSize)++;
        return;
    }
    struct letters* s;
    HASH_FIND(hh, *letterHashHead, &digits[i], sizeof(char), s);
    const char* possibleLetters = s->value;
    // printf("i: %d, possibleLetters: %s\n", i, possibleLetters);
    while (*possibleLetters) {
        path[pathLen] = *possibleLetters;
        dfs(letterHashHead, digits, n, i + 1, path, pathLen + 1, ans, returnSize);
        possibleLetters++;
    }
}

char** letterCombinations(char* digits, int* returnSize) {
    *returnSize = 0;
    int n = strlen(digits);
    // printf("n: %d\n", n);
    if (n == 0) {
        return NULL;
    }
    struct letters  m2 = {'2', "abc"}, m3 = {'3', "def"}, m4 = {'4', "ghi"},
                    m5 = {'5', "jkl"}, m6 = {'6', "mno"}, m7 = {'7', "pqrs"},
                    m8 = {'8', "tuv"}, m9 = {'9', "wxyz"}, *s,
                    *letterHashHead = NULL;
    
    HASH_ADD(hh, letterHashHead, id, sizeof(char), &m2);
    HASH_ADD(hh, letterHashHead, id, sizeof(char), &m3);
    HASH_ADD(hh, letterHashHead, id, sizeof(char), &m4);
    HASH_ADD(hh, letterHashHead, id, sizeof(char), &m5);
    HASH_ADD(hh, letterHashHead, id, sizeof(char), &m6);
    HASH_ADD(hh, letterHashHead, id, sizeof(char), &m7);
    HASH_ADD(hh, letterHashHead, id, sizeof(char), &m8);
    HASH_ADD(hh, letterHashHead, id, sizeof(char), &m9);

    char** ans = (char**)malloc((4*4*4*4) * sizeof(char*));
    char* path = (char*)malloc(5 * sizeof(char));
    
    dfs(&letterHashHead, digits, n, 0, path, 0, ans, returnSize);
    return ans;
}
