#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct bin_tree_node{
    int value;
    struct bin_tree_node* left;
    struct bin_tree_node* right;
} BinTreeNode;

BinTreeNode* create_node(int value){
    BinTreeNode* new_node = (BinTreeNode*)malloc(sizeof(BinTreeNode));
    if (new_node == NULL){
        return NULL;
    }
    new_node -> value = value;
    new_node -> left = NULL;
    new_node -> right = NULL;
    return new_node;
}

BinTreeNode* get_min(BinTreeNode* tree){
    if (tree == NULL){
        return NULL;
    }
    BinTreeNode* curr = tree;
    while (curr -> left != NULL){
        curr = curr -> left;
    }
    return curr;
}

void insert(BinTreeNode** tree, int value){
    if (*tree == NULL){
        *tree = create_node(value);
    }
    else if (value < (*tree) -> value){
        if ((*tree) -> left == NULL){
            (*tree) -> left = create_node(value);
        }
        else{
            insert(&((*tree) -> left), value);
        }
    }
    else if (value > (*tree) -> value){
        if ((*tree) -> right == NULL){
            (*tree) -> right = create_node(value);
        }
        else{
            insert(&((*tree) -> right), value);
        }
    }
}

BinTreeNode* get_max(BinTreeNode* tree){
    if (tree == NULL){
        return NULL;
    }
    BinTreeNode* curr = tree;
    while (curr -> right != NULL){
        curr = curr -> right;
    }
    return curr;
}

BinTreeNode* delete_node(BinTreeNode* tree, int value){
    if (tree == NULL){
        return NULL;
    }
    else if (value < tree -> value){
        tree -> left = delete_node(tree -> left, value);
    }
    else if (value > tree -> value){ 
        tree -> right =  delete_node(tree -> right, value);
    }
    else{
        if (tree -> left == NULL){
                BinTreeNode* temp = tree -> right;
                free(tree);
                return temp;
            }
        else if (tree -> right == NULL){
                BinTreeNode* temp = tree -> left;
                free(tree);
                return temp;
        }
        else{
            BinTreeNode* parent_max = tree;
            BinTreeNode* max_of_left = tree -> left;

            while (max_of_left -> right != NULL){
                parent_max = max_of_left;
                max_of_left = max_of_left -> right;
            }
            tree -> value = max_of_left -> value;
            if (parent_max == tree){
                parent_max -> left = delete_node(max_of_left, max_of_left -> value);
            }
            else{
                parent_max -> right = delete_node(max_of_left, max_of_left -> value);
            }
        }
    }
    return tree;
}

void delete_tree(BinTreeNode* tree){
    if (tree == NULL){
        return;
    }
    delete_tree(tree -> left);
    delete_tree(tree -> right);
}


int search_node(BinTreeNode* tree, int value){
    if (tree == NULL) return 0;
    if (tree -> value == value) return 1;
    else if (tree -> value < value){
        return search_node(tree -> right, value);
    }
    else{
        return search_node(tree -> left, value);
    }
}


void postorder_print(const BinTreeNode* tree){
    if(tree == NULL) return;
    postorder_print(tree -> left);
    postorder_print(tree -> right);
    printf("%d ", tree -> value);
}


void inorder_print(const BinTreeNode* tree){
    if (tree == NULL) return;
    inorder_print(tree -> left);
    printf("%d ", tree -> value);
    inorder_print(tree -> right);
}

void preorder_print_recursive(const BinTreeNode* tree){
    if (tree == NULL) return;
    printf("%d ", tree -> value);
    preorder_print_recursive(tree -> left);
    preorder_print_recursive(tree -> right);
}

void preorder_print_iterative(const BinTreeNode* tree);


int main(){
    BinTreeNode* tree = NULL;
    insert(&tree, 5);
    insert(&tree, 4);
    insert(&tree, 3);
    insert(&tree, 2);
    insert(&tree, 7);
    insert(&tree, 6);
    insert(&tree, 8);
    insert(&tree, 1);
    postorder_print(tree);
    printf("\n");
    inorder_print(tree);
    printf("\n");
    preorder_print_recursive(tree);
    BinTreeNode* i = get_max(tree);
    BinTreeNode* j = get_min(tree);
    int m = search_node(tree, 5);
    int n = search_node(tree, 140);
    printf("\n%d %d %d %d", i -> value, j -> value, m, n);
    printf("\n");
    delete_node(tree, 6);
    preorder_print_recursive(tree);

}