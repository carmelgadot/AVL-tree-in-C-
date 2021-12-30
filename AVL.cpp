#include "AVL.h"

/**
 * Constructor. Constructs an empty AVL tree
 */
AVL::AVL () : _root (nullptr)
{}

/**
 * Copy constructor
 * @param other other AVL obj to copy
 */
AVL::AVL (const AVL &other) : AVL ()
{
  *this = other;
}

/**
 * destructor for AVL class
 */
AVL::~AVL ()
{
  free_avl (_root);
}

/**
 * Assignment operator - copies the contents of another AVL object to this
 * @param rhs AVL to copy values from
 * @return reference to this AVL
 */
AVL &AVL::operator= (const AVL &rhs)
{
  // making sure rhs is not this. no need to copy
  if (this != &rhs)
    {
      free_avl (_root);
      _root = helper_copy (rhs.get_root ());

    }
  return *this;
}

/**
 * recursive func that free all nodes of a tree in post order.
 * @param curr_node current node in the tree
 */
void AVL::free_avl (AVL::node *curr_node)
{
  if (curr_node == nullptr)
    { // base case
      return;
    }

  free_avl (curr_node->get_left ());
  free_avl (curr_node->get_right ());
  delete (curr_node);

}

/**
 * A constructor that receives a vector of pairs. Each such pair is an
 * apartment that will inserted to the tree. Insert can be used to insert the
 * apartments a vector of a pairs
 * @param coordinates vector of pairs
 */
AVL::AVL (const std::vector<std::pair<double, double>> &coordinates) : AVL ()
{
  for (auto x: coordinates)
    {
      Apartment a (x);
      insert (a);
    }
}

/**
 * @return the root node of this tree
 */
AVL::node *AVL::get_root () const
{
  return _root;
}

/**
 * The function inserts the new apartment into the tree so that it maintains
 * the legality of the tree.
 * @param apartment Apartment object to add to tree
 */
void AVL::insert (const Apartment &apartment)
{

  _root = helper_insert (apartment, _root);

}

/**
 * The function deletes the apartment from the tree (if it is in that tree)
 * so that it maintains
 * the legality of the tree.
 * @param apartment Apartment object to erase from the tree
 */
void AVL::erase (const Apartment &apartment)
{
  _root = helper_erase (apartment, _root);
}

/**
 * find successor for a node with left child. the successor is the left most
 * leaf
 * @param node pointer to node for it we want to find successor
 * @return the successor of node
 */
AVL::node *find_successor (AVL::node *node)
{
  AVL::node *curr_node = node;

  // go over to the most left leaf
  while (curr_node->get_left () != nullptr)
    {
      curr_node = curr_node->get_left ();
    }

  return curr_node;
}

/**
 * recursive func for erasing the node of a given apartment
 * @param apartment apartment to erase from the tree
 * @param curr_node the current node in the tree
 * @return new root of the AVL tree after after the node of apartment was
 * erased
 */
AVL::node *AVL::helper_erase (const Apartment &apartment,
                              AVL::node *curr_node)
{
  if (curr_node == nullptr) // base case
    {
      return curr_node;
    }

    // the apartment key is smaller than the apartment in the node,
    // call this func with the left child
  else if (apartment < curr_node->get_data ())
    {
      curr_node->set_left (helper_erase (apartment,
                                         curr_node->get_left ()));
    }
    // the apartment key is bigger than the apartment in the node,
    // call this func with the right child
  else if (apartment > curr_node->get_data ())
    {
      curr_node->set_right (helper_erase (apartment,
                                          curr_node->get_right ()));
    }

  else // this the node with the apartment we need to delete
    {

      if ((curr_node->get_left () == nullptr) // no children case
          && (curr_node->get_right () == nullptr))
        {
          delete (curr_node);
          return nullptr;
        }

      if ((curr_node->get_left () != nullptr) // only left child case
          && (curr_node->get_right () == nullptr))
        {
          AVL::node *temp = curr_node->get_left ();
          delete (curr_node);
          return temp;
        }

      if ((curr_node->get_left () == nullptr) // only right child case
          && (curr_node->get_right () != nullptr))
        {
          AVL::node *temp = curr_node->get_right ();
          delete (curr_node);
          return temp;
        }

      if ((curr_node->get_left () != nullptr) // 2 children case
          && (curr_node->get_right () != nullptr))
        {
          AVL::node *temp = find_successor (curr_node->get_right ());

          //replace data with the successor
          curr_node->data_ = temp->get_data ();

          //call again the func with the right subtree and the successor
          // apartment
          curr_node->set_right (helper_erase (curr_node->data_,
                                              curr_node->get_right ()));

        }

    }

  update_height (curr_node);
  return balance_tree (curr_node);

}

