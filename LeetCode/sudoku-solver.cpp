// https://leetcode.com/problems/sudoku-solver

class Solution {

    const static int SIZE = 9;
    const static int SIZESQRT = 3;

    class CandidateNode {
        public:
        int digit, row, col;
        CandidateNode() {}
        CandidateNode(int digit, int row, int col) {
            this->digit = digit;
            this->row = row;
            this->col = col;
        }

        string getName() {
            return "(" + to_string(digit) + ", " + to_string(row) + ", " + to_string(col) + ")";
        }
    };


    class Node {
        void setupAttrs(Node * defaultNode) {
            l = defaultNode;
            r = defaultNode;
            u = defaultNode;
            d = defaultNode;
            constraintColumn = defaultNode;
            size = 0;
        }

        public:
        Node * l, *r, *u, *d;
        string name;
        int size;
        CandidateNode * c;

        Node * constraintColumn;

        Node() {
            setupAttrs(this);
        }

        Node(string name) {
            setupAttrs(this);
            this->name = name;
        }

        Node(string name, CandidateNode * c) {
            setupAttrs(this);
            this->name = name;
            this->c = c;
        }
    };


    class DLX {
        Node * head, *columnTop;
        map<pair<int, int>, Node*> posConstraints, rowConstraints, colConstraints, gridConstraints;
        
        map<tuple<int, int, int>, Node *> candidates;
        
        void addConstraintColumn(Node * u) {
            columnTop->r->l = u;
            u->r = columnTop->r;
            columnTop->r = u;
            u->l = columnTop;
            columnTop = u;
        }

        void setupConstraintsForPositions() {
            for (int i = 0; i < SIZE; i ++) {
                for (int j = 0; j < SIZE; j ++) {
                    Node * u = new Node("pos" + to_string(i) + to_string(j));
                    addConstraintColumn(u);
                    posConstraints[{i, j}] = u;
                }
            }
        }

        void setupConstraintsForRows() {
            for (int i = 0; i < SIZE; i ++) {
                for (int digit = 1; digit <= SIZE; digit ++) {
                    Node *u = new Node("row" + to_string(i) + "_d" + to_string(digit));
                    addConstraintColumn(u);
                    rowConstraints[{i, digit}] = u;
                }
            }
        }

        void setupConstraintsForCols() {
            for (int j = 0; j < SIZE; j ++) {
                for (int digit = 1; digit <= SIZE; digit ++) {
                    Node *u = new Node("col" + to_string(j) + "_d" + to_string(digit));
                    addConstraintColumn(u);
                    colConstraints[{j, digit}] = u;
                }
            }
        }

        void setupConstraintsForGrid() {
            for (int g = 0; g < SIZE; g ++) {
                for (int digit = 1; digit <= SIZE; digit ++) {
                    Node *u = new Node("grid" + to_string(g) + "_d" + to_string(digit));
                    addConstraintColumn(u);
                    gridConstraints[{g, digit}] = u;
                }
            }
        }

        public:

        stack<CandidateNode *> solutions;
        
        DLX() {
            head = new Node("head");
            columnTop = head;

            posConstraints = map<pair<int, int>, Node *>();
            rowConstraints = map<pair<int, int>, Node *>();
            colConstraints = map<pair<int, int>, Node *>();
            gridConstraints = map<pair<int, int>, Node *>();

            candidates = map<tuple<int, int, int>, Node *>();

            setupConstraintsForPositions();
            setupConstraintsForRows();
            setupConstraintsForCols();
            setupConstraintsForGrid();
        }

        void printColumns() {
            Node * cur = head;
            do {
                cout << cur->name << "\n";
                cur = cur->r;
            } while(cur != head);
        }

        void connectRow(Node * posNode, Node * rowNode, Node * colNode, Node * gridNode) {
            posNode->r = rowNode;
            rowNode->l = posNode;

            rowNode->r = colNode;
            colNode->l = rowNode;

            colNode->r = gridNode;
            gridNode->l = colNode;

            gridNode->r = posNode;
            posNode->l = gridNode;
        }

        void addRowNodeToCol(Node * constraint, Node * row) {
            constraint->u->d = row;
            row->u = constraint->u;
            row->d = constraint;
            constraint->u = row;

            row->constraintColumn = constraint;
            constraint->size ++;
        }

