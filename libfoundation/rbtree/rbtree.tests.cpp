// ------------------------------------------------------
//  John Alexander Ferguson, 2023
//  Distributed under CC0 1.0 Universal licence
// ------------------------------------------------------

#include <memory>
#include <stdexcept>
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

// These tests are for very low-level, simple functions
// they are tested separately from the main test suite as the 
// main test suite depends upon the functions tested here.
// {{{ test: NodeCreate
TEST(NodeTest1, NodeCreate)
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
// {{{ test: setLeft1
TEST(NodeTest1, setLeft1)
{
    NodeSptr<int> n0 = createNodeSptr(0, 0);
    NodeSptr<int> n1 = createNodeSptr(1, 1);

    setLeft(n0, n1);
    ASSERT_FALSE(n0->parent());
    ASSERT_EQ(n0->left(), n1);
    ASSERT_FALSE(n0->right());
    ASSERT_EQ(n1->parent(), n0);
    ASSERT_FALSE(n1->left());
    ASSERT_FALSE(n1->right());
    
}
// }}}
// {{{ test: setLeft2
TEST(NodeTest1, setLeft2)
{
    // create the nodes
    NodeSptr<int> n0 = createNodeSptr(0, 0);
    NodeSptr<int> n1 = createNodeSptr(1, 1);
    NodeSptr<int> n2 = createNodeSptr(2, 2);
    NodeSptr<int> n3 = createNodeSptr(3, 3);
    NodeSptr<int> n4 = createNodeSptr(4, 4);
    NodeSptr<int> n5 = createNodeSptr(5, 5);
    NodeSptr<int> n6 = createNodeSptr(6, 6);
    NodeSptr<int> n7 = createNodeSptr(7, 7);

    // build the trees, one rooted at n0 the other rooted at n4
    n0->right() = n1;
    n1->parent() = n0;

    n1->left() = n2;
    n2->parent() = n1;

    n1->right() = n3;
    n3->parent() = n1;


    n4->right() = n5;
    n5->parent() = n4;

    n5->left() = n6;
    n6->parent() = n5;

    n5->right() = n7;
    n7->parent() = n5;

    setLeft(n1, n5);

    // check the orphans
    ASSERT_FALSE(n2->parent());
    ASSERT_FALSE(n2->left());
    ASSERT_FALSE(n2->parent());
    ASSERT_FALSE(n4->left());
    ASSERT_FALSE(n4->right());
    ASSERT_FALSE(n4->right());
    // check the main tree
    ASSERT_FALSE(n0->parent());
    ASSERT_FALSE(n0->left());
    ASSERT_EQ(n0->right(), n1);
    ASSERT_EQ(n1->parent(), n0);
    ASSERT_EQ(n1->left(), n5);
    ASSERT_EQ(n1->right(), n3);
    ASSERT_EQ(n3->parent(), n1);
    ASSERT_FALSE(n3->left());
    ASSERT_FALSE(n3->right());
    ASSERT_EQ(n5->parent(), n1);
    ASSERT_EQ(n5->left(), n6);
    ASSERT_EQ(n5->right(), n7);
    ASSERT_EQ(n6->parent(), n5);
    ASSERT_FALSE(n6->left());
    ASSERT_FALSE(n6->right());
    ASSERT_EQ(n7->parent(), n5);
    ASSERT_FALSE(n7->left());
    ASSERT_FALSE(n7->right());
}
// }}}
// {{{ test: setRight1
TEST(NodeTest1, setRight1)
{
    NodeSptr<int> n0 = createNodeSptr(0, 0);
    NodeSptr<int> n1 = createNodeSptr(1, 1);
    setRight(n0, n1);
    ASSERT_FALSE(n0->parent());
    ASSERT_FALSE(n0->left());
    ASSERT_EQ(n0->right(), n1);
    ASSERT_EQ(n1->parent(), n0);
    ASSERT_FALSE(n1->left());
    ASSERT_FALSE(n1->right());
}
// }}}
// {{{ test: setRight2
TEST(NodeTest1, setRight2)
{
    // create the nodes
    NodeSptr<int> n0 = createNodeSptr(0, 0);
    NodeSptr<int> n1 = createNodeSptr(1, 1);
    NodeSptr<int> n2 = createNodeSptr(2, 2);
    NodeSptr<int> n3 = createNodeSptr(3, 3);
    NodeSptr<int> n4 = createNodeSptr(4, 4);
    NodeSptr<int> n5 = createNodeSptr(5, 5);
    NodeSptr<int> n6 = createNodeSptr(6, 6);
    NodeSptr<int> n7 = createNodeSptr(7, 7);

    // build the trees, one rooted at n0 the other rooted at n4
    n0->right() = n1;
    n1->parent() = n0;

    n1->left() = n2;
    n2->parent() = n1;

    n1->right() = n3;
    n3->parent() = n1;


    n4->right() = n5;
    n5->parent() = n4;

    n5->left() = n6;
    n6->parent() = n5;

    n5->right() = n7;
    n7->parent() = n5;

    setRight(n1, n5);

    // check the orphans
    ASSERT_FALSE(n3->parent());
    ASSERT_FALSE(n3->left());
    ASSERT_FALSE(n3->parent());
    ASSERT_FALSE(n4->left());
    ASSERT_FALSE(n4->right());
    ASSERT_FALSE(n4->right());
    // check the main tree
    ASSERT_FALSE(n0->parent());
    ASSERT_FALSE(n0->left());
    ASSERT_EQ(n0->right(), n1);
    ASSERT_EQ(n1->parent(), n0);
    ASSERT_EQ(n1->left(), n2);
    ASSERT_EQ(n1->right(), n5);
    ASSERT_EQ(n2->parent(), n1);
    ASSERT_FALSE(n2->left());
    ASSERT_FALSE(n2->right());
    ASSERT_EQ(n5->parent(), n1);
    ASSERT_EQ(n5->left(), n6);
    ASSERT_EQ(n5->right(), n7);
    ASSERT_EQ(n6->parent(), n5);
    ASSERT_FALSE(n6->left());
    ASSERT_FALSE(n6->right());
    ASSERT_EQ(n7->parent(), n5);
    ASSERT_FALSE(n7->left());
    ASSERT_FALSE(n7->right());
}
// }}}

