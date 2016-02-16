bool increasingTriplet(int* nums, int numsSize) {
    int t[2];
    int candidate = 0x7fffffff;
    int ready = 0, i, x;
    
    for (i = 0; i < numsSize; i++) {
        x = nums[i];
        if (ready) {
            if (x > t[1]) return true;
            else if (x > t[0]) {
                t[1] = x;
            } else if (x < t[0]) {
                candidate = x;
            }
        } else {
            if (x > candidate) {
                t[0] = candidate;
                t[1] = x;
                ready = 1;
            } else if (x < candidate) {
                candidate = x;
            }
        }
    }
    return false;
}
