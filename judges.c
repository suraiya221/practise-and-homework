#include <stdio.h>

int main() {
    
    char name[5][20] = {
        "Youngsoo", "Jiyoung", "Minjun", "Hyunwoo", "Jiyoung"
    };
    char gen[5][10] = {
        "Male", "Female", "Male", "Male", "Female"
    };
    char affiliation[5][30] = {
        "JYK Studio", "DK Studio", "JM Studio", "Starlight Entertainment", "Association"
    };
    char title[5][20] = {
        "Producer", "Director", "Director", "Director", "Critic"
    };
    char expertise[5][20] = {
        "Music", "Dance", "Vocal", "Visual", "Critic"
    };
    char email[5][40] = {
        "youngsu@outlook.com",
        "jiyounghere@outlook.com",
        "minjun@outlook.com",
        "hyunwoo@outlook.com",
        "jiyoung@outlook.com"
    };
    char phone[5][20] = {
        "010-1234-5678",
        "010-2345-6789",
        "010-3456-7890",
        "010-4567-8901",
        "010-5678-9012"
    };

    int i = 0;
    while (i < 5) {
        printf("Name: %s\n", name[i]);
        printf("Gender: %s\n", gen[i]);
        printf("Affiliation: %s\n", affiliation[i]);
        printf("Title: %s\n", title[i]);
        printf("Expertise: %s\n", expertise[i]);
        printf("Email: %s\n", email[i]);
        printf("Phone: %s\n", phone[i]);
        printf("---------------------------\n");
        i++;
    }

    return 0;
}