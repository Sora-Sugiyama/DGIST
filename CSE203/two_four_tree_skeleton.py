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
    
    # begin _split
    def _split(self,x):
    
        if len(x._keys) < 4:return True
        
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

        return False
        
    # end _split
        
    
    # begin search
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
            
    # end search
    

    # begin _findInsertPosition
    def _findInsertPosition(self, element):
    
        x = self._root
        
        if x == None    :   return  True, None
        
        while x._children[0] != None :
            
            match len(x._keys):
            
                case 1:
                
                    a   =   x._keys[0]
                    
                    if      element < a :   x = x._children[0]
                    elif    element > a :   x = x._children[1]
                    else                :   return  False, x
                    
                    
                case 2:
                
                    a, b    =   x._keys
                    
                    if      element == a:   return  False, x
                    elif    element == b:   return  False, x
                    
                    
                    if      element < a :   x = x._children[0]
                    elif    element < b :   x = x._children[1]
                    else                :   x = x._children[2]
                    
                    
                case 3:
                
                    a, b, c =   x._keys
                    
                    if      element == a:   return  False, x
                    elif    element == b:   return  False, x
                    elif    element == c:   return  False, x
                        
                    if      element < a :   x = x._children[0]
                    elif    element < b :   x = x._children[1]
                    elif    element < c :   x = x._children[2]
                    else                :   x = x._children[3]
        
        
        
        return True, x
    # end _findInsertPosition

    
    # begin insert
    def insert(self, element):

        needInsert, x = self._findInsertPosition(element)

        if not needInsert: return

        if x == None:
            x = self._Node(None, [element], [None, None])
            self._size += 1
            
            return


        insertPosition = 0

        # begin match
        match len(x._keys):
        
            case 1:
                
                a   =   x._keys[0]
                
                if      element < a :   insertPosition = 0
                elif    element > a :   insertPosition = 1
                else                :   return
                    
                    
            case 2:
                
                a, b    =   x._keys
                
                if      element == a:   return
                elif    element == b:   return
                
                
                if      element < a :   insertPosition = 0
                elif    element < b :   insertPosition = 1
                else                :   insertPosition = 2
                    
                    
            case 3:
            
                a, b, c =   x._keys
                
                if      element == a:   return  False, x
                elif    element == b:   return  False, x
                elif    element == c:   return  False, x
                    
                if      element < a :   insertPosition = 0
                elif    element < b :   insertPosition = 1
                elif    element < c :   insertPosition = 2
                else                :   insertPosition = 3
        
        # end match

        self._size += 1
        x._keys     = (
                            x._keys[:insertPosition] +
                            [element] +
                            x._keys[insertPosition:]
                        )
                                    
        x._children = (
                            x._children[:insertPosition] +
                            [None, None] +
                            x._children[insertPosition+1:]
                        )

        while x != None:
            if self._split(x): break
            x = x._parent
            
    # end insert
        
    def delete(self, element):

        x, index = self.search(element)

        if node == None:return

        

    def display(self):
        self._display(self._root, 0)

    def _display(self, node, depth):
        if node == None:
            return
        # try to impelement a recursive traversal that is displaying the tree content
