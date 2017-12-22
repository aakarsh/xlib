#ifndef RB_TREE_H
#define RB_TREE_H

/**
 * All paths from a node down to a descendent will have 
 * same number of black nodes.
 */
enum rb_color { black, red };

struct rb_node
{
  
  enum rb_color color:1;  
};



#endif
