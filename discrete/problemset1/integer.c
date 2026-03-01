#include <stdio.h>
#include <stdlib.h>
#include "integer.h"


#define BASE (sizeof(limb_t) << 3)
#define GET_LIMB_SIGN ()
#define 
#define SMASK ((limb_t))
#define AMASK ((limb_t)(SMASK - 1))

int get_integer_sign(Integer* num){
    if (num == NULL){ return 52; }
    if (num -> high_limb < 0){
        return 1;
    }
    return 0;
}

void set_integer_sign(Integer* num, int sign){
    limb_t azaza = (limb_t)num -> high_limb & AMASK;
    num -> high_limb = sign ? (int)(azaza | SMASK) : (int)azaza; 
}

Integer* from_limbs(limb_t* limb_array, limb_t len){
    if (limb_array == NULL){ return NULL; }
    while (len > 0 && limb_array[len - 1] == 0){ len--; }

    Integer* res = (Integer*)malloc(sizeof(Integer));
    if (res == NULL){ return NULL; }

    if (len == 0){
        res -> high_limb = 0;
        res -> limbs = NULL;
        return res;
    }

    if (limb_array[len - 1] & SMASK){
        res -> high_limb = 0;
        res -> limbs = (limb_t*)calloc(len + 1, sizeof(limb_t));
        if (res -> limbs == NULL){ return NULL; }
        res -> limbs[0] = 0;
        limb_t i;
        for (i = 0; i < len; i++){
            res -> limbs[i + 1] = limb_array[i];
        }
        return res;
    }

    res -> high_limb = (int)(limb_array[len - 1] & AMASK);
    if (len == 1){
        res -> limbs = NULL;
        return res;
    }

    limb_t cnt = len - 1;
    r -> limbs = (limb_t*)calloc(cnt + 1, sizeof(limb_t));
    if (r -> limbs == NULL){ return NULL; }
    r -> limbs[0] = cnt;
    int i;
    for (i = 0; i < cnt; i++){
        res -> limbs[i + 1] = limb_array[i];
    }
    return res;
}

limb_t get_size(Integer* num){
    if (num == NULL){ return 52; }
    if (num -> limbs == NULL && num -> high_limb == 0){
        return 0;
    }
    else if (num -> limbs == NULL && num -> high_limb != 0){
        return 1;
    }
    return num -> limbs[0];
}

limb_t get_limb(Integer* num, limb_t index){
    if (num == NULL){ return 52; }
    if (num -> limbs == NULL){
        if (i == 0){ return (limb_t)num -> high_limb & AMASK;}
        return 0;  
    }
    if (i < num -> limbs[0]){ return num -> limbs[i + 1];}
    else if (i == num -> limbs[0]) { return num -> high_limb & AMASK;}
    return 0;
}

Integer* copy_integer(Integer* num){
    if (num == NULL){ return NULL;}
    Integer* buffer = (Integer*)malloc(sizeof(Integer));
    if (buffer == NULL){ return NULL; }
    buffer -> high_limb = num -> high_limb;
    if (num -> limbs == NULL){
        buffer -> limbs = NULL;
        return buffer;
    }
    int size = num -> limbs[0];
    buffer -> limbs = (limb_t*)calloc(n + 1, sizeof(limb_t));
    if (buffer -> limbs == NULL){ return NULL; }
    buffer -> limbs[0] = size;
    if (n > 0){
        memcpy(buffer -> limbs + 1, num -> limbs + 1, size * sizeof(limb_t));
    }
    return buffer;
}

int cmp_integer_abs(Integer* first, Integer* second){
    if (first == NULL || second == NULL){ return 52; }
    limb_t size_first = get_size(first);
    limb_t size_second = get_size(second);

    while (size_first > 0 && get_limb(first, size_first - 1) == 0){
        size_first--;
    }
    while (size_second > 0 && get_limb(second, size_second - 1) == 0){
        size_second--;
    }

    if (size_first != size_second){
        if (size_first > size_second){
            return 1;
        }
        return -1;
    }

    int i;
    for (i = size_first - 1; i >= 0; i--){
        limb_t limb_first = get_limb(first, i);
        limb_t limb_second = get_limb(second, i);
        if (limb_first != limb_second){
            if (limb_first > limb_second){
                return 1
            }
            return -1;
        }
    }
    return 0;
}

Integer* init_integer(void){
    Integer* num = (Integer*)malloc(sizeof(Integer));
    if (num == NULL) { return NULL; } 
    num -> high_limb = 0;
    num -> limbs = NULL;
    return num;
}

void delete_integer(Integer* num){
    if (num == NULL){
        return;
    }
    if (num -> limbs != NULL){
        free(num -> limbs);
        num -> limbs = NULL;
    }
    free(num);
}

void print_integer(Integer* num){
    if (num == NULL){ return; }
    if ((limb_t)num -> high_limb & AMASK == 0 && (num -> limbs == NULL)){
        printf("0");
        return;
    }
    if (get_integer_sign(num)){
        printf("-");
    }

}

Integer* add_integer_abs(Integer* first, Integer* second){
    if (first == NULL || second == NULL){ return NULL; }
    limb_t size_first = get_size(first);
    limb_t size_second = get_size(second);
    limb_t max_size;
    if (size_first > size_second){
        max_size = size_first;
    }
    else{
        max_size = size_second;
    }

    limb_t* buffer = (limb_t*)calloc(max_size + 1, sizeof(limb_t));
    if (buffer == NULL){ return NULL; }
    long_t carry_flag = 0;
    int i;
    for (i = 0; i < max_size; i++){
        long_t s = (long_t)get_limb(first, i) + (long_t)get_limb(second, i) + carry_flag;
        buffer[i] = (limb_t)(s & DMASK);
        carry_flag = s >> BITS:
    }
    
    Integer* result = from_limbs(buffer, max_size + 1);
    if (result == NULL){ return NULL; }
    free(buffer);
    return result;
}

