public class NumArray {
    private int[] sumCache;
    private int[] ints;
    
    public NumArray(int[] nums) {
	sumCache = new int[1 + nums.length];
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
    
    public static void dumpArray(int[] arr)
    {
	for (int i = 0; i < arr.length; i++) {
	    System.out.format("%d ", arr[i]);
	}
	System.out.println("\n");
    }
    
}


// Your NumArray object will be instantiated and called as such:
// NumArray numArray = new NumArray(nums);
// numArray.sumRange(0, 1);
// numArray.sumRange(1, 2);


class Solution {
    public static void main(String[] argv)
    {
	int arr[] = {1, 2, 3, 4, 5, 6};
	int x;
	
	NumArray.dumpArray(arr);

	NumArray num = new NumArray(arr);
	
	x = num.sumRange(0, 0);
	System.out.format("%d\n", x);
	x = num.sumRange(2, 3);
	System.out.format("%d\n", x);	
    }
}
