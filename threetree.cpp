/**
 * @file            threetree.cpp
 * @author          your CWL
 * @description     Implementation of ThreeTree functions
 *
 * THIS FILE WILL BE SUBMITTED
**/

#include "threetree.h"

/**
 * ThreeTree constructor given tolerance for variance.
**/
ThreeTree::ThreeTree(PNG& imIn, double tol) {
    //call buildtree with the stats object, imIn.width(), imIn.height(), and tol
    //ul is a new pair of 0, 0
    Stats s = new Stats(imIn);
    pair<int, int> p(0, 0);
    BuildTree(s, p, imIn.width(), imIn.height(). tol);
}

/**
 * Helper for the ThreeTree constructor.
**/
Node* ThreeTree::BuildTree(Stats& s, pair<int, int> ul, int w, int h, double tol) {
    /* Replace the line below with your implementation */
    //make a new node as specified
    RGBAPixel avg = s.GetAvg(ul, w, h);
    double var = s.GetVar(ul, w, h);
    Node* curr = new Node(ul, w, h, avg, var);
    //set the new node to the root if the root hasn't already been set
    if (root == NULL) {
        root == curr;
    }
    //check that the node is legal for splitting
    //node is illegal if it's a single pixel (1 x 1) OR var is <= tol
    if (!(((w == 1) && (h == 1)) || var < tol)) {
        if (w < h) {
            //split tall
            if (h >= 3) {
                //height for a and c
                int ACVal = split(h);
                //height for b
                int BVal = (h - (2*ACVal));
                pair<int, int> ulA(ul.first, ul.second);
                pair<int, int> ulB(ul.first, (ul.second + ACVal));
                pair<int, int> ulC(ul.first, (ul.second + ACVal + BVal));
                curr->A = BuildTree(s, ulA, w, ACVal, tol);
                curr->B = BuildTree(s, ulB, w, BVal, tol);
                curr->C = BuildTree(s, ulC, w, ACVal, tol);
                //Set current node's children to a recursive 
                //call BuildTree using each child's stats
            //dimensions are 1 x 2
            } else {
                //Set current node's children to a recursive 
                //call BuildTree using each child's stats
                //with B being NULL
                pair<int, int> ulA(ul.first, ul.second);
                pair<int, int> ulC(ul.first, (ul.second + 1));
                //height will be 1 since height is 2
                curr->A = BuildTree(s, ulA, w, 1, tol);
                curr->B = NULL;
                curr->C = BuildTree(s, ulC, w, 1, tol);
            }
        //case where w >= h
        } else {
            //split wide
            if (w >= 3) {
                //width for a and c
                int ACVal = split(w);
                //width for b
                int BVal = (w - (2*ACVal));
                //Set current node's children to a recursive 
                //call BuildTree using each child's stats
                pair<int, int> ulA(ul.first, ul.second);
                pair<int, int> ulB((ul.first + ACVal), ul.second);
                pair<int, int> ulC((ul.first + ACVal + BVal), ul.second);
                curr->A = BuildTree(s, ulA, ACVal, h, tol);
                curr->B = BuildTree(s, ulB, BVal, h, tol);
                curr->C = BuildTree(s, ulC, ACVal, h, tol);
            //dimensions are 2 x 1 or 2 x 2
            } else {
                //Set current node's children to a recursive 
                //call BuildTree using each child's stats
                //with B being NULL
                pair<int, int> ulA(ul.first, ul.second);
                pair<int, int> ulC((ul.first + 1), ul.second);
                //width is 1 since width was 2
                curr->A = BuildTree(s, ulA, 1, h, tol);
                curr->B = NULL;
                curr->C = BuildTree(s, ulC, 1, h, tol);
            }
        }
    }
    return curr;
}

/**
 * Render ThreeTree and return the resulting image.
**/
PNG ThreeTree::Render() const {
    //make PNG with width and height of the root/original image
    unsigned int w = root->width;
    unsigned int h = root->height;
    PNG out(w, h);
    Render(out, root);
    return PNG();
}

/**
 * Delete allocated memory.
**/
void ThreeTree::Clear() {
    clearAll();
}

/**
 * Copy other tree into this tree object.
**/
void ThreeTree::Copy(const ThreeTree& other) {
    //clear the current tree and set the root to the other's root
    Clear();
    copyAll(root, other.root);
}

/**
 * Returns the number of nodes in the tree
**/
int ThreeTree::Size() const {
    return Size(root);
}

