/**
 * Return an array of arrays.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int** generateMatrix(int n) {
        int i, j, x=1;
        int rowStart = 0, rowEnd = n-1;
        int colStart = 0, colEnd = n-1;
        int ** res;

        if (n == 0) return NULL;

        res = (int**)calloc(n, sizeof(int*));
        for (i = 0; i < n; i++) {
            res[i] = (int*)calloc(n, sizeof(int));
        }
        
        i = j = 0;
        
        while (x <= n*n) {
            for (j = colStart; j <= colEnd; j++) {
                  res[i][j] = x++;
            }
            ++rowStart;
            --j;
            /* fall through */
            for (i = rowStart; i <= rowEnd; i++) {
                res[i][j] = x++;
            }
            --colEnd;
            --i;
            for (j = colEnd; j >= colStart; j--) {
                res[i][j] = x++;
            }
            --rowEnd;
            ++j;
            for (i = rowEnd; i >= rowStart; i--) {
                res[i][j] = x++;
            }
            ++colStart;
            ++i;
        }
        return res;
}
