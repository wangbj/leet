/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:

  // Encodes a tree to a single string.
  std::string serialize(TreeNode* root) {
    if (!root) return "l";
    return ("n"+std::to_string(root->val)+serialize(root->left)+serialize(root->right));
  }

  TreeNode* des(std::string& data, int& k)
  {
    int val = 0, i;
    int sign = 0;

    if (k > (int)data.size()) return NULL;

    if (data[k] == 'l') {
      ++k;
      return NULL;
    }
    
    ++k; /* skip `n` */
    if (data[k] == '-') {
        sign = 1;
        ++k;
    }
    while(data[k] >= '0' && data[k] <= '9') {
      val = 10 * val + data[k++] - '0';
    }
    if (sign) val = -val;

    TreeNode* node = new TreeNode(val);
    node->left = des(data, k);
    node->right = des(data, k);
    return node;
  }
  // Decodes your encoded data to tree.
  TreeNode* deserialize(std::string data) {
    int k = 0;
    return des(data, k);
  }
};



// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));
