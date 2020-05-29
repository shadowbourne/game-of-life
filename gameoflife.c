// #include<stdio.h>
#include"gol.h"
int main(int argc, char *argv[]){
  // printf("%d", argc);
  int stats = 0;
  int outputting = 0;
  int inputting = 0;
  int number_of_generations = -1;
  int generations_change = 0;
  int (* rule)(struct universe *, int , int) =  will_be_alive;
  char output[101];
  char input[101];
  char command[101];
  for(int i = 1; i < argc; i++) {
    if(strlen(argv[i]) > 99) {
      fprintf(stderr, "ERROR: Command line option number %d too long.\n", i+1);
      exit(3);
    } 
    strcpy(command, argv[i]);
    if(command[0] == '-') {
      switch(command[1]) {
        case 's':
          stats = 1;
          break;
        case 't':
          rule = will_be_alive_torus;
          break;
        case 'o':
          if( i+2 > argc) {
            fprintf(stderr, "ERROR: No output file name supplied.\n");
            exit(3);
          }
          if( strlen(argv[i+1]) > 99) {
            fprintf(stderr, "ERROR: Output file name too long.\n");
            exit(3);
          } 
          if(outputting == 1) {
            if( strcmp(output,argv[i+1]) != 0) {
            fprintf(stderr, "ERROR: Contradicting'-o' command line options supplied.\n");
            exit(3);
          } 
          }
          outputting = 1;
          
          
          strcpy(output, argv[i+1]);
          i++;
          break;
        case 'i':
          if( i+2 > argc) {
            fprintf(stderr, "ERROR: No input file name supplied.\n");
            exit(3);
          }
          if( strlen(argv[i+1]) > 99) {
            fprintf(stderr, "ERROR: Input file name too long.\n");
            exit(3);
          } 
          if(inputting == 1) {
            if( strcmp(input,argv[i+1]) != 0) {
              fprintf(stderr, "ERROR: Contradicting'-i' command line options supplied.\n");
              exit(3);
          }
          } 
          inputting = 1;
          strcpy(input, argv[i+1]);
          i++;
          // printf("will input\n");
          break;
        case 'g':
          if( i+2 > argc) {
            fprintf(stderr, "ERROR: No generations number supplied.\n");
            exit(3);
          } 
          for(unsigned int j = 0; j<strlen(argv[i+1]); j++) {
            if( isdigit(argv[i+1][j]) == 0 ) {
              fprintf(stderr, "ERROR: Generations argument is not a number.\n");
              exit(3);
            }
          }
          if( generations_change ==1) {
            if(number_of_generations != atoi(argv[i+1]) ) {
              fprintf(stderr, "ERROR: Contradicting'-g' command line options supplied.\n");
              exit(3);
            } 
          }
          generations_change = 1;
          number_of_generations = atoi(argv[i+1]);
          i++;
          break;
        default:
        fprintf(stderr, "ERROR: Invalid command line parameter supplied.\n");
        exit(3);  
        break;
      }
    }
    else {
      fprintf(stderr, "ERROR: Invalid command line parameter supplied.\n");
      exit(3);
    }
  }
  struct universe v; 
  if(inputting == 0) {
    read_in_file(stdin, &v);
  }
  else {
    FILE * infile = fopen(input, "r");
    if( infile == NULL) {
      fprintf(stderr, "ERROR: Unable to open input file.\n");
      exit(3);
    }
    read_in_file(infile, &v);
    fclose(infile);
  }
  if( number_of_generations == -1) {
    number_of_generations = 5;
  }
  for(int i = 0; i < number_of_generations; i++) {
      evolve(&v,rule);
  }
  if(outputting == 0) {
    
    write_out_file(stdout,&v);
  }
  else {
    FILE * outfile = fopen(output, "w");
    if( outfile == NULL) {
      fprintf(stderr, "ERROR: Unable to write to output file.\n");
      exit(3);
    }
    write_out_file(outfile, &v);
    fclose(outfile);
  }
  if(stats==1) {
    print_statistics(&v);
  }
return 0;
}
