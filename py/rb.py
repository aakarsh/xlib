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
class rb_tree:

    def __init__(self):
        self.key     = ""
        self.value   = {};
        self.left    = None
        self.parent  = None
        self.right   = None
        self.color   = "."

    def __repr__(self):
        def node_str(node,depth,dir):
            retval  = ("*" * depth) + " "
            retval  += "(" + dir+ ":"+ node.color +")"
            retval  += "["+str(node.key)+"]"
            retval  +=  "\n"
            if node.left != None:
                retval += node_str(node.left,depth+1,"l")
            if node.right != None:
                retval += node_str(node.right,depth+1,"r")
            return retval
        return node_str(self, 1, "-")

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
        while pos < len(s) and s[pos]!= '(': pos += 1
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
                    root = rb_tree()
                    cur  = root
                    stack.append(cur)
                    parent = cur
                else:
                    stack.append(cur)
                    child = rb_tree()
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
    
    def insert(self, key, value = None):
        z = rb_tree()
        z.key = key
        z.value = value
        z.color = "red"
        z.left = None
        z.right = None
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
    
if __name__ == "__main__":
    print("rb:start")
    rb = rb_tree()
    print("rb:end")
