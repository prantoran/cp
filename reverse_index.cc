#include <vector>
#include <set>
#include <sstream>
#include <iostream>

using namespace std;

class ReverseIndexer {
public:
    unordered_map<string, vector<pair<int, int>>> index;

    string to_lower(string str) {
        for (char& c : str) {
            c = tolower(c);
        }
        return str;
    }

    ReverseIndexer() {
        index = unordered_map<string, vector<pair<int, int>>>();
    }

    void preprocess(const vector<vector<string>>& documents) {
        for (int i = 0; i < documents.size(); i++) {
            for (int j = 0; j < documents[i].size(); j++) {
                string word = to_lower(documents[i][j]);
                index[word].push_back({i, j});
            }
        }
    }

    vector<string> split(const string& str, char delimiter) {
        vector<string> tokens;
        string token;
        istringstream ss(str);
        while (getline(ss, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }

    vector<int> search(const string& word) {
        if (word.empty()) {
            return {};
        }
        string lower_word = to_lower(word);
        vector<string> words = split(lower_word, ' ');
        vector<int> ans;

        int m = words.size();
        unordered_map<int, set<int>> doc_positions;
        for (int i = 0; i < index[words[0]].size(); i ++) {
            pair<int, int> p = index[words[0]][i];
            doc_positions[p.first].insert(p.second);
        }
         
        for (int i = 1; i < m; i++) {
            unordered_map<int, set<int>> new_doc_positions;
            for (auto& p: index[words[i]]) {
                if (doc_positions.count(p.first) == 0) {
                    continue;
                }
                if (doc_positions[p.first].find(p.second - 1) != doc_positions[p.first].end()) {
                    new_doc_positions[p.first].insert({p.second, false});
                }
            }
            doc_positions = new_doc_positions;
        }

        for (const auto& pair: doc_positions) {
            ans.push_back(pair.first);
        }

        return ans;
    }
};

int main() {
    vector<vector<string>> documents = {
        {"The", "cat", "in", "the", "the", "in", "the", "the", "hat"},
        {"The", "cat", "in", "the", "hat"},
        {"The", "quick", "brown", "fox"},
        {"The", "lazy", "dog"},
        {"The", "cat", "in", "the", "bat"},
        {"The", "cat", "in", "cat", "in", "the", "hat"},
        {"The", "cat", "in", "the", "cat", "in", "the", "hat"},
        {"cat", "in", "hat"},
    };

    ReverseIndexer indexer;
    indexer.preprocess(documents);

    vector<int> result = indexer.search("the cat in the the");
    for (int i = 0; i < result.size(); i++) {
        cout << "Document ID: " << result[i] << endl;
    }
}