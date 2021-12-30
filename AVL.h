#ifndef _AVL_H_
#define _AVL_H_
#include <vector>
#include "Apartment.h"
#include <stack>

#define HEIGHT_NODE_FACTOR 1
#define HEIGHT_NULL_NODE -1
#define BF_NULL_NODE 0
#define R_BF_FACTOR -1
#define RR_BF_FACTOR 0
#define L_BF_FACTOR 1
#define LL_BF_FACTOR 0
#define HEIGHT_NEW_NODE 0

/**
 * this class represents AVL tree
 */
class AVL {

 public:
  /**
   * To manage the tree nodes, we use a nested struct. This struct contains
   * the apartment corresponding to the node, the left son and the right son
   * of the node, both of them node type themselves.
   */
  struct node {
      /**
       * Constructor - It can be expanded
       * @param data the corresponding apartment object
       * @param left child
       * @param right child
       */
      node (Apartment data, node *left, node *right)
          : data_ (data), left_ (left), right_ (right),
            height_ (HEIGHT_NEW_NODE)
      {}
      /**
       * @return the left child of this node
       */
      node *get_left () const
      {
        return left_;
      }
      /**
       * @return the right child of this node
       */
      node *get_right () const
      {
        return right_;
      }

      /**
       * @return the height of this node
       */
      int get_height () const
      {
        return height_;
      }

      /**
       * set the height of this node
       */
      void set_height (int height)
      {
        height_ = height;
      }

      /**
       * set the the right child of this node
       */
      void set_right (node *right)
      {
        right_ = right;
      }

      /**
       * set the the left child of this node
       */
      void set_left (node *left)
      {
        left_ = left;
      }

      /**
       * @return the const reference apartment of this node
       */
      const Apartment &get_data () const
      {
        return data_;
      }
      Apartment data_;
      node *left_, *right_;
      int height_;

  };

  /**
   * Constructor. Constructs an empty AVL tree
   */
  AVL ();

  /**
   * Copy constructor
   * @param other other AVL obj to copy
   */
  AVL (const AVL &other);

  /**
   * destructor for AVL class
   */
  ~AVL ();

  /**
   * Assignment operator - copies the contents of another AVL object to this
   * @param rhs AVL to copy values from
   * @return reference to this AVL
   */
  AVL &operator= (const AVL &rhs);

  /**
   * A constructor that receives a vector of pairs. Each such pair is an
   * apartment that will inserted to the tree. Insert can be used to insert
   * the apartments a vector of a pairs
   * @param coordinates vector of pairs
   */
  AVL (const std::vector<std::pair<double, double>> &coordinates);

  /**
   * @return the root node of this tree
   */
  node *get_root () const;

  /**
   * The function inserts the new apartment into the tree so that it maintains
   * the legality of the tree.
   * @param apartment Apartment object to add to tree
   */
  void insert (const Apartment &apartment);

  /**
    * The function deletes the apartment from the tree (if it is in that tree)
    * so that it maintains
    * the legality of the tree.
    * @param apartment Apartment object to erase from the tree
    */
  void erase (const Apartment &apartment);

  /**
   * The class should support forward iterator. Don't forget to define the
   * iterator traits and all the actions required to support a forward
   * iterator the iterator will move in preorder.
   */
  class Iterator {
    std::stack<AVL::node *> stack;
   public:
    AVL::node *cur;
    typedef Apartment value_type;
    typedef Apartment &reference;
    typedef Apartment *pointer;
    typedef std::forward_iterator_tag iterator_category;
    typedef std::ptrdiff_t difference_type;

    /**
     * Constructor.
     * @param cur pointer to node to make iterator from it that node
     * is the root
     */
    Iterator (AVL::node *cur)
        : cur (cur)
    {
      stack.push (cur);
    }

    /**
     * pointer operator
     * @return pointer to Apartment the data of the node in the iterator
     */
    pointer operator-> () const
    {
      return &cur->data_;
    }

    /**
     * dereference operator
     * @return reference to Apartment the data of the node in the iterator
     */
    reference operator* () const
    {
      return cur->data_;
    }

    /**
     * Pre-increment operator.
     * @return reference to this
     */
    Iterator &operator++ ()
    {
      if (stack.empty ()) // end of iterator
        {
          cur = nullptr;
          return *this;
        }
      // in pre-order take the first in stack(the parent) and put his 2
      // children in stack
      node *prev_top = stack.top ();
      stack.pop ();

      if (prev_top->get_right () != nullptr)
        {
          stack.push (prev_top->get_right ());
        }

      if (prev_top->get_left () != nullptr)
        { stack.push (prev_top->get_left ()); }

      if (stack.empty ()) // end of iterator
        {
          cur = nullptr;
          return *this;
        }
      node *new_top = stack.top ();
      cur = new_top;
      return *this;
    }

