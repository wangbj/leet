struct TrieNode {
  int val;
  struct TrieNode* next[26];
};

/** Initialize your data structure here. */
struct TrieNode* trieCreate(void) {
    struct TrieNode* t = calloc(1, sizeof(struct TrieNode));
}

/** Inserts a word into the trie. */
void insert(struct TrieNode* root, char* word) {
    char* p = word;
    struct TrieNode* link;
    int x;
    
    link = root;
    while(p && *p) {
        x = *p - 'a';
        if (!link->next[x]) {
            link->next[x] = trieCreate();
        }
        link = link->next[x];
        ++p;
    }
    link->val = 1;
}

/** Returns if the word is in the trie. */
bool search(struct TrieNode* root, char* word) {
    struct TrieNode* link = root;
    int x;
    char* p = word;
    
    while(p && *p) {
        x = *p - 'a';
        if (!link->next[x]) return false;
        link = link->next[x];
        ++p;
    }
    if (link->val == 1) return true;
    return false;
}

/** Returns if there is any word in the trie 
    that starts with the given prefix. */
bool startsWith(struct TrieNode* root, char* prefix) {
    struct TrieNode* link = root;
    int x;
    char* p = prefix;
    
    while(p && *p) {
        x = *p - 'a';
        if (!link->next[x]) return false;
        link = link->next[x];
        ++p;
    }
    return true;
}

/** Deallocates memory previously allocated for the TrieNode. */
void trieFree(struct TrieNode* root) {
    
}

// Your Trie object will be instantiated and called as such:
// struct TrieNode* node = trieCreate();
// insert(node, "somestring");
// search(node, "key");
// trieFree(node);
