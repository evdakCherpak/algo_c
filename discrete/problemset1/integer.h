#ifndef INTEGER_H
#define INTEGER_H

typedef unsigned int limb_t;
typedef unsigned long long long_t;

typedef struct big_int{
    int high_limb;
    limb_t* limbs;
} Integer;

Integer* init_integer(void);

Integer* delete_integer(Integer* number);

void print_integer(Integer* number);

Integer* add_at_first(Integer** first, Integer* second);

Integer* add_new_num(Integer* first, Integer* second);

Integer* sub_at_first(Integer** first, Integer* second);

Integer* sub_new_num(Integer* first, Integer* second);

Integer* mul_at_first(Integer** first, Integer* second);

Integer* mul_new_num(Integer* first, Integer* second);

Integer* caratsuba_at_first(Integer** first, Integer* second);

Integer* caratsuba_new_num(Integer* first, Integer* second);


#endif