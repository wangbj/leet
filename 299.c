static inline int min(int a, int b) {
    return a < b? a: b;
}

char* getHint(char* secret, char* guess) {
    int s[10] ={0,}, d[10] = {0,};
    int b = 0, c = 0, i;
    char* r = calloc(128, sizeof(char));
    
    while(*secret) {
        if (*secret == *guess) {
            ++b;
        } else {
            ++s[*secret - '0'];
            ++d[*guess - '0'];
        }
        ++secret;
        ++guess;
    }
    
    for (i = 0; i < 10; i++) {
        c += min(s[i], d[i]);
    }
    snprintf(r, 127, "%dA%dB", b, c);
    
    return r;
}
