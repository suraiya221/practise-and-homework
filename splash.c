#include <stdio.h>

int main() {
    char name[50];
    char date[11]; // Format yyyy-mm-dd requires 11 characters including the null terminator.

    // Prompt for user input
    printf("[Please enter the current date in the \"yyyy-mm-dd\" format]: ");
    scanf("%10s", date); // Limit input to 10 characters to avoid overflow.

    printf("[Please enter your name]: ");
    scanf("%49s", name); // Limit input to 49 characters.

    // Output the splash screen
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("\n");
    printf("                                        [Magrathea ver 0.1]\n");
    printf("                   Magrathea, where a shining planet is created in a wasteland with no grass,\n");
    printf("           a place where unseen potential is discovered and gems are polished by the hands of experts,\n");
    printf("                                        Welcome to Magrathea.\n");
    printf("\n");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("[User]: %s                                   [Execution Time]: %s\n", name, date);
    printf("==================================================================================\n");

    return 0;
}