// {{{ class NodeTest2
class NodeTest2 : public ::testing::Test 
{
    protected: 

    NodeSptr<int> empty_tree_;
    NodeSptr<int> one_node_tree_;
    NodeSptr<int> two_node_tree_left_;
    NodeSptr<int> two_node_tree_right_;
    NodeSptr<int> three_node_tree_;
    NodeSptr<int> five_node_tree_1_;
    NodeSptr<int> five_node_tree_2_;

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
        // {{{ com: five node tree 2
        {
            five_node_tree_2_= createNodeSptr(1, 0);
            auto n2 = createNodeSptr( 2, 1);     
            auto n3 = createNodeSptr(3, 2);
            auto n4 = createNodeSptr(4, 3);
            auto n5 = createNodeSptr(5, 4);
            setLeft(five_node_tree_2_, n2);
            setRight(five_node_tree_2_, n3);
            setLeft(five_node_tree_2_->right(), n4);
            setRight(five_node_tree_2_->right(), n5);
        }
        // }}}
    }

};
// }}}
// {{{ test: setLeftAndRight
TEST_F(NodeTest2, setLeftAndRight1) 
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
// {{{ test: leftRotateErrors
TEST_F(NodeTest2, leftRotateErrors)
{
    NodeSptr<int> null_ptr;
    ASSERT_THROW(leftRotate(null_ptr, one_node_tree_->right()), 
                std::invalid_argument);

    ASSERT_THROW(leftRotate(one_node_tree_, null_ptr), 
                std::invalid_argument);

    ASSERT_THROW(leftRotate(two_node_tree_left_, two_node_tree_left_->left()), 
                std::invalid_argument);
}
// }}}
// {{{ test: leftRotate1
TEST_F(NodeTest2, leftRotate1)
{
    auto x = two_node_tree_right_;
    auto y = two_node_tree_right_->right();
    leftRotate(x, y);
    ASSERT_FALSE(y->parent());
    ASSERT_EQ(y->left(), x);
    ASSERT_FALSE(y->right());
    ASSERT_EQ(x->parent(), y );
    ASSERT_FALSE(x->left());
    ASSERT_FALSE(x->right());

}
// }}}
// {{{ test: leftRotate2
TEST_F(NodeTest2, leftRotate2)
{
    auto n0 = five_node_tree_2_;
    auto n1 = five_node_tree_2_->left();
    auto n2 = five_node_tree_2_->right();
    auto n3 = five_node_tree_2_->right()->left();
    auto n4 = five_node_tree_2_->right()->right();
    ASSERT_TRUE(n0);
    ASSERT_TRUE(n1);
    ASSERT_TRUE(n2);
    ASSERT_TRUE(n3);
    ASSERT_TRUE(n4);

    leftRotate(n0, n2);
    ASSERT_EQ(n0->parent(), n2);
    ASSERT_EQ(n0->left(), n1);
    ASSERT_EQ(n0->right(), n3);
    ASSERT_EQ(n1->parent(), n0);
    ASSERT_FALSE(n1->left());
    ASSERT_FALSE(n1->right());
    ASSERT_FALSE(n2->parent());
    ASSERT_EQ(n2->left(), n0 );
    ASSERT_EQ(n2->right(), n4);
    ASSERT_EQ(n3->parent(), n0);
    ASSERT_FALSE(n3->left());
    ASSERT_FALSE(n3->right());
}
// }}}
// {{{ test: leftRotate3
TEST_F(NodeTest2, leftRotate3)
{
    auto n0 = five_node_tree_2_;
    auto n1 = five_node_tree_2_->left();
    auto n2 = five_node_tree_2_->right();
    auto n3 = five_node_tree_2_->right()->left();
    auto n4 = five_node_tree_2_->right()->right();
    ASSERT_TRUE(n0);
    ASSERT_TRUE(n1);
    ASSERT_TRUE(n2);
    ASSERT_TRUE(n3);
    ASSERT_TRUE(n4);

    leftRotate(n2, n4);
    // test n0
    ASSERT_FALSE(n0->parent());
    ASSERT_EQ(n0->left(), n1);
    ASSERT_EQ(n0->left(), n4);
    // test n1
    // ASSERT_EQ(n1->parent(), n0);
    // ASSERT_FALSE(n1->left());
    // ASSERT_FALSE(n1->right());
    // test n2
    // ASSERT_EQ(n2->parent(), n4);
    // ASSERT_EQ(n2->left(), n3);
    // ASSERT_FALSE(n2->right());
    // test n3
    // ASSERT_EQ(n3->parent(), n2);
    // ASSERT_FALSE(n3->left());
    // ASSERT_FALSE(n3->right());
    // test n4
    // ASSERT_EQ(n4->parent(), n0);
    // ASSERT_EQ(n4->left(), n2);
    // ASSERT_FALSE(n4->right());
}
// }}}
// {{{ test: rightRotateErrors
TEST_F(NodeTest2, rightRotateErros)
{
    NodeSptr<int> null_ptr;
    ASSERT_THROW(rightRotate(null_ptr, one_node_tree_->right()), 
                std::invalid_argument);
            
    ASSERT_THROW(rightRotate(one_node_tree_, null_ptr), 
                 std::invalid_argument);

    ASSERT_THROW(rightRotate(two_node_tree_right_, two_node_tree_right_->right()), 
                std::invalid_argument);
}
// }}}
// {{{ test: rightRotate1 
TEST_F(NodeTest2, rightRotate1)
{
    auto x = two_node_tree_left_;
    auto y = two_node_tree_left_->left();
    rightRotate(x, y);
    ASSERT_FALSE(y->parent());
    ASSERT_EQ(y->right(), x);
    ASSERT_FALSE(y->left());
    ASSERT_EQ(x->parent(), y );
    ASSERT_FALSE(x->left());
    ASSERT_FALSE(x->right());
}
// }}}
// {{{ test: rightRotate2
TEST_F(NodeTest2, rightRotate2)
{
    auto n0 = five_node_tree_1_;
    auto n1 = five_node_tree_1_->left();
    auto n2 = five_node_tree_1_->right();
    auto n3 = five_node_tree_1_->left()->left();
    auto n4 = five_node_tree_1_->left()->right();
    ASSERT_TRUE(n0);
    ASSERT_TRUE(n1);
    ASSERT_TRUE(n2);
    ASSERT_TRUE(n3);
    ASSERT_TRUE(n4);

    rightRotate(n0, n1);
    ASSERT_FALSE(n1->parent());
    ASSERT_EQ(n1->left(), n3 );
    ASSERT_EQ(n1->right(), n0);
    ASSERT_EQ(n0->left(), n4);
    ASSERT_EQ(n0->right(), n2);
}
// }}}
// {{{ test: rightRotate3
TEST_F(NodeTest2, rightRotate3)
{
    auto n0 = five_node_tree_1_;
    auto n1 = five_node_tree_1_->left();
    auto n2 = five_node_tree_1_->right();
    auto n3 = five_node_tree_1_->left()->left();
    auto n4 = five_node_tree_1_->left()->right();
    ASSERT_TRUE(n0);
    ASSERT_TRUE(n1);
    ASSERT_TRUE(n2);
    ASSERT_TRUE(n3);
    ASSERT_TRUE(n4);

    rightRotate(n1, n3);
    ASSERT_EQ(n3->parent(), n0);
}
// }}}
}
}
