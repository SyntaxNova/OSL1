#include <stdio.h>
#include <string.h>

#define MAX 100

struct AddressBook {
    char name[50], phone[15], email[50];
};

void display(struct AddressBook book[], int count) {
    for (int i = 0; i < count; i++) {
        printf("Name: %s, Phone: %s, Email: %s\n", book[i].name, book[i].phone, book[i].email);
    }
}

int main() {
    struct AddressBook book[MAX];
    int count = 0, choice;
    char name[50];

    while (1) {
        printf("\n1. Create Address Book\n2. View Address Book\n3. Insert Record\n4. Delete Record\n5. Modify Record\n6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();  // consume newline

        switch (choice) {
            case 1: count = 0; printf("Address Book Created.\n"); break;
            case 2: display(book, count); break;
            case 3:
                printf("Enter Name: "); fgets(book[count].name, 50, stdin); book[count].name[strcspn(book[count].name, "\n")] = 0;
                printf("Enter Phone: "); fgets(book[count].phone, 15, stdin); book[count].phone[strcspn(book[count].phone, "\n")] = 0;
                printf("Enter Email: "); fgets(book[count].email, 50, stdin); book[count].email[strcspn(book[count].email, "\n")] = 0;
                count++;
                break;
            case 4:
                printf("Enter Name to Delete: "); fgets(name, 50, stdin); name[strcspn(name, "\n")] = 0;
                for (int i = 0; i < count; i++) {
                    if (strcmp(book[i].name, name) == 0) {
                        for (int j = i; j < count - 1; j++) book[j] = book[j + 1];
                        count--;
                        printf("Record deleted.\n");
                        break;
                    }
                }
                break;
            case 5:
                printf("Enter Name to Modify: "); fgets(name, 50, stdin); name[strcspn(name, "\n")] = 0;
                for (int i = 0; i < count; i++) {
                    if (strcmp(book[i].name, name) == 0) {
                        printf("Enter new Phone: "); fgets(book[i].phone, 15, stdin); book[i].phone[strcspn(book[i].phone, "\n")] = 0;
                        printf("Enter new Email: "); fgets(book[i].email, 50, stdin); book[i].email[strcspn(book[i].email, "\n")] = 0;
                        printf("Record modified.\n");
                        break;
                    }
                }
                break;
            case 6: return 0;
            default: printf("Invalid choice.\n");
        }
    }
}

