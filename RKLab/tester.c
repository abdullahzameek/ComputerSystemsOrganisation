
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <strings.h>
#include <assert.h>
#include <time.h>
#include <ctype.h>

/* The normalize procedure examines a character array of size len 
	 in ONE PASS and does the following:
	 1) turn all upper case letters into lower case ones
	 2) turn any white-space character into a space character and, 
	    shrink any n>1 consecutive spaces into exactly 1 space only
			Hint: use C library function isspace() 
	 You must do the normalization IN PLACE so that when the procedure
	 returns, the character array buf contains the normalized string and 
	 the return value is the length of the normalized string.
*/
int normalize(char *buf,	/* The character array containing the string to be normalized*/
					int len			/* the size of the original character array */)
{
	int change = 0; //a marker to the change element on the buffer
	int peek = 0; //a marker to the element behind change

	for(change = 0; change < len; change++)
	{
		//check for uppercase chara and replace with lower
		if(isupper(buf[change]) > 0){
			buf[peek++] = tolower(buf[change]);
		}
		else if((isspace(buf[change])) == 0 && isspace(buf[change+1]) != 0){
			peek++;
		}
        // else if((isspace(buf[change])) != 0 && isspace(buf[change+1]) != 0){
		// 	while(isspace(buf[peek]) != 0){
        //         peek++;
        //     }
            

		// }
		
        else{
			peek++;
		}


	}
    return len;
}


int main(int argc, char** argv){
    int testlen = 15;
    char abc[15] = "OnE spacE   two";
    printf("%s\n", abc);
    normalize(abc,testlen);
    printf("%s\n",abc);    
    return 0;
}