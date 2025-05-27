class TwoFourTree():
    class _Node:
        """Lightweight, nonpublic class for storing a node."""
        __slots__ = '_parent', '_keys', '_children' # streamline memory usage

        def __init__(self, parent=None, keys=[], children=[]):
            self._parent = parent
            self._keys = keys
            self._children = children

    def __init__(self):
        """Create an initially empty binary tree."""
        self._root = None
        self._size = 0
    
    # _split begin
    def _split(self,x):
    
        assert  len(x._keys) == 4,"Wrong call - Overflow did not occurred.\n"
        
        a, b, c, d          =   x._keys
        aa, bb, cc, dd, ee  =   x._children
        myNewNodeLeft       =   self._Node(x,   [a, b], [aa, bb, cc])
        myNewNodeRight      =   self._Node(x,   [d],    [dd, ee])
        
        x._keys             =   [c]
        x._children         =   [myNewNodeLeft, myNewNodeRight]
        
        if x != self._root:
            
            xParent         =   x._parent
            insertPosition  =   xParent._children.index(x)
                
            xParent._keys       =   (
                                        xParent._keys[:insertPosition]  +
                                        x._keys                         +
                                        xParent._keys[insertPosition:]
                                    )
                                    
            xParent._children   =   (
                                        xParent._children[:insertPosition]  +
                                        x._children                         +
                                        xParent._children[insertPosition+1:]
                                    )
            x = None
            
    # _split end
        
    
    # search begin
    def search(self, element):
    
        x = self._root
        
        while x != None:
        
            match len(x._keys):
            
                case 1:
                
                    a   =   x._keys[0]
                    
                    if      element < a :   x = x._children[0]
                    elif    element > a :   x = x._children[1]
                    else                :   return  x, 0
                    
                    
                case 2:
                
                    a, b    =   x._keys
                    
                    if      element == a:   return  x,0
                    elif    element == b:   return  x,1
                    
                    
                    if      element < a :   x = x._children[0]
                    elif    element < b :   x = x._children[1]
                    else                :   x = x._children[2]
                    
                    
                case 3:
                
                    a, b, c =   x._keys
                    
                    if      element == a:   return  x,0
                    elif    element == b:   return  x,1
                    elif    element == c:   return  x,2
                        
                    if      element < a :   x = x._children[0]
                    elif    element < b :   x = x._children[1]
                    elif    element < c :   x = x._children[2]
                    else                :   x = x._children[3]
        
        
        
        return None,None
            
    # search end
    
    
    def _findInsertPosition(self, element):
    
        x       =   self._root
        prev    =   None
        
        if x == None    :   return  True, None, None
        prev = None
        while x != None and x:
            
            match len(x._keys):
            
                case 1:
                
                    a   =   x._keys[0]
                    
                    if      element < a :   x = x._children[0]
                    elif    element > a :   x = x._children[1]
                    else                :   return  False, x, 0
                    
                    
                case 2:
                
                    a, b    =   x._keys
                    
                    if      element == a:   return  False, x,0
                    elif    element == b:   return  False, x,1
                    
                    
                    if      element < a :   x = x._children[0]
                    elif    element < b :   x = x._children[1]
                    else                :   x = x._children[2]
                    
                    
                case 3:
                
                    a, b, c =   x._keys
                    
                    if      element == a:   return  False, x,0
                    elif    element == b:   return  False, x,1
                    elif    element == c:   return  False, x,2
                        
                    if      element < a :   x = x._children[0]
                    elif    element < b :   x = x._children[1]
                    elif    element < c :   x = x._children[2]
                    else                :   x = x._children[3]
        
        
        
        return True,None,prev
    
    def insert(self, element):
        ## IMPLEMENT HERE

    def delete(self, element):
        ## IMPLEMENT HERE

    def display(self):
        self._display(self._root, 0)

    def _display(self, node, depth):
        if node == None:
            return
        # try to impelement a recursive traversal that is displaying the tree content
