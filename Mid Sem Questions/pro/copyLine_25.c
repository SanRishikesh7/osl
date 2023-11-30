#include <stdio.h>

int main() {
    FILE *fp1, *fp2;
    char line[100]; 

    fp1 = fopen("abc.txt", "r");
    fp2 = fopen("xyz.txt", "w");

    while (fgets(line, sizeof(line), fp1))
        fputs(line, fp2);

    fclose(fp1);
    fclose(fp2);

    return 0;
}

