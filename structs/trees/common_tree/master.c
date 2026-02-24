#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tree.h"

static int read_int(const char *prompt, int *out) {
    char buf[64];
    printf("%s", prompt);
    fflush(stdout);
    if (!fgets(buf, sizeof(buf), stdin)) {
        return 0;
    }
    char *endptr = NULL;
    long val = strtol(buf, &endptr, 10);
    if (endptr == buf) {
        printf("Ошибка: ожидается целое число.\n");
        return 0;
    }
    *out = (int)val;
    return 1;
}

static void menu_print(ComTree *t) {
    printf("\n");
    tree_print(t);
    printf("Узлов: %d  |  Глубина: %d\n", tree_size(t), tree_depth(t));
}

static void menu_insert_root(ComTree *t) {
    int key, val;
    if (!read_int("Ключ корня : ", &key)) return;
    if (!read_int("Значение   : ", &val)) return;
    if (tree_insert_root(t, (unsigned int)key, val) == 0)
        printf("Корень {%d, %d} создан.\n", key, val);
    else
        printf("Не удалось создать корень (возможно, он уже есть или ключ занят).\n");
}

static void menu_insert(ComTree *t) {
    int pkey, key, val;
    if (!read_int("Ключ родителя : ", &pkey)) return;
    if (!read_int("Новый ключ    : ", &key))  return;
    if (!read_int("Значение      : ", &val))  return;
    if (tree_insert(t, (unsigned int)pkey, (unsigned int)key, val) == 0)
        printf("Узел {%d, %d} добавлен к родителю %d.\n", key, val, pkey);
    else
        printf("Не удалось добавить узел (нет родителя или ключ занят).\n");
}

static void menu_delete(ComTree *t) {
    int key;
    if (!read_int("  Ключ для удаления : ", &key)) return;
    if (tree_delete(t, (unsigned int)key) == 0)
        printf("Узел %d и его поддерево удалены.\n", key);
    else
        printf("Узел с ключом %d не найден.\n", key);
}

static void menu_find_key(ComTree *t) {
    int key;
    if (!read_int("Искать по ключу : ", &key)) return;
    ComTreeNode *n = find_by_key_tree(t, (unsigned int)key);
    if (n)
        printf("Найден: {key=%u, val=%d}  родитель: %s%u\n",
               n->key, n->value,
               n->parent ? "" : "(корень)",
               n->parent ? n->parent->key : 0u);
    else
        printf("Узел с ключом %d не найден.\n", key);
}

static void menu_find_value(ComTree *t) {
    int val;
    if (!read_int("  Искать по значению : ", &val)) return;
    ComTreeNode *n = find_by_value_tree(t, val);
    if (n)
        printf("Найден: {key=%u, val=%d}\n", n->key, n->value);
    else
        printf("Узел со значением %d не найден.\n", val);
}

static void menu_update(ComTree *t) {
    int key, val;
    if (!read_int("Ключ узла      : ", &key)) return;
    if (!read_int("Новое значение : ", &val)) return;
    if (update_value(t, (unsigned int)key, val) == 0)
        printf("Узел %d: значение обновлено на %d.\n", key, val);
    else
        printf("Узел с ключом %d не найден.\n", key);
}

static void menu_depth(ComTree *t) {
    printf("Глубина дерева: %d\n", tree_depth(t));
}

static void menu_size(ComTree *t) {
    printf("Число узлов: %d\n", tree_size(t));
}

static void menu_clear(ComTree *t) {
    printf("Вы уверены? Все узлы будут удалены. [y/N] ");
    fflush(stdout);
    char buf[20];
    if (fgets(buf, sizeof(buf), stdin) && (buf[0] == 'y' || buf[0] == 'Y')) {
        clear_tree(t);
        printf("Дерево очищено.\n");
    } else {
        printf("Отменено.\n");
    }
}

static void print_menu(void) {
    printf("дерево  (key → int value)\n");
    printf("1 │ показать дерево            \n");
    printf("2 │ создать корень             \n");
    printf("3 │ добавить узел              \n");
    printf("4 │ удалить узел (с поддеревом)\n");
    printf("5 │ найти по ключу             \n");
    printf("6 │ найти по значению          \n");
    printf("7 │ обновить значение          \n");
    printf("8 │ глубина дерева             \n");
    printf("9 │ число узлов                \n");
    printf("0 │ очистить дерево            \n");
    printf("q │ выход                      \n");
    printf("Выбор: ");
    fflush(stdout);
}

int main(void) {
    ComTree *test_tree = create_tree();
    if (test_tree == NULL) {
        printf("Не удалось создать дерево.\n");
        return 1;
    }

    char buf[32];
    print_menu();
    while(1) {
        if (!fgets(buf, sizeof(buf), stdin)) {
            break;
        }
        char choice = buf[0];

        switch (choice) {
            case '1': menu_print(test_tree);      break;
            case '2': menu_insert_root(test_tree);break;
            case '3': menu_insert(test_tree);     break;
            case '4': menu_delete(test_tree);     break;
            case '5': menu_find_key(test_tree);   break;
            case '6': menu_find_value(test_tree); break;
            case '7': menu_update(test_tree);     break;
            case '8': menu_depth(test_tree);      break;
            case '9': menu_size(test_tree);       break;
            case '0': menu_clear(test_tree);      break;

            case 'q':
            case 'Q':
                printf("Выход.\n");
                free_tree(test_tree);
                return 0;

            case '\n':
            case '\r':
                break;

            default:
                printf("Неизвестная команда.\n");
                break;
        }
    }

    free_tree(test_tree);
    return 0;
}