/**
 * Returns the number of leaf nodes in the tree
**/
int ThreeTree::NumLeaves() const {
    return NumLeaves(root);
}

/**
 * Rearranges the tree contents so that when rendered, the image appears
 * to be rotated 90 degrees clockwise.
 * See threetree.h for specification details.
 *
 * You may want a recursive helper function for this.
**/
void ThreeTree::RotateCW() {
    /* Complete your implementation below */
    //swap w and h for root
    //run recursive for children
        //turns wide to tall
        //tall to wide with swapped A and C
        //swap w and h for each node
        //change ul for all nodes
}

/*****************************************************************
* IF YOU HAVE DEFINED ANY PRIVATE FUNCTIONS IN sqtree-private.h, *
* ADD YOUR IMPLEMENTATIONS BELOW                                 *
*****************************************************************/

//helper function for splitting a node
//returns the split size for children A and C
//if i = 3p/3p+1 then it will return p
//if i = 3p + 2 then it will return p + 1
int split(int i) {
    int a = (i % 3);
    //if the remainer is 0 or 1
    if (a < 2) {
        return ((i - a)/3);
    //if the remainder is 2
    } else {
        return (((i - 2)/3) + 1);
    }
}

//recursive helper for rendering the tree
//renders each leaf node by writing their average pixel value to img
void Render(PNG& img, const Node* n) const {
    //TODO
}

//recursive helper for the clear function
//deletes nodes in post-order traversal
//through its non-null children
void clearAll(Node* victim) {
    if (victim != NULL) {
        if (victim->A) clearAll(victim->A);
        if (victim->B) clearAll(victim->B);
        if (victim->C) clearAll(victim->C);
        delete victim;
        victim = NULL;
    }
}

//recursive helper for the copy function
//curr is the current node considered
//other is its equivalent node in the other tree
//sets the root if the root is empty
//recursivly travels through the other tree
//adding it's children to the current node
void copyAll(Node* curr, Node* other) {
    //set the root if it was deleted/doesn't exist
    if (other != NULL) {
        //if the curr is NULL then the root was passed after the tree was cleared
        if (curr == NULL) {
            //set root and curr to the other node
            root = other;
            curr = other;
        //case where copyAll is not called immediately after clearing the tree
        } else {
            //check and add the children
            if (other->A != NULL) {
                curr->A = other->A;
                copyAll(curr->A, other->A);
            }
            if (other->B != NULL) {
                curr->B = other->B;
                copyAll(curr->B, other->B);
            }
            if (other->C != NULL) {
                curr->C = other->C;
                copyAll(curr->C, other->C);
            }
        }
    }
}

//a recursive helper function for Size
int Threetree::Size(const Node* n) const {
    if (n != NULL) {
        //the sizes of the node's subtrees
        int sizeA = 0;
        int sizeB = 0;
        int sizeC = 0;
        //if there are no children, return 1
        if ((n->A == NULL) && (n->B == NULL) && (n->C == NULL)) {
            return 1;
        } else {
            //for every non-null child, set their size to their recursive call
            if (n->A) sizeA = Size(n->A);
            if (n->B) sizeB = Size(n->B); 
            if (n->C) sizeC = Size(n->C); 
        }
        return (1 + sizeA + sizeB + sizeC);
    } else {
        return 0;
    }
    
}

//recursive helper function for NumLeaves
int Threetree::NumLeaves(const Node* n) const {
    if (n != NULL) {
        //the number of leaves in the node's subtrees
        int leavesA = 0;
        int leavesB = 0;
        int leavesC = 0;
        //if the node is a leaf, return 1
        if ((n->A == NULL) && (n->B == NULL) && (n->C == NULL)) {
            return 1;
        } else {
            //for every non-null child, count the leaves in their subtrees
            if (n->A) leavesA = NumLeaves(n->A);
            if (n->B) leavesB = NumLeaves(n->B); 
            if (n->C) leavesC = NumLeaves(n->C); 
        }
        return (leavesA + leavesB + leavesC);
    } else {
        return 0;
    }
}

//recursive helper for RotateCW
//ul, w, and h are the parameters of the parent node
//n is the current node in recursion
//swaps w and h for the node 
//ends here if the node is a leaf
//changes ul based on if the parent is wide or tall
//if wide, change ul to (parent's x, node's x)
//if the node is A (ul == parent's ul) then no change
//if tall, swap A and C's uls and change ul to (node's x, parent's y)
void rotateNodes(Node* n, pair<int, int> ul, int w, int h) {

}
