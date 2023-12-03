


#include <cstddef>
#include <memory>
#include <stack>
#include <string>

#include <libfoundation/core/io.hpp>
#include <libfoundation/core/assertions.hpp>

namespace foundation {
namespace rbree {


    static const long int NIL_UID = 0;

    //--------------------------------------------------------------------------------------------//
    //                                       struct Node                                          //
    //--------------------------------------------------------------------------------------------//
    template <typename T>
    struct Node;

    template <typename T>
    using Snode = std::shared_ptr<Node<T>>;

    template <typename T>
    struct Node 
    {

        T data_{};
        long int uid_{NIL_UID};
        Snode<T> p_;
        Snode<T> l_;
        Snode<T> r_;

        Node() = default;
        Node(const T& value, long int uid)
        {
            init(value, uid);
        }
        void init(const T& value, long int uid)
        {
            data_ = value;
            uid_ = uid;    
        }

        static Snode<T> newFromData(const T& data, long int uid)
        {
            return std::make_shared<Node<T>>(data, uid);
        }

        static Snode<T> newFromJson(const core::Json& json)
        {
            auto out = std::make_shared<Node<T>>();
            out->fromJson(json);
            return out;
        }

        bool isRed() const 
        {
            return uid_ >= 0;
        }

        void flip()
        {
            uid_ = -uid_;
        }

        bool isLeft() const 
        {
            bool is_left{false};
            if(p_) 
            {
                is_left = this == p_->l_.get();
            }
            return is_left;
        }


        bool isRight() const 
        {
            bool is_right{false};
            if(p_) 
            {
                is_right = this == p_->r_.get();
            }
            return is_right;
        }

        bool isLeaf() const 
        {
            bool is_leaf = !l_ && !r_;
            return is_leaf;
        }

        bool isNil() const 
        {
            return uid_ == NIL_UID;
        }

        core::Json toJson() const 
        {
            core::Json json;
            json["data"] = data_;
            json["uid"] = uid_;
            json["p"] = p_ ? std::abs(p_->uid_) : NIL_UID;
            json["l"] = l_ ? std::abs(l_->uid_) : NIL_UID;
            json["r"] = r_ ? std::abs(r_->uid_) : NIL_UID;
            return json;
        }

        void fromJson(const core::Json& json) 
        {
            data_ = json["data"];
            uid_ = json["uid"];
        }
    };

    template <typename T> 
    std::string format_as(Node<T> node) 
    {
        core::Json json = node.toJson();
        auto json_str = json.dump(4);
        return json_str;
    }


    //--------------------------------------------------------------------------------------------//
    //                                       class RBtree                                         //
    //--------------------------------------------------------------------------------------------//
    template <typename T, typename Compare = std::less<T>> 
    class RBtree
    {
        private: 

        Snode<T> root_;
        const Snode<T> nil_node_{std::make_shared<Node<T>>(0.0, NIL_UID)};
        Compare cmp_;
        std::size_t size_{0};

        public: 



        RBtree() = default;

        RBtree(Compare cmp)
        {
            cmp_ = cmp;
        }

        Snode<T>& root() {return root_;};
        const Snode<T>& root() const {return root_;};

        const Compare& cmp() const {return cmp_;};

        Snode<T>& search(const T& value)
        {
            Compare cmp;
            Snode<T> cur = root_;
            Snode<T> prev = nullptr;
            while (cur)
            {
                prev = cur;
                if (cmp_(value, cur->data_))
                {
                    cur = cur->l_;
                }
                else if(cmp_(cur->data_, value)) 
                {
                    cur = cur->r_;
                }
                else 
                {
                    return cur;
                }
            }
            return nil_node_;
        }


        core::Json toJson() const 
        {
            core::Json json;

            json["size"] = size_;
            json["root"] = std::abs(root_->uid_);

            std::stack<Snode<T>> node_stack;
            node_stack.push(root_);

            while(!node_stack.empty())
            {
                auto cur = node_stack.top();
                node_stack.pop();

                auto cur_uid_str = core::format("{}", std::abs(cur->uid_));

                json[cur_uid_str] = cur->toJson();

                if(cur->l_)
                    node_stack.push(cur->l_);

                if(cur->r_)
                    node_stack.push(cur->r_);

            }
            return json;
        }

        void fromJson(const core::Json& json)
        {
            std::size_t size = json["size"].get<std::size_t>();
            size_ = size;

            long int root_uid = json["root"];


            std::stack<long int> node_ids;
            node_ids.push(root_uid);

            while(!node_ids.empty())
            {
                long int cur_uid = node_ids.top();
                auto cur_uid_str = core::format("{}", cur_uid);
                node_ids.pop();

                core::Json cur_json = json[cur_uid_str];
                auto cur = Node<T>::newFromJson(cur_json);

                if(!root_) root_ = cur;

                long int l_uid = cur_json["l"];
                if (l_uid != NIL_UID)
                {

                    auto l_uid_str = core::format("{}", l_uid);
                    core::Json l_json = json[l_uid_str];
                    auto l = Node<T>::newFromJson(l_json);
                    cur->l_ = l;
                    l->p_ = cur;
                    node_ids.push(std::abs(l_uid));
                }


                long int r_uid = cur_json["r"];
                if (r_uid != NIL_UID)
                {

                    auto r_uid_str = core::format("{}", r_uid);
                    core::Json r_json = json[r_uid_str];
                    auto r = Node<T>::newFromJson(r_json);
                    cur->r_ = r;
                    r->p_ = cur;
                    node_ids.push(std::abs(r_uid));
                }

            }


        }


    };

    template <typename T> 
    std::string format_as(RBtree<T> tree) 
    {
        core::Json json = tree.toJson();
        auto json_str = json.dump(4);
        return json_str;
    }

    template <typename T> 
    void leftRotate(RBtree<T>& tree, Snode<T>& x)
    {
        if(x->r_)
        {
            // extract right subtree
            auto y = x->r_;
            // turn y's left tree into x's right tree
            x->r_ = y->l_;
            if (y->l_)
                y->l_->p_ = x;
            // link x's parent to y
            y->p_->x->parent;
            if (x->isRoot())
                tree->root() = y;
            else if(x->isLeft())
                x->p_->l_ = y;
            else 
                x->p_->r_ = y;
            // make x left subtree of y
            y->l_ = x;
            x.p_ = y;
        }
    }


    template <typename T> 
    void rightRotate(RBtree<T>& tree, Snode<T>& node)
    {

    }
}
}