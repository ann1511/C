#include <stdlib.h>
#include <stdio.h>

struct Array
{
    int* pointer;
    int size;
    int capacity;
};

void array_free(int* pointer) {
    free(pointer);
}

int array_init(struct Array* arr, int capacity) {
    (*arr).capacity = capacity;
    (*arr).size = 0;
    (*arr).pointer = (int*)malloc(sizeof(int) * capacity);
    if ((*arr).pointer == NULL) {
        return 1;
    }

    return 0;
}

int array_expand_capacity(struct Array* arr) {
    arr->capacity *= 2;
    int* prev = arr->pointer;
    arr->pointer = (int*)realloc(arr->pointer, arr->capacity);
    if (arr->pointer == NULL) {
        free(prev);
        return 1;
    }

    return 0;
}

int array_push(struct Array* arr, int element) {
    if (arr->size == arr->capacity) {
        if (array_expand_capacity(arr) == 1) {
            return 1;
        }
    }

    arr->pointer[arr->size] = element;
    arr->size++;

    return 0;
}

int array_delete(struct Array* arr, int index) {
    for (int i = index; i < arr->size - 1; i++) {
        arr->pointer[i] = arr->pointer[i + 1];
    }
    arr->size--;

    return 0;
}

int array_insert(struct Array* arr, int index, int value) {
    arr->size++;
    int current = value;
    int next;
    for (int i = index; i < arr->size + 1; i++) {
        next = arr->pointer[i];
        arr->pointer[i] = current;
        current = next;
    }

    return 0;
}

int array_set(struct Array* arr, int index, int value) {
    if (index > arr->size) {
        return 1;
    }
    if (arr->size == arr->capacity) {
        int err = array_expand_capacity(arr);
        if (err > 0) {
            return err;
        }
    }

    array_insert(arr, index, value);

    return 0;
}

void array_print(struct Array* arr) {
    for (int i = 0; i < (*arr).size; i++) {
        printf("%d\n", *((*arr).pointer + i));
    }
}

int main() {
    struct Array arr;

    array_init(&arr, 3);
    array_push(&arr, 1);
    array_push(&arr, 2);
    array_push(&arr, 3);
    // добавить обработку ошибок - ?
    int err = array_set(&arr, 3, 4);
    if (err) return err;

    array_set(&arr, 0, 0);
    array_set(&arr, 0, -1);
    array_set(&arr, 0, -2);
    array_set(&arr, 0, -3);
    array_delete(&arr, 4);
    array_delete(&arr, 0);

    array_delete(&arr, arr.size - 1);

    array_print(&arr);
    printf("%d", arr.capacity);

    return 0;
}
