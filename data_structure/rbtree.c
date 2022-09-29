#include <stdlib.h>
#include <stdio.h>
#include "rbtree.h"



void rbtree_left_rotate(rbtree* T, rbtree_node* x) {
    // NULL --> T->nil
    if (x == T->nil) return;
    // 1
    rbtree_node* y = x->right;

    x->right = y->left;
    if (y->left != T->nil) {
        y->left->parent = x;
    }

    // 2
    y->parent = x->parent;
    if (x->parent == T->nil) {
        T->root = y;
    }
    else if (x == x->parent->left) {
        x->parent->left = y;
    }
    else {
        x->parent->right = y;
    }

    // 3
    y->left = x;
    x->parent = y;

}

// x --> y, y -->x 
// left --> right, right --> left

void rbtree_right_rotate(rbtree* T, rbtree_node* y) {
    // NULL --> T->nil
    if (y == T->nil) return;
    // 1
    rbtree_node* x = y->left;

    y->left = x->right;
    if (y->left != T->nil) {
        y->left->parent = x;
    }

    // 2
    y->parent = x->parent;
    if (x->parent == T->nil) {
        T->root = y;
    }
    else if (x == x->parent->left) {
        x->parent->left = y;
    }
    else {
        x->parent->right = y;
    }

    // 3
    y->left = x;
    x->parent = y;

}


void rbtree_insert_fixup(rbtree* T, rbtree_node* z) {
    //
    // z->color == RED
    // z->parent->color == RED

    // z--> RED
    while (z->parent->color == RED) { // 

        if (z->parent == z->parent->parent->left) {

            rbtree_node* y = z->parent->parent->right; //

            if (y->color == RED) {

                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                y->color = BLACK;

                z = z->parent->parent; //
            }
            else { // 

                if (z = z->parent->right) {
                    z = z->parent;
                    rbtree_left_rotate(T, z);
                }

                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rbtree_right_rotate(T, z->parent->parent);

            }


        }

    }


}

void rbtree_insert(rbtree* T, rbtree_node* z) {

    rbtree_node* y = T->nil;
    rbtree_node* x = T->root;

    while (x != T->nil) {

        y = x;

        if (z->key < x->key) {
            x = x->left;
        }
        else if (z->key > x->key) {
            x = x->right;
        }
        else { //Exist

        }

    }

    z->parent = y;
    if (y == T->nil) {
        T->root = z;
    }
    else if (z->key < y->key) {
        y->left = z;
    }
    else {
        y->right = z;
    }

    // z --> 
    z->color = RED;
    z->left = T->nil;
    z->right = T->nil;

    // 

}



