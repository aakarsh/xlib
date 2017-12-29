#!/usr/bin/python

# Eric Demaine : Balanced Search Trees
# https://www.youtube.com/watch?v=O3hI9FdxFOM
"""
red-black tree
1. binery search trees

red-black properties
1. node-color: { red , black}
2. node-color(nil): black
3. color[parent[black-node]] == black
4. 2* length(path[x->leaf(x)] ! filter color == black) <= path-length[x->leaf(x)]
5. black-height[nil] == 1
"""
class rb_tree:

    def __init__(self):
        self.left  = None
        self.right = None
        self.color = None

    def __rotate__(self, left, right):
        pass

    def __rotate_right__(self, left, right):
        pass

    def __rotate_left(self, left, right):
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

if __name__ == "__main__":
    print("rb:start")
    rb = rb_tree()
    print("rb:end")
