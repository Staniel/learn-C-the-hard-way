/*************************************************************************
	> File Name: ex18.c
	> Author: Lixin Yao
    */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void die(const char* message)
{
    if (errno){
        perror(message);
    }
    else{
        printf("ERROR:%s\n", message);
    }
    exit(1);
}
void print_array(int* array, int count)
{
    int i;
    for (i=0;i<count;i++)
    printf("%d\t", array[i]);
    printf("\n");
}
// remember how to define the function pointer
typedef int (*compare_cb)(int a, int b);

int divide(int* array, int low, int high, compare_cb cmp)
{
    int temp=array[low];
    while(low< high)
    {
        while(low<high && cmp( array[high], temp) > 0 ) high--;
        if (low < high ) array[low++]=array[high];
        while(low<high && cmp( array[low], temp) < 0 ) low++;
        if (low < high ) array[high--]=array[low];
    }
    array[low]=temp;
    return low;
}
void q_sort(int* array,int low, int high, compare_cb cmp )
{
    if (low>=high) return;
    int middle=divide(array, low, high, cmp);
    q_sort(array, low, middle-1, cmp);
    q_sort(array, middle+1, high, cmp);
}
// wrap quick sort in same api
int* quick_sort(int* array,int  count, compare_cb cmp)
{
    int* target=malloc(count * sizeof(int));
    if (!target) die("fail4");
    memcpy(target, array, count * sizeof(int));
    q_sort(target,0, count-1, cmp);
    return target;
}
int* bubble_sort(int* array, int count, compare_cb cmp)
{
    int* target=malloc(sizeof(int) * count);
    memcpy(target, array, count * sizeof(int) );
    int i,j, temp;
    for (i=0;i<count;i++)
    {
        for (j=0;j<count-1;j++)
        {
            if (cmp(target[j], target[j+1])>0)
            {
                temp=target[j];
                target[j]=target[j+1];
                target[j+1]=temp;
            }
        }
    }
    return target;
}
int sorted_order(int a, int b)
{
    return a-b;
}
int reverse_order(int a, int b)
{
    return b-a;
}
int ramdom_order(int a, int b)
{
    if (a==0 || b==0)
    {
        return 0;
    }
    else{
        return a%b;
    }
}
unsigned char test(int j)
{
    return 0;
}
void test_sorting(int* numbers, int count, compare_cb cmp)
{
    int i;
    int* array=quick_sort(numbers, count, cmp);
    if (!array)
    die("fail");
    print_array(array, count);
    free(array);
   /*
    unsigned char* data=(unsigned char* )cmp;
    for (i=0;i<50;i++)
    printf("%02x:", data[i]);
    printf("\n");
    */
}
int main(int argc, char* argv[])
{
    if (argc<2)
    die(" not enough argument");
    int count=argc-1;
    int i;
    int* numbers=malloc(count * sizeof(int));
    for (i=1;i<count+1;i++)
    numbers[i-1]=atoi(argv[i]);
    test_sorting(numbers, count, sorted_order);
    test_sorting(numbers, count, reverse_order);
    free(numbers);
    return 0;

}
