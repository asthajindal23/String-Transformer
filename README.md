# String-Transformer
This module consists of String Transformation algorithms to be applied in succession to rearrange data in such away the transformed message is more compressible. Please refer https://auth.geeksforgeeks.org/user/everythings13/articles for discussions on these topics.

Burrows – Wheeler Data Transform Algorithm
What is the Burrows – Wheeler Transform?
The BWT is a data transformation algorithm that restructures data in such a way that the transformed message is more compressible. Technically, it is a lexicographical reversible permutation of the characters of a string. It is first of the three steps to be performed in succession while implementing Burrows – Wheeler Data Compression algorithm that forms the basis of the Unix compression utility bzip2.

Why BWT? The main idea behind it.
The most important application of BWT is found in biological sciences where genomes(long strings written in A, C, T, G alphabets) don’t have many runs but they do have many repeats.
The idea of the BWT is to build an array whose rows are all cyclic shifts of the input string in dictionary order, and return the last column of the array that tends to have long runs of identical characters. The benefit of this is that once the characters have been clustered together, they effectively have an ordering, which can make our string more compressible for other algorithms like run length encoding and Huffman Coding.
The remarkable thing about BWT is that this particular transform is reversible with minimal data overhead.

Steps involved in BWT algorithm
Let’s take the word “banana$” as an example.
Step 1: Form all cyclic rotations of the given text.

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
Following is the code for way of implementation explained above
