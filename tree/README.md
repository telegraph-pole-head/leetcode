# Tree

## Tree Fundamentals

**Node**: Basic unit of a tree containing data and references to other nodes.

- **Root**: The topmost node with no parent
- **Leaf**: Node with no children
- **Parent**: Node directly above another node
- **Child**: Node directly below another node
- **Sibling**: Nodes sharing the same parent

**Edge**: Connection between two nodes (parent-child relationship)

**Height**: Length of longest path from node to a leaf (height of tree = height of root)

**Level**: Distance from root (root is at level 0)

**Depth**: Distance from node to root

**Subtree**: A node and all its descendants

**Path**: Sequence of nodes connected by edges

**Degree**:

- Of a node: Number of children it has
- Of a tree: Maximum degree among all nodes

**Forest**: Collection of disjoint trees

## Binary Tree

### Types of Binary Trees

**Proper (Strict)**: Every node has either 0 or 2 children

**Complete**: All levels filled except possibly the last, which is filled from left to right

**Perfect**: All internal nodes have 2 children and all leaves are at the same level

**Full**: Every level is completely filled. Equivalent to a perfect binary tree.


### Numerical Properties

For a binary tree of height h:

- **Minimum nodes**: $$h + 1$$ (one node per level)
- **Maximum nodes**: $$2^{h+1} - 1$$ (perfect binary tree)
- **Maximum nodes at level i**: $$2^i$$
- **Height of tree with n nodes**:
  - Minimum: $$\lfloor \log_2(n) \rfloor$$ (perfect/complete tree)
  - Maximum: $$n - 1$$ (skewed tree)

### Binary Tree Implementation

```cpp
struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};
```

### Tree Traversals

```cpp
// Pre-order: Root -> Left -> Right
void preorder(TreeNode* root) {
    if (!root) return;
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

// In-order: Left -> Root -> Right
void inorder(TreeNode* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

// Post-order: Left -> Right -> Root
void postorder(TreeNode* root) {
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

// Level-order (BFS)
void levelorder(TreeNode* root) {
    if (!root) return;
    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        TreeNode* node = q.front();
        q.pop();
        cout << node->data << " ";

        if (node->left) q.push(node->left);
        if (node->right) q.push(node->right);
    }
}
```

### Applications

**Expression Trees**: Represent mathematical expressions where operators are internal nodes and operands are leaves.

**Reverse Polish Notation (RPN)**: Post-order traversal of expression tree gives RPN. Example: `(3 + 4) * 5` becomes `3 4 + 5 *`

## Priority Queue and Binary Heap

### Min-Heap Implementation

```cpp
class MinHeap {
private:
    vector<int> heap;

    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }

    void percolateUp(int i) {
        while (i > 0 && heap[parent(i)] > heap[i]) {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

    void percolateDown(int i) {
        int minIndex = i;
        int left = leftChild(i);
        int right = rightChild(i);

        if (left < heap.size() && heap[left] < heap[minIndex])
            minIndex = left;
        if (right < heap.size() && heap[right] < heap[minIndex])
            minIndex = right;

        if (minIndex != i) {
            swap(heap[i], heap[minIndex]);
            percolateDown(minIndex);
        }
    }

public:
    bool isEmpty() { return heap.empty(); }
    int size() { return heap.size(); }

    void enqueue(int val) {
        heap.push_back(val);
        percolateUp(heap.size() - 1);
    }

    int dequeueMin() {
        if (isEmpty()) throw runtime_error("Heap is empty");

        int minVal = heap[0];
        heap[0] = heap.back();
        heap.pop_back();

        if (!isEmpty())
            percolateDown(0);

        return minVal;
    }

    int getMin() {
        if (isEmpty()) throw runtime_error("Heap is empty");
        return heap[0];
    }

    // Build heap from array in $$O(n)$$ time
    void buildHeap(vector<int>& arr) {
        heap = arr;
        for (int i = parent(heap.size() - 1); i >= 0; i--) {
            percolateDown(i);
        }
    }
};
```

### Applications

**Heap Sort**:

```cpp
void heapSort(vector<int>& arr) {
    MinHeap heap;
    heap.buildHeap(arr);

    for (int i = 0; i < arr.size(); i++) {
        arr[i] = heap.dequeueMin();
    }
}
```
Time complexity: $$O(n \log n)$$

