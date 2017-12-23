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
enum rb_color { black, red };

struct rb_node
{
  enum   rb_color color:1;
  struct rb_node* parent;
  struct rb_node* left;
  struct rb_node* right;
  
  void* data;
  size_t data_size;
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

