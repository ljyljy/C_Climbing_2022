
#define DEGREE		3
typedef int KEY_VALUE;

// B树：自上而下的实现，无需旋转，故无需parent（但B+树需要）
typedef struct _btree_node {
    KEY_VALUE* keys; // 关键字值，个数∈[0, DEGREE-1]
    // b-树：M叉搜索树，M建议为偶数，便于分裂
    struct _btree_node** childrens; // 最多M叉 = DEGREE = 2*t
    // struct _btree_node* childrens[DEGREE]; // 或定义为指针数组
    int num; // key的个数，∈[0, DEGREE-1] = [0, 2*t-1]
    int leaf; // 是否是叶子
} btree_node;

typedef struct _btree {
    btree_node* root;
    int t; // 分叉相关，M叉 = DEGREE = 2*t，便于分裂&合并
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