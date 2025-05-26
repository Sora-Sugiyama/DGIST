class AVLTree():
    class _Node:
        """Lightweight, nonpublic class for storing a node."""
        __slots__ = '_element', '_parent', '_left', '_right', '_height' # streamline memory usage

        def __init__(self, element, parent=None, left=None, right=None):
            self._element = element
            self._parent = parent
            self._left = left
            self._right = right
            self._height = 0

        def left_height(self):
            return self._left._height if self._left != None else 0

        def right_height(self):
            return self._right._height if self._right != None else 0

        def set_height(self, new_height):
            self._height = new_height
        
    def __init__(self):
        """Create an initially empty binary tree."""
        self._root = None
        self._size = 0
    
    def _getHeight(self,x):
        x._height=1
        if x._left!=None:x._height=max(x._height,x._left._height+1)
        if x._right!=None:x._height=max(x._height,x._right._height+1)
        
    def _updateHeight(self,x):
        while x!=None:
            self._getHeight(x)
            x=x._parent
            
    def _drehenLeft(self,x):
        y=x._right
        z=y._left
        
        y._left=x
        x._right=z
        
        y._parent=x._parent
        x._parent=y
        if z!=None:z._parent=x
        
        if y._parent==None:self._root=y
        elif y._parent._left==x:y._parent._left=y
        else:y._parent._right=y
        
        self._getHeight(x)
        self._getHeight(y)
        self._updateHeight(x)
    
    def _drehenRight(self,x):
        y=x._left
        z=y._right
        
        y._right=x
        x._left=z
        
        y._parent=x._parent
        x._parent=y
        if z!=None:z._parent=x
        
        if y._parent==None:self._root=y
        elif y._parent._left==x:y._parent._left=y
        else:y._parent._right=y
        
        self._getHeight(x)
        self._getHeight(y)
        self._updateHeight(x)
    
    def _threesome(self,x):
        Catherine,Tim=x._left,x._right
        hCatherine=Catherine._height if Catherine!=None else 0
        hTim=Tim._height if Tim!=None else 0
        
        partnerHash=1
        
        firstPartner=x
        if hCatherine>hTim:
            partnerHash*=2
            firstPartner=Catherine
        else:
            partnerHash*=3
            firstPartner=Tim
        
        Hanabe,GuetaeHwang=firstPartner._left,firstPartner._right
        hHanabe=Hanabe._height if Hanabe!=None else 0
        hGuetaeHwang=GuetaeHwang._height if GuetaeHwang!=None else 0
        
        secondPartner=x
        if hHanabe>hGuetaeHwang:
            partnerHash*=5
            secondPartner=Hanabe
        else:
            partnerHash*=7
            secondPartner=GuetaeHwang
        
        match partnerHash:
            case 10:
                self._drehenRight(x)
            case 14:
                self._drehenLeft(firstPartner)
                self._drehenRight(x)
            case 15:
                self._drehenRight(firstPartner)
                self._drehenLeft(x)
            case 21:
                self._drehenRight(x)
        
    def _findPartners(self,x):
        if x==None:return
        while x._parent!=None:
            Albert=x._parent
            Ernst,Karl=Albert._left,Albert._right
            hErnst=Ernst._height if Ernst!=None else 0
            hKarl=Karl._height if Karl!=None else 0
            
            if abs(hErnst-hKarl)>1:
                self._threesome(Albert)
                break
            Albert._height=max(hErnst,hKarl)+1
            x=Albert
            
    def _search(self,element):
        x,y=self._root,None
        while x!=None:
            if element==x._element:return x,y
            else:
                y=x
                if element>x._element:x=x._right
                else:x=x._left
                
        return x,y
        
    def search(self,element):
        return self._search(element)[0]
        
    def insert(self, element):
        x,y=self._search(element)
        if x!=None:return
        x=self._Node(element,y)
        if y==None:self._root=x
        elif element<y._element:y._left=x
        else:y._right=x
        self._findPartners(y)
        
    def _smallest(self,x):
        assert(x!=None)
        while x!=None:
            if x._left==None:return x
            x=x._left
        assert(x!=None)
        return None
        
    def delete(self, element):
        x,y=self._search(element)
        if x==None:return
        
        n=(2 if x._left!=None else 1)*(3 if x._right!=None else 1)
        tmp,z=x,x
        
        if n==6:
            if x._right._left==None:n=3
            
        match n:
            case 2:
                z=x._left
                z._parent=y
            case 3:
                z=x._right
                z._parent=y
            case 6:
                z=self._smallest(x._right)
                
                if z._right!=None:
                    z._parent._left=z._right
                    z._right._parent=z._parent
                
                z._left=x._left
                z._right=x._right
                z._parent=y
                
                if x._left!=None:x._left._parent=z
                if x._right!=None:x._right._parent=z
            
        if y!=None:
            if y._left==x:y._left=z
            else:y._right=z
            
        x=None
        self._findPartners(z);
            
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
        print(f'{"    "*depth}* {node._element}({node._height}){label}')
        if node._left != None:
            self._display(node._left, depth+1)
