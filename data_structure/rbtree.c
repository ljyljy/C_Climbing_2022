#include <stdlib.h>
#include <stdio.h>
#include "rbtree.h"


// x: old root/parent, y = x->right 
//   = > y = new root / x.parent，x = y.左孩子
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
    else if (x == x->parent->left) { // 若x是父亲.左孩子
        x->parent->left = y; // y继承x的父亲
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


void rbtree_insert_fixup(rbtree* T, rbtree_node* z);

// 添加节点
void rbtree_insert(rbtree* T, rbtree_node* z) {

    rbtree_node* y = T->nil;
    rbtree_node* x = T->root;

    // 遍历查找红黑树（根据key）
    while (x != T->nil) {
        y = x;
        if (z->key < x->key) {
            x = x->left;
        }
        else if (z->key > x->key) {
            x = x->right;
        }
        else { //Exist
            // 找到x结点，满足z->key == x->key
            // ljy：插入时遇到重复key的节点：更新 / 直接返回插入成功or失败 等。
        }
    }

    // 找到合适的插入位置x（nil）& 父亲y，x初始化为待插入结点z
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
    z->color = RED; // 新插入结点默认为红色
    z->left = T->nil;
    z->right = T->nil;

    // RBT调整
    rbtree_insert_fixup(T, z);
}



// z: 新插入的节点，默认为红，可能需要左旋/右旋/颜色反转
void rbtree_insert_fixup(rbtree* T, rbtree_node* z) {
    //
    // z->color == RED
    // z->parent->color == RED

    // z--> RED
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) { // z.父亲是属于左孩子
            rbtree_node* y = z->parent->parent->right; //

            if (y->color == RED) { // y叔为红 - 颜色反转
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                y->color = BLACK;
                // z.爷爷以下：颜色反转完毕 ↑
                z = z->parent->parent; // z上移到爷爷，继续while。
            }
            else { // y叔为黑 
                if (z = z->parent->right) {
                    z = z->parent;
                    rbtree_left_rotate(T, z);
                }
                // if：z属于右孩子且已左旋 || z属于左孩子
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rbtree_right_rotate(T, z->parent->parent);
            }
        }
    }
}

// todo：结点的删除
/**
    当前结点是父结点的左子树的情况
    1.当前结点的兄弟结点是红色的
    2.当前结点的兄弟结点是黑色的，而且兄弟结点的两个孩子结点都是黑色的
    3.当前结点的兄弟结点是黑色的，而且兄弟结点的左孩子是红色的，右孩子是黑色的
    4.当前结点的兄弟结点是黑色的，而且兄弟结点的右孩子是红色的
 */
 //  (可参考btree、LC - q450 - https://leetcode.cn/submissions/detail/253241588/)