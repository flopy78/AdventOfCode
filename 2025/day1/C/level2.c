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
        int last_dial = dial;
        if (rotation == 'L') {
            dial = (dial-distance);

            while (dial < 0) dial += 100; //to make sure the rest is between 0 and 99
             
            if (dial == 0 ||(dial > last_dial && last_dial != 0)) {
                password ++;
            } 
        } else if (rotation == 'R') {
            dial = (dial+distance);
            while (dial > 99) dial -= 100;

            if (dial < last_dial) {
                password ++;
            }
        } else {
            printf("STOP\n");
            exit(1);
        }
        password += distance/100;
        printf("%c%d %d %d\n",rotation,distance,dial,password);

    }

    printf("password : %d\n",password);
    fclose(input);
}