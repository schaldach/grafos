/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <string.h>

int main()
{
    const char* str_inp1 = "ab";
	const char* str_inp2 = "ab";
	
    std::cout << "Hello World";
    if(strcmp(str_inp2, str_inp1) == 0){
        std::cout << "alo";
    }

    return 0;
}