/**
 * rl rotation
 * @param curr_node pointer to node to make rotation on
 * @return pointer to the node after rotation
 */
AVL::node *AVL::do_rl_rotation (AVL::node *curr_node)
{
  curr_node->set_right (do_rr_rotation (curr_node->get_right ()));
  return do_ll_rotation (curr_node);
}

/**
 * rr rotation
 * @param curr_node pointer to node to make rotation on
 * @return pointer to the node after rotation
 */
AVL::node *AVL::do_rr_rotation (AVL::node *curr_node)
{
  AVL::node *new_root = curr_node->get_left ();
  AVL::node *temp = new_root->get_right ();

  new_root->set_right (curr_node);
  curr_node->set_left (temp);

  update_height (curr_node);
  update_height (new_root);

  return new_root;
}

/**
 * ll rotation
 * @param curr_node pointer to node to make rotation on
 * @return pointer to the node after rotation
 */
AVL::node *AVL::do_ll_rotation (AVL::node *curr_node)
{
  AVL::node *new_root = curr_node->get_right ();
  AVL::node *temp = new_root->get_left ();

  new_root->set_left (curr_node);
  curr_node->set_right (temp);

  update_height (curr_node);
  update_height (new_root);

  return new_root;
}

/**
 * lr rotation
 * @param curr_node pointer to node to make rotation on
 * @return pointer to the node after rotation
 */
AVL::node *AVL::do_lr_rotation (AVL::node *curr_node)
{
  curr_node->set_left (AVL::do_ll_rotation (curr_node->get_left ()));
  return AVL::do_rr_rotation (curr_node);
}

/**
 * @return Iterator object that corresponds to the beginning of the tree
 * (root)
 */
AVL::Iterator AVL::begin ()
{
  AVL::Iterator itr (_root);
  return itr;
}

/**
 * @return ConstIterator object that corresponds to the beginning of the tree
 * (root)
 */
AVL::ConstIterator AVL::begin () const
{
  AVL::ConstIterator c_itr (_root);
  return c_itr;
}

/**
 * @return ConstIterator object that corresponds to the beginning of the tree
 * (root)
 */
AVL::ConstIterator AVL::cbegin ()
{
  AVL::ConstIterator c_itr (_root);
  return c_itr;
}

/**
 * @return Iterator object that corresponds to the end of the tree
 * (nullptr)
 */
AVL::Iterator AVL::end ()
{
  AVL::Iterator itr (nullptr);
  return itr;
}

/**
 * @return ConstIterator object that corresponds to the end of the tree
 * (nullptr)
 */
AVL::ConstIterator AVL::end () const
{
  AVL::ConstIterator c_itr (nullptr);
  return c_itr;
}

/**
 * @return ConstIterator object that corresponds to the end of the tree
 * (nullptr)
 */
AVL::ConstIterator AVL::cend ()
{
  AVL::ConstIterator c_itr (nullptr);
  return c_itr;
}

/**
 * recursive func for find the node of the given apartment
 * @param data Apartment obj we want to find
 * @param curr_node the current node in tree
 * @return the node that corresponds to the apartment we were looking for.
 * If there is no such node, return nullptr.
 */
AVL::node *helper_find (const Apartment &data, AVL::node *curr_node)
{
  if (curr_node == nullptr || curr_node->get_data () == data) // base case
    {
      return curr_node;
    }

    // the apartment we are looking for is smaller than the apartment in the
    // current node, call this func with the left child
  else if (data < curr_node->get_data ())
    {
      return helper_find (data, curr_node->get_left ());
    }
    // the apartment we are looking for is bigger than the apartment in the
    // current node, call this func with the right child
  else
    {
      return helper_find (data, curr_node->get_right ());
    }
}

/**
 * The function returns an iterator to the item that corresponds to the item
 * we were looking for. If there is no such member, returns end ().
 * @param data apartment to search
 * @return iterator to the item that corresponds to the item
 * we were looking for. If there is no such member, returns end ().
 */
AVL::iterator AVL::find (const Apartment &data)
{

  AVL::iterator itr (helper_find (data, _root));
  return itr;

}

/**
 * The function returns a const iterator to the item that corresponds to the
 * item we were looking for. If there is no such member, returns end ().
 * @param data apartment to search
 * @return const iterator to the item that corresponds to the item
 * we were looking for. If there is no such member, returns end ().
 */
