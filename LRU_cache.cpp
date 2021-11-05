class LRUCache {
    
    class DLinkedNode {
        public:
        DLinkedNode *prev, *next;
        int key, value;
    };
    
    int capacity, size;
    unordered_map<int, DLinkedNode*> cache;
    DLinkedNode *head, *tail;
    
    void removeNode(DLinkedNode * node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    
    void addNode(DLinkedNode * node) {
        node->prev = this->head;
        node->next = this->head->next;
        this->head->next->prev = node;
        this->head->next = node;
    }
    
    void moveToHead(DLinkedNode * node) {
        removeNode(node);
        addNode(node);
    }
    
    DLinkedNode * popTail() {
        auto node = this->tail->prev;
        removeNode(node);
        return node;
    }
    
public:
    LRUCache(int capacity) {
        this->capacity = capacity;
        this->size = 0;
        this->head = new DLinkedNode();
        this->tail = new DLinkedNode();
        this->head->next = this->tail;
        this->tail->prev = this->head;
        this->cache.clear();
    }
    
    int get(int key) {
        auto node = this->cache[key];
        if (node == NULL) return -1;
        moveToHead(node);
        return node->value;
    }
    
    void put(int key, int value) {
        auto node = this->cache[key];    
        if (node) {
            node->value = value;
            moveToHead(node);
        } else {
            auto newNode = new DLinkedNode();
            newNode->value = value;
            newNode->key = key;
            this->cache[key] = newNode;
            addNode(newNode);
            this->size ++;
            if (this->size > this->capacity) {
                auto lastNode = popTail();
                cache[lastNode->key] = NULL;
                delete lastNode;
                this->size --;
            }
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
