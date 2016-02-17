struct WordDictionary {
    int val;
    struct WordDictionary* next[26];
};

/** Initialize your data structure here. */
struct WordDictionary* wordDictionaryCreate(void) {
    return calloc(1, sizeof(struct WordDictionary));
}

/** Inserts a word into the data structure. */
void addWord(struct WordDictionary* wordDictionary, char* word) {
    struct WordDictionary* link = wordDictionary;
    char* p = word;
    int x;
    
    while (*p) {
        x = *p - 'a';
        if (!link->next[x]) {
            link->next[x] = wordDictionaryCreate();
        }
        link = link->next[x];
        ++p;
    }
    link->val = 1;
}

/** Returns if the word is in the data structure. A word could
    contain the dot character '.' to represent any one letter. */
bool search(struct WordDictionary* wordDictionary, char* word) {
    struct WordDictionary* link = wordDictionary;
    struct WordDictionary* link1;
    char* p = word;
    int x;
    
    while (*p) {
        if (*p == '.') {
            for (x = 0; x < 26; x++) {
                link1 = link->next[x];
                if (link1 && search(link1, 1+p)) return true;
            }
            return false;
        } else {
            x = *p - 'a';
            if (!link->next[x]) return false;
            
            link = link->next[x];
            ++p;
        }
    }
    if (link->val == 1) return true;
    return false;
}

/** Deallocates memory previously allocated for the data structure. */
void wordDictionaryFree(struct WordDictionary* wordDictionary) {
    
}

// Your WordDictionary object will be instantiated and called as such:
// struct WordDictionary* wordDictionary = wordDictionaryCreate();
// addWord(wordDictionary, "word");
// search(wordDictionary, "pattern");
// wordDictionaryFree(wordDictionary);
