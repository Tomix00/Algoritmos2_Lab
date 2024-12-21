/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* Maximum allowed length of the array */
#define MAX_SIZE 100000

void print_help(char *program_name) {
    /* Print the usage help of this program. */
    printf("Usage: %s <input file path>\n\n"
           "Loads an array given in a file in disk and prints it on the screen."
           "\n\n"
           "The input file must have the following format:\n"
           " * The first line must contain only a positive integer,"
           " which is the length of the array.\n"
           " * The second line must contain the members of the array"
           " separated by one or more spaces. Each member must be an integer."
           "\n\n"
           "In other words, the file format is:\n"
           "<amount of array elements>\n"
           "<array elem 1> <array elem 2> ... <array elem N>\n\n",
           program_name);
}

char *parse_filepath(int argc, char *argv[]) {
    /* Parse the filepath given by command line argument. */
    char *result = NULL;
    // Program takes exactly two arguments
    // (the program's name itself and the input-filepath)
    bool valid_args_count = (argc == 2);

    if (!valid_args_count) {
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }

    result = argv[1];

    return result;
}


unsigned int array_from_file(int array[],unsigned int max_size,const char *filepath) {
    FILE *fp = fopen(filepath,"r");
    unsigned int tamaño;
    fscanf(fp,"%u",&tamaño);//primera fila->  tamaño del array

    assert(tamaño<max_size);

    for (unsigned int i=0;i<tamaño;i++){
        fscanf(fp,"%d",&array[i]);
    }

    fclose(fp);
    return tamaño;
    /*
    1234f56
    
    fscanf(referencia del arhivo, que quiero que lea %d %c..., donde quiero que lo guarde)
    fscanf() iterado una ves mueve el "puntero" al segundo item que contenga el archivo
    |1234 -> 1|234
    cuando se lee el arhivo, no toma en cuenta los saltos de linea, por lo tanto es toda una fila de elementos
    
    */
}

void array_dump(int a[], unsigned int length) {
    printf("[");
    for (unsigned int i=0;i<length;i++){
        printf("%d,",a[i]);
    }
    printf("]\n");
}


int main(int argc, char *argv[]) {
    char *filepath = NULL;

    /* parse the filepath given in command line arguments */
    filepath = parse_filepath(argc, argv);

    /* create an array of MAX_SIZE elements */
    int array[MAX_SIZE];

    /* parse the file to fill the array and obtain the actual length */
    unsigned int length = array_from_file(array, MAX_SIZE, filepath);

    /*dumping the array*/
    array_dump(array, length);

    return EXIT_SUCCESS;
}