# String-Transformer
This module consists of String Transformation algorithms to be applied in succession to rearrange data in such away the transformed message is more compressible. Please refer https://auth.geeksforgeeks.org/user/everythings13/articles for discussions on these topics.

1) Burrows – Wheeler Data Transform Algorithm

What is the Burrows – Wheeler Transform?
The BWT is a data transformation algorithm that restructures data in such a way that the transformed message is more compressible. Technically, it is a lexicographical reversible permutation of the characters of a string. It is first of the three steps to be performed in succession while implementing Burrows – Wheeler Data Compression algorithm that forms the basis of the Unix compression utility bzip2.

Why BWT? The main idea behind it.
The most important application of BWT is found in biological sciences where genomes(long strings written in A, C, T, G alphabets) don’t have many runs but they do have many repeats.
The idea of the BWT is to build an array whose rows are all cyclic shifts of the input string in dictionary order, and return the last column of the array that tends to have long runs of identical characters. The benefit of this is that once the characters have been clustered together, they effectively have an ordering, which can make our string more compressible for other algorithms like run length encoding and Huffman Coding.
The remarkable thing about BWT is that this particular transform is reversible with minimal data overhead.

Steps involved in BWT algorithm
Let’s take the word “banana$” as an example.
Step 1: Form all cyclic rotations of the given text.

                                     banana$                                                
       $    b                        $banana 
    a           a                    a$banan
   Cyclic rotations    ---------->   na$bana                                 
    n         n                      ana$ban                                         
          a                          nana$ba
                                     anana$b
Step 2: The next step is to sort the rotations lexicographically. The ‘$’ sign is viewed as first letter lexicographically, even before ‘a’.

          banana$                    $banana
          $banana                    a$banan
          a$banan       Sorting      ana$ban
          na$bana      ---------->   anana$b 
          ana$ban    alphabetically  banana$
          nana$ba                    na$bana
          anana$b                    nana$ba
Step 3: The last column is what we output as BWT.

          BWT(banana$) = annb$aa
Examples:

Input : banana$ // Input text
Output : annb$aa // Burrows - Wheeler Transform

Input : abracadabra$
Output : ard$rcaaaabb
Why last column is considered BWT?
1. The last column has better symbol clustering than any other columns.

2. If we only have BWT of our string, we can recover the rest of the cyclic rotations entirely. The rest of the columns don’t possess this characteristic which is highly important while computing inverse of BWT.

Why ‘$’ sign is embedded in the text?
We can compute BWT even if our text is not concatenated with any EOF character (‘$’ here). The implication of ‘$’ sign comes while computing the inverse of BWT.

Way of implementation
1. Let’s instantiate “banana$” as our input_text and instantiate character array bwt_arr for our output.

2. Let’s get all the suffixes of “banana$” and compute it’s suffix_arr to store index of each suffix.

          0 banana$                6 $   
          1 anana$                 5 a$
          2 nana$      Sorting     3 ana$
          3 ana$     ---------->   1 anana$
          4 na$     alphabetically 0 banana$
          5 a$                     4 na$
          6 $                      2 nana$
3. Iterating over the suffix_arr, let’s now add to our output array bwt_arr, the last character of each rotation.

4. The last character of each rotation of input_text starting at the position denoted by the current value in the suffix array can be calculated with input_text[(suffix_arr[i] – 1 + n ) % n], where n is the number of elements in the suffix_arr.

bwt_arr[0] = input_text[(suffix_arr[0] - 1 + 7) % 7] 
           = input_text[5] 
           = a
bwt_arr[1] = input_text[(suffix_arr[1] - 1 + 7) % 7] 
           = input_text[4] 
           = n
Above is the code for way of implementation explained above



2) Move To Front Data Transform Algorithm

What is the MTF transform?
The MTF (Move to Front) is a data transformation algorithm that restructures data in such a way that the transformed message is more compressible and therefore used as an extra step in compression. Technically, it is an invertible transform of a sequence of input characters to an array of output numbers.

Why MTF?
1. In many cases, the output array gives frequently repeated characters’ lower indexes which is useful in data compression algorithms.

2. It is first of the three steps to be performed in succession while implementing Burrows – Wheeler Data Compression algorithm that forms the basis of the Unix compression utility bzip2.

The main idea behind MTF:

1. The primary idea behind MTF is to maintain an ordered list of legal symbols (a to z, in our example).

