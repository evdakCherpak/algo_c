#ifndef TREE_H
#define TREE_H


/*Структура узла и дерева*/
typedef struct com_tree_node{
    int value;
    unsigned int key;
    struct com_tree_node* first_child;
    struct com_tree_node* bro_on_level;
    struct com_tree_node* parent;
} ComTreeNode;

typedef struct{
    ComTreeNode* root;
    int size;
} ComTree;

/*Создание-удаление дерева*/
ComTree* create_tree(void);

void free_tree(ComTree* tree);

void clear_tree(ComTree* tree);

/*Вставка корня и узла*/
int tree_insert_root(ComTree* tree, unsigned int key, int value);

int tree_insert(ComTree* tree, unsigned int parent_key, unsigned int key, int value);

/*Удаление узла с поддеревом*/
int tree_delete(ComTree* tree, unsigned int key);

/*Поиск по ключу и значению*/
ComTreeNode* find_by_key_tree(const ComTree* tree, unsigned int key);

ComTreeNode* find_by_value_tree(const ComTree* tree, int value);

/*Обновить значение по ключу*/
int update_value(ComTree* tree, unsigned int key, int new_value);

/*Информациия и вывод*/
int tree_depth(const ComTree* tree);

int tree_size(const ComTree* tree);

int tree_empty(const ComTree* tree);

void tree_print(const ComTree* tree);

#endif
