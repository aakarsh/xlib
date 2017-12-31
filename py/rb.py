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
        self.value   = "";
        self.left    = None
        self.parent  = None
        self.right   = None
        self.color   = "."

    def __rotate__(self, left, right):
        pass

    def __rotate_right__(self, left, right):
        pass

    def __rotate_left__(self, left, right):
        pass

    def search(self):
        pass

    def succ(self,key):
        pass

    def pred(self,key):
        pass

    def insert(self,key,data):
        pass

    def delete(self,key):
        pass

    def __repr__(self):
        def node_str(node,depth,dir):
            retval  = ("*" * depth) + " "
            retval  += "(" + dir+ ":"+ node.color +")"
            retval  += "["+str(node.value)+"]"
            retval  +=  "\n"
            if node.left != None:
                retval += node_str(node.left,depth+1,"l")
            if node.right != None:
                retval += node_str(node.right,depth+1,"r")
            return retval
        return node_str(self, 1, "-")

    @classmethod
    def parse(self,s):
        pos = 0
        stack = []
        while pos < len(s) and s[pos]!= '(':
            pos += 1
        cur = None
        root = None
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
                else:
                    stack.append(cur)
                    child = rb_tree()
                    if cur.left == None:
                        cur.left = child
                    elif cur.right == None:
                        cur.right = child
                    else:
                        raise ValueError("node already has two children")
                    cur = child
            elif c == ')':
                value = ""
                cur = stack.pop()
            else:
                cur.value += c
        return root


if __name__ == "__main__":
    print("rb:start")
    rb = rb_tree()
    print("rb:end")
