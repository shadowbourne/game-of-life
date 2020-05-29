#include "gol.h"
int is_alive(struct universe *u, int column, int row) {
    if (u->UniverseArray[row][column] == '*') {
        return 1;
    }
    else {if( u->UniverseArray[row][column] == '.') {
            return 0;
    }
        else {
            fprintf(stderr, "ERROR: Invalid cells in input file (characters other than '.' or '*' present).\n");
            exit(3);
        }
    }
}

int will_be_alive(struct universe *u, int column, int row) {
    int LocalLife = 0;
    for (int x = -1; x < 2; x++) {
        for (int y = -1; y < 2; y++) {
            if (!(x==0 && y==0)) {
                if (!(column+x < 0 || column+x > u-> MaxColumns-1 || row+y<0 || row+y > u-> MaxRows-1)) {
                    if (is_alive(u, column + x, row + y)) {
                        LocalLife++;
                    }
                }
            }
        }
    }
    if (is_alive(u, column, row)) {
        if (LocalLife == 2 || LocalLife == 3) {
            return 1;
        }
        else { 
            return 0;
    }
    }
    else {
        if (LocalLife == 3) {
            return 1;
        }
        else {
            return 0;
        }
    }
}

int will_be_alive_torus(struct universe *u, int column, int row) {
    int LocalLife = 0;
    for (int x = -1; x < 2; x++) {
        for (int y = -1; y < 2; y++) {
            if (!(x==0 && y==0)) {
                int tempX = 0;
                int tempY = 0;
                if ((column+x < 0)) {
                    tempX = u->MaxColumns;
                }
                else{ if(column+x > u->MaxColumns - 1 ) {
                    tempX = -u->MaxColumns;
                }}
                if (row+y<0) {
                    tempY = u->MaxRows;
                }
                else{ if(row+y > u->MaxRows - 1 ) {
                    tempY = -u->MaxRows;
                }}
                if (is_alive(u, column + x + tempX, row + y + tempY)) {
                    LocalLife += 1;
                }
            }
        }
    }

    if (is_alive(u, column, row)) {
        if (LocalLife == 2 || LocalLife == 3) {
            return 1;
        }
        else { 
            return 0;
    }
    }
    else {
        if (LocalLife == 3) {
            return 1;
        }
        else {
            return 0;
        }
    }
}

void evolve(struct universe *u, int (*rule)(struct universe *u, int column, int row)) {
    char ** NewUniverseArray = (char **) malloc(u->MaxRows * sizeof(char *));
    assert(NewUniverseArray != NULL);
    for(int i =0; i < u->MaxRows; i++) {
        NewUniverseArray[i] = (char *) malloc(u->MaxColumns * sizeof(char));
        assert(NewUniverseArray[i] != NULL);
    }
    int total_alive = 0;
    for(int i = 0; i< u->MaxRows; i++) {
        for(int j = 0; j< u->MaxColumns; j++) {
            if(rule(u, j, i) == 1) {
                NewUniverseArray[i][j] = '*';
            }
            else {
                NewUniverseArray[i][j] = '.';
            }
        }
    }
    for(int i =0; i < u->MaxRows; i++) {
        free(u->UniverseArray[i]);
    }
    free(u->UniverseArray);
    u->UniverseArray = NewUniverseArray;
    for(int i = 0; i< u->MaxRows; i++) {
        for(int j = 0; j< u->MaxColumns; j++) {
            if(is_alive(u,j,i) == 1) {
            total_alive++;
            }
        }
    }
    u->CurrentAlive = total_alive;
    u->TotalEverAlive += total_alive;
    u->Generations++;
}


void read_in_file(FILE *infile, struct universe *u) {
    char buffer[515];
    int row = 0;
    char next_char;
    int total_alive = 0;
    int i = 0;
    while(!feof(infile)) {      
        next_char = fgetc(infile);
        buffer[i] = next_char;
        if(next_char == '\n') {
            row++;
            break;
        }
        if(next_char == '*') {
            total_alive++;
        }
        else { if(!feof(infile)) {if(next_char != '.') {
            fprintf(stderr, "ERROR: Invalid cells in input file (characters other than '.' or '*' present).\n");
            exit(3);
        }}}
        
        i++;
        if(i>512) {
            fprintf(stderr, "ERROR: Invalid input file, more than 512 columns present.\n");
            exit(3);
        }

    }
    u -> MaxColumns = i;
    i = 0;
    int currentmemorysizeofArray = 25;
    u -> UniverseArray  = ( char **) malloc(currentmemorysizeofArray * sizeof(char*));
    assert(u->UniverseArray != NULL);
    u -> UniverseArray[0] = (char *) malloc(u->MaxColumns * sizeof(char));
    assert(u->UniverseArray[0] != NULL);
    // if(u->UniverseArray == NULL {
    //         fprintf(stderr, "ERROR: Malloc failed to allocate sufficient memory.\n");
    //         exit(3);
    //     }
    for(int j = 0; j < u->MaxColumns; j++) {
        u->UniverseArray[0][j] = buffer[j];
        // printf("hi");
    }
            // printf("hi");
    while(!feof(infile)) {
        next_char = fgetc(infile);
        buffer[i] = next_char;
        i++;
        if(next_char == '\n') {
            if(i-1!= u->MaxColumns) {
                fprintf(stderr, "ERROR: Non rectangular input universe.\n");
                exit(3);
            }
            if(row >= currentmemorysizeofArray) {
                currentmemorysizeofArray *= 2;
                u->UniverseArray = realloc(u -> UniverseArray, currentmemorysizeofArray * sizeof(char*));
                assert(u->UniverseArray != NULL);  
            }
            u -> UniverseArray[row] = (char *) malloc(u->MaxColumns * sizeof(char));
            assert(u->UniverseArray[row] != NULL);
            for(int j = 0; j < u->MaxColumns; j++) {
                u->UniverseArray[row][j] = buffer[j];
                }
            row++;
            i = 0;
        }
        if(next_char == '*') {
            total_alive++;
        }
        else { if(!feof(infile)) {if(next_char != '.' && next_char != '\n') {
            fprintf(stderr, "ERROR: Invalid cells in input file (characters other than '.' or '*' present).\n");
            exit(3);
        }}}
    }
    u->CurrentAlive = total_alive;
    u->TotalEverAlive = total_alive;
    u->Generations = 1;
    u -> MaxRows = row;
}

void write_out_file(FILE *outfile, struct universe *u) {
    for(int i = 0; i<u->MaxRows; i++) {
        for(int j = 0; j<u->MaxColumns; j++) {
            fprintf(outfile, "%c", u->UniverseArray[i][j]);
        }
        fprintf(outfile, "\n");
    }
}

void print_statistics(struct universe *u) {
    double cells = (double) u->MaxColumns * u->MaxRows;
    double current_percentage = (double) u->CurrentAlive / cells *100.0;
    double average_percentage = (double) u->TotalEverAlive / cells / u->Generations *100.0;
    printf("%.3f%% of cells currently alive\n%.3f%% of cells alive on average\n", current_percentage, average_percentage);
}