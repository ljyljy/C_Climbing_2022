#define RED     0
#define BLACK   1

typedef int KEY_TYPE;

typedef struct _rbtree_node {
    //rbtree
    unsigned char color;
    struct _rbtree_node* parent;
    struct _rbtree_node* left;
    struct _rbtree_node* right;
    // end


    KEY_TYPE key;

    // value
    //
} rbtree_node;


typedef struct rbtree {
    rbtree_node* root;
    rbtree_node* nil; // NULL
}rbtree;

// rotate 
void rbtree_left_rotate(rbtree* T, rbtree_node* x);
void rbtree_right_rotate(rbtree* T, rbtree_node* y);
void rbtree_insert_fixup(rbtree* T, rbtree_node* z);
void rbtree_insert(rbtree* T, rbtree_node* z);

