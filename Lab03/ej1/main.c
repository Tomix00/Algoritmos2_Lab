#include <stdlib.h>
#include <stdio.h>

#define MAX_SIZE 1000

char *parse_filepath(int argc, char *argv[]){
    char *result = NULL;

    if (argc < 2) {
        printf("no funca\n");
        exit(EXIT_FAILURE);
    }

    result = argv[1];

    return result;
}

unsigned int data_from_file(const char *path,unsigned int indexes[],char sorted[],char letters[],unsigned int max_size){
    //devuelve arreglo de int y arreglo de char cargado y el tamaño de uno de los dos
    FILE *fp = fopen(path,"r");
    if (fp==NULL){
        exit(1);
    }

    unsigned int i=0;
    while(!feof(fp) && i<max_size){
        fscanf(fp,"%u -> *%c*\n",&indexes[i],&letters[i]);
        if(indexes[i]<max_size){
            sorted[indexes[i]]=letters[i];
        }
        i++;
    }
    fclose(fp);
    
    return i;
}



static void dump(char a[], unsigned int length) {
    printf("\"");
    for (unsigned int j=0u; j < length; j++) {
        printf("%c", a[j]);
    }
    printf("\"");
    printf("\n\n");
}


int main(int argc, char *argv[]) {
    char *filepath = NULL;

    filepath = parse_filepath(argc, argv);

    unsigned int indexes[MAX_SIZE];
    char letters[MAX_SIZE];
    char sorted[MAX_SIZE];

    unsigned int length=data_from_file(filepath,indexes,sorted,letters,MAX_SIZE);

    dump(sorted, length);

    return EXIT_SUCCESS;
}

