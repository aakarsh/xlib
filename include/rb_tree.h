#ifndef RB_TREE_H
#define RB_TREE_H

/**
 * red-black tree is a binary search tree:
 *
 * - every node has an additional bit field indicating color
 *
 * - max-path {root -> leaf} <= 2 min-path {root -> leaf}
 *
 * - tree is *approximately* balanced.
 *
 * red-black tree invariants are :
 *
 *  - The root is black
 *
 *  - every leaf(NIL) node is black
 *
 *  - if node is red , then both children *must* be black:
 *      color(node) == red ? color(node.left) == color(node.right) == black
 *
 *  - all paths from node to leaves contain same-number of black nodes.
 *
 *      forall(n| n node(t), ):
 *           forall-pairs((l1,l2)| l1 leaf(n),l2 leaf(n)):
 *                 p1 <- path(n,l1):
 *                 p2 <- path(n,l2):
 *                 num_black_nodes(p1) == num_black_nodes(p2)
 *
 *
 *  RB-Properites:
 *  - A R-B tree with n-internal nodes has a height of at most
 *    2 * lg(n + 1)
 *  -- bh(x) - black height of x
 *  -- {x| node in T} => | internal-nodes(x) |  >=  2^bh(x) - 1

 *  -- let c = child(x) => { bh(c) = {bh(x) | c is red} or {bh(x) -1 | c is black} }
 *
 *  -- by inductive hypothesis :
 *     | internal-nodes(x.left) + internal(x.right) | >= 2^(bh(x)-1) -1 + 2^(bh(x)-1) -1| =  2^bh(x) - 1
 *
 *  -- at-least half nodes
 *
 *  -- n >= 2^(h/2) - 1
 *
 *  -- if h is height of tree,
 *     at least half nodes on any simple path  must be black
 *
 *  -- bh(root) >= h/2 | h - height of tree
 *
 *  -- |internal-nodes(root)| >= 2^bh(root) -1 >= 2^(h/2) -1
 *
 *  -- n >= 2^(h/2) -1 => h <= 2*lg(n+1) | Thus giving a O(lg(n)) bound on tree height.
 *
 *  Rotations:
 *   left-rotate(x):
 *       make right-child parent  // right-child!=Nil
 *       Adopt its left-child as your right child
 *
 *   (x \alpha nil  (y \beta \gamma)) ---> (y (x \alpha \beta) \gamma)
 *
 *   right-rotate(y):
 *       make left-child parent // left-child != Nil
 *       adopt its right-child
 *
 */

/**
 * All paths from a node down to a descendent will have same number of
 * black nodes.
 */
enum rb_color  { black, red };
enum rb_branch { rb_left, rb_right};

struct rb_key {
  void* key;
  size_t size;
};

struct rb_node
{
  enum   rb_color color:1;
  struct rb_node* parent;
  struct rb_node* left;
  struct rb_node* right;

  struct rb_key key;

};

inline bool
rb_is_root(struct rb_node* rb)
{
  return rb->parent == NULL;
}

inline bool
rb_color(struct rb_node* rb)
{
  if(rb == NULL)
    return black;
  else
    return rb->color;
}

struct rb_node*
rb_get_child(struct rb_node* node,
             enum rb_branch branch)
{
  if(node == NULL)
    return NULL;
  switch(branch) {
  case rb_left:
    return node->left;
  case rb_right:
    return node->right;
  default:
    return NULL;
  }
}

struct rb_node**
rb_get_child_ref(struct rb_node* node,
                 enum rb_branch branch)
{
  switch(branch) {
  case rb_left:
    return &(node->left);
  case rb_right:
    return &(node->right);
  default:
    return NULL;
  }
}

void
rb_set_child(struct rb_node** root,
             struct rb_node* parent,
             struct rb_node* child,
             enum rb_branch branch)
{
  if(parent == NULL)  // root has no parents
    *root = child;

  struct rb_node** child_ref =
    rb_get_child_ref(parent,branch);

  *child_ref = child;
}

enum rb_branch
rb_child_type(struct rb_node* node)
{
  return (rb_get_child(node->parent,rb_left) == node) ? rb_left : rb_right;
}

