#include <cstdio>
#include <set>

class MedianFinder {
private:
  std::multiset<int> minset;
  std::multiset<int> maxset;
  unsigned long size;
public:
  MedianFinder() {
    size = 0;
    minset.clear();
    maxset.clear();
  }
  // Adds a number into the data structure.
  void addNum(int num) {
    ++size;
    if (size == 1) {
      minset.insert(num);
      return;
    } else if (size == 2) {
      auto i1 = minset.begin();
      if (num < *i1) {
	auto x = *i1;
	minset.clear();
	minset.insert(num);
	maxset.insert(x);
      } else {
	maxset.insert(num);
      }
      return;
    }

    auto i1 = minset.end();
    --i1;
    auto i2 = maxset.begin();
    if (num > *i1) {
      maxset.insert(num);
    } else if (num <= *i2) {
      minset.insert(num);
    } else {
      printf("???\n");
    }

    while (minset.size() > 1 + maxset.size()) {
      auto i1 = minset.end();
      --i1;
      auto x = *i1;
      minset.erase(i1);
      maxset.insert(x);
    }
    while (maxset.size() > 1 + minset.size()) {
      auto i2 = maxset.begin();
      auto x = *i2;
      maxset.erase(i2);
      minset.insert(x);
    }
  }

  // Returns the median of current data stream
  double findMedian(void) const {
    if (size == 1) {
      auto i1 = minset.begin();
      return *i1;
    }
      
    if (size & 1) {
      if (minset.size() == 1 + maxset.size()) {
	auto i1 = minset.rbegin();
	return (double)*i1;
      } else if (maxset.size() == 1 + minset.size()) {
	auto i2 = maxset.begin();
	return (double)*i2;
      } else {
	printf("%s: set isn't balanced, min.size: %ld, max.size: %ld\n",
	       __func__, minset.size(), maxset.size());
	return 0;
      }
    } else {
      if (minset.size() == maxset.size()) {
	auto i1 = minset.rbegin();
	auto i2 = maxset.begin();
	return ((double)(*i1 + *i2)) / 2;
      } else {
	printf("%s: set isn't balanced, min.size: %ld, max.size: %ld\n",
	       __func__, minset.size(), maxset.size());
	return 0;
      }
    }
  }
};

// Your MedianFinder object will be instantiated and called as such:
// MedianFinder mf;
// mf.addNum(1);
// mf.findMedian();

int main(int argc, char* argv[])
{
  class MedianFinder F;
  int n, x;

  scanf("%d\n", &n);

  for (int i = 0; i < n; i++) {
    scanf("%d", &x);
    F.addNum(x);
    printf("median: %g\n", F.findMedian());
  }

  return 0;
}
