// ------------------------------------------------------
//  John Alexander Ferguson, 2023
//  Distributed under CC0 1.0 Universal licence
// ------------------------------------------------------

#include <cassert>
#include <cstddef>
#include <memory>
#include <utility>
#include <iterator>
#include <cmath>
#include <string>

#include <fmt/core.h>

#include <libfoundation/core/io.hpp>


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
            return std::signbit(uid_);
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
    void setLeft(NodeSptr<T>& root, NodeSptr<T>& new_left)
    {        
        if(root)
        {
            if(new_left)
            {
                /* doc
                If the new left substree root is not null then 
                the old left subtree must be unlinked by severing its' 
                parent pointer
                */
                if(root->left())
                {
                    // unlink the left subtree 
                    root->left()->parent().reset();
                }
                // link new left subtree
                root->left() = new_left;
                root->left()->parent() = root;
            }
            else 
            {
                /* doc
                If new_left is nullptr then this function simply 
                severs the left subtree.
                */
                if(root->left())
                {
                    // unlink the left subtree
                    root->left()->parent().reset();
                    // set the left substree to nullptre
                    root->left().reset();
                }
            }
        }
    }
    // }}}
    // {{{ function setRight
    template <class T> 
    void setRight(NodeSptr<T>& root, NodeSptr<T>& new_right)
    {
        assert(root);        
        if(new_right)
        {
            /* doc
            If the new right substree root is not null then 
            the old left subtree must be unlinked by severing its' 
            parent pointer
            */
            if(root->right())
            {
                // unlink the left subtree 
                root->right()->parent().reset();
            }
            // link new left subtree
            root->right() = new_right;
            root->right()->parent() = root;
        }
        else 
        {
            /* doc
            If new_left is nullptr then this function simply 
            severs the left subtree.
            */
            if(root->right())
            {
                // unlink the left subtree
                root->right()->parent().reset();
                // set the left substree to nullptre
                root->right().reset();
            }
        }
    }
    // }}}
    // {{{ function: leftRotate
    // template <class T>
    // NodeSptr<T>  leftRotate(NodeSptr<T> x)
    // {
    //     NodeSptr<T> y{nullptr};
    //     if(internal::notNull(x->left()))
    //     {
    //         // x is the this pointer
    //         // create local variable to hold left child called y
    //         y = x->left();
    //         // set the right subtree of x to be the left subtree of y
    //         x->right() = y->left();
    //         // if left child of y in not null then set its parent to x
    //         if(internal::notNull(y->left()))
    //         {
    //             y->left()->parent() = this;
    //         }
    //         // set the parent of y to the parent of x
    //         y->parent_ = parent_;
    //         // if x is the root node then set y to the root node
    //         if(internal::isNull(parent_))
    //         {
    //             owner_->root_ = y;
    //         }
    //         else
    //         {
    //             if(isLeft())
    //             {
    //                 parent_->left_ = y;
    //             }
    //             else
    //             {
    //                 parent_->right_ = y;
    //             }
    //         }
    //         y->left_.reset(this);
    //         parent_ = y.get();                
    //     }
    //     fmt::print("{} . {}\n", y->stringify(), y.use_count());
    //     return y;
    // }
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

