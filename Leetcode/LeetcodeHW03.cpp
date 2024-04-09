#include<vector>
#include<string>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    std::vector<std::string> binaryTreePaths(TreeNode* root) {
        std::vector<std::string> paths = {};
        if(root){
            dfs(root, "", paths);
        }
        return paths;
    }
    void dfs(TreeNode* root, std::string path, std::vector<std::string>& paths) {
        path += std::to_string(root->val);
        if(!root->left && !root->right) {
            paths.push_back(path);
        }
        path += "->";
        if(root->left){
            dfs(root->left, path, paths);
        }
        if(root->right){
            dfs(root->right, path, paths);
        }
    }
};