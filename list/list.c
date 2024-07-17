// int main(int argc, char const *argv[]) {
//     int a = 5;
//     int* p = &a;
//     int** pp = &p;

//     printf("%d\n", a);

//     *(*pp) = 10;

//     printf("%d\n", a);

//     return 0;
// }

#include <stdio.h>

struct Node
{
    int value;
    struct Node* next;
    struct Node *prev;
};

void print_list(struct Node* head)
{
    struct Node* current = head;
    while (current != NULL)
    {
        printf("%d\t", current->value);
        current = current->next;
    }

    printf("\n");
}

void print_prev_list(struct Node *tail)
{
    struct Node *current = tail;
    while (current != NULL)
    {
        printf("%d\t", current->value);
        current = current->prev;
    }
}

struct Node* reverse_list(struct Node *head)
{
    struct Node *current = head;
    struct Node *savedNext;
    struct Node *savedPrev = NULL;

    while (current != NULL)
    {
        savedNext = current->next;
        savedPrev = current->prev;

        current->next = savedPrev;
        current->prev = savedNext;

        savedPrev = current;
        current = savedNext;
    }

    return savedPrev;
}

void add_node(struct Node *start, struct Node *node, struct Node *end)
{
    node->next = start->next;
    node->prev = start;

    if(end != NULL) {
        end->prev = node;
    } else {
        node->next = NULL;
    }

    if(start != NULL) {
        start->next = node;
    } else {
        node->prev = NULL;
    }
}

void remove_node(struct Node *node) {

    if (node->prev != NULL && node->next != NULL) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    else if (node->prev != NULL && node->next == NULL) {
        node->prev->next = NULL;
    }
    else if (node->prev == NULL && node->next != NULL) {
        node->next->prev = NULL;
    }
}

int main()
{
    struct Node node4 = {4, NULL, NULL};
    struct Node node3 = {3, NULL, NULL};
    struct Node node2 = {2, NULL, NULL};
    struct Node node1 = {1, NULL, NULL};
    struct Node node0 = {0, NULL, NULL};

    add_node(&node0, &node1, &node2);
    add_node(&node1, &node2, &node3);
    add_node(&node2, &node3, &node4);
    add_node(&node3, &node4, NULL);

    print_list(&node0);

    remove_node(&node4);

    print_list(reverse_list(&node0));

    return 0;
}