2. Read one character at a time from input string .

3. Print out the position at which that character appears in the list.

4. Move that character to front of the list and repeat the process until indexes for all input characters are obtained.

Illustration for "panama".  
List initially contains English alphabets in order. 
We one by one characters of input to front.

input_str chars   output_arr       list
  p              15               abcdefghijklmnopqrstuvwxyz
  a              15 1             pabcdefghijklmnoqrstuvwxyz
  n              15 1 14          apbcdefghijklmnoqrstuvwxyz
  a              15 1 14 1        napbcdefghijklmoqrstuvwxyz
  m              15 1 14 1 14     anpbcdefghijklmoqrstuvwxyz
  a              15 1 14 1 14     manpbcdefghijkloqrstuvwxyz
Inference:
1. If the letters occur many times in the input, then many of the output values will be small integers such as 0, 1, 2 etc.

2. Thus, encoding extremely high frequency of these letters makes an ideal scenario for Huffman Coding.



3) Inverting the Burrows – Wheeler Transform

Prerequisite: Burrows – Wheeler Data Transform Algorithm

Why inverse of BWT? The main idea behind it:

1. The remarkable thing about BWT algorithm is that this particular transform is invertible with minimal data overhead.

2. To compute inverse of BWT is to undo the BWT and recover the original string. The naive method of implementing this algorithm can be studied from here. The naive approach is speed and memory intensive and requires us to store |text| cyclic rotations of the string |text|.

3. Let’s discuss a faster algorithm where we have with us only two things:
i. bwt_arr[] which is the last column of sorted rotations list given as “annb$aa”.
ii. ‘x’ which is the row index at which our original string “banana$” appears in the sorted rotations list. We can see that ‘x’ is 4 in the example below.

 Row Index    Original Rotations    Sorted Rotations
 ~~~~~~~~~    ~~~~~~~~~~~~~~~~~~    ~~~~~~~~~~~~~~~~
    0             banana$               $banana
    1             anana$b               a$banan
    2             nana$ba               ana$ban
    3             ana$ban               anana$b
   *4             na$bana               banana$
    5             a$banan               na$bana
    6             $banana               nana$ba
4. An important observation: If the jth original rotation (which is original rotation shifted j characters to the left) is the ith row in the sorted order, then l_shift[i] records in the sorted order where (j+1)st original rotation appears. For example, the 0th original rotation “banana$” is row 4 of sorted order, and since l_shift[4] is 3, the next original rotation “anana$b” is row 3 of the sorted order.

Row Index  Original Rotations  Sorted Rotations l_shift 
~~~~~~~~~ ~~~~~~~~~~~~~~~~~~  ~~~~~~~~~~~~~~~~  ~~~~~~~
   0           banana$         $banana           4
   1           anana$b         a$banan           0
   2           nana$ba         ana$ban           5
   3           ana$ban         anana$b           6
  *4           na$bana         banana$           3
   5           a$banan         na$bana           1
   6           $banana         nana$ba           2
5. Our job is to deduce l_shift[] from the information available to us which is bwt_arr[] and ‘x’ and with its help compute the inverse of BWT.

How to compute l_shift[] ?
1. We know BWT which is “annb$aa”. This implies that we know all the characters of our original string, even though they’re permuted in wrong order.

2. By sorting bwt_arr[], we can reconstruct first column of sorted rotations list and we call it sorted_bwt[].

 Row Index    Sorted Rotations   bwt_arr    l_shift  
 ~~~~~~~~~    ~~~~~~~~~~~~~~~~~~~~~~~~~~    ~~~~~~~   
     0         $  ?  ?  ?  ?  ?  a             4
     1         a  ?  ?  ?  ?  ?  n
     2         a  ?  ?  ?  ?  ?  n
     3         a  ?  ?  ?  ?  ?  b
    *4         b  ?  ?  ?  ?  ?  $             3
     5         n  ?  ?  ?  ?  ?  a
     6         n  ?  ?  ?  ?  ?  a
3. Since ‘$’ occurs only once in the string ‘sorted_bwt[]’ and rotations are formed using cyclic wrap around, we can deduce that l_shift[0] = 4. Similarly, ‘b’ occurs once, so we can deduce that l_shift[4] = 3.

