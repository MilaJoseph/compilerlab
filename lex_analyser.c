#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int isKeyword(const char* word) {
    const char* keywords[] = {"while","for","if","do","switch","case","default","int","float","char"};
    int n = sizeof(keywords)/sizeof(keywords[0]);
    for(int i = 0; i < n; i++){
        if(strcmp(word, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

int main(int argc, char **argv) {
    if(argc < 2){
        printf("Usage: %s <input filename>\n", argv[0]);
        return 0;
    }

    FILE *f = fopen(argv[1], "r");
    if(!f){
        printf("Cannot open file %s\n", argv[1]);
        return 0;
    }

    char ch, word[100];
    while((ch = fgetc(f)) != EOF) {

        // Skip whitespaces
        if(isspace(ch)) continue;

        // Identifiers / Keywords
        if(isalpha(ch) || ch == '_'){
            int i = 0;
            word[i++] = ch;
            while((ch = fgetc(f)) != EOF && (isalnum(ch) || ch == '_')){
                word[i++] = ch;
            }
            word[i] = '\0';
            if(ch != EOF) fseek(f, -1, SEEK_CUR); // put back last read char
            if(isKeyword(word)) 
                printf("%s -> Keyword\n", word);
            else 
                printf("%s -> Identifier\n", word);
        }
        // Numbers
        else if(isdigit(ch)){
            int i = 0;
            word[i++] = ch;
            while((ch = fgetc(f)) != EOF && isdigit(ch)){
                word[i++] = ch;
            }
            word[i] = '\0';
            if(ch != EOF) fseek(f, -1, SEEK_CUR);
            printf("%s -> Integer\n", word);
        }
        // Strings
        else if(ch == '"'){
            int i = 0;
            while((ch = fgetc(f)) != EOF && ch != '"'){
                word[i++] = ch;
            }
            word[i] = '\0';
            printf("%s -> String Literal\n", word);
        }
        // Single-line comments
        else if(ch == '/' && (ch = fgetc(f)) == '/'){
            while((ch = fgetc(f)) != EOF && ch != '\n'); // skip line
            printf("Single-line comment ignored\n");
        }
        // Multi-line comments
        else if(ch == '/' && (ch = fgetc(f)) == '*'){
            char prev = 0;
            while((ch = fgetc(f)) != EOF){
                if(prev == '*' && ch == '/') break;
                prev = ch;
            }
            printf("Multi-line comment ignored\n");
        }
        // Operators & punctuators
        else{
            printf("%c -> Operator/Punctuator\n", ch);
        }
    }

    fclose(f);
    return 0;
}
