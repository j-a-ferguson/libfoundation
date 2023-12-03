
#include <functional>
#include <libfoundation/core/io.hpp>
#include <libfoundation/rbtree/rbtree.hpp>

#include <gtest/gtest.h>

namespace foundation {
namespace rbree {


template <typename T, typename Compare = std::less<T>>
bool equal(const RBtree<T, Compare>& t1, 
           const RBtree<T, Compare>& t2, 
           bool compare_data = false)
{
    auto cmp = t1.cmp();
    bool is_eq{true};
    std::stack<std::pair<Snode<T>, Snode<T>>> ptr_pair_stack;
    ptr_pair_stack.push({t1.root(), t2.root()});

    while(!ptr_pair_stack.empty())
    {
        auto cur_pair = ptr_pair_stack.top();
        ptr_pair_stack.pop();

        is_eq = cur_pair.first->uid_ == cur_pair.second->uid_;
        if(!is_eq) break;

        if(compare_data)
        {
            is_eq = compare_data && cmp(cur_pair.first->data_, cur_pair.second->data_);
            if(!is_eq) break;
        }


        is_eq = bool(cur_pair.first->l_) == bool(cur_pair.second->l_);
        if(is_eq && cur_pair.first->l_ && cur_pair.second->l_)
        {
            ptr_pair_stack.push({cur_pair.first->l_, cur_pair.second->l_});
        }
        else break;

        is_eq = bool(cur_pair.first->r_) == bool(cur_pair.second->r_);
        if(is_eq && cur_pair.first->r_ && cur_pair.second->r_)
        {
            ptr_pair_stack.push({cur_pair.first->r_, cur_pair.second->r_});
        }
        else break;

    }
    return is_eq;
}



TEST(NodeTests, create){

    Snode<double> n1 = Node<double>::newFromData(0.0, 1); 

    core::Json json = core::loadJson("assets/rbtree/node1.json");
    Snode<double> n2 = Node<double>::newFromJson(json);

    ASSERT_DOUBLE_EQ(n1->data_, n2->data_);
    ASSERT_EQ(n1->uid_, n2->uid_);
}

TEST(NodeTests, queries)
{
    Snode<double> n1 = Node<double>::newFromData(0.0, 1); 
    Snode<double> n2 = Node<double>::newFromData(0.0, 2); 


}


TEST(TreeTests, create) {

    RBtree<double> tree;

    core::Json json = core::loadJson("assets/rbtree/tree3.json");
    tree.fromJson(json);
    ASSERT_EQ(tree.root()->uid_, -1);
    ASSERT_EQ(tree.root()->l_->uid_, 2);
    ASSERT_EQ(tree.root()->l_->p_->uid_, -1);
    ASSERT_EQ(tree.root()->r_->uid_, 3);
    ASSERT_EQ(tree.root()->r_->p_->uid_, -1);
}

TEST(TreeTests, equal) {

    RBtree<double> tree1, tree2;
    core::Json json = core::loadJson("assets/rbtree/tree3.json");
    tree1.fromJson(json);
    tree2.fromJson(json);

    ASSERT_TRUE(equal(tree1, tree2));

}


TEST(TreeTests, leftRotate)
{

    core::Json json1 = core::loadJson("assets/rbtree/tree2-left.json");
    core::Json json2 = core::loadJson("assets/rbtree/tree2-right.json");
    RBtree<double> tree1, tree2;
    tree1.fromJson(json1);
    tree2.fromJson(json2);

    leftRotate(tree1, tree1.root());
    core::print("{}\n", tree1);
    core::print("{}\n", tree2);
    ASSERT_TRUE(equal(tree1, tree2));
}


}
}