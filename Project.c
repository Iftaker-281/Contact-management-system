#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Contact {
    char name[50];
    char phone[30];
    char email[40];
};

void addContact();
void viewContacts();
void searchContact();
void editContact();

int main() {
    int choice;

    while (1) {
        printf("\n===== Contact Management System =====\n");
        printf("1. Add Contact\n");
        printf("2. View Contacts\n");
        printf("3. Search Contact\n");
        printf("4. Edit Contact\n");
        printf("5. Exit\n");
        printf("-------------------------------------\n");
        printf("Please select your option (1-5): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addContact();
                break;
            case 2:
                viewContacts();
                break;
            case 3:
                searchContact();
                break;
            case 4:
                editContact();
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}

void addContact() {
    struct Contact c;

    FILE *file = fopen("contact.txt", "a");

    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter Name: ");
    scanf("%s", c.name);
    printf("Enter Phone: ");
    scanf("%s", c.phone);
    printf("Enter Email: ");
    scanf("%s", c.email);

    fprintf(file, "%s %s %s\n", c.name, c.phone, c.email);
    fclose(file);

    printf("Contact added successfully!\n");
}

void viewContacts() {
    struct Contact c;
    FILE *file = fopen("contact.txt", "r");

    if (file == NULL) {
        printf("No contacts found.\n");
        return;
    }

    printf("\n=== Contact List ===\n");
    while (fscanf(file, "%s %s %s", c.name, c.phone, c.email) == 3) {
        printf("Name: %s\nPhone: %s\nEmail: %s\n\n", c.name, c.phone, c.email);
    }

    fclose(file);
}

void searchContact() {
    char searchName[50];
    struct Contact c;
    int found = 0;

    FILE *file = fopen("contact.txt", "r");

    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter name to search: ");
    scanf("%s", searchName);

    while (fscanf(file, "%s %s %s", c.name, c.phone, c.email) == 3) {
        if (strcmp(c.name, searchName) == 0) {
            printf("\nContact Found:\nName: %s\nPhone: %s\nEmail: %s\n", c.name, c.phone, c.email);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Contact not found.\n");
    }

    fclose(file);
}

void editContact() {
    char NametoEdit[50];
    struct Contact c;
    int found = 0;

    FILE *file = fopen("contact.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (file == NULL || temp == NULL) {
        printf("Error opening files.\n");
        return;
    }

    printf("Enter name to edit: ");
    scanf("%s", NametoEdit);

    while (fscanf(file, "%s %s %s", c.name, c.phone, c.email) == 3) {
        if (strcmp(c.name, NametoEdit) == 0) {
            found = 1;
            printf("Enter new phone number: ");
            scanf("%s", c.phone);
            printf("Enter new email: ");
            scanf("%s", c.email);
        }
        fprintf(temp, "%s %s %s\n", c.name, c.phone, c.email);
    }

    fclose(file);
    fclose(temp);

    remove("contact.txt");
    rename("temp.txt", "contact.txt");

    if (found)
        printf("Contact updated successfully.\n");
    else
        printf("Contact not found.\n");
}
