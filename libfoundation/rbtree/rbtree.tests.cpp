// ------------------------------------------------------
//  John Alexander Ferguson, 2023
//  Distributed under CC0 1.0 Universal licence
// ------------------------------------------------------

#include <memory>
#include <libfoundation/rbtree/rbtree.hpp>

#include <fmt/color.h>
#include <fmt/core.h>
#include <gtest/gtest.h>


namespace foundation
{
namespace rbtree {

template <class T>
NodeSptr<T> createNodeSptr(Tree<T>* tree, const T& value, long int uid)
{
    return std::make_shared<Node<T>>(tree, value, uid);
}

TEST(rbtree, RBNodeCreate)
{
    Tree<double> tree;
    Node<double> node(&tree, 1.2, 0);
}

TEST(rbtree, setLeftAndRight) 
{

    Tree<int> tree;

    auto n1 = createNodeSptr<int>(&tree, 1, 0);

    n1->setLeft(createNodeSptr(&tree, 2, 1));
    n1->setRight(createNodeSptr(&tree, 3, 2));

    n1->left()->setLeft(createNodeSptr(&tree, 4, 3));
    n1->left()->setRight(createNodeSptr(&tree, 5, 4));

    /*
    fmt::print("{}\n", n1->stringify());
    fmt::print("{}\n", n1->left()->stringify());
    fmt::print("{}\n", n1->right()->stringify());
    fmt::print("{}\n", n1->left()->left()->stringify());
    fmt::print("{}\n", n1->left()->right()->stringify());
    */
}


class NodeTest : public ::testing::Test 
{
    protected: 

    NodeSptr<int> empty_tree_;
    Tree<int> t1_;
    NodeSptr<int> one_node_tree_;
    Tree<int> t2_;
    NodeSptr<int> two_node_tree_left_;
    Tree<int> t3_;
    NodeSptr<int> two_node_tree_right_;
    Tree<int> t4_;
    NodeSptr<int> three_node_tree_;

    void SetUp() override {

        // {{{ com: one node tree
        one_node_tree_ = std::make_shared<Node<int>>(&t1_, 0, 0);
        // }}}
        // {{{ com two node tree left
        two_node_tree_left_ = createNodeSptr(&t2_, 0, 0);        
        two_node_tree_left_->setLeft(createNodeSptr(&t2_, 0, 0));
        // }}}
        // {{{ com two node tree right
        two_node_tree_right_ = createNodeSptr(&t3_, 0, 0);        
        two_node_tree_right_->setLeft(createNodeSptr(&t3_, 0, 0));
        // }}}
    }
};

TEST_F(NodeTest, leftRotate)
{
    one_node_tree_->leftRotate();
}

}
}
