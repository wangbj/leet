#include <algorithm>
#include <vector>
#include <deque>

class Solution {
private:
  void BFS(std::vector<std::vector<int>>& G, std::deque<std::pair<int, int>>& Q, std::vector<bool>& visited, std::pair<int, int> &res)
  {
    if (Q.empty()) return;

    auto front = Q.front();
    Q.pop_front();

    if (!visited[front.first]) {
      visited[front.first] = true;
      res = front;

      for (auto next : G[front.first]) {
	Q.push_back(std::make_pair(next, 1 + front.second));
      }
    }
    BFS(G, Q, visited, res);
  }

  void MHT(std::vector<std::vector<int>>& G, std::deque<std::pair<int, int>>& Q,
	   std::vector<bool>& visited, int depth, std::vector<std::pair<int, int>>& res)
  {
    if (Q.empty()) return;

    auto front = Q.front();
    Q.pop_front();

    if (!visited[front.first]) {
      visited[front.first] = true;
      // printf("visiting: %d %d\n", front.first, front.second);
      if (depth & 1) {
	if (front.second == depth / 2 || front.second == 1 + depth / 2)
	  res.push_back(front);
      } else {
	if (front.second == depth / 2)
	  res.push_back(front);
      }
      
      for (auto next : G[front.first]) {
	Q.push_back(std::make_pair(next, 1 + front.second));
      }
    }
    MHT(G, Q, visited, depth, res);
  }
  
  void showGraph(std::vector<std::vector<int>>& G) {
    for (int i = 0; i < (int)G.size(); i++) {
      printf("%d ->", i);
      for (auto x : G[i]) {
	printf(" %d", x);
      }
      printf("\n");
    }
  }
public:
  std::vector<int> findMinHeightTrees(int n, std::vector<std::pair<int, int>>& edges)
  {
    std::vector<int> res;
    std::vector<std::pair<int, int>> v1, v2;
    std::vector<std::vector<int>> G;
    std::deque<std::pair<int, int>> Q;
    std::vector<bool>V;
    std::pair<int, int> last, first;
    int depth;
    
    G.resize(n);
    V.resize(n);

    for (auto it = edges.begin(); it != edges.end(); ++it) {
      G[it->first].push_back(it->second);
      G[it->second].push_back(it->first);
    }

    Q.push_back(std::make_pair(0, 0));
    BFS(G, Q, V, last);
    V.clear();
    Q.clear();
    V.resize(n);
    Q.push_back(std::make_pair(last.first, 0));
    BFS(G, Q, V, first);

    depth = first.second;

    V.clear();
    V.resize(n);
    Q.clear();
    Q.push_back(std::make_pair(first.first, 0));
    MHT(G, Q, V, depth, v1);
    V.clear();
    V.resize(n);
    Q.clear();
    Q.push_back(std::make_pair(last.first, 0));
    MHT(G, Q, V, depth, v2);

    for (auto x : v1) {
      for (auto y : v2) {
	// printf("x (%d %d), y (%d %d)\n", x.first, x.second, y.first, y.second);
	if (x.first == y.first) {
	  if (!(depth & 1)) {
	    if (x.second == y.second && x.second == depth / 2)
	      res.push_back(x.first);
	  } else {
	    if ( (x.second == depth / 2 && y.second == 1 + depth / 2) ||
		 (x.second == 1 + depth / 2 && y.second == depth / 2) ) {
	      res.push_back(x.first);
	    }
	  }
	}
      }
    }
    
    // showGraph(G);
    
    return res;
  }
};

int main(int argc, char* argv[])
{
  std::vector<std::pair<int, int>> G;
  Solution S;
  int n;
  int x, y;

  scanf("%d\n", &n);

  while(!feof(stdin)) {
    scanf("%d %d\n", &x, &y);
    G.push_back(std::make_pair(x, y));
  }
  
  auto res = S.findMinHeightTrees(n, G);

  for (auto x : res) {
    printf("%d\n", x);
  }

  return 0;
}
