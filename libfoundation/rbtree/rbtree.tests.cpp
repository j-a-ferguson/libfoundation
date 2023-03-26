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

TEST(rbtree, RBNodeCreate)
{
    Tree<double> tree;
    Node<double> node(1.2, 0);
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

    fmt::print("{}\n", n1->stringify());
    fmt::print("{}\n", n1->left()->stringify());
    fmt::print("{}\n", n1->right()->stringify());
    fmt::print("{}\n", n1->left()->left()->stringify());
    fmt::print("{}\n", n1->left()->right()->stringify());
    fmt::print("--------------------------------------------");
    fmt::print("{} {} \n", n1->stringify(),n1.use_count()); 
    fmt::print("{} {} \n", n2->stringify(),n2.use_count());
    fmt::print("{} {} \n", n3->stringify(),n3.use_count());
    fmt::print("{} {} \n", n4->stringify(),n4.use_count());
    fmt::print("{} {} \n", n5->stringify(),n5.use_count());
}

/*
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
        one_node_tree_ = createNodeSptr(&t1_, 0, 0);
        // }}}
        // {{{ com two node tree left
        two_node_tree_left_ = createNodeSptr(&t2_, 0, 0);        
        two_node_tree_left_->setLeft(createNodeSptr(&t2_, 1, 1));
        // }}}
        // {{{ com two node tree right
        // two_node_tree_right_ = createNodeSptr(&t3_, 0, 0);        
        // two_node_tree_right_->setLeft(createNodeSptr(&t3_, 1, 1));
        // }}}
    }
};

TEST_F(NodeTest, leftRotate)
{
    // auto out1 = one_node_tree_->leftRotate();
    // ASSERT_EQ(out1, nullptr);
    fmt::printf("%p\n", (void*)two_node_tree_left_.get());
    auto out2 = two_node_tree_left_->leftRotate();
    ASSERT_EQ(out2->uid(), 1);

}
*/

}
}
