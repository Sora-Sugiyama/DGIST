class SplayTree():
    class _Node:
        """Lightweight, nonpublic class for storing a node."""
        __slots__ = '_element', '_parent', '_left', '_right' # streamline memory usage

        def __init__(self, element, parent=None, left=None, right=None):
            self._element = element
            self._parent = parent
            self._left = left
            self._right = right

    def ___r(self,x):
        _=x._parent
        __=x
        if x==_._left:
            _._left,__=x._right,x._right
            x._right=_
        else:
            _._right,__=x._left,x._left
            x._left=_
        x._parent=_._parent
        _._parent=x
        if __!=None:__._parent=_
        if x._parent!=None:
            if x._parent._left==_:x._parent._left=x
            else:x._parent._right=x
        else:self._root=x
    
    def ___s(self,x):
        while x._parent!=None:
            _=x._parent
            g_=_._parent
            if g_!=None:
                if (x==_._left)==(_==g_._left):self.___r(_)
                else:self.___r(x)
            self.___r(x)
    
    def __init__(self):
        """Create an initially empty binary tree."""
        self._root = None
        self._last=None
        self._size = 0

    def search(self, element):
        _,__=self._root,None
        if(_==None):return False,None
        while _!=None:
            if element==_._element:break
            else:
                __=_
                if element<_._element:_=_._left
                else:_=_._right
        if _!=None:___s(_)
        else:___s(__)
        return _
        
    def insert(self, element):
        if self.search(element)==None:return
        self._size+=1
        p=self._root
        pp=None
        if p==None:
            x=self._Node(element)
            self._root=x
            return
        while 1:
            if element<p._element:
                if p._left==None:
                    pp='_left'
                    break
                p=p._left
            else:
                if p._right==None:
                    pp='_right'
                    break
                p=p._right
        
        x=self._Node(element,p)
        setattr(p,pp,x)
        self.___s(x)
        self._last=x
        
        
    def ___dr(self):
        p=self._root
        if p._left!=None:
            if p._right!=None:
                self._root=p._left
                self._root._parent=None
                x=self._root
                while x._right!=None:x=x._right
                x._right=p._right
                p._right._parent=x
                self.___s(x)
                return
            self._root=p._left
            self._root._parent=None
            self._size-=1
            return
        if p._right!=None:
            self._root=p._right
            self._root._parent=None
            self._size-=1
            return
            
    def delete(self, element):
        if self.search(element)==None:return
        self.___dr()

    def display(self):
        self._display(self._root, 0)

    def _display(self, node, depth):
        if node == None:
            return

        if node._right != None:
            self._display(node._right, depth+1)
        label = ''
        if node == self._root:
            label += '  <- root'
        if node == self._last:
            label += '  <- last'
        print(f'{"    "*depth}* {node._element}{label}')
        if node._left != None:
            self._display(node._left, depth+1)
