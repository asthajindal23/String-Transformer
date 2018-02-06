// C program to find move to front transform of
// a given string
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
// Returns index at which character of the input text
// exists in the list
int search(char input_char, char* list)
{
    int i;
    for (i = 0; i < strlen(list); i++) {
        if (list[i] == input_char) {
            return i;
            break;
        }
    }
}
 
// Takes curr_index of input_char as argument
// to bring that character to the front of the list
void moveToFront(int curr_index, char* list)
{
    char* record = (char*)malloc(sizeof(char) * 26);
    strcpy(record, list);
 
    // Characters pushed one position right
    // in the list up until curr_index
    strncpy(list + 1, record, curr_index);
 
    // Character at curr_index stored at 0th position
    list[0] = record[curr_index];
}
 
// Move to Front Encoding
void mtfEncode(char* input_text, int len_text, char* list)
{
    int i;
    int* output_arr = (int*)malloc(len_text * sizeof(int));
 
    for (i = 0; i < len_text; i++) {
 
        // Linear Searches the characters of input_text 
        // in list
        output_arr[i] = search(input_text[i], list);
 
        // Printing the Move to Front Transform
        printf("%d ", output_arr[i]);
 
        // Moves the searched character to the front 
        // of the list
        moveToFront(output_arr[i], list);
    }
}
 
// Driver program to test functions above
int main()
{
    char* input_text = "panama";
    int len_text = strlen(input_text);
 
    // Maintains an ordered list of legal symbols
    char* list = (char*)malloc(sizeof(char) * 26);
    strcpy(list, "abcdefghijklmnopqrstuvwxyz");
 
    printf("Input text: %s", input_text);
    printf("\nMove to Front Transform: ");
 
    // Computes Move to Front transform of given text
    mtfEncode(input_text, len_text, list);
   
    return 0;
}