// ------------------------------------------------------
//  John Alexander Ferguson, 2023
//  Distributed under CC0 1.0 Universal licence
// ------------------------------------------------------

#include <cstddef>
#include <memory>
#include <stdexcept>
#include <utility>
#include <iterator>
#include <cmath>
#include <string>
#include <stdexcept>

#include <fmt/core.h>

#include <libfoundation/core/io.hpp>
#include <libfoundation/core/assertions.hpp>


namespace foundation
{
namespace rbtree
{
    // {{{ collection: forward declarations
    template <class T>
    class Node;


    template <class T> 
    void to_json(core::Json& json, const Node<T>& node);

    template <class T> 
    void from_json(const core::Json* json, Node<T>& node);

    /**
    @brief Shared pointer type for RBNode 
    
    @tparam T data type stored within RBNode
     */
    template <class T> 

    using NodeSptr = std::shared_ptr<Node<T>>;  

    template <class T>
    void setLeft(NodeSptr<T> root, NodeSptr<T> new_left);

    template <class T>
    void setRight(NodeSptr<T> root, NodeSptr<T> new_left);

    /**
    @brief Raw pointer type for RBNode
    
    @tparam T data type stored within RBNode
     */
    template <class T> 
    using NodeRptr = Node<T>*;

    template <class T> 
    class Tree;
    // }}}
    // {{{ collection Node
    // {{{ class Node
    /**
    @brief Node class of the red-black tree.
    
    @tparam T Underlying type this node is storing.

    Some notes on the design: The ``left_`` and ``right_`` pointers are 
    owning pointers. This is because these nodes form part of a
    red-black tree where nodes are added dynamically and will be 
    assigned to the children of existing nodes.
    
    The ``parent_`` pointer is not an owning pointer. 

     */
    template <class T>
    class Node
    {
        // {{{ collection: friends
        friend void setLeft<T>(NodeSptr<T> root, NodeSptr<T> new_left);
        friend void setRight<T>(NodeSptr<T> root, NodeSptr<T> new_left);
        // }}}

        private:
        // {{{ collection: private fields
        /** Value this node stores*/
        T value_{};
        /** Pointer to the parent */
        NodeSptr<T> parent_;
        /** Pointer to the left child */
        NodeSptr<T> left_;
        /** Pointer to thr right child */
        NodeSptr<T> right_;
        /** Sign bit is the color, positive = red and negative = black. Remaining bits are the uid*/
        long int uid_{0};        
        // }}}  
        public:


        // {{{ collection: creation/destruction
        Node() = default;
        Node(const T& value, long int uid)
        {
            value_ = value;
            uid_ = uid;
        }
        // }}}
        // {{{ collection: accessors
        T& value() {
            return value_;
        }
        const T& value() const {
            return value_;
        }

        NodeSptr<T>& parent() {
            return parent_;
        }

        const NodeSptr<T>& parent() const {
            return parent_;
        }

        NodeSptr<T>& left() {
            return left_;
        }

        const NodeSptr<T>& left() const {
            return left_;
        }

        NodeSptr<T>& right() {
            return right_;            
        }

        const NodeSptr<T>& right() const {
            return right_;
        }

        long int uid() const {
            return std::abs(uid_);
        }        
        // }}}
        // {{{ collection: queries
        bool isRed() {
            bool is_red = (uid_ >= 0);
            return is_red;
        }

        bool isLeft() {
            bool is_left{false};
            if(parent_)
            {
                is_left = parent_->left_.get() == this;
            }
            return is_left;
        }

        bool isRight() {
            bool is_right{false};
            if(parent_) 
            {
                is_right = parent_->right_.get() == this;
            }
            return is_right;
        }

