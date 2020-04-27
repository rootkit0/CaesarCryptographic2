#include <stdio.h>
#include <string.h>
#include <ctype.h>

int index_of(char string[], char c) {
    for(int i=0; i<strlen(string); ++i) {
        if(string[i] == c) {
            return i;
        }
    }
}

void encriptar_arxiu(FILE *decoded, char key[]) {
    char abc_majus[] = "ABCDEFGHILMNOPQRSTUVXYZ";
    char abc_minus[] = "abcdefghilmnopqrstuvxyz";
    int index = 0, pos_key = 0;
    char actual;
    while((actual = getc(decoded)) != EOF) {
        if(isalpha(actual)) {
            if(isupper(actual)) {
                index = index_of(abc_majus, actual) + index_of(abc_majus, key[pos_key % strlen(key)]);
                ++pos_key;
                putchar(abc_majus[index % strlen(abc_majus)]);
            }
            if(islower(actual)) {
                index = index_of(abc_minus, actual) + index_of(abc_minus, key[pos_key % strlen(key)]);
                ++pos_key;
                putchar(abc_minus[index % strlen(abc_minus)]);
            }
        }
        else {
            putchar(actual);
        }
    }
}

int main (int argc, char *argv[]) {
    if(argc > 2) {
        //Obrem l'arxiu decoded_file
        FILE *decoded_file;
        decoded_file = fopen(argv[1], "r");
        //Obtenim la clau
        char *clau = argv[2];
        //Encriptem l'arxiu
        printf("L'arxiu %s encriptat amb la clau %s, es:\n", argv[1], argv[2]);
        encriptar_arxiu(decoded_file, clau);
        //Per acabar tanquem el fitxer
        fclose(decoded_file);
    }
    else {
        printf("Us: ./encrypt fitxer_descodificat.txt clau\n");
    }
}
