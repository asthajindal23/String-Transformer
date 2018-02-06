// C program to find Inverse of Move to Front
// Transform of a given string
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
 
// Takes index of printed character as argument
// to bring that character to the front of the list
void moveToFront(int index, char *list)
{
    char record[27];
    strcpy(record, list);
 
    // Characters pushed one position right
    // in the list up until index
    strncpy(list+1, record, index);
 
    // Character at index stored at 0th position
    list[0] = record[index];
}
 
// Move to Front Decoding
void mtfDecode(int arr[], int n)
{
    // Maintains an ordered list of legal symbols
    char list[] = "abcdefghijklmnopqrstuvwxyz";
 
    int i;
    printf("\nInverse of Move to Front Transform: ");
    for (i = 0; i < n; i++)
    {
        // Printing characters of Inverse MTF as output
        printf("%c", list[arr[i]]);
 
        // Moves the printed character to the front 
        // of the list
        moveToFront(arr[i], list);
    }
}
 
// Driver program to test functions above
int main()
{
    // MTF transform and number of elements in it.
    int arr[] = {15, 1, 14, 1, 14, 1};
    int n = sizeof(arr)/sizeof(arr[0]);
 
    // Computes Inverse of Move to Front transform
    // of given text
    mtfDecode(arr, n);
 
    return 0;
}