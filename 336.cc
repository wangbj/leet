class Solution {
private:
  bool isPrefixOf(const std::string& s, const std::string& t) const
  {
    int i = 0;

    for (i = 0; i < (int)s.size(); i++) {
      if (i >= (int)t.size()) return false;

      if (s[i] != t[i]) return false;
    }
    return true;
  }

  bool isSuffixOf(const std::string& s, const std::string& t) const
  {
    int i = (int)s.size() - 1;
    int j = (int)t.size() - 1;

    while(i >= 0) {
      if (j < 0) return false;
      if (s[i--] != t[j--]) return false;
    }
    return true;
  }

  bool isPalindrome(const std::string& s, int i, int j) const
  {
    while (i <= j) {
      if (s[i] != s[j]) return false;
      ++i;
      --j;
    }
    return true;
  }

  void push(std::vector<std::vector<int>>& res, int i, int j)
  {
    std::vector<int> v = {i, j};

    res.push_back(v);
  }
  
public:
  std::vector<std::vector<int>> palindromePairs(std::vector<std::string>& words)
  {
    std::unordered_multimap<std::string, int> dict;
    std::vector<std::vector<int>> res;
    
    int k = 0;

    /* setup hash table */
    for (auto s : words) {
      auto s1 = s;
      
      std::reverse(s1.begin(), s1.end());

      dict.insert(std::make_pair(s1, k));
      ++k;
    }

    for (auto s : dict) {
      k = 0;
      for (auto w : words) {
	if (w.size() < s.first.size()) {++k; continue;}
	if (k == s.second) {++k; continue; }

	if (isPrefixOf(s.first, w)) {
	  if (isPalindrome(w, (int)s.first.size(), (int)w.size() - 1)) {
	    push(res, k, s.second);
	  }
	}
	if (isSuffixOf(s.first, w)) {
	  if (isPalindrome(w, 0, (int)(w.size() - s.first.size() -1))) {
	    push(res, s.second, k);
	  }
	}
	++k;
      }
    }
    std::sort(res.begin(), res.end());
    res.erase(std::unique(res.begin(), res.end()), res.end());
    return res;
  }
};
