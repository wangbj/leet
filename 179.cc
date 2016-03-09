/* sort with descending order */
static inline bool cmp(std::string& s1, std::string& s2)
{
  int i = 0, j = 0;

  while (1) {
    if (s1[i] > s2[j]) {
      return true;
    } else if (s1[i] < s2[j]) {
      return false;
    } else {
      if (i == s1.size() - 1 && j == s2.size() - 1) {
	return false;
      } else if (i == s1.size() - 1) {
	++j;
	i = 0;
      } else if (j == s2.size() - 1) {
	++i;
	j = 0;
      } else {
	++i;
	++j;
      }
    }
  }
}

class Solution {
public:
  std::string largestNumber(std::vector<int>& nums) {
    std::vector<std::string> work;
    std::string res;
    bool allz = true;

    if (nums.size() == 0) return res;

    for (auto x : nums) {
      if (x != 0) allz = false;
      work.push_back(std::to_string(x));
    }

    if (allz) return "0";
    
    std::sort(work.begin(), work.end(), cmp);

    for (auto s : work) {
      res += s;
    }

    return res;
  }
};

/* 824 8247 */
/* 8247 824 */
