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
	int peek = 0; //a marker to the element in front of change, "peeks" at what's ahead
    int spaceCounter = 0; //a counter to keep track of spaces when traversing consecutive spaces.
    int buflen = len; //this is gonna be used so that the length can be modified in the function


    for(change = 0; change < len; change++)
	{   
        //check for uppercase chara and replace with lower
		if(isupper(buf[change]) > 0){
			buf[peek++] = tolower(buf[change]);
		}
		
        //if there are no changes to be made, increment peek
        else if((isspace(buf[change])) == 0 && isspace(buf[change+1]) != 0){
			peek++;
		}
        
        //check for consecutive spaces
        else if((isspace(buf[change])) != 0 && isspace(buf[change+1]) != 0){
			//keep moving peek until it hits another letter, or hits the end of the string, and count the spaces along the way
            while(isspace(buf[peek]) != 0 && peek < len){
                peek++;
                spaceCounter++;
            }
            //adjust the space counter for overshoot, and increment change to keep a single space character behind
            spaceCounter--;
            change++;

            //while peek hasnt hit another letter or hasnt reached the end of the string, swap buf[peek] with buf[change] and move both forward
            while(isspace(buf[peek]) == 0 && peek < len){
                buf[change] = tolower(buf[peek]);
                buf[peek] = ' ';
                peek++; 
                change++;
            }
            
            //update new length and prevent change from overshooting
            buf[change] = ' ';
            buflen = buflen-spaceCounter;
            spaceCounter = 0;
            change--;
		}
        
        //if nothing to be done, move peek
        else
        {
		    peek++;
		}

        //fail safe - if either peek or change exceed length, break to prevent stack smashing from occuring
        if(peek >= len || change >= len){
            break;
        }
	}
    //update and return len
    len = buflen;
    return len;
}


int main(int argc, char** argv){
    char abc[124] = "It   WorKs    fOr shorT   SentenceS   and  it   PROBABLY   DOES   FOR  LONGER       SENTENCES     TOOOO    MAYYYYYBEEeeeEEEE";
    abc[124] = '\0';
    printf("%s\n", abc);
    printf("Normalizing now\n");
    int newlen = normalize(abc,124); 
    printf("Newlen is %d\n", newlen);
    for(int i = 0; i < newlen; i++){
        printf("%c", abc[i]);
    } 
    printf("\n");
    return 0;
}

 