**Median Maintenance**:

```cpp
class MedianFinder {
private:
    priority_queue<int> maxHeap; // for smaller half
    priority_queue<int, vector<int>, greater<int>> minHeap; // for larger half

public:
    void addNum(int num) {
        if (maxHeap.empty() || num <= maxHeap.top()) {
            maxHeap.push(num);
        } else {
            minHeap.push(num);
        }

        // Balance heaps
        if (maxHeap.size() > minHeap.size() + 1) {
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        } else if (minHeap.size() > maxHeap.size()) {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
    }

    double findMedian() {
        if (maxHeap.size() > minHeap.size()) {
            return maxHeap.top();
        }
        return (maxHeap.top() + minHeap.top()) / 2.0;
    }
};
```

### Key Tips

1. **Time Complexities**:

   - Enqueue/Dequeue: $O(\log n)$
   - GetMin: $O(1)$
   - Build heap from array: $O(n)$

2. **Space Complexity**: $O(n)$ for storing n elements

3. **STL Priority Queue**:

   - `priority_queue<int>` is a max-heap by default
   - For min-heap: `priority_queue<int, vector<int>, greater<int>>`

4. **Common Pitfalls**:
   - Remember array indices start at 0
   - Check for empty heap before dequeue/getMin
   - Maintain heap property after every operation

## Binary Search Tree

A binary tree where each node has a **comparable, distinct** key following the BST property:
**Left subtree < Node < Right subtree**

### Binary Search Tree Implementation

```cpp
struct BSTNode {
    int key;
    BSTNode* left;
    BSTNode* right;
    BSTNode(int k) : key(k), left(nullptr), right(nullptr) {}
};

class BST {
private:
    BSTNode* root;

    BSTNode* search(BSTNode* node, int key) {
        if (!node || node->key == key) return node;
        if (key < node->key) return search(node->left, key);
        return search(node->right, key);
    }

    BSTNode* insert(BSTNode* node, int key) {
        if (!node) return new BSTNode(key);
        if (key < node->key) node->left = insert(node->left, key);
        else if (key > node->key) node->right = insert(node->right, key);
        return node;
    }

    BSTNode* findMin(BSTNode* node) {
        while (node->left) node = node->left;
        return node;
    }

    BSTNode* deleteNode(BSTNode* node, int key) {
        if (!node) return nullptr;
        if (key < node->key) node->left = deleteNode(node->left, key);
        else if (key > node->key) node->right = deleteNode(node->right, key);
        else {
            if (!node->left) return node->right;
            if (!node->right) return node->left;
            BSTNode* successor = findMin(node->right);
            node->key = successor->key;
            node->right = deleteNode(node->right, successor->key);
        }
        return node;
    }

public:
    BST() : root(nullptr) {}
    bool search(int key) { return search(root, key) != nullptr; }
    void insert(int key) { root = insert(root, key); }
    void remove(int key) { root = deleteNode(root, key); }
};
```

| Operation | Time Complexity (Average) | Time Complexity (Worst) |
|-----------|---------------------------|-------------------------|
| Search    | $$O(\log n)$$             | $$O(n)$$                |
| Insert    | $$O(\log n)$$             | $$O(n)$$                |
| Delete    | $$O(\log n)$$             | $$O(n)$$                |

**Depth h**: Time complexity is $O(h)$
**n nodes**: Average $O(\log n)$, Worst $O(n)$ for degenerate tree

### Additional Operations

```cpp
// Output in Sorted Order: In-order traversal - $$O(n)$$
void inorder(BSTNode* node) {
    if (!node) return;
    inorder(node->left);
    cout << node->key << " ";
    inorder(node->right);
}

// Get Min/Max - $$O(h)$$
int getMin() {
    BSTNode* node = root;
    while (node->left) node = node->left;
    return node->key;
}

int getMax() {
    BSTNode* node = root;
    while (node->right) node = node->right;
    return node->key;
}

// Get Predecessor/Successor - $$O(h)$$
BSTNode* predecessor(BSTNode* node) {
    if (node->left) return findMax(node->left);
    // Find ancestor where node is in right subtree
}

// Rank Search (k-th smallest) - $$O(h + k)$$
// Range Search [low, high] - $$O(h + \text{output size})$$
void rangeSearch(BSTNode* node, int low, int high, vector<int>& result) {
    if (!node) return;
    if (node->key > low) rangeSearch(node->left, low, high, result);
    if (node->key >= low && node->key <= high) result.push_back(node->key);
    if (node->key < high) rangeSearch(node->right, low, high, result);
}
```