    /**
     *  Post-increment operator.
     * @return this
     */
    Iterator operator++ (int)
    {

      iterator it = *this;
      if (stack.empty ()) // end of iterator
        {
          cur = nullptr;
          return it;
        }

      // in pre-order take the first in stack(the parent) and put his 2
      // children in stack
      node *prev_top = stack.top ();
      stack.pop ();

      if (prev_top->get_right () != nullptr)
        {
          stack.push (prev_top->get_right ());
        }

      if (prev_top->get_left () != nullptr)
        { stack.push (prev_top->get_left ()); }

      if (stack.empty ()) // end of iterator
        {
          cur = nullptr;
          return it;
        }
      node *new_top = stack.top ();
      cur = new_top;
      return it;
    }

    /**
     * Operator ==, Two Iterators are identical if their cur is the same
     * @param other other Iterator obj
     * @return true if the two Iterators are equal, false otherwise
     */
    bool operator== (const Iterator &rhs) const
    {
      return cur == rhs.cur;
    }

    /**
     * Operator !=, Two Iterators are not identical if their cur is not the
     * same
     * @param other other Iterator obj
     * @return true if the two Iterators are not equal, false otherwise
     */
    bool operator!= (const Iterator &rhs) const
    {
      return !(rhs == *this);
    }
  };

  /**
   * const iterator
   * The class support forward iterator.
   * The iterator will move in preorder.
   */
  class ConstIterator {
    AVL::node *cur;
    std::stack<node *> stack;

   public:
    typedef const Apartment value_type;
    typedef const Apartment &reference;
    typedef const Apartment *pointer;
    typedef std::forward_iterator_tag iterator_category;
    typedef std::ptrdiff_t difference_type;

    /**
     * Constructor.
     * @param cur pointer to node to make const iterator from it that node
     * is the root
     */
    ConstIterator (node *cur)
        : cur (cur)
    {
      stack.push (cur);
    }

    /**
     * Constructor.
     * @param it iterator obj to make const iterator from it
     */
    ConstIterator (const Iterator &it) : cur (it.cur)
    {}

    /**
     * pointer operator
     * @return const pointer to Apartment the data of the node in the iterator
     */
    pointer operator-> () const
    {
      return &cur->get_data ();
    }

    /**
     * dereference operator
     * @return const reference to Apartment the data of the node in the
     * iterator
     */
    reference operator* () const
    {
      return cur->get_data ();
    }

    /**
     * Pre-increment operator.
     * @return reference to this
     */
    ConstIterator &operator++ ()
    {
      if (stack.empty ()) // end of iterator
        {
          cur = nullptr;
          return *this;
        }
      // in pre-order take the first in stack(the parent) and put his 2
      // children in stack
      node *prev_top = stack.top ();
      stack.pop ();

      if (prev_top->get_right () != nullptr)
        {
          stack.push (prev_top->get_right ());
        }

      if (prev_top->get_left () != nullptr)
        { stack.push (prev_top->get_left ()); }

      if (stack.empty ()) // end of iterator
        {
          cur = nullptr;
          return *this;
        }
      node *new_top = stack.top ();
      cur = new_top;
      return *this;
    }

    /**
     *  Post-increment operator.
     * @return this
     */
    ConstIterator operator++ (int)
    {
      const_iterator it = *this;
      if (stack.empty ()) // end of iterator
        {
          cur = nullptr;
          return it;
        }
      // in pre-order take the first in stack(the parent) and put his 2
      // children in stack
      node *prev_top = stack.top ();
      stack.pop ();

      if (prev_top->get_right () != nullptr)
        {
          stack.push (prev_top->get_right ());
        }

      if (prev_top->get_left () != nullptr)
        { stack.push (prev_top->get_left ()); }

      if (stack.empty ()) // end of iterator
        {
          cur = nullptr;
          return it;
        }
      node *new_top = stack.top ();
      cur = new_top;
      return it;
    }

    /**
     * Operator ==, Two const Iterators are identical if their cur is the same
     * @param other other ConstIterator obj
     * @return true if the two const Iterators are equal, false otherwise
     */
    bool operator== (const ConstIterator &rhs) const
    {
      return cur == rhs.cur;
    }

