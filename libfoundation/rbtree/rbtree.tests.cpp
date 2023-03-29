// ------------------------------------------------------
//  John Alexander Ferguson, 2023
//  Distributed under CC0 1.0 Universal licence
// ------------------------------------------------------

#include <memory>
#include <libfoundation/rbtree/rbtree.hpp>

#include <fmt/color.h>
#include <fmt/core.h>
#include <fmt/printf.h>
#include <gtest/gtest.h>


namespace foundation
{
namespace rbtree {

template <class T>
NodeSptr<T> createNodeSptr(const T& value, long int uid)
{
    return std::make_shared<Node<T>>(value, uid);
}


class NodeTest : public ::testing::Test 
{
    protected: 

    NodeSptr<int> empty_tree_;
    NodeSptr<int> one_node_tree_;
    NodeSptr<int> two_node_tree_left_;
    NodeSptr<int> two_node_tree_right_;
    NodeSptr<int> three_node_tree_;
    NodeSptr<int> five_node_tree_1_;

    void SetUp() override {

        // {{{ com: one node tree
        {
            one_node_tree_ = createNodeSptr(0, 0);
        }
        // }}}
        // {{{ com: two node tree left
        {
            two_node_tree_left_ = createNodeSptr<int>(0, 0);    
            auto ntmp =  createNodeSptr<int>(1, 1);   
            setLeft<int>(two_node_tree_left_,  ntmp);
        }
        // }}}
        // {{{ com: two node tree right
        {
            two_node_tree_right_ = createNodeSptr(0, 0);        
            auto ntmp = createNodeSptr(1, 1);
            setRight(two_node_tree_right_ , ntmp);
        }
        // }}}
        // {{{ com: three_node_tree
        {
            three_node_tree_ = createNodeSptr(0, 0);
            auto ntmp1 = createNodeSptr(1, 1);
            auto ntmp2 = createNodeSptr(2, 2);
            setLeft(three_node_tree_, ntmp1);
            setRight(three_node_tree_, ntmp2);
        }
        // }}}
        // {{{ com: five node tree 1
        {
            five_node_tree_1_ = createNodeSptr(1, 0);
            auto n2 = createNodeSptr( 2, 1);     
            auto n3 = createNodeSptr(3, 2);
            auto n4 = createNodeSptr(4, 3);
            auto n5 = createNodeSptr(5, 4);
            setLeft(five_node_tree_1_, n2);
            setRight(five_node_tree_1_, n3);
            setLeft(five_node_tree_1_->left(), n4);
            setRight(five_node_tree_1_->left(), n5);
        }
        // }}}
    }

};

// {{{ test: NodeCreate
TEST_F(NodeTest, NodeCreate)
{
    Node<double> node(1.2, 5);
    ASSERT_EQ(node.value(), 1.2);
    ASSERT_FALSE(node.parent());
    ASSERT_FALSE(node.left());
    ASSERT_FALSE(node.right());
    ASSERT_EQ(node.uid(), 5);
    ASSERT_TRUE(node.isRed());
    ASSERT_FALSE(node.isLeft());
    ASSERT_FALSE(node.isRight());
    ASSERT_TRUE(node.isLeaf());

    NodeSptr<double> node_ptr = createNodeSptr(1.2, -5);
    ASSERT_EQ(node_ptr->value(), 1.2);
    ASSERT_FALSE(node_ptr->parent());
    ASSERT_FALSE(node_ptr->left());
    ASSERT_FALSE(node_ptr->right());
    ASSERT_EQ(node_ptr->uid(), 5);
    ASSERT_FALSE(node_ptr->isRed());
    ASSERT_FALSE(node_ptr->isLeft());
    ASSERT_FALSE(node_ptr->isRight());
    ASSERT_TRUE(node_ptr->isLeaf());
}
// }}}
// {{{ test: setLeftAndRight
TEST_F(NodeTest, setLeftAndRight) 
{
    ASSERT_FALSE(five_node_tree_1_->parent());
    ASSERT_FALSE(five_node_tree_1_->isLeft());
    ASSERT_FALSE(five_node_tree_1_->isRight());
    ASSERT_FALSE(five_node_tree_1_->isLeaf());
    ASSERT_EQ(five_node_tree_1_.use_count(), 3);

    ASSERT_EQ(five_node_tree_1_->left()->uid(), 1);
    ASSERT_TRUE(five_node_tree_1_->left()->isLeft());
    ASSERT_FALSE(five_node_tree_1_->left()->isRight());
    ASSERT_FALSE(five_node_tree_1_->left()->isLeaf());
    ASSERT_EQ(five_node_tree_1_->left().use_count(), 3);

    ASSERT_EQ(five_node_tree_1_->right()->uid(), 2);
    ASSERT_FALSE(five_node_tree_1_->right()->isLeft());
    ASSERT_TRUE(five_node_tree_1_->right()->isRight());
    ASSERT_TRUE(five_node_tree_1_->right()->isLeaf());
    ASSERT_EQ(five_node_tree_1_->right().use_count(), 1);

    ASSERT_EQ(five_node_tree_1_->left()->left()->uid(), 3);
    ASSERT_TRUE(five_node_tree_1_->left()->left()->isLeft());
    ASSERT_FALSE(five_node_tree_1_->left()->left()->isRight());
    ASSERT_TRUE(five_node_tree_1_->left()->left()->isLeaf());
    ASSERT_EQ(five_node_tree_1_->left()->left().use_count(), 1);


    ASSERT_EQ(five_node_tree_1_->left()->right()->uid(), 4);
    ASSERT_FALSE(five_node_tree_1_->left()->right()->isLeft());
    ASSERT_TRUE(five_node_tree_1_->left()->right()->isRight());
    ASSERT_TRUE(five_node_tree_1_->left()->right()->isLeaf());
    ASSERT_EQ(five_node_tree_1_->left()->right().use_count(), 1);

}
// }}}
// {{{ test: leftRotate
TEST_F(NodeTest, leftRotate)
{

}
// }}}

// }

}
}
