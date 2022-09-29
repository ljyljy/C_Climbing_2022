
#define DEGREE		3
typedef int KEY_VALUE;

typedef struct _btree_node {
    KEY_VALUE* keys;
    struct _btree_node** childrens;
    int num;
    int leaf;
} btree_node;

typedef struct _btree {
    btree_node* root;
    int t;
} btree;

btree_node* btree_create_node(int t, int leaf);

void btree_destroy_node(btree_node* node);

void btree_create(btree* T, int t);

void btree_split_child(btree* T, btree_node* x, int i);

void btree_insert_nonfull(btree* T, btree_node* x, KEY_VALUE k);

void btree_insert(btree* T, KEY_VALUE key);

void btree_traverse(btree_node* x);

void btree_print(btree* T, btree_node* node, int layer);

int btree_bin_search(btree_node* node, int low, int high, KEY_VALUE key);

//{child[idx], key[idx], child[idx+1]} 
void btree_merge(btree* T, btree_node* node, int idx);

void btree_delete_key(btree* T, btree_node* node, KEY_VALUE key);


int btree_delete(btree* T, KEY_VALUE key);