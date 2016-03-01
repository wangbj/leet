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
            if (matrix[i][j] == '1') {res[i][j] = 1; }
        }
    }

    for (i = 1; i < rows; i++) {
        for (j = 1; j < cols; j++) {
            if (matrix[i][j] == '1') {
                int t;
                t = min(res[i-1][j-1], res[i-1][j]);
                res[i][j] = 1 + min(t, res[i][j-1]);
            } else {
                res[i][j] = 0;
            }
        }
    }
    
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            if (res[i][j] > r) r = res[i][j];
        }
    }
    free2d(res, rows, cols);

    return (r*r);
}
