#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <cstdlib>
#include <unistd.h>
#include <string>

using namespace std;

bool w = false;
bool l = false;
bool c = false;
int totalWords=0;
int totalLines=0;
int totalChars=0;

void readFile(FILE* file, string filename){
	if(file == NULL){
  	      printf("File %s cannot be opened, skipping", filename.c_str());
        }
        else{
              int words = 0;
              int lines = 0;
              int chars = 0;
              int character;
              int prevChar;

              //parse the file
              while(character!=EOF){
            	  character = fgetc(file);
		  if(character!=EOF){
                  if(l){
                  	if(character == '\n'){
                        	lines++;
                                totalLines++;
                  	}
                  }
                  if(w){
                        if(isspace(character) && isprint(prevChar) && !isspace(prevChar)){
                               // printf("%c,", prevChar);
				words++;
                                totalWords++;
                        }
                  }
                  if(c){
	//		printf("%c,", character);
                  	chars++;
                        totalChars++;
                  }

                  prevChar=character;
		  }
              }
	      
	      //print everything
              if(l){
	          printf("\t%d", lines);
	      }
	      if(w){
	          printf("\t%d", words);
	      }
	      if(c){
	          printf("\t%d", chars);
	      }
              printf("\t%s\n", filename.c_str());
	}
}

int main ( int argc, char *argv[]) {
	int index;
	int flag;

	while ((flag = getopt (argc, argv, "wlc")) != -1){
		switch(flag){
			case 'w':
				w=true;	
				break;
			case 'l':
				l=true;
                                break;
			case 'c':
				c=true;
                                break;
			case '?':
				printf("USAGE: Only accepts files and -w -c -l as arguments\n");
				exit(-1);
		}
	}
	
	//If no flags are set, all flags are set
	if(!w && !l && !c){
		w=true;
		l=true;
		c=true;	
	}

	int numOfFiles = argc-optind;

	FILE* file;

	if(numOfFiles<1){
		//IF TEHRE ARE NO OPTIONS USE STDIN
		file = fopen(stdin, "r");
		readFile(file, "");
	}
	else{
		//Loop through each file
		for (index = optind; index < argc; index++){
			string filename=argv[index];
			if(filename=="-"){
				//USE STDIN IF IT IS A DASH
				//Open the file. If it can't be opened print an error
                                file = fopen(stdin, "r");
                                readFile(file, filename);

			}
			else{
				//Open the file. If it can't be opened print an error
				file = fopen(filename.c_str(), "r");
				readFile(file, filename);

				//close file when we're done with it
				fclose(file);
			}	
		}
	}
	//close file when we're done with it
        fclose(file);

	return(0);
}
