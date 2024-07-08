/*
________________________________    _____  ._____________________________  ______________
\__    ___/\_   _____/\______   \  /     \ |   \__    ___/\_   _____/\   \/  /\__    ___/
  |    |    |    __)_  |       _/ /  \ /  \|   | |    |    |    __)_  \     /   |    |   
  |    |    |        \ |    |   \/    Y    \   | |    |    |        \ /     \   |    |   
  |____|   /_______  / |____|_  /\____|__  /___| |____|   /_______  //___/\  \  |____|   
                   \/         \/         \/                       \/       \_/          Ver: 0.0.1 
 *
 * A PROGRAM FOR IMPLEMENTING ASCII ART LETTER
 * ANIMATIONS AND EFFECTS IN THE LINUX TERMINAL
 *
 * WRITTEN BY YDNAWIZARD
 */

/*Libraries*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
/* Define structure for passing inputs from CLI to program easily
 * "Text" is passed in via the command line with 3 options: ASCII art "style", "color", and the animation "effect", 
 * All of this data is stored in the banner struct which is then passed into different functions that transform
 * the input into an animated output of the specified characteristics
 */
struct banner{
	char* text;
	char* style;
	char* color;
	char* effect;
};

/* Define alphabet so letter indexes can be used to choose letters from font alphabets. Acts like a key for python-dictionary-esque
 * character fetching
 * */
char alphabet[52] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

/* ---STYLES---
 * Define ASCII art characters in hex codes for handling of backslashes which are misinterperted as escape sequences. 
 * This also just makes the approach to manipulating the text more straightforward.
 * This is done for every 'style' of ASCII lettering this program suppports.
 */

/*Define grafitti style */
unsigned char graffiti_A[71] = {0x20, 0x20, 0x20, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x20, 0x20, 0x20, 0x0A, 0x20, 0x20, 0x2F, 0x20, 0x20, 0x5F, 0x20, 0x20, 0x5C, 0x20, 0x20, 0x0A, 0x20, 0x2F, 0x20, 0x20, 0x2F, 0x5F, 0x5C, 0x20, 0x20, 0x5C, 0x20, 0x0A, 0x2F, 0x20, 0x20, 0x20, 0x20, 0x7C, 0x20, 0x20, 0x20, 0x20, 0x5C, 0x0A, 0x5C, 0x5F, 0x5F, 0x5F, 0x5F, 0x7C, 0x5F, 0x5F, 0x20, 0x20, 0x2F, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x5C, 0x2F, 0x20};

unsigned char graffiti_B[71] = {0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x20, 0x0A, 0x5C, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x20, 0x20, 0x20, 0x5C, 0x0A, 0x20, 0x7C, 0x20, 0x20, 0x20, 0x20, 0x7C, 0x20, 0x20, 0x5F, 0x2F, 0x0A, 0x20, 0x7C, 0x20, 0x20, 0x20, 0x20, 0x7C, 0x20, 0x20, 0x20, 0x5C, 0x0A, 0x20, 0x7C, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x20, 0x20, 0x2F, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x5C, 0x2F, 0x20};

unsigned char graffiti_C[71] = {0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x20, 0x20, 0x0A, 0x5C, 0x5F, 0x20, 0x20, 0x20, 0x5F, 0x5F, 0x5F, 0x20, 0x5C, 0x20, 0x0A, 0x2F, 0x20, 0x20, 0x20, 0x20, 0x5C, 0x20, 0x20, 0x5C, 0x2F, 0x20, 0x0A, 0x5C, 0x20, 0x20, 0x20, 0x20, 0x20, 0x5C, 0x5F, 0x5F, 0x5F, 0x5F, 0x0A, 0x20, 0x5C, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x20, 0x20, 0x2F, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x5C, 0x2F, 0x20};

/*Pass graffiti characters into a graffiti alphabet for indexing against a standard alphabet*/
unsigned char* graffiti[52] = {graffiti_A, graffiti_B, graffiti_C};

/* Style: Takes in a banner struct and returns the "text" in the specified "style" */
unsigned char** style(struct banner* banner_obj){
	int i;
	int j = 0;
	char* style=banner_obj->style;
	char* text=banner_obj->text;
	unsigned char** styled_letters=(unsigned char**)malloc(sizeof(unsigned char*));
	if(strcmp(style,"graffiti")==0){
		while(j<strlen(text)){
			for(i=0;i<26;i++){
				if(text[j]==alphabet[i]){
					styled_letters[j]=graffiti[i];
					j+=1;
					styled_letters=(unsigned char**)realloc(styled_letters,(sizeof(unsigned char*)*j)+1);
				}
			}
		}
	}
	return styled_letters;
}

/* Spell: Takes in an array of ASCII art characters and and a banner struct. 
 * It outputs the ASCII letters as one array so it can be printed on one line.
 * The text is easier to animate in this form. */
unsigned char* spell(unsigned char** styled_letters, struct banner* banner_obj){
	int i=0;
	int j=0;
	int k=0;
	int l=0;
	int limiter;
	int holder=0;
	char* style=banner_obj->style;
	char* text=banner_obj->text;
	int size=strlen(text);
	int length=strlen(text)*66;
	unsigned char* spelled_text=(unsigned char*)malloc((sizeof(unsigned char)*length)+5);
	if(strcmp(style,"graffiti")==0){
		limiter=11;
		for(i=0;i<6;i++){
			for(j=0;j<size;j++){
				if((j-size)==-1){
					limiter +=1;
					for(k=holder;k<limiter;k++){
						spelled_text[l]=styled_letters[j][k];
						l+=1;
					}
					holder+=12;
					limiter+=11;
				}
				else{
					for(k=holder;k<limiter;k++){
						spelled_text[l]=styled_letters[j][k];
						l+=1;
					}
				}
			}
		}
	}
	return(spelled_text);
}

/* Oscillate: Takes in an an array of ASCII art letters and a banner struct.
 * It outputs the ASCII letters one shift right as one array so it can be printed on one line.
 * When applied recursively, this gives the effect of "Oscillating" the text. */
unsigned char* oscillate(unsigned char* spelled_text, struct banner* banner_obj){
	int i;
	int pivot;
	int holder;
	char* style=banner_obj->style;
	char* text=banner_obj->text;
	int size=strlen(text);
	int length=(strlen(text)*66)+4;
	if(strcmp(style,"graffiti")==0){
		i=length;
		pivot=length;
		holder=spelled_text[length];
		while(i>=0){
			if(i==0){
				spelled_text[i]=holder;
				i-=1;
			}
			else if((pivot-i)==(11*size)-1){
				spelled_text[i]=holder;
				i-=2;
				pivot=i;
				holder=spelled_text[i];
			}
			else{
				spelled_text[i]=spelled_text[i-1];
				i-=1;
			}
		}
	}
	return(spelled_text);
}




int main(int argc, char* argv[]){
	int i=0;
	int j=0;
	int opt;
	unsigned char** text;
	unsigned char* spelled;
	while((opt=getopt(argc,argv,":a"))!=1){
		switch(opt){
			case 'a':
				struct banner banner1={"ABCABCABCABC","graffiti","default","oscillate"};
				text=style(&banner1);
				spelled=spell(text,&banner1);
				system("clear");
				while(i>=0){					spelled=oscillate(spelled,&banner1);
					fflush(stdout);
					printf("%s\r",spelled);
					printf("\x1b[1f\r");
					fflush(stdout);
					spelled=oscillate(spelled,&banner1);
					j=0;
					usleep(60000);
				}
				break;
		}
	}
}



