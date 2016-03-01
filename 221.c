static inline int min(int a, int b)
{
    return a <= b? a : b;
}

static inline int max(int a, int b)
{
    return a >= b? a: b;
}

int** alloc2d(int m, int n)
{
    int** res = (int**)calloc(m, sizeof(int*));
    int i;
    
    for (i = 0; i < m; i++) {
        res[i] = (int*)calloc(n, sizeof(int));
    }
    
    return res;
}

void free2d(int**r, int m, int n)
{
    int i;
    
    for (i = 0; i < m; i++) free(r[i]);
    free(r);
}

int maximalSquare(char** matrix, int rows, int cols) {
    int i, j, r = 0;
    int** res;
    
    if (rows == 0 || cols == 0) return 0;
    
    res = alloc2d(rows, cols);

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            if (matrix[i][j] == '1') {res[i][j] = 1; r = 1;}
        }
    }

    for (i = 1; i < rows; i++) {
        for (j = 1; j < cols; j++) {
            if (matrix[i][j] == '1') {
                for (int k = 1; k <= min(i, j); k++) {
                    int t1, t2, t3, t;
                    t1 = res[i-k][j-k];
                    t2 = min(t1, res[i-k][j]);
                    t3 = min(t2, res[i][j-k]);
                    t = 1 + t3;
                    if (t > res[i][j]) {
                        res[i][j] = t;
                    } else {
                        break;
                    }
                }
                r = max(r, res[i][j]);
            }
        }
    }
    
    free2d(res, rows, cols);

    return (r*r);
}