## k-d Tree

A binary search tree where **each level represents a different dimension**.
For i-th level node in k-dimensional space:
- Left subtree: all points < current point in $(i \bmod k)$-th dimension
- Right subtree: all points ≥ current point in $(i \bmod k)$-th dimension

### k-d Tree Implementation

```cpp
struct Point {
    vector<int> coords;
    Point(vector<int> c) : coords(c) {}
};

struct KDNode {
    Point point;
    KDNode* left;
    KDNode* right;
    KDNode(Point p) : point(p), left(nullptr), right(nullptr) {}
};

class KDTree {
private:
    KDNode* root;
    int k; // dimensions

    KDNode* build(vector<Point>& points, int depth) {
        if (points.empty()) return nullptr;
        int axis = depth % k;

        sort(points.begin(), points.end(),
             [axis](const Point& a, const Point& b) {
                 return a.coords[axis] < b.coords[axis];
             });

        int median = points.size() / 2;
        KDNode* node = new KDNode(points[median]);

        vector<Point> left(points.begin(), points.begin() + median);
        vector<Point> right(points.begin() + median + 1, points.end());

        node->left = build(left, depth + 1);
        node->right = build(right, depth + 1);
        return node;
    }

    bool search(KDNode* node, Point target, int depth) {
        if (!node) return false;
        if (node->point.coords == target.coords) return true;

        int axis = depth % k;
        if (target.coords[axis] < node->point.coords[axis])
            return search(node->left, target, depth + 1);
        else
            return search(node->right, target, depth + 1);
    }

public:
    KDTree(int dimensions) : k(dimensions), root(nullptr) {}
    void build(vector<Point>& points) { root = build(points, 0); }
    bool search(Point target) { return search(root, target, 0); }
};
```

### Additional Operations

```cpp
// Range Search - $$O(\sqrt{n} + \text{output size})$$ average
void rangeSearch(KDNode* node, vector<int>& low, vector<int>& high,
                vector<Point>& result, int depth) {
    if (!node) return;

    bool inRange = true;
    for (int i = 0; i < k; i++) {
        if (node->point.coords[i] < low[i] || node->point.coords[i] > high[i]) {
            inRange = false;
            break;
        }
    }
    if (inRange) result.push_back(node->point);

    int axis = depth % k;
    if (low[axis] <= node->point.coords[axis])
        rangeSearch(node->left, low, high, result, depth + 1);
    if (high[axis] >= node->point.coords[axis])
        rangeSearch(node->right, low, high, result, depth + 1);
}

// Nearest Neighbor Search - $$O(\log n)$$ average, $$O(n)$$ worst
```

## AVL Tree

**Self-balancing BST** where height difference between left and right subtrees ≤ 1.

**Height bound**: $\log_2(n + 1) - 1 \leq h \leq 1.44 \log_2(n + 2)$
**Guaranteed** $O(\log n)$ **operations**

### Rotations (Rebalancing)

