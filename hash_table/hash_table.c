#include <stdlib.h>
#include <stdio.h>

struct HashTableEntry
{
    int key;
    void* value;
    struct HashTableEntry* next;
};

struct HashTable
{
    struct HashTableEntry** entries;
    int empty;
    int size;
    int capacity;
};

int _hash(int key, int capacity) {
    return key % capacity;
}

int hash_table_init(struct HashTable* t, int capacity) {
    t->capacity = capacity == -1 ? 16 : capacity;
    t->empty = t->capacity;
    t->size = 0;

    t->entries = (struct HashTableEntry**)malloc(sizeof(struct HashTableEntry*) * t->capacity);
    if (t->entries == NULL) {
        return 1;
    }

    for (int i = 0; i < t->capacity; i++) {
        t->entries[i] = NULL;
    }

    return 0;
};

void* hash_table_get(struct HashTable* t, int key) {
    int hash = _hash(key, t->capacity);
    if (t->entries[hash] != NULL) {
        struct HashTableEntry* current = t->entries[hash];
        while (current != NULL && current->key != key) {
            current = current->next;
        }
        if (current != NULL && current->key == key) {
            return current->value;
        }
    }

    return NULL;
};

int hash_table_set(struct HashTable* t, int key, void* value) {
    int hash = _hash(key, t->capacity);
    if (t->entries[hash] != NULL) {
        struct HashTableEntry* current = t->entries[hash];

        while (current->next != NULL && current->key != key) {
            current = current->next;
        }

        if (current->next == NULL) {
            current->next = (struct HashTableEntry*)malloc(sizeof(struct HashTableEntry));

            struct HashTableEntry* new = current->next;
            new->key = key;
            new->next = NULL;
            new->value = value;
        }
        else {
            current->value = value;
        }
    }
    else {
        t->size++;
        t->entries[hash] = (struct HashTableEntry*)malloc(sizeof(struct HashTableEntry));

        struct HashTableEntry* new = t->entries[hash];
        new->key = key;
        new->next = NULL;
        new->value = value;
    }

    return 0;
};

int hash_table_delete(struct HashTable* t, int key) {
    int hash = _hash(key, t->capacity);
    if (t->entries[hash] != NULL) {
        struct HashTableEntry* current = t->entries[hash];
        // если нет коллизий;
        if(current->next == NULL) {
            if (current->key == key) {
                free(t->entries[hash]);
                t->entries[hash] = NULL;
            }

            return 0;
        }

        struct HashTableEntry* prev;
        while (current != NULL && current->key != key) {
            current = current->next;
            prev = current;
        }
        if (current != NULL && current->key == key) {
            prev->next = current->next;
            free(current);
        }
    }

    return 0;
};

int main(int argc, char const* argv[]) {
    struct HashTable hash_table;
    int value17 = 17;
    int value1 = 1;

    hash_table_init(&hash_table, -1);
    hash_table_set(&hash_table, 17, &value17);
    hash_table_set(&hash_table, 1, &value1);

    printf("%d", *((int*)hash_table_get(&hash_table, 17)));
    printf("\n");
    printf("%d", *((int*)hash_table_get(&hash_table, 1)));
    printf("\n");

    hash_table_delete(&hash_table, 1);
    printf("%d", *((int*)hash_table_get(&hash_table, 17)));
    printf("\n");


    return 0;
}
