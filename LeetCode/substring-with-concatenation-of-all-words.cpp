// https://leetcode.com/problems/substring-with-concatenation-of-all-words

class Solution {

int n, wordLength, m, totalLength;
unordered_map<string, int> wordCount;
        
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        n = s.length();
        m = words.size();
        wordLength = words[0].length();
        totalLength = m * wordLength;

        for (string w: words)
            wordCount[w] ++;
        
        vector<int> ans;

        for (int leftStart = 0; leftStart < wordLength; leftStart ++)
            slidingWindow(leftStart, s, ans);

        return ans;
    }

    void slidingWindow(int l, const string & s, vector<int> & ans) {
        unordered_map<string, int> wordsFound;
        int wordsUsed = 0;
        bool excessWord = false;

        for (int r = l; r <= n-wordLength; r += wordLength) {
            string rightmostWord = s.substr(r, wordLength);
            if (wordCount.find(rightmostWord) == wordCount.end()) {
                wordsFound.clear();
                wordsUsed = 0;
                excessWord = false;
                l = r + wordLength;
            } else {

                while (r-l == totalLength || excessWord) {
                    string leftmostWord = s.substr(l, wordLength);
                    l += wordLength;
                    wordsFound[leftmostWord] --;

                    if (wordsFound[leftmostWord] >= wordCount[leftmostWord])
                        excessWord = false;
                    else 
                        wordsUsed --;
                }

                wordsFound[rightmostWord] ++;

                if (wordsFound[rightmostWord] <= wordCount[rightmostWord])
                    wordsUsed ++;
                else 
                    excessWord = true;
                
                if (wordsUsed == m && !excessWord)
                    ans.emplace_back(l);
            }
        }
    }
};
