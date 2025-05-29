#ifndef TWO_FOUR_TREE_SKELETON_py
#define TWO_FOUR_TREE_SKELETON_py

class TwoFourTree():
    
    nullptr = None
    
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
            self._root = x
            
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
    
    
    #begin _deleteSubroutine
    
    def _deleteSubroutine(self, x):
        
        if x == self._root:
            self._root = nullptr
            
            return False
            
            
        xPosition = x._parent._children.index(x)
        x._parent._children.pop(xPosition)
        
        if xPosition:
        
            y = x._parent._children[xPosition - 1]
            z = x._parent._keys[xPosition - 1]
            
            
            if len(y._keys) < 3:
                x._parent._keys.pop(xPosition - 1)
                
                y._keys.append(z)
                y._children.append(nullptr)
                
            else:
                x._parent._keys[xPosition - 1] = y._keys[-1]
                
                y._keys.pop()
                y._children.pop()
                
                x._keys[0] = z
                
            
        else:
            y = x._parent._children[xPosition + 1]
            z = x._parent._keys[xPosition]
            
            if len(y._keys) < 3:
                x._parent._keys.pop(xPosition)
                
                y._keys.insert(0, z)
                y._children.append(nullptr)
                
            else:
                x._parent._keys[xPosition] = y._keys[0]
                
                y._keys.pop(0)
                y._children.pop()
                
                x._keys[0] = z
        
        
        return True
        
    #end _deleteSubroutine
    
    
    # begin delete
    def delete(self, element):

        x, eindex = self.search(element)

        if x == None:return
        
        
        while x._children[0] != nullptr:
            
            x._keys[eindex] = x._children[eindex]._keys[-1]
            x               = x._children[eindex]
            eindex          = len(x._keys) - 1
        
        
        xKeysSize = len(x._keys)
            
        if  xKeysSize > 1:
            x._keys.pop(eindex)
            x._children = [nullptr] * (xKeysSize - 1)
            
            self._size -= 1
            
            return
        
        
        
        if x == self._root:
            self._root = nullptr
            x = None
            
            self._size -= 1
            
            
            return
        
        
        
        while self._deleteSubroutine(x):pass
        
        
        x = None
        self._size -= 1
        
    # end delete
    
    
    
    ''' In python, recursions are harmful '''
    
    # begin iterationDispaly
    def lightweightDisplay(self):
    
        queue           = [None] * (self._size + 5)
        begin, end      = 0, 0
        maxDepth        = 0
        tmp             = "            " * (self._size << 3)
        queue[begin]    = (self._root, 0, self._size)
        
        while begin <= end:
        
            currentVertex, depth, position = queue[begin]
            begin += 1
            
            
            strVertex           = str(currentVertex._keys)
            
            count = 0
            for _ in strVertex:
                tmp[position + count] = _
            
            
            if depth > maxDepth:
                print(tmp)
                maxDepth    = depth
                tmp         = "            " * (self._size << 3)
                
                
            if currentVertex._children[0] == nullptr:continue
            
            
            count = -2
            for nextVertex in currentVertex._children:
                queue[end] = (nextVertex, depth + 1, position + count * 12)
                end += 1
                count += 1
        
        print(tmp)
        
    # end iterationDisplay
    
    
    def display(self):
        self._display(self._root, 0)

    def _display(self, node, depth):
        if node == None:
            return
        # try to impelement a recursive traversal that is displaying the tree content
        
        for i in range(len(node._children)-1,-1,-1):
            if node._children[i] != nullptr:
                self._display(node._children[i], depth + 1)
                
            if i>0 and i-1<len(node._keys):
                print("    "*depth+f"[{node._keys[i-1]}]")


#endif /* TWO_FOUR_TREE_SKELETON_py */