4. But, because ‘n’ appears twice, it seems ambiguous whether l_shift[5] = 1 and l_shift[6] = 2 or whether l_shift[5] = 2 and l_shift[6] = 1.

5. Rule to solve this ambiguity is that if rows i and j both start with the same letter and i<j, then l_shift[i] < l_shift[j]. This implies l_shift[5] = 1 and l_shift[6] =2. Continuing in a similar fashion, l_shift[] gets computed to the following.

 Row Index    Sorted Rotations   bwt_arr    l_shift  
 ~~~~~~~~~    ~~~~~~~~~~~~~~~~~~~~~~~~~~    ~~~~~~~   
     0         $  ?  ?  ?  ?  ?  a             4
     1         a  ?  ?  ?  ?  ?  n             0
     2         a  ?  ?  ?  ?  ?  n             5
     3         a  ?  ?  ?  ?  ?  b             6
    *4         b  ?  ?  ?  ?  ?  $             3
     5         n  ?  ?  ?  ?  ?  a             1
     6         n  ?  ?  ?  ?  ?  a             2
Why is the ambiguity resolving rule valid?

1. The rotations are sorted in such a way that row 5 is lexicographically less than row 6.

2. Thus, the five unknown characters in row 5 must be less than the five unknown characters in row 6 (as both start with ‘n’).

3. We also know that between the two rows than end with ‘n’, row 1 is lower than row 2.

4. But, the five unknown characters in rows 5 and 6 are precisely the first five characters in rows 1 and 2 or this would contradict the fact that rotations were sorted.

5. Thus, l_shift[5] = 1 and l_shift[6] = 2.

Way of implementation:

1. Sort BWT: Using qsort(), we arrange characters of bwt_arr[] in sorted order and store it in sorted_arr[].

2. Compute l_shift[]: 
i. We take an array of pointers struct node *arr[], each of which points to a linked list.

ii. Making each distinct character of bwt_arr[] a head node of a linked list, we append nodes to the linked list whose data part contains index at which that character occurs in bwt_arr[].

   i        *arr[128]           Linked Lists
~~~~~~~~~    ~~~~~~~~~      ~~~~~~~~~~~~~~~~~~~~~~  
   37          $     ----->    4 ->  NULL
   97          a     ----->    0 -> 5 -> 6 -> NULL
   110         n     ----->    1 -> 2 -> NULL
   98          b     ----->    3 -> NULL
iii. Making distinct characters of sorted_bwt[] heads of linked lists, we traverse linked lists and get corresponding l_shift[] values.

     int[] l_shift = { 4, 0, 5, 6, 3, 1, 2 };
3. Iterating string length times, we decode BWT with x = l_shift[x] and output bwt_arr[x].

     x = l_shift[4] 
     x = 3
     bwt_arr[3] = 'b'

     x = l_shift[3] 
     x = 6
     bwt_arr[6] = 'a'
Examples:

Input : annb$aa // Burrows - Wheeler Transform
        4 // Row index at which original message 
          // appears in sorted rotations list 
Output : banana$

Input : ard$rcaaaabb
        3
Output : abracadabra$



4) Inverting the Move to Front Transform

Prerequisite:Move To Front Data Transform Algorithm

The main idea behind inverse of MTF Transform:

1. To compute inverse of MTF Transform is to undo the MTF Transform and recover the original string. We have with us “input_arr” which is the MTF transform and “n” which is the number of elements in “input_arr”.

2. Our task is to maintain an ordered list of characters (a to z, in our example) and read in “ith”element from “input_arr” one at a time.

3.Then, taking that element as index j, print “jth” character in the list.

Illustration for "[15 1 14 1 14 1]"
List initially contains English alphabets in order.
We move characters at indexes depicted by input 
to front of the list one by one.

input arr chars   output str  list
15                p           abcdefghijklmnopqrstuvwxyz
1                 pa          pabcdefghijklmnoqrstuvwxyz
14                pan         apbcdefghijklmnoqrstuvwxyz
1                 pana        napbcdefghijklmoqrstuvwxyz
14                panam       anpbcdefghijklmoqrstuvwxyz
1                 panama      manpbcdefghijkloqrstuvwxyz
Examples:

Input : arr[] = {15, 1, 14, 1, 14, 1}
Output : panama

Input : arr[] = {6, 5, 0, 10, 18, 8, 15, 18, 
                6, 6, 0, 6, 6};
Output : geeksforgeeks
