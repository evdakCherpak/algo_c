#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

static ComTreeNode* create_node(ComTreeNode* parent_node, unsigned int key, int value){
    ComTreeNode* new_node = (ComTreeNode*)malloc(sizeof(ComTreeNode));
    if (new_node == NULL){
        return NULL;
    }
    new_node -> key = key;
    new_node -> value = value;
    new_node -> first_child = NULL;
    new_node -> bro_on_level = NULL;
    new_node -> parent = parent_node;
    return new_node;
}



static void free_subtree(ComTreeNode* node){
    /*without node -> bro_on_level*/
    if (node == NULL){
        return;
    }
    ComTreeNode* child = node -> first_child;
    while (child != NULL){
        ComTreeNode* next = child -> bro_on_level;
        child -> bro_on_level = NULL;
        free_subtree(child);
        child = next;
    }
    free(node);
}

static int node_count(const ComTreeNode* node){
    if (node == NULL){
        return 0;
    }
    return 1 + node_count(node -> first_child) + node_count(node -> bro_on_level);
}

static int subtree_depth(const ComTreeNode* node){
    if (node == NULL){
        return 0;
    }
    int cnt = 0;
    const ComTreeNode* child = node -> first_child;
    while (child != NULL){
        int d = subtree_depth(child);
        if (d > cnt){
            cnt = d;
        }
        child = child -> bro_on_level;
    }
    return 1 + cnt;
}

static void print_subtree(const ComTreeNode* node, unsigned int level){
    if (node == NULL){
        return;
    }
    unsigned int i;
    for (i = 0; i < level; i++) printf("\t");
    printf("|-- {key=%u, val=%d}", node -> key, node -> value);
    if (node -> parent != NULL){
        printf("\t(parent: %d)\n", node -> parent -> key);
    }
    else{
        printf("\t(root)\n");
    }
    print_subtree(node -> first_child, level + 1);
    print_subtree(node -> bro_on_level, level);
}

ComTree* create_tree(void){
    ComTree* t = (ComTree*)malloc(sizeof(ComTree));
    if (t == NULL){
        return NULL;
    }
    t -> root = NULL;
    t -> size = 0;
    return t;
}



void clear_tree(ComTree* tree){
    if (tree == NULL){
        return;
    }
    free_subtree(tree -> root);
    tree -> root = NULL;
    tree -> size = 0;
}

void free_tree(ComTree* tree){
    if (tree == NULL){
        return;
    } 
    clear_tree(tree);
    free(tree);
}

int tree_insert_root(ComTree* tree, unsigned int key, int value){
    if (tree == NULL){
        return 1;
    }
    if (tree -> root != NULL){
        return 1;
    }
    if (find_by_key_tree(tree, key) != NULL){
        return 1;
    }
    tree -> root = create_node(NULL, key, value);
    tree -> size = 1;
    return 0;
}

int tree_insert(ComTree* tree, unsigned int parent_key, unsigned int key, int value){
    if ((tree == NULL) || (tree -> root == NULL)){
        return 1;
    }
    if (find_by_key_tree(tree, key) != NULL){
        return 1;
    }
    ComTreeNode* parent = find_by_key_tree(tree, parent_key);
    if (parent == NULL){
        return 1;
    }

    ComTreeNode* new_node = create_node(parent, key, value);
    if (parent -> first_child == NULL){
        parent -> first_child = new_node;
    }
    else{
        ComTreeNode* child = parent -> first_child;
        while (child -> bro_on_level != NULL){
            child = child -> bro_on_level;
        }
        child -> bro_on_level = new_node;
    }

    (tree -> size)++;
    return 0;
}

int tree_delete(ComTree* tree, unsigned int key){
    if ((tree == NULL) || (tree -> root == NULL)){
        return 1;
    }
    ComTreeNode* node_for_del = find_by_key_tree(tree, key);
    if (node_for_del == NULL){
        return 1;
    }
    int removed = node_count(node_for_del) - node_count(node_for_del -> bro_on_level);

    ComTreeNode* parent = node_for_del -> parent;
    if (parent == NULL){
        free_subtree(tree -> root);
        tree -> root = NULL;
        tree -> size = 0;
        return 0;
    }

    if (parent -> first_child == node_for_del){
        parent -> first_child = node_for_del -> bro_on_level;
    }
    else{
        ComTreeNode* prev = parent -> first_child;
        while (prev -> bro_on_level != node_for_del){
            prev = prev -> bro_on_level;
        }
        prev -> bro_on_level = node_for_del -> bro_on_level;
    }
    node_for_del -> bro_on_level = NULL;
    free_subtree(node_for_del);
    (tree -> size) -= removed;
    return 0;
}

static ComTreeNode* find_by_key_subtree(const ComTreeNode* node, unsigned int key){
    if (node == NULL){
        return NULL;
    }
    if (node -> key == key) return (ComTreeNode*)node;
    ComTreeNode* res = find_by_key_subtree(node -> first_child, key);
    if (res) return res;
    return find_by_key_subtree(node -> bro_on_level, key);
}

static ComTreeNode* find_by_value_subtree(const ComTreeNode* node, int value){
    if (node == NULL){
        return NULL;
    }
    if (node -> value == value) return (ComTreeNode*)node;
    ComTreeNode* res = find_by_value_subtree(node -> first_child, value);
    if (res) return res;
    return find_by_value_subtree(node -> bro_on_level, value);
}

ComTreeNode* find_by_key_tree(const ComTree* tree, unsigned int key){
    if (tree == NULL){
        return NULL;
    }
    return find_by_key_subtree(tree -> root, key);
}

ComTreeNode* find_by_value_tree(const ComTree* tree, int value){
    if (tree == NULL){
        return NULL;
    }
    return find_by_value_subtree(tree -> root, value);
}

int update_value(ComTree* tree, unsigned int key, int new_value){
    ComTreeNode* find_node = find_by_key_tree(tree, key);
    if (find_node == NULL){
        return 1;
    }
    find_node -> value = new_value;
    return 0;
}

int tree_depth(const ComTree* tree){
    if (tree == NULL){
        return 1;
    }
    return subtree_depth(tree -> root);
}

int tree_size(const ComTree* tree){
    return tree != NULL ? tree -> size : 0;
}

int tree_empty(const ComTree* tree){
    return (tree == NULL) || (tree -> size == 0) || (tree -> root == NULL);
}

void tree_print(const ComTree* tree){
    if (tree == NULL){
        return;
    }
    if (tree -> size == 0){
        printf("Tree is empty");
    }
    else{
        print_subtree(tree -> root, 0 );
    }
}