void
rb_move_child(struct rb_node* demoted,
              struct rb_node* promoted,
              enum   rb_branch branch_type)
{

  switch(branch_type) {
  case rb_left:
    // child moves from:
    // promoted-left to demoted-right
    demoted->right = promoted->left;
    if(promoted->left != NULL) { // adopt left child
      (promoted->left)->parent = demoted;
    }
    break;
  case rb_right:
    // child moves from:
    // promoted-right to demoted-left
    demoted->left = promoted->right;
    if(promoted->right != NULL) { // adopt right child
      (promoted->right)->parent = demoted;
    }
  }
}

void
rb_swap_parents(struct rb_node** root,
                struct rb_node* demoted,
                struct rb_node* promoted)
{
  promoted->parent = demoted->parent;
  // set parents
  rb_set_child(root,
               demoted->parent,
               promoted,
               rb_child_type(demoted));

  demoted->parent = promoted;
}

/**
 * During left rotation the right child
 * of node is promoted to be a parent.
 * The prmoted node's prevous left child
 * becomes the right child of
 * demoted node.
 *
 * Left rotation refers to the fact that
 * node moves down in leftward direction
 * in the final tree.
 */
void
rb_rotate(struct rb_node** root,
               struct rb_node* demoted,
               enum rb_branch rotate_direction)
{
  struct rb_node* promoted =
    rb_get_child(demoted, rotate_direction);

  rb_move_child(demoted, promoted, rotate_direction);

  rb_swap_parents(root,demoted,promoted);

  // set demoted to be child promoted
  struct rb_node** child_ref =
    rb_get_child_ref(promoted, rotate_direction);

  *child_ref  = demoted;
}

void
rb_left_rotate(struct rb_node** root,
               struct rb_node* demote)
{
  rb_rotate(root, demote, rb_left);
}

void
rb_right_rotate(struct rb_node** root,
                struct rb_node* demote)
{
  rb_rotate(root, demote, rb_right);
}


/**
 * rb_insert_fixup :
 *
 * Restores the r-b properties of
 * the tree after a new node has been
 * inserted into it.
 *
 * Needs
 */
void
rb_insert_fixup(struct rb_node** root,
                struct rb_node*  z)
{  
  /**
   * Invariants:
   *
   *  1. New node z is always red.
   *  2. if z->parent is root then z->parent is black.
   *  3. There is at most one violation of rb property:
   *     3.1 z is root and is red.
   *     3.2 z and z->parent are red.
   */
  
}

void
rb_insert(struct rb_node** root,
          struct rb_node*  new,
          int (*key_compare)(struct rb_key* k1,
                             struct rb_key* k2))
{
  new->color = red;
  new->left  = NULL;
  new->right = NULL;

  struct rb_node* parent = NULL; // find-parent a
  struct rb_node* cur = *root;

  while ( cur != NULL ) {
    parent = cur;

    // new is smaller
    if( key_compare(&(new->key), &(cur->key)) < 0) {
      cur = cur->left;
    } else {
      cur = cur->right;
    }
  }
  new->parent = parent;
  if(parent == NULL) { // new node is root
    *root = new;
  } else {
    if( key_compare(&(new->key), &(parent->key)) < 0) {
      parent->left  = new;
    } else {
      parent->right = new;
    }
  }
  rb_insert_fixup(root,new);
}

/**
 * Insertion:
 * The new node z starts out colored red.
 * 1. Find parent/insertion position in bst.
 * 2. Let parent[z] <- <insert>
 * 3. For empty tre set z as parent.
 * 4. Choose to be left of right child of parent
 * 5. Since node is inserted leaf. Set left[z] <- Nil, right[z] <- Nil
 * 6. color[z] <- red
 *
 * Rebalancing involves going through the tree and
 * fixing it up to restore the tree property.
 *
 * Insertion can violate proeprties:
 * 1. red node does not have red child. <if parent[z] == red>
 * 2. root must be black <when z is root>
 *
 * rotational-loop-invariants:
 *   1. color[z] == red
 *   2. if p[z] == root | color[p[z]] = red
 *   3. There is at-most one violation of heap property.
 *
 *   Violation only happens :
 *     1. if z is root, color[z] = red | change color to black
 *     2. if z, p[z] are red
 */


#endif
