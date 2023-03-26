// ------------------------------------------------------
//  John Alexander Ferguson, 2023
//  Distributed under CC0 1.0 Universal licence
// ------------------------------------------------------

#include <cstddef>
#include <memory>
#include <utility>
#include <iterator>
#include <cmath>
#include <string>

#include <libfoundation/core/io.hpp>


namespace foundation
{
namespace rbtree
{
    // {{{ collection: utilities
    namespace internal
    {  
        inline bool isNull(void* ptr)
        {
            return (ptr == nullptr);
        }
        inline bool notNull(void* ptr)
        {
            return (ptr != nullptr);
        } 
        template <class T> 
        inline bool isNull(const std::shared_ptr<T>& ptr)
        {
            return (ptr == nullptr);
        }
        template <class T>
        inline bool notNull(const std::shared_ptr<T>& ptr)
        {
            return (ptr != nullptr);
        }
    }
    // }}}
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
        /** Pointer to the tree which owns this node */
        Tree<T>* owner_;
        /** Value this node stores*/
        T value_{};
        /** Pointer to the parent */
        NodeRptr<T> parent_;
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
        Node(Tree<T>* owner, const T& value, long int uid)
        {
            owner_ = owner;
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

        NodeRptr<T>& parent() {
            return parent_;
        }

        NodeRptr<T> parent() const {
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
            if(internal::notNull(parent_))
            {
                is_left = parent_->left_.get() == this;
            }
            return is_left;
        }

        bool isRight() {
            bool is_right{false};
            if(internal::notNull(parent_)) 
            {
                is_right = parent_->right_.get() == this;
            }
            return is_right;
        }

        bool isLeaf() {
            bool is_leaf{left_ == nullptr && right_ == nullptr};
            return is_leaf;
        }
        // }}}
        // {{{ collection: alteration
        void setLeft(NodeSptr<T> node)
        {
            if(internal::notNull(node))
            {
                left_ = std::move(node);
                left_->parent_ = this;
            }
        }

        void setRight(NodeSptr<T> node)
        {
            if(internal::notNull(node))
            {
                right_ = std::move(node);
                right_->parent_ = this;
            }
        }

        /**
        @brief Performs the left rotation operation to the 
        
        @return NodeSptr<T> 
         */
        NodeSptr<T>  leftRotate()
        {
            NodeSptr<T> y{nullptr};
            if(internal::notNull(left_))
            {
                // x is the this pointer
                // create local variable to hold left child called y
                y = left_;
                // set the right subtree of x to be the left subtree of y
                right_ = y->left_;
                // if left child of y in not null then set its parent to x
                if(internal::notNull(y->left_))
                {
                    y->left_->parent_ = this;
                }
                // set the parent of y to the parent of x
                y->parent_ = this->parent_;
                // if x is the root node then set y to the root node
                if(internal::isNull(parent_))
                {
                    owner_->root_ = y;
                }
                else
                {
                    if(isLeft())
                    {
                        parent_->left_ = y;
                    }
                    else
                    {
                        parent_->right_ = y;
                    }
                }
                y->left_.reset(this);
                parent_ = y.get();                
            }
            return y;
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

        if(internal::notNull(node.parent()))
            json["parent"] = node.parent()->uid();

        if(internal::notNull(node.left()))
            json["left"] = node.left()->uid();
            
        if(internal::notNull(node.right()))
            json["right"] = node.right()->uid();

    }
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