```cpp
struct AVLNode {
    int key, height;
    AVLNode* left;
    AVLNode* right;
    AVLNode(int k) : key(k), height(1), left(nullptr), right(nullptr) {}
};

class AVLTree {
private:
    AVLNode* root;

    int getHeight(AVLNode* node) {
        return node ? node->height : 0;
    }

    int getBalance(AVLNode* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    void updateHeight(AVLNode* node) {
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    }

    // Right rotation
    AVLNode* rotateRight(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;
        x->right = y;
        y->left = T2;
        updateHeight(y);
        updateHeight(x);
        return x;
    }

    // Left rotation
    AVLNode* rotateLeft(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;
        y->left = x;
        x->right = T2;
        updateHeight(x);
        updateHeight(y);
        return y;
    }

    AVLNode* insert(AVLNode* node, int key) {
        // Standard BST insertion
        if (!node) return new AVLNode(key);
        if (key < node->key) node->left = insert(node->left, key);
        else if (key > node->key) node->right = insert(node->right, key);
        else return node; // Duplicate keys not allowed

        // Update height
        updateHeight(node);

        // Get balance factor
        int balance = getBalance(node);

        // Left Left Case
        if (balance > 1 && key < node->left->key)
            return rotateRight(node);

        // Right Right Case
        if (balance < -1 && key > node->right->key)
            return rotateLeft(node);

        // Left Right Case
        if (balance > 1 && key > node->left->key) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // Right Left Case
        if (balance < -1 && key < node->right->key) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

public:
    void insert(int key) { root = insert(root, key); }
};
```

**Four rotation cases**:
- **Left-Left**: Right rotation
- **Right-Right**: Left rotation
- **Left-Right**: Left rotation on left child, then right rotation
- **Right-Left**: Right rotation on right child, then left rotation

## Red-Black Tree

**Self-balancing BST** with color-coded nodes following specific rules:

### Rules:
1. Every node is either **red** or **black**
2. **Root rule**: Root is black
3. **Red rule**: Red nodes have only black children
4. **Path rule**: All paths from node to NULL have same number of black nodes

### Properties:
- **Black height**: Number of black nodes on path to NULL
- **Height bound**: $h \leq 2 \log_2(n + 1)$
- Red node with children must have **two black children**
- Black node with one child has a **red leaf child**

### Operations

```cpp
enum Color { RED, BLACK };

struct RBNode {
    int key;
    Color color;
    RBNode* left;
    RBNode* right;
    RBNode* parent;
    RBNode(int k) : key(k), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree {
private:
    RBNode* root;
    RBNode* NIL; // Sentinel node

    void rotateLeft(RBNode* x) {
        RBNode* y = x->right;
        x->right = y->left;
        if (y->left != NIL) y->left->parent = x;
        y->parent = x->parent;
        if (x->parent == NIL) root = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    void rotateRight(RBNode* y) {
        RBNode* x = y->left;
        y->left = x->right;
        if (x->right != NIL) x->right->parent = y;
        x->parent = y->parent;
        if (y->parent == NIL) root = x;
        else if (y == y->parent->right) y->parent->right = x;
        else y->parent->left = x;
        x->right = y;
        y->parent = x;
    }

    void insertFixup(RBNode* z) {
        while (z->parent->color == RED) {
            if (z->parent == z->parent->parent->left) {
                RBNode* uncle = z->parent->parent->right;
                if (uncle->color == RED) {
                    // Case 1: Uncle is red - recolor
                    z->parent->color = BLACK;
                    uncle->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->right) {
                        // Case 2: Uncle is black, z is right child
                        z = z->parent;
                        rotateLeft(z);
                    }
                    // Case 3: Uncle is black, z is left child
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rotateRight(z->parent->parent);
                }
            } else {
                // Symmetric cases
                RBNode* uncle = z->parent->parent->left;
                if (uncle->color == RED) {
                    z->parent->color = BLACK;
                    uncle->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rotateRight(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rotateLeft(z->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

public:
    RedBlackTree() {
        NIL = new RBNode(0);
        NIL->color = BLACK;
        root = NIL;
    }

    void insert(int key) {
        RBNode* z = new RBNode(key);
        z->left = z->right = NIL;

        // Standard BST insertion
        RBNode* y = NIL;
        RBNode* x = root;
        while (x != NIL) {
            y = x;
            if (z->key < x->key) x = x->left;
            else x = x->right;
        }
        z->parent = y;
        if (y == NIL) root = z;
        else if (z->key < y->key) y->left = z;
        else y->right = z;

        insertFixup(z);
    }
};
```

### Insert Fixup Cases:
1. **Uncle is red**: Recolor parent, uncle to black; grandparent to red
2. **Uncle is black, z is right child**: Rotate left at parent
3. **Uncle is black, z is left child**: Recolor parent to black, grandparent to red; rotate right at grandparent

All operations (Search, Insert, Delete) are $O(\log n)$ guaranteed
