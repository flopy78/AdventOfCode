#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

int main() {
    FILE* input = fopen("input.txt","r");
    int dial = 50;
    int password = 0;
    char rotation;
    int distance;

    while (fscanf(input,"%c%d\n",&rotation,&distance) == 2) {
        if (rotation == 'L') {
            dial = (dial - distance)%100;
        } else if (rotation == 'R'){
            dial = (dial + distance)%100;
        } else {
            fprintf(stderr,"wrong rotation input");
            exit(1);
        }
        if (dial == 0) password ++;
    }
    printf("the password is : %d\n",password);
    fclose(input);
}
