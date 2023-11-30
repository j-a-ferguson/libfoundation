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
#include <limits>
#include <stack>

#include <fmt/core.h>

#include <libfoundation/core/io.hpp>
#include <libfoundation/core/assertions.hpp>


namespace foundation
{
namespace rbtree
{

    // ....................................................................... forwared declarations
    static const long int NIL_UID = std::numeric_limits<long int>::max();

    template <class T>
    class Node;

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


    template <class T> 
    class Tree;
    // ..............................................................................  class Node
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
        // ...................................... friends
        friend class Tree<T>;
        friend void setLeft<T>(NodeSptr<T> root, NodeSptr<T> new_left);
        friend void setRight<T>(NodeSptr<T> root, NodeSptr<T> new_left);

        // ...................................... private members 
        private:
        
        /** Value this node stores*/
        T value_{};
        /** Sign bit is the color, positive = red and negative = black. Remaining bits are the uid*/
        long int uid_{0};        
        /** Pointer to the parent */
        NodeSptr<T> parent_;
        /** Pointer to the left child */
        NodeSptr<T> left_;
        /** Pointer to thr right child */
        NodeSptr<T> right_;

        //....................................... public methods
        public:


        Node() = default;
        Node(const T& value, long int uid)
        {
            init(value, uid);
        }

        void init(const T& value, long int uid)
        {
            value_ = value;
            uid_ = uid;
        }

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
        bool isRed() const {
            bool is_red = (uid_ >= 0);
            return is_red;
        }

        bool isLeft() const {
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

        core::Json toJson() const
        {
            core::Json json;
            json["value"] = value_;
            json["uid"] = uid();
            json["is_red"] = isRed(); 

            if(parent())
                json["parent"] = parent()->uid();
            else  
                json["parent"] = NIL_UID;

            if(left())
                json["left"] = left()->uid();
            else 
                json["left"] = NIL_UID;
                
            if(right())
                json["right"] = right()->uid();
            else 
                json["right"] = NIL_UID;
            
            return json;
        }

        void fromJson(const core::Json& json)
        {
            value_ = json["value"].get<T>();
            bool is_red = json["is_red"];
            uid_ = is_red ? json["uid"].get<long int>() : -json["uid"].get<long int>();
        }
    };
    //..............................................................................................

    template <typename T>
    std::string format_as(Node<T> node)
    {
        core::Json json = node.toJson();
        std::string json_str = json.dump(4);
        return json_str;
    }

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

    // template <typename T> 
    // auto format_as(Node<T>& node)
    // {
    //     core::Json json = node.toJson();
    //     std::string json_str = json.dump(4);
    //     return json_str;
    // }


    // .................................................................................class RBTree
    template <class T>
    class Tree
    {
        friend class Node<T>;

        private: 

        std::size_t size_{0};
        NodeSptr<T> root_;
        long int next_uid_{0};

        public:

        
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

            Iterator() = default;

            Iterator(Node<T>* node)
            {
                node_ = node;
            }

            void init(Node<T> *node)
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
        

        Tree() = default;

         std::pair<bool, Iterator> insert(const T& value)
        {
            std::pair<bool, Iterator> out;
            out.first = false;

            NodeSptr<T> y;
            NodeSptr<T> x = root_;

            while (x)
            {
                if(x->value_ == value)
                {
                    out.second.init(x.get());
                    return out;
                }
                y = x;
                if (value < x->value_)
                {
                    x = x->left_;
                }
                else {
                    x = x->right_;
                }
            }

            NodeSptr<T> new_node;
            if (!y) 
            {
                root_ = newNode(value);
                out.first = true;
                out.second.init( root_.get());
                new_node = root_;
            }
            else if (value < y->value()) 
            {
                y->left() = newNode(value);
                out.first = true;
                out.second.init(y->left().get());
                new_node = y->left();
            }
            else 
            {
                y->right() = newNode(value);
                out.first = true;
                out.second.init(y->right().get());
                new_node = y->right();
            }

            insertFixup(new_node);

            return out;
        }

        Iterator erase(const T& value);
        Iterator erase(Iterator iter);        

        core::Json toJson() 
        {
            core::Json json; 
            json["root"] = root_->uid();

            std::stack<NodeSptr<T>> next_nodes;
            next_nodes.push(root_);
            
            while (!next_nodes.empty())
            {
                NodeSptr<T> cur = next_nodes.top(); 
                next_nodes.pop();

                auto uid_str = std::to_string(cur->uid());
                json[uid_str] = cur->toJson();

                if(cur->left())
                    next_nodes.push(cur->left());

                if(cur->right()) 
                    next_nodes.push(cur->right());

            }
            return json;
        }

        void fromJson(const core::Json& json)
        {
            std::string root_uid = std::to_string(json["root"].get<long int>());
            root_ = newNode(json[root_uid]);
            
            std::stack<std::string> next_nodes;
            next_nodes.push(root_uid);

            while (!next_nodes.empty())
            {
                std::string cur_uid  = next_nodes.top();
                next_nodes.pop();

                std::string left_uid = std::to_string(json[cur_uid]["left"].get<long int>());
                std::string right_uid = std::to_string(json[cur_uid]["right"].get<long int>());

                auto new_node = newNode(json[cur_uid]);
                auto left_node = newNode(json[left_uid]);
                auto right_node = newNode(json[right_uid]);


                new_node->left() = left_node;
                left_node->parent() = new_node;
                new_node->right() = right_node;
                right_node->parent() = new_node;

            }

        }



        private: 

        void insertFixup(NodeSptr<T> node)
        {
            while(node->parent()->isRed())
            {
                if(node->parent()->isLeft())
                {
                    auto y = node->parent()->parent()->
                }
            }    
        }

        NodeSptr<T> newNode(const T& value)
        {
            NodeSptr<T> new_node = std::make_shared<Node<T>>(value, next_uid_);
            ++next_uid_;
            return new_node;
        }

        NodeSptr<T> newNode(const core::Json& json)
        {
            NodeSptr<T> new_node = std::make_shared<Node<T>>();
            new_node->fromJson(json);
            return new_node;
        }
        
    };
    //..............................................................................................


    template <typename T>
    std::string format_as(Tree<T> node)
    {
        core::Json json = node.toJson();
        std::string json_str = json.dump(4);
        return json_str;
    }



    
}
}