Integer* sub_integer_abs(Integer* first, Integer* second){
    if (first == NULL || second == NULL){ return NULL; }
    limb_t size_first = get_size(first);
    limb_t* buffer = (limb_t*)calloc(size_first, sizeof(limb_t));
    if (buffer == NULL){ return NULL; }

}


Integer* add_at_new_integer(Integer* first, Integer* second){
    char first_sign = get_integer_sign(first);
    char second_sign = get_integer_sign(second);
    Integer* res;
}

Integer* add_at_first_integer(Integer** fisrt, Integer* second){
    Integer* res = add_at_new_integer(*first, second);
    delete_integer(*first);
    *first = res;
    return *first;
}

Integer* sub_at_new_integer(Integer* first, Integer* second){

}

Integer* sub_at_first_integer(Integer** first, Integer* second){
    Integer* res = sub_at_new_integer(*first, second);
    delete_integer(*first);
    *first = res;
    return *first;
}

Integer* mul_at_new_integer(Integer* first, Integer* second){

}

Integer* mul_at_first_integer(Integer** first, Integer* second){

}

Integer* shift_limbs(Integer* num, limb_t shift){
    if (num == NULL){ return NULL; }
    if (((limb_t)num -> high_limb & AMASK) == 0 && (num -> limbs == NULL)){
        return init_integer();
    }

    limb_t size_num = get_size(num);
    limb_t size_with_shift = size_num + shift;
    limb_t* buffer = (limb_t*)calloc(size_with_shift, sizeof(limb_t));
    if (buffer == NULL){ return NULL; }

    int i;
    for (i = 0; i < size_num; i++){
        buffer[i + shift] = get_word(num, i);
    }
    Integer* res = from_limbs(buffer, size_with_shift);
    free(buffer);
    return res;
}

Integer* get_low_half(Integer* num, limb_t half){
    if (num == NULL){ return NULL; }

    limb_t size_num = get_size(num);
    limb_t take_size = size_num < half ? size_num : half;
    
    if (take_size == 0){ return init_integer; }

    limb_t* buffer = (limb_t*)calloc(take_size, sizeof(limb_t));
    if (buffer == NULL){ return NULL; }
    
    int i;
    for (i = 0; i < take_size; i++){
        buffer[i] = get_limb(num, take_size);
    }
    Integer* res = from_limbs(buffer, take_size);
    free(buffer);
    return res;
}

Integer* get_high_half(Integer* num, limb_t half){
    if (num == NULL){ return NULL; }
    limb_t size_num = get_size(num);
    if (size_num <= half){ return init_integer(); }

    limb_t take_size = size_num - half;
    limb_t* buffer = (limb_t*)calloc(take_size, sizeof(limb_t));
    if (buffer == NULL){ return NULL; }

    int i;
    for (i = 0; i < take_size; i++){
        buffer[i] = get_limb(num, take_size);
    }
    Integer* res = from_limbs(buffer, take_size);
    free(buffer);
    return res;
}

Integer* rec_algo_karatsuba(Integer* first, Integer* second){
    if (first == NULL || second == NULL){ return NULL; }
    limb_t size_first = get_size(first);
    limb_t size_second = get_size(second);
    if (size_first <= 2 || size_second <= 2){
        return mul_at_new_integer(first, second);
    }
    limb_t half = (size_first > size_second ? size_first : size_second) / 2;

    Integer* first_low = get_low(first, half);
    Integer* first_high = get_high(first, half);
    Integer* second_low = get_low(second, half);
    Integer* second_high = get_high(second, half);

    Integer* low_mul = rec_algo_karatsuba(first_low, second_low);
    Integer* high_mul = rec_algo_karatsuba(first_high, second_high);

    Integer* sum_first_parts = add_at_new_integer();
    Integer* sum_second_parts = add_at_new_integer();
    Integer* middle_mul = rec_algo_karatsuba(sum_first_parts, sum_second_parts);
    sub_at_first_integer();
    sub_at_first_integer();

    Integer* high_part = shift_limbs(high_mul, 2 * half);
    Integer* middle_part = shift_limbs(middle_mul, half);
    Integer* res = add_at_new_integer(high_part, middle_part);
    add_at_first_integer(&res, low_mul);

    delete_integer(first_low); delete_integer(first_high);
    delete_integer(second_low); delete_integer(second_high);
    delete_integer(sum_first_parts); delete_integer(sum_second_parts);
    delete_integer(high_mul); delete_integer(middle_mul); delete_integer(low_mul);
    delete_integer(high_part); delete_integer(middle_part);
    
    return res;
}

Integer* karatsuba_at_new_integer(Integer* fisrt, Integer* second){
    if (first == NULL || second == NULL){ return NULL; }
    Integer* first_copy = copy_integer(first);
    Integer* second_copy = copy_integer(second);
    set_integer_sign(first_copy, 0);
    set_integer_sign(second_copy, 0)

    Integer* res = rec_algo_karatsuba(first_copy, second_copy);
    set_sign(res, get_integer_sign(first) ^ get_integer_sign(second));

    if (((limb_t)res -> high_limb & AMASK) == 0 && (res -> limbs == NULL)){
        res -> high_limb = 0;
    }

    delete_integer(first_copy); delete_integer(second_copy);
    return res;

}

Integer* karatsuba_at_first_integer(Integer** first, Integer* second){
    if (first == NULL || second == NULL){ return NULL; }
    Integer* res = karatsuba_at_new_integer(*first, second)
    delete_integer(*first);
    *first = res;
    return * first;
}

Integer* integer_from_str(char* num_string){

}