// https://leetcode.com/problems/accounts-merge

class Solution {


    class User {
        public:
        int id;
        string name;
        bool merged;
        set<string> emails;
        User(string name, int id) {
            this->name = name;
            this->emails = set<string>();
            this->id = id;
            this->merged = false;
        }

        void insert(string email) {
            this->emails.insert(email);
        }

        void mergeEmails(User & b) {
            this->emails.insert(b.emails.begin(), b.emails.end());
            b.merged = true;
        }

        void addEmail(string email) {
            this->emails.insert(email);
        }
    };

    int findParent(int p, vector<int> & parents) {
        if (p == parents[p])
            return p;
        return parents[p] = findParent(parents[p], parents);
    }

public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        int n = accounts.size();
        vector<int> parents(n);
        for(int i = 0; i < n; i ++)
            parents[i] = i;
        
        map<string, int> emailOwner;
        vector<User> users;
        int userIDs = 0;
        for(int i = 0; i < n; i ++) {
            vector<string> acc = accounts[i];
            int uid = -1;
            for (int j = 1; j < acc.size(); j ++) {
                string email = accounts[i][j];
                if (emailOwner.find(email) != emailOwner.end()) {
                    int eid = findParent(emailOwner[email], parents);
                    if (eid == uid)
                        continue;
                    else if (uid == -1)
                        uid = eid;
                    else {
                        users[uid].mergeEmails(users[eid]);
                        parents[eid] = uid;
                        emailOwner[email] = uid;
                    }
                    
                }
            }

            if (uid == -1) {
                uid = userIDs ++;
                users.emplace_back(User(accounts[i][0], uid));
            } 

            User &u = users[uid];
            for (int j = 1; j < acc.size(); j ++) {
                string email = accounts[i][j];
                u.addEmail(email);
                emailOwner[email] = uid;
            }
        }


        for (User & u: users) {
            int p = findParent(u.id, parents);
            if (p != u.id) {
                users[p].mergeEmails(u);
            }
        }

        vector<vector<string>> ans;

        for (const User & u: users) {
            if (u.merged)
                continue;
            vector<string> acc;
            acc.emplace_back(u.name);
            for (string email: u.emails) {
                acc.emplace_back(email);
            }
            ans.emplace_back(acc);
        }

        return ans;
    }
};
