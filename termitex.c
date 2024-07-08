#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>

int i = 0;
int j = 0;
int ticker = 0;
int text_size;

struct banner{
	char* text;
	char* effect;
};

unsigned char A[71] = {0x20, 0x20, 0x20, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x20, 0x20, 0x20, 0x0A, 0x20, 0x20, 0x2F, 0x20, 0x20, 0x5F, 0x20, 0x20, 0x5C, 0x20, 0x20, 0x0A, 0x20, 0x2F, 0x20, 0x20, 0x2F, 0x5F, 0x5C, 0x20, 0x20, 0x5C, 0x20, 0x0A, 0x2F, 0x20, 0x20, 0x20, 0x20, 0x7C, 0x20, 0x20, 0x20, 0x20, 0x5C, 0x0A, 0x5C, 0x5F, 0x5F, 0x5F, 0x5F, 0x7C, 0x5F, 0x5F, 0x20, 0x20, 0x2F, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x5C, 0x2F, 0x20};

int main(char argc, char* argv[]){
	char holder;
	int opt;
	int i = 0;
	int pivot;
	int size;
	char* text;
	FILE* file;
	char** final_text;
	while((opt = getopt(argc, argv, ":apo")) != -1){
		switch(opt){
			case 'a':
				i = 0;
				system("clear");
				while(i >= 0){
					printf("%s", A);
					printf("\x1b[1f\r");
					fflush(stdout);
					while(j <= 400000000){
						j += 1;
					}
					j = 70;
					pivot = 70;
					holder = A[70];
					while(j >= 0){
						if(j == 0){
							A[j] = holder;
							j -= 1;
						}
						else if((pivot - j == 10)){
							A[j] = holder;
							j -= 2;
							pivot = j;
							holder = A[j];
						}
						else{
							A[j] = A[j-1];
							j -= 1;
						}
					}
					fflush(stdout);
				}
				break;

			case 'p':
				text_size = strlen(argv[2]);
				text = (char*)malloc(sizeof(char)*(text_size));
				text = argv[2];
				while(i < text_size){
					printf("%s %s", text, "\r");
					while(j <= 999999999){
						j += 1;
					}
					j = 0;
					while(j < text_size-1){
						text[text_size-(j+1)] = text[text_size-(j+2)];
						j += 1;
					}
					text[i] = ' ';
					i += 1;
				}
				break;
			case 'o':
				system("clear");
				text_size = strlen(argv[2]);
				text = (char*)malloc(sizeof(char)*(text_size+10));
				text = argv[2];
				i = text_size;
				while(i <= (text_size + 18)){
					text[i] = ' ';
					i += 1;
				}
				text_size = i;
				i = 0;
				while(i >= 0){
					printf("%s %s", text, "\r");
					while(j <= 450000000){
						j += 1;
					}
					j = 0;
					while(j < text_size-1){
						text[text_size-(j+1)] = text[text_size-(j+2)];
						j += 1;
					}
					text[0] = text[text_size-1];
					i += 1;
					fflush(stdout);
				}
				break;

			default:
				break;
		}
	}
	return 0;
}

