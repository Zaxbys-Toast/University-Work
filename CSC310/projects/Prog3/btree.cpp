#include "btree.h"
#include "album.h"
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;
/* ======== Constructor ======== */
BTree::BTree() {
    rootAddr = -1;
    height = 0;
    read = 0;
    write = 0;
    memset(treeFileName, 0, sizeof(treeFileName));
}

/* ======== Main Methods ======== */
void BTree::writeHeader(char* fileName) {
    strncpy(treeFileName, fileName, sizeof(treeFileName)-1);
    treeFile.open(treeFileName, ios::binary | ios::in | ios::out);

    if (!treeFile) {
        // File doesn't exist → create it
        treeFile.open(treeFileName, ios::binary | ios::out);
        treeFile.close();
        treeFile.open(treeFileName, ios::binary | ios::in | ios::out);

        // Initialize header node
        BTNode header;
        header.currSize = 0;
        header.child[0] = -1;
        treeFile.seekp(0);
        treeFile.write(reinterpret_cast<char*>(&header), sizeof(BTNode));
        write++;
    }

    // Read header to get rootAddr
    treeFile.seekg(0);
    treeFile.read(reinterpret_cast<char*>(&root), sizeof(BTNode));
    read++;
    rootAddr = root.child[0];
}

// Public method to print entire tree
void BTree::printTree() {
    if (rootAddr == -1) {
        cout << "Tree is empty" << endl;
        return;
    }
    cout << "B-Tree Structure:" << endl;
    printTree(rootAddr, 0);  // Start with root at level 0
}

// Private recursive method to print subtree
void BTree::printTree(int recAddr, int level) {
    if (recAddr == -1) {
        return;  // Base case: empty subtree
    }

    BTNode node = getNode(recAddr);
    
    // Print indentation based on level
    for (int i = 0; i < level; i++) {
        cout << "  ";
    }
    
    // Print current node contents
    cout << "Level: " << level << " ";
    cout << "Node " << recAddr << " [";
    for (int i = 0; i < node.currSize; i++) {
        cout << node.contents[i].getUPC();
        if (i < node.currSize - 1) cout << "|";
    }
    cout << "]";
    
    // Print child pointers if not leaf
    if (!isLeaf(node)) {
        cout << " -> (";
        for (int i = 0; i <= node.currSize; i++) {
            cout << node.child[i];
            if (i < node.currSize) cout << " ";
        }
        cout << ")";
    }
    cout << endl;
    
    // Recursively print children
    if (!isLeaf(node)) {
        for (int i = 0; i <= node.currSize; i++) {
            printTree(node.child[i], level + 1);
        }
    }
}

void BTree::insert(keyType key, int recAddr, int oneAddr, int twoAddr) {
    if (recAddr == -1) {
        adjRoot(key, oneAddr, twoAddr);
        return;
    }

    BTNode node = getNode(recAddr);

    if (isLeaf(node)) {
        if (node.currSize < ORDER-1) {
            placeNode(key, recAddr, oneAddr, twoAddr);
        } else {
            // Leaf is full - need to split
            keyType promoteKey = key;
            int leftAddr = recAddr;
            int rightAddr = -1;

            splitNode(promoteKey, leftAddr, rightAddr, oneAddr, twoAddr);

            // Propagate the split upward
            int parentAddr = findpAddr(promoteKey, getNode(rootAddr), rootAddr);
            insert(promoteKey, parentAddr, leftAddr, rightAddr);
        }
    } else {
        // Internal node case
        int i = 0;
        while (i < node.currSize && key > node.contents[i]) {
            i++;
        }

        int childAddr = node.child[i];
        BTNode child = getNode(childAddr);

        if (child.currSize < ORDER-1) {
            insert(key, childAddr, oneAddr, twoAddr);
        } else {
            // Child is full - split it first
            keyType childKey = key;
            int childLeft = childAddr;
            int childRight = -1;

            splitNode(childKey, childLeft, childRight, oneAddr, twoAddr);

            // Now insert the promoted key into this node
            if (node.currSize < ORDER-1) {
                placeNode(childKey, recAddr, childLeft, childRight);
            } else {
                // Current node is also full - need to split
                keyType promoteKey = childKey;
                int leftAddr = recAddr;
                int rightAddr = -1;

                splitNode(promoteKey, leftAddr, rightAddr, childLeft, childRight);

                // Propagate upward
                int parentAddr = findpAddr(promoteKey, getNode(rootAddr), rootAddr);
                insert(promoteKey, parentAddr, leftAddr, rightAddr);
            }
        }
    }
}


void BTree::insert(keyType key) {
    if (rootAddr == -1) {
        // Create new root
        BTNode newRoot;
        newRoot.contents[0] = key;
        newRoot.currSize = 1;
        newRoot.child[0] = -1;
        newRoot.child[1] = -1;

        // Write to file
        treeFile.seekp(0, ios::end);
        rootAddr = treeFile.tellp() / sizeof(BTNode);
        treeFile.write((char*)&newRoot, sizeof(BTNode));
        write++;

        // Update header
        root.child[0] = rootAddr;
        treeFile.seekp(0);
        treeFile.write((char*)&root, sizeof(BTNode));
        write++;

        height = 1;
        return;
    }

    // Start recursive insertion
    insert(key, rootAddr, -1, -1);
}

