static int cache[1 << 20];

#define INF (0x70FFFFFF)

static int compare_int(const void* l, const void* r)
{
    int l_ = *(int*)l;
    int r_ = *(int*)r;
    
    return l_ - r_;
}

int coinChange(int* coins, int coinsSize, int amount) {
    int i, j, k, m;
    
    for(i = 0; i <= amount; i++) {
        cache[i] = INF;
    }
    
    qsort(coins, coinsSize, sizeof(int), compare_int);
    
    cache[0] = 0;

    for (i = 0; i < coinsSize; i++) {
        cache[coins[i]] = 1;
    }
    
    for (i = 1; i <= amount; i++) {
        m = INF;
        if (cache[i] == INF) {
            for (j = 0; j < coinsSize; j++) {
                k = i - coins[j];
                if (k < 0) continue;
                if (cache[k] == INF) continue;
                if (cache[k] < m) m = cache[k];
            }
        }
        if (m != INF) {
            cache[i] = 1 + m;
        }
    }

    return cache[amount] == INF? -1: cache[amount];
}
