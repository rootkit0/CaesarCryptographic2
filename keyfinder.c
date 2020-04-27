#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

char abc_minus[] = "abcdefghilmnopqrstuvxyz";
char abc_majus[] = "ABCDEFGHILMNOPQRSTUVXYZ";
char forbidden_letters[] = "jkwJKW";

void permuta(char **permutacions, int perm, int x, int j);
void decrypt_text(char text[], char key[], char *known_word);
int index_of(char string[], char c);

int main (int argc, char *argv[]) {
    if(argc > 2) {
        //Obrem l'arxiu decoded_file
        FILE *coded_file;
        coded_file = fopen(argv[1], "r");
        //Obtenim la paraula coneguda
        char *known_word = argv[2];
        //Obtenim la llargada de la clau
        int min_len_key = 0;
        int max_len_key = 23;
        if(argc > 4) {
            min_len_key = atoi(argv[3]);
            max_len_key = atoi(argv[4]);
        }
        //Guardem el fitxer al vector de caràcters text
        char text[2500];
        int text_pos = 0;
        while(1) {
            if(feof(coded_file)) {
                break;
            }
            else{
                text[text_pos] = fgetc(coded_file);
                ++text_pos;
            }
        }
        //Per acabar tanquem el fitxer
        fclose(coded_file);

        //Obtenim les permutacions amb les quals desxifrarem el text
        for(int i=min_len_key; i<max_len_key+1; ++i) {
            int num_perms = pow(strlen(abc_minus), i);
            char *permutacions[num_perms];
            char key[i];
            //Reservem memòria
            for(int j=0; j<num_perms; ++j) {
                permutacions[j] = (char *)malloc(i);
            }
            //Cridem a la funcio permuta tants cops com la long de la clau
            int aux = 1;
            for(int k=0; k<i; ++k) {
                permuta(permutacions, num_perms, aux, k);
                aux = strlen(abc_minus)*aux;
            }
            //Recorrem totes les permutacions i les anem tractant
            for(int x=0; x<num_perms; ++x) {
                for(int y=0; y<i; ++y) {
                    key[y] = permutacions[x][y];
                }
                //Desencriptem el text amb la clau actual
                decrypt_text(text, key, known_word);
            }
        }
    }
    else {
        printf("Us: ./keyfinder fitxer_codificat.txt paraula_coneguda\n");
    }
}

void permuta(char **permutacions, int perm, int x, int j){
    int aux1=0;
    int aux2=0;
    for(int i = 0; i<perm ; i++){
        permutacions[i][j]=abc_minus[aux2];
        aux1++;
        if(aux1 == x){
            aux2 = (aux2+1) % strlen(abc_minus);
            aux1=0;
        }

    }
}

void decrypt_text(char text[], char key[], char *known_word) {
    int index = 0, pos_key = 0;
    char decrypted_text[2500];
    for(int i=0; i<strlen(text); ++i) {
        if(isalpha(text[i])) {
            if(isupper(text[i])) {
                index = index_of(abc_majus, text[i]) - index_of(abc_majus, key[pos_key % strlen(key)]);
                ++pos_key;
                decrypted_text[i] = abc_majus[index % strlen(abc_majus)];
            }
            if(islower(text[i])) {
                index = index_of(abc_minus, text[i]) - index_of(abc_minus, key[pos_key % strlen(key)]);
                ++pos_key;
                decrypted_text[i] = abc_minus[index % strlen(abc_minus)];
            }
        }
        else {
            decrypted_text[i] = text[i];
        }
    }
    if(strstr(decrypted_text, known_word) != NULL) {
        printf("Clau trobada!: %s\n", key);
        printf("Text desencriptat: %s\n", decrypted_text);
    }
    else {
        printf("Clau no trobada, seguim intentant.\n");
        printf("Text desencriptat: %s\n", decrypted_text);
    }
}

int index_of(char string[], char c) {
    for(int i=0; i<strlen(string); ++i) {
        if(string[i] == c) {
            return i;
        }
    }
}