        bool isLeaf() {
            bool is_leaf{(!left_) && (!right_)};
            return is_leaf;
        }
        // }}}
        // {{{ collection: io
        std::string stringify()
        {
            core::Json json = *this;
            std::string out = json.dump(2);
            return out;
        }
        // }}}
    };
    // }}}
    // {{{ function: to_json
    template <class T> 
    void to_json(core::Json& json, const Node<T>& node) {
        json["value"] = node.value();
        json["uid"] = node.uid();

        if(node.parent())
            json["parent"] = node.parent()->uid();

        if(node.left())
            json["left"] = node.left()->uid();
            
        if(node.right())
            json["right"] = node.right()->uid();

    }
    // }}}
    // {{{ collection: node alteration 
    // {{{ function: setLeft
    /**
    @brief Sets the left child of a given node.
    
    @tparam T Underlying type stored in node
    @param node Node who's left child will be edited
    @param new_left Node to be assigned as left child.

    Notes on 
     */
    template <class T>
    void setLeft(NodeSptr<T> root, NodeSptr<T> new_left)
    {        
        ERR_ASSERT_THROW_INVARG_m(root, "root is nullptr");        
        ERR_ASSERT_THROW_INVARG_m(new_left, "new_left is nullptr");        
        // set parent of old left to null
        auto old_left = root->left_;
        if(old_left) old_left->parent_ = nullptr;
        // set old parent left or right to null
        auto old_parent = new_left->parent_;
        if(old_parent)
        {
            if(new_left->isLeft()) // if new left is left child 
                old_parent->left_ = nullptr;
            else if(new_left->isRight()) // if new left is right child
                old_parent->right_ = nullptr;
        } 

        root->left_ = new_left;
        new_left->parent_ = root;
    }
    // }}}
    // {{{ function setRight
    template <class T> 
    void setRight(NodeSptr<T> root, NodeSptr<T> new_right)
    {
        ERR_ASSERT_THROW_INVARG_m(root, "root is nullptr");        
        ERR_ASSERT_THROW_INVARG_m(new_right, "new_left is nullptr");        
        // set parent of old left to null
        auto old_right = root->right_;
        if(old_right) old_right->parent_ = nullptr;
        // set old parent left or right to null
        auto old_parent = new_right->parent_;
        if(old_parent)
        {
            if(new_right->isLeft()) // if new left is left child 
                old_parent->left_ = nullptr;
            else if(new_right->isRight()) // if new left is right child
                old_parent->right_ = nullptr;
        } 

        root->right_ = new_right;
        new_right->parent_ = root;
    }
    // }}}
    // {{{ function: leftRotate
    /**
    @brief 
    
    @tparam T Underlying type stored by the RB-tree
    @param[in] x node on which to perform 
    @param[in] y     
    @return void
     */
    template <class T>
    void leftRotate(NodeSptr<T>& x, NodeSptr<T>& y)
    {
        ERR_ASSERT_THROW_INVARG_m(x, "x is nullptr");
        ERR_ASSERT_THROW_INVARG_m(y, "y is nullptr");
        ERR_ASSERT_THROW_INVARG_m(x->right() == y, "y is not right subtree of x");

        // set right subtree of x to left subtree of y
        if(y->left())
            setRight(x, y->left());
        else 
            x->right() = nullptr;

        if(x->parent())
        {
            // if x is not root then set y to be child of x->parent()
            if(x->isLeft())
                setLeft(x->parent(), y);
            else if(x->isRight())
                setRight(x->parent(), y);
        }
        else
        {
            y->parent() = nullptr;
        }

        // finally set x to be the left subchild of y
        setLeft(y, x);        
    }
    // }}}
    // {{{ function: rightRotate
    template <class T> 
    void rightRotate(NodeSptr<T>& x, NodeSptr<T>& y)
    {
        ERR_ASSERT_THROW_INVARG_m(x, "x is nullptr");
        ERR_ASSERT_THROW_INVARG_m(y, "y is nullptr");
        ERR_ASSERT_THROW_INVARG_m(x->left() == y, "y is not left subtree of x");


        // set the left subtree of x to be the right subtree of y
        if(y->right())
            setLeft(x, y->right());
        else 
            x->left() = nullptr;
        
        if(x->parent())
        {
            // if x is not root then set y to be child of x->parent()
            if(x->isLeft())
                setLeft(x->parent(), y);
            else if(x->isRight())
                setRight(x->parent(), y);
        }
        else 
        {
            // if x is root then set y to be root
            y->parent() = nullptr;
        }

        // finally set x to be the right child of y 
        setRight(y, x);
    }
    // }}}
    // }}}
    // }}}
    // {{{ class RBTree
    template <class T>
    class Tree
    {
        friend class Node<T>;

        private: 

        std::size_t size_{0};
        NodeSptr<T> root_;
        long int next_uid_{0};

        public:

        // {{{ class: Iterator
        /**
        @brief The iterator associated with this container
        
         */
        class Iterator
        {
            private:

            Node<T>* node_;

            public:

            using iterator_category = std::forward_iterator_tag;
            using difference_type = std::ptrdiff_t;
            using value_type = T;
            using pointer = T*;
            using reference = T&;

            Iterator(Node<T>* node)
            {
                node_ = node;
            }

            Iterator(const Iterator& iter)
            {
                node_ = iter.node_;                
            }

            Iterator& operator=(const Iterator& iter) 
            {
                if(this != &iter)
                {
                    node_ = iter.node_;
                }
                return *this;
            }

            Iterator(Iterator&& iter)
            {

            }

            Iterator& operator=(Iterator&& iter)
            {

            }

            reference operator*() 
            {
                return node_->value();
            }

            pointer operator->()
            {
                return &(node_->value());
            }

            Iterator& operator++() 
            {

            }

            Iterator& operator++(int)
            {

            }

            friend bool operator==(const Iterator& iter1, const Iterator& iter2)
            {

            }


            friend bool operator!=(const Iterator& iter1, const Iterator& iter2)
            {

            }


        };
        // }}}

        Tree() = default;
        std::pair<Iterator, bool> insert(const T& value)
        {

        }
        Iterator erase(const T& value);
        Iterator erase(Iterator iter);        



        
    };
    // }}}
}
}

