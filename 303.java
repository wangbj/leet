public class NumArray {
    private int[] sumCache;
    private int[] ints;
    
    public NumArray(int[] nums) {
	sumCache = new int[nums.length];
	ints = new int[nums.length];
	int p = 0;

	// sumCache[0] = 0;
	
	for (int i = 0; i < nums.length; i++) {
	    ints[i] = nums[i];
	    sumCache[i] = p + nums[i];
	    p += nums[i];
	}
    }

    public int sumRange(int i, int j) {
	return sumCache[j] - sumCache[i] + ints[i];
    }
}


// Your NumArray object will be instantiated and called as such:
// NumArray numArray = new NumArray(nums);
// numArray.sumRange(0, 1);
// numArray.sumRange(1, 2);
