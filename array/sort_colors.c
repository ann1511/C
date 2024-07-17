#include <stdint.h>
#include <stdio.h>

void print_array(int **arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d\t%p\n", *(*(arr + i)), *(arr + i));
    }
}

void swap(int **nums, int i, int j)
{
    int *tmp = nums[i];
    nums[i] = nums[j];
    nums[j] = tmp;
}

void sortColors(int **nums, int numsSize)
{
    int start = 0;
    int end = numsSize - 1;
    int i = 0;

    while (i <= end)
    {
        int item = *(*(nums + i));
        if (item < 1)
        {
            swap(nums, i, start);
            i++;
            start++;
        }
        else if (item > 1)
        {
            swap(nums, i, end);
            end--;
        }
        else
            i++;
    }
}

int main()
{
    int size = 4;
    uint32_t arr[4] = {256, 2, 3, 6};
    // printf("%d\n", arr[1]);
    // printf("%d\n", *(arr + 500));
    // printf("%lu\n", sizeof(arr[0]));

    // printf("%p\n", arr);
    // printf("%p\n", arr + 1);

    // uint8_t *arr8 = (uint8_t *)arr;
    // printf("%d\n", *(arr8));
    // print_array(arr8, 16);

    int data[] = {1, 2, 2, 1, 0, 1, 0, 2, 2, 1};
    int *colors[10];
    for (int i = 0; i < 10; ++i)
    {
        colors[i] = &data[i];
    }

    print_array(colors, 10);
    printf("eeeend\n");

    sortColors(colors, 10);

    print_array(colors, 10);

    return 0;
}