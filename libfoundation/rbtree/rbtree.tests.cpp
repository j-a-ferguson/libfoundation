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

    void SetUp() override {

        // {{{ com: one node tree
        one_node_tree_ = createNodeSptr(0, 0);
        // }}}
        // {{{ com two node tree left
        two_node_tree_left_ = createNodeSptr<int>(0, 0);    
        auto ntmp =  createNodeSptr<int>(1, 1);   
        setLeft<int>(two_node_tree_left_,  ntmp);
        // }}}
        // {{{ com two node tree right
        // two_node_tree_right_ = createNodeSptr(&t3_, 0, 0);        
        // two_node_tree_right_->setLeft(createNodeSptr(&t3_, 1, 1));
        // }}}
    }
};



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

TEST(rbtree, setLeftAndRight) 
{

    Tree<int> tree;

    auto n1 = createNodeSptr<int>(1, 0);
    auto n2 = createNodeSptr<int>( 2, 1);     
    auto n3 = createNodeSptr<int>(3, 2);
    auto n4 = createNodeSptr(4, 3);
    auto n5 = createNodeSptr(5, 4);
    setLeft(n1, n2);
    setRight(n1, n3);
    setLeft(n1->left(), n4);
    setRight(n1->left(), n5);

    ASSERT_EQ(n1->left(), n2);
    ASSERT_EQ(n2->parent(), n1);
    ASSERT_EQ(n1->right(), n3);
    ASSERT_EQ(n3->parent(), n1);
    ASSERT_EQ(n2->left(), n4);
    ASSERT_EQ(n2->right(), n5);
}

// TEST_F(NodeTest, leftRotate)
// {
//     // auto out1 = one_node_tree_->leftRotate();
//     // ASSERT_EQ(out1, nullptr);
//     fmt::printf("%p\n", (void*)two_node_tree_left_.get());
//     auto out2 = two_node_tree_left_->leftRotate();
//     ASSERT_EQ(out2->uid(), 1);

// }

}
}
