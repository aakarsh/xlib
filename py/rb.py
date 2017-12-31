#!/usr/bin/python
# Eric Demaine : Balanced Search Trees
# https://www.youtube.com/watch?v=O3hI9FdxFOM
"""
Red Black Tree:
Red/Black Properties:
1. node-color: { red , black}
2. node-color(nil): black
3. color[parent[black-node]] == black
4. 2* length(path[x->leaf(x)] ! filter color == black) <= path-length[x->leaf(x)]
5. black-height[nil] == 1
"""

class rb_node:
    
    def __init__(self):
        self.key     = ""
        self.value   = {};
        self.left    = None
        self.parent  = None
        self.right   = None
        self.color   = "red"

    def __init__(self, key = "", value = {},parent=None):
        self.key     = key
        self.value   = value
        self.left    = None
        self.parent  = parent
        self.right   = None
        self.color   = "red"

    def __repr__(self):
        def node_string(node):
            retval =""
            retval  += "("
            retval  += str(node.key)
            if node.left != None:
                retval += " "+node_string(node.left)
            if node.right != None:
                retval += " "+node_string(node.right)
            retval +=" )"
            return retval
        return node_string(self)
    
    def __str__(self):
        def node_string(node,depth,dir):
            retval  = ("*" * depth) + " "
            retval  += "(" + dir+ ":"+ node.color +")"
            retval  += "["+str(node.key)+"]"
            retval  +=  "\n"
            if node.left != None:
                retval += node_string(node.left,depth+1,"l")
            if node.right != None:
                retval += node_string(node.right,depth+1,"r")
            return retval
        return node_string(self, 1, "-")

    def search(self,key):
        cur = self
        while cur != None:
            if cur.key == key:
                return cur
            elif cur.key > key:
                cur = cur.left
            elif cur.key < key:
                cur = cur.right
        return None;

    @classmethod
    def parse(self,s):
        pos = 0
        stack = []
        while pos < len(s) and s[pos]!= '(':
            pos += 1
        cur = None
        root = None
        parent = None
        while pos < len(s):
            c = s[pos]
            pos += 1
            if c == ' ':
                continue
            elif c == '(': # push current node, into stack keep parsing
                if root == None:
                    root = rb_node()
                    cur  = root
                    stack.append(cur)
                    parent = cur
                else:
                    stack.append(cur)
                    child = rb_node()
                    child.parent = cur
                    if cur.left == None:
                        cur.left = child
                    elif cur.right == None:
                        cur.right = child
                    else:
                        raise ValueError("node already has two children")
                    cur = child
            elif c == ')':
                cur.key = int(cur.key)
                cur = stack.pop()
            else:
                cur.key += c
        return root

    def insert(self, key, value=None):
        # Create :- *rb-tree node*
        z = rb_node(key,value)
        y = self
        x = self
        while x != None:
            y = x
            if key < x.key:
                x = x.left
            else:
                x = x.right
        if key < y.key:
            y.left = z
        else:
            y.right = z
        z.parent = y
        self.fix_up(z)

    def __rotate__(self, left, right):
        pass

    def __rotate_right__(self, left, right):
        pass

    def __rotate_left__(self, left, right):
        pass

    def succ(self,key):
        pass

    def pred(self,key):
        pass

    def fix_up(self,z):
        pass

    def delete(self,key):
        pass

class rb_test():
    
    def __init__(self):
        self.tree = rb_node.parse("(2 (1) (3)")
        assert self.tree != None

    def all(self):        
        print("ran tests!")
        pass
    
rb_test().all()
if __name__ == "__main__":
    print("rb:start")
    rb_test().all()
    print("rb:end")