AVL::const_iterator AVL::find (const Apartment &data) const
{

  AVL::const_iterator c_itr (helper_find (data, _root));
  return c_itr;

}

/**
 * Insertion operator, prints the apartment in the tree in preorder traversal.
 * Each apartment will be printed in the format: (x,y)\n
 * @param os reference to std::ostream
 * @param avl tree
 * @return os reference to std::ostream
 */
std::ostream &operator<< (std::ostream &os, const AVL &avl)
{
  for (auto x : avl)
    {
      os << x;
    }
  return os;
}

/**
 * recursive func for create new AVL according other AVL
 * @param other other AVL to copy
 * @return new AVL tree the same as other AVL
 */
AVL::node *AVL::helper_copy (AVL::node *other)
{
  if (other == nullptr) // base case
    {
      return nullptr;
    }
  auto *new_root = new AVL::node (other->get_data (),
                                  helper_copy (other->get_left ()),
                                  helper_copy (other->get_right ()));
  return new_root;
}

/**
 * balance the tree according the legality of AVL tree
 * @param curr_node pointer to node to balance if balance is needed
 * @return balanced node (sub tree)
 */
AVL::node *AVL::balance_tree (AVL::node *curr_node)
{
  if (curr_node == nullptr) // no need to balance
    {
      return curr_node;
    }

  if (get_balance_factor_of_node (curr_node) < R_BF_FACTOR) // R case
    {

      if (get_balance_factor_of_node (curr_node->get_right ())
          <= RR_BF_FACTOR) //RR case
        {

          return AVL::do_ll_rotation (curr_node);
        }
      else
        {

          return AVL::do_rl_rotation (curr_node); //RL case
        }
    }

  if (get_balance_factor_of_node (curr_node) > L_BF_FACTOR) // L case
    {

      if (get_balance_factor_of_node (curr_node->get_left ())
          >= LL_BF_FACTOR) //LL case
        {

          return AVL::do_rr_rotation (curr_node);
        }
      else
        {

          return AVL::do_lr_rotation (curr_node); // LR case
        }
    }

  return curr_node; // balance is not needed

}

/**
 * recursive func for insertion a new apartment into the tree so that it
 * maintains the legality of the tree.
 * @param apartment apartment to add the tree
 * @param curr_node pointer to the current node in tree
 * @return new root of the tree that includes the new apartment
 */
AVL::node *AVL::helper_insert (const Apartment &apartment,
                               AVL::node *curr_node)
{
  if (curr_node == nullptr) // base case
    {
      return new AVL::node (apartment, nullptr, nullptr);
    }
    // the apartment key is bigger than the apartment in the node,
    // call this func with the right child
  else if (apartment > curr_node->get_data ())
    {
      curr_node->set_right (helper_insert (apartment,
                                           curr_node->get_right ()));
    }

  else
    {
      // the apartment key is smaller than the apartment in the node,
      // call this func with the left child.
      // we assume that there are not two equal apartments
      curr_node->set_left (helper_insert (apartment,
                                          curr_node->get_left ()));
    }

  update_height (curr_node);
  return balance_tree (curr_node);

}

/**
 * @param curr_node pointer to node to get its height
 * @return the height of the node. if the node is nullptr return -1.
 */
int AVL::get_height_of_node (const AVL::node *curr_node)
{
  if (curr_node == nullptr)
    {
      return HEIGHT_NULL_NODE;
    }
  return curr_node->get_height ();
}

/**
 * update height of a node
 * @param curr_node pointer to node we ant to update its height
 */
void AVL::update_height (AVL::node *curr_node)
{
  if (curr_node == nullptr)
    {
      return;
    }
  // update the maximum from the height of the 2 children of a node +1
  if (get_height_of_node (curr_node->get_left ())
      > get_height_of_node (curr_node->get_right ()))
    {
      curr_node->set_height (
          HEIGHT_NODE_FACTOR +
          get_height_of_node (curr_node->get_left ()));
    }
  else
    {
      curr_node->set_height (
          HEIGHT_NODE_FACTOR +
          get_height_of_node (curr_node->get_right ()));
    }
}

/**
 * calculate the balance factor of a node
 * @param p_node pointer to node we want to
 * @return the balance factor of a node
 */
int AVL::get_balance_factor_of_node (const AVL::node *p_node)
{
  if (p_node == nullptr)
    {
      return BF_NULL_NODE;
    }
  return get_height_of_node (p_node->get_left ()) -
         get_height_of_node (p_node->get_right ());
}