        void addOptionRow(int digit, int i, int j, int g) {
            Node * posConstraint = posConstraints[{i, j}];
            Node * rowConstraint = rowConstraints[{i, digit}];
            Node * colConstraint = colConstraints[{j, digit}];
            Node * gridConstraint = gridConstraints[{g, digit}];

            CandidateNode * c = new CandidateNode(digit, i, j);

            Node * posNode = new Node("pos_" + c->getName(), c);
            Node * rowNode = new Node("row_" + c->getName(), c);
            Node * colNode = new Node("col_" + c->getName(), c);
            Node * gridNode = new Node("grid_" + c->getName(), c);

            connectRow(posNode, rowNode, colNode, gridNode);

            addRowNodeToCol(posConstraint, posNode);
            addRowNodeToCol(rowConstraint, rowNode);
            addRowNodeToCol(colConstraint, colNode);
            addRowNodeToCol(gridConstraint, gridNode);
        }

        void cover(Node * constraintCol) {
            constraintCol->r->l = constraintCol->l;
            constraintCol->l->r = constraintCol->r;
            for (Node * i = constraintCol->d; i != constraintCol; i = i->d) {
                for (Node * j = i->r; j != i; j = j->r) {
                    j->d->u = j->u;
                    j->u->d = j->d;
                }
            }
        }

        void uncover(Node * constraintCol) {
            for (Node * i = constraintCol->u; i != constraintCol; i = i->u) {
                for (Node * j = i->l; j != i; j = j->l) {
                    j->d->u = j;
                    j->u->d = j;
                }
            }
            constraintCol->r->l = constraintCol;
            constraintCol->l->r = constraintCol;
        }

        Node * getConstraintWithLeastOptions() {
            // This is called after ensuring head->r != head
            Node * u = head->r;
            Node * ans = u;
            while (u != head) {
                if (u->size < ans->size) {
                    ans = u;
                }
                u = u->r;
            } 

            return ans;
        }
        
        bool search(int step) {
            if (head->r == head) return true;
            bool found = false;
            Node * constraint = getConstraintWithLeastOptions();

            if (constraint != constraint->d) {
                // there are valid options for the constraint 
                // (exactly single occurrence of 1 in the column)

                cover(constraint);

                for (Node * r = constraint->d; r != constraint; r = r->d) {
                    solutions.push(r->c);
                    for (Node * j = r->r; j != r; j = j->r) {
                        cover(j->constraintColumn);
                        j->constraintColumn->size --;
                    }

                    if (search(step + 1)) {
                        found = true;
                        break;
                    }
                    
                    for (Node * j = r->l; j != r; j = j->l) {
                        uncover(j->constraintColumn);
                        j->constraintColumn->size ++;
                    }

                    solutions.pop();
                }

                uncover(constraint);
            } 
            return found;
        }

        void solve() {
            solutions = stack<CandidateNode *>();
            bool found = search(0);
        }
    };

    vector<set<int>> grid;
    vector<set<int>> rows;
    vector<set<int>> cols;
    
    int gridID(int i, int j) {
        return (i/SIZESQRT)*3 + j/SIZESQRT;
    }

    bool checkValidOption(int digit, int i, int j, int g) {
        if (rows[i].find(digit) != rows[i].end()) return false;
        if (cols[j].find(digit) != cols[j].end()) return false;
        if (grid[g].find(digit) != grid[g].end()) return false;
        return true;
    }

public:
    void solveSudoku(vector<vector<char>>& board) {
        grid = vector<set<int>>(SIZE);
        rows = vector<set<int>>(SIZE);
        cols = vector<set<int>>(SIZE);

        DLX dlx = DLX();
        // dlx.printColumns();
        
        for (int i = 0; i < SIZE; i ++) {
            for (int j = 0; j < SIZE; j ++) {
                char c = board[i][j];
                if (c != '.') {
                    int u = c - '0';
                    rows[i].insert(u);
                    cols[j].insert(u);
                    grid[gridID(i, j)].insert(u);
                }
            }
        }

        for (int i = 0; i < SIZE; i ++) {
            for (int j = 0; j < SIZE; j ++) {
                if (board[i][j] == '.') {
                    for (int digit = 1; digit <= 9; digit ++) {
                        if (checkValidOption(digit, i, j, gridID(i, j))) {
                            dlx.addOptionRow(digit, i, j, gridID(i, j));
                        }
                    }
                } else {
                    int digit = board[i][j] - '0';
                    dlx.addOptionRow(digit, i, j, gridID(i, j));
                }
            }
        }

        dlx.solve();

        while (!dlx.solutions.empty()) {
            CandidateNode * u = dlx.solutions.top();
            dlx.solutions.pop();
            board[u->row][u->col] = u->digit + '0';
        }
    }
};