void BTree::splitNode(keyType& key, int& originalAddr, int& newAddr, int oneAddr, int twoAddr) {
    BTNode original = getNode(originalAddr);
    set<Pair> s;

    // Insert existing pairs
    for (int i = 0; i < original.currSize; i++) {
        Pair p = {original.contents[i], original.child[i], original.child[i+1]};
        s.insert(p);
    }

    // Insert the new key and its children
    Pair newP = {key, oneAddr, twoAddr};
    s.insert(newP);

    // Create new nodes
    BTNode leftNode, rightNode;
    int medianPos = ORDER/2;
    auto it = s.begin();

    // Fill left node (original node)
    int i;
    for (i = 0; i < medianPos; i++, it++) {
        leftNode.contents[i] = it->element;
        leftNode.child[i] = it->loffset;
    }
    leftNode.child[i] = it->loffset;  // Last child pointer
    leftNode.currSize = medianPos;

    // Get median key to promote
    key = it->element;
    it++;

    // Fill right node (new node)
    for (i = 0; it != s.end(); i++, it++) {
        rightNode.contents[i] = it->element;
        rightNode.child[i] = it->loffset;
    }
    rightNode.child[i] = it->loffset;  // Last child pointer
    rightNode.currSize = (ORDER-1) - medianPos - 1;

    // Write the left node back to its original position
    treeFile.seekp(originalAddr * sizeof(BTNode));
    treeFile.write((char*)&leftNode, sizeof(BTNode));

    // Write the right node to a new position
    treeFile.seekp(0, ios::end);
    newAddr = treeFile.tellp() / sizeof(BTNode);
    treeFile.write((char*)&rightNode, sizeof(BTNode));
    write += 2;
}

/* ========= Basic Node Operations ======== */
BTNode BTree::getNode(int recAddr) {
    BTNode node;
    treeFile.seekg(recAddr * sizeof(BTNode), ios::beg);
    treeFile.read((char*) &node, sizeof(BTNode));
    read++;
    return node;
}

bool BTree::isLeaf(int recAddr) {
    BTNode node = getNode(recAddr);
    return isLeaf(node);
}

bool BTree::isLeaf(BTNode t) {
     return t.child[0] == -1;
}

/* ======== Helper Methods ======= */

// Prints node and what it's children
void BTree::printNode(int recAddr) {

    BTNode node = getNode(recAddr);
    cout << "Node " << recAddr << " [";
    for (int i = 0; i < node.currSize; i++) {
        cout << node.contents[i].getUPC();
        if (i < node.currSize - 1) cout << "|";
    }
    cout << "]" << endl;
    if(!isLeaf(node)) {
        cout << " -> (";
        for (int i = 0; i <= node.currSize; i++) {
            cout << node.child[i];
            if (i < node.currSize) cout << " ";
        }
        cout << ")";
    }

    cout << endl;
}

// Should be used on the root
int BTree::countLeaves(int recAddr) {
    BTNode node = getNode(recAddr);

    if (isLeaf(node)) {
        return 1;
    }

    int count = 0;

    for (int i = 0; i <= node.currSize; i++) {
        if (node.child[i] != -1) {
            count += countLeaves(node.child[i]);
        }
    }

    return count;
}

int BTree::countLeaves() {
    if (rootAddr == -1) return 0;  // Add this check
    return countLeaves(rootAddr);
}
// Find the address of a UPC
int BTree::findAddr(keyType key, BTNode t, int tAddr) {
    int i = 0;
    while (i < t.currSize && key > t.contents[i]) {
        i++;
    }

    // Current
    if (i < t.currSize && key == t.contents[i]) {
        return tAddr;
    }

    // Not found
    if (isLeaf(t)) {
        return -1;
    }

    return findAddr(key, getNode(t.child[i]), t.child[i]);
}

int BTree::findpAddr(keyType key, BTNode t, int tAddr) {
    // root doesn't have a parent
    if (tAddr == rootAddr) {
        return -1;
    }

    // If current node is a leaf we went too far
    if (isLeaf(t)) {
        return -1;
    }

    // Search appropriate child
    int i = 0;
    while (i < t.currSize && key > t.contents[i]) {
        i++;
    }

    int childAddr = t.child[i];
    BTNode child = getNode(childAddr);

    // If next node has the keys position its the parent
    if (childAddr == tAddr) {
        return tAddr;
    }

    // Keep going
    return findpAddr(key, child, childAddr);
}
// Places a key into a node that isn't full and updates it's children
void BTree::placeNode (keyType k,int recAddr,int oneAddr,int twoAddr) {
    BTNode node = getNode(recAddr);

    int i = node.currSize - 1;
    while (i >= 0 && k < node.contents[i]) {
        node.contents[i+1] = node.contents[i];
        node.child[i+2] = node.child[i+1];
        i--;
    }

    node.contents[i+1] = k;

    if (!isLeaf(node)) {
        node.child[i+1] = oneAddr;
        node.child[i+2] = twoAddr;
    }

    node.currSize++;

    // Write back to disk
    treeFile.seekp(recAddr * sizeof(BTNode));
    treeFile.write(reinterpret_cast<char*>(&node), sizeof(BTNode));
    write++;
}

void BTree:: totalio() const{
        cout << "Total read/write: " << read + write << endl;
}

void BTree::adjRoot(keyType rootElem, int oneAddr, int twoAddr) {
    BTNode newRoot;
    newRoot.contents[0] = rootElem;
    newRoot.child[0] = oneAddr;
    newRoot.child[1] = twoAddr;
    newRoot.currSize = 1;

    treeFile.seekp(0, ios::end);
    rootAddr = treeFile.tellp() / sizeof(BTNode);
    treeFile.write((char*)&newRoot, sizeof(BTNode));
    write++;

    // Update header
    root.child[0] = rootAddr;
    treeFile.seekp(0);
    treeFile.write((char*)&root, sizeof(BTNode));
    write++;
    height++;
}
