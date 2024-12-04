#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE * fp;
    char buffer[140];
    size_t size = 140;
    char * lines[140];
    while (getline(&buffer,&size,fp) != -1) {
        printf("%d",(int)strlen(buffer));
    }
    free(buffer);
    fclose(fp);



    return 0;
}
