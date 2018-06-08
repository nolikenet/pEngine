#include <iostream>
#include <vector>
#include <memory>

struct TreeNode
{
public:
    TreeNode(int value);
    void Render();

    int depth;
    int height;
    int value;
    std::shared_ptr<TreeNode> parent;
    std::vector<std::shared_ptr<TreeNode>> children;
};

class Tree
{
public:
    Tree();
    bool IsEmpty();
    bool IsRoot(std::shared_ptr<TreeNode> node);
    void Render(std::shared_ptr<TreeNode> node);
    void Insert(std::shared_ptr<TreeNode> node);
    void InsertChildOf(std::shared_ptr<TreeNode> parent, std::shared_ptr<TreeNode> child);

    std::shared_ptr<TreeNode> rootNode;
};
