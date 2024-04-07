# Polish Calc

Simple calculator using polish notation and data structures (stack and queue) with support for user-defined variables as the univercuty lab

The program was written on clearly C. Math functions realized by adding math.h libruary. 

![ui.png](imgs/ui.png)
### Explaination

#### Main idea

Expression counting takes place in 4 steps
1) Tokenizing an expression for further processing 
2) Checking the entered expression for correctness, absence of errors
3) Converting an expression to Polish notation 
4) Calculating


#### First step - Tokenization

In order to immediately recognize what we are working with, we decided to tokenize the whole mathematical expression including brackets

All further interactions will be performed with special objects - tokens, which store type of token, math function (if type is function), value (double) and character which stores operator or variable letter
I know I could have used the union to save memory, but i doesnt do that XD

Full structure of token store in file structures.h  

//write more bout this


	
#### Second step - checking correctness

I write three funcrions that checks does input is correct
1) CheckBrackets()
	This functions checking brackets positions, it works with stack. 
1) CheckInput()
   This function is pretty simple function that checks does every character in the Whitelist
    char WhitelistChar[] = " 1234567890+-^*!/()abcdefghijklmnopqrstuvwxyz.,";
   WhiteList contains all summands that can be used in a mathematical expression
3) CheckTokenPosutions()
   The function checks pairwise tokens, whether there are possible cases of their combination in a mathematical expression
   It checks if there is a parenthesis after the function, the existence of repeated consecutive operators (excluding brackets) and containing of token with error value
   
   
   
#### Stack and Queue

Expression counting is optimized through the use of data structures (queue and stack)
Queue and stack are the linear list data structures.
All these data structures in file structures.c

##### How does queue and stack works? 

1) Stack
   The stack data structure is **a linear data structure
   Simply put, a stack is like a plate of pancakes. Only the last pancake cooked can be eaten, we can't take a pancake from the bottom or from the middle
   ![1.png](imgs/1.png)
2) Queue
   A queue is **a linear data structure that stores the elements sequentially in the queue**
   For example, imagine a queue in the supermarket. Angry grannies won't allow you stand at the front of the queue, you can to join queue only to rear side
   ![2.png](imgs/2.png)

##### How works lenear linked lists?
Linear data structure where elements are not stored at contiguous location, instead the elements are linked using pointers. In a linked list data is stored in nodes and each node is linked to the next and, optionally, to the previous

1) Singly linked lists. 
   Every element - Node has value (in our case Token) and pointer to next elenebt of list. We can go back, we can only see what is in the previous element by going through all the elements of the linear list first 
   
   In this case, singly linked list using in queue
   ![3.png](imgs/3.png)
2) Doubly linked lists.
   Every node has two pointers: to next element and to previous element. 
   
    In this case, double linked list using in stack
   ![4.png](imgs/4.png)
All these data stuctures you can find in structures.c and structures.h



### How to run

To compile and run the build, the easiest way is to add the source files in visual studio and compile them.
Just add .c files to source files folder and .h files to headers and run (ctrl + f5)