    /**
     * Operator !=, Two const Iterators are not identical if their cur is not
     * the same
     * @param other other ConstIterator obj
     * @return true if the two const Iterators are not equal, false otherwise
     */
    bool operator!= (const ConstIterator &rhs) const
    {
      return !(rhs == *this);
    }
  };

  typedef Iterator iterator;
  typedef ConstIterator const_iterator;

  /**
   * @return Iterator object that corresponds to the beginning of the tree
   * (root)
   */
  Iterator begin ();

  /**
   * @return ConstIterator object that corresponds to the beginning of the
   * tree (root)
   */
  ConstIterator begin () const;

  /**
   * @return ConstIterator object that corresponds to the beginning of the
   * tree (root)
   */
  ConstIterator cbegin ();

  /**
   * @return Iterator object that corresponds to the end of the tree
   * (nullptr)
   */
  Iterator end ();

  /**
   * @return ConstIterator object that corresponds to the end of the tree
   * (nullptr)
   */
  ConstIterator end () const;

  /**
   * @return ConstIterator object that corresponds to the end of the tree
   * (nullptr)
   */
  ConstIterator cend ();

  /**
   * The function returns an iterator to the item that corresponds to the item
   * we were looking for. If there is no such member, returns end ().
   * @param data apartment to search
   * @return iterator to the item that corresponds to the item
   * we were looking for. If there is no such member, returns end ().
   */
  iterator find (const Apartment &data);
  /**
   * The function returns an iterator to the item that corresponds to the item
   * we were looking for. If there is no such member, returns end ().
   * @param data apartment to search
   * @return iterator to the item that corresponds to the item
   * we were looking for. If there is no such member, returns end ().
   */
  const_iterator find (const Apartment &data) const;
  /**
   * Insertion operator, prints the apartment in the tree in preorder
   * traversal.
   * Each apartment will be printed in the format: (x,y)\n
   * @param os reference to std::ostream
   * @param avl tree
   * @return os reference to std::ostream
   */
  friend std::ostream &operator<< (std::ostream &os, const AVL &avl);

 private:
  node *_root;

  /**
   * recursive func for create new AVL according other AVL
   * @param other other AVL to copy
   * @return new AVL tree the same as other AVL
   */
  AVL::node *helper_copy (AVL::node *other);

  /**
   * recursive func that free all nodes of a tree in post order.
   * @param curr_node current node in the tree
   */
  void free_avl (AVL::node *curr);

  /**
   * recursive func for insertion a new apartment into the tree so that it
   * maintains the legality of the tree.
   * @param apartment apartment to add the tree
   * @param curr_node pointer to the current node in tree
   * @return new root of the tree that includes the new apartment
   */
  AVL::node *helper_insert (const Apartment &apartment, AVL::node *node);

  /**
   * recursive func for erasing the node of a given apartment
   * @param apartment apartment to erase from the tree
   * @param curr_node the current node in the tree
   * @return new root of the AVL tree after after the node of apartment was
   * erased
   */
  node *helper_erase (const Apartment &apartment, AVL::node *curr_node);

  /**
   * rl rotation
   * @param curr_node pointer to node to make rotation on
   * @return pointer to the node after rotation
   */
  static node *do_rl_rotation (AVL::node *curr_node);

  /**
   * rr rotation
   * @param curr_node pointer to node to make rotation on
   * @return pointer to the node after rotation
   */
  static node *do_rr_rotation (AVL::node *curr_node);

  /**
   * ll rotation
   * @param curr_node pointer to node to make rotation on
   * @return pointer to the node after rotation
   */
  static node *do_ll_rotation (AVL::node *curr_node);

  /**
   * lr rotation
   * @param curr_node pointer to node to make rotation on
   * @return pointer to the node after rotation
   */
  static node *do_lr_rotation (AVL::node *curr_node);

  /**
   * balance the tree according the legality of AVL tree
   * @param curr_node pointer to node to balance if balance is needed
   * @return balanced node (sub tree)
   */
  static AVL::node *balance_tree (AVL::node *curr_node);

  /**
   * @param curr_node pointer to node to get its height
   * @return the height of the node. if the node is nullptr return -1.
   */
  static int get_height_of_node (const AVL::node *curr_node);

  /**
   * update height of a node
   * @param curr_node pointer to node we ant to update its height
   */
  static void update_height (AVL::node *curr_node);

  /**
   * calculate the balance factor of a node
   * @param p_node pointer to node we want to
   * @return the balance factor of a node
   */
  static int get_balance_factor_of_node (const AVL::node *p_node);

};

#endif //_AVL_H_
