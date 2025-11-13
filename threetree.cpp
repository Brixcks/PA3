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
    //make the root a new node with all the given parameters

    //pass root node to a recursive helper that does the following
        //split based on above rules to create children
        //if w and h are not both 1 or the variability of current node isn't <= tol
            //if height > width then split tall
            //if width <= height then split wide
            //if the larger side is > 2 then split accordingly
                //for splitting, take the taller side and use mod 3
                //if mod 3 = 0 then uls for each child is (0/1/2) * (side - 1)/3 with w and h being the same
                //if mod 3 = 1 then ul for b is (side - 1)/3 and for c is 2((side - 1)/3) + 1 with b being 1 larger than a and c
                //if mode3 = 2 then ul for b is (side - 1)/3 + 1 and c is 2(side - 1)/3 + 1 with a and c being 1 larger than b
            //otherwise, the area is 2 x 2 or 2 x 1 then split down the middle and assign areas to A and C
        //create new nodes at each point and assign children accordingly
        //at some point convert nodes with stats into nodes with average and variability
        //recursivly call the function on each child
    return nullptr;
}

/**
 * Render ThreeTree and return the resulting image.
**/
PNG ThreeTree::Render() const {
    /* Replace the line below with your implementation */
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
    copyAll(other.root);
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

    
}

/*****************************************************************
* IF YOU HAVE DEFINED ANY PRIVATE FUNCTIONS IN sqtree-private.h, *
* ADD YOUR IMPLEMENTATIONS BELOW                                 *
*****************************************************************/

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
int Threetree::Size(Node* n) {
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
}

//recursive helper function for NumLeaves
int Threetree::NumLeaves(Node* n) {
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
}
