#ifndef FILE_OPTIMIZE_H
#define FILE_OPTIMIZE_H

typedef struct LinkedListNode {
    int value;
    struct LinkedListNode* next;
} LinkedListNode;

typedef struct {
    LinkedListNode* begin;
    LinkedListNode* end;
} LinkedList;

#define MAX_REGISTER (10000)

void update_pos();
void optimize_1();
void optimize_2();
void optimize_3();

LinkedListNode* new_linked_list_node();
LinkedList* new_linked_list();
LinkedList** new_linked_list_n(int);
void linked_list_insert(LinkedList*, int);
int linked_list_find(LinkedList*, int);
int optimize_merge_set(LinkedList*, LinkedList*);
int optimize_merge_set_1(LinkedList*, LinkedList*, LinkedList*);
int optimize_calc_in_out(int, int);

int cmp(const void*, const void*);
void optimize_register_allocate(int, int);
void optimize_4();

void optimize();

extern int *next_pos, *prev_pos;
extern int real_register_begin, real_register_end;

#endif
