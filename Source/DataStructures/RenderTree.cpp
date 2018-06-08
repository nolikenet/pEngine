#include "RenderTree.hpp"

TreeNode::TreeNode(int value)
{
    this->parent = NULL;
    this->depth = 0;
    this->height = -1;
    this->value = value;
}

void TreeNode::Render()
{
    std::cout << "Rendering Node " << this->value << std::endl;
}

Tree::Tree()
{
}

bool Tree::IsEmpty()
{
    auto isEmpty = rootNode == NULL ? true : false;
    return isEmpty;
}

bool Tree::IsRoot(std::shared_ptr<TreeNode> node)
{
    auto isRoot = rootNode == node ? true : false;
    return isRoot;
}

void Tree::Render(std::shared_ptr<TreeNode> node)
{
    node->Render();
    for (auto& item : node->children)
    {
        Render(item);
    }
}

void Tree::Insert(std::shared_ptr<TreeNode> node)
{
    if (IsEmpty())
    {
        rootNode = node;
        return;
    }
    rootNode->children.push_back(node);
    node->parent = rootNode;
}

void Tree::InsertChildOf(std::shared_ptr<TreeNode> parent, std::shared_ptr<TreeNode> child)
{
    parent->children.push_back(child); 
}

