//HERE WE WILL CODE OR YOU PASTE THE CODE HERE 
#include <stdio.h>    // for input-output functions
#include <stdlib.h>   // for file handling functions
#include <string.h>   // for string operations

// Structure to store book information
struct Book {
    int bookID;            // unique ID for the book
    char title[50];        // book title
    char author[50];       // author name
    int copies;            // number of copies available
};

// Array of structures to store multiple books
struct Book library[100];

// Variable to store current number of books
int count = 0;

// Function declarations
void addBook();
void displayBooks();
void searchBook();
void issueBook();
void returnBook();
void saveToFile();
void loadFromFile();

int main() {
    int choice;

    // Load data from file when program starts
    loadFromFile();

    // Menu-driven program
    do {
        printf("\n--- Library Management System ---\n");
        printf("1. Add Book\n");
        printf("2. Display All Books\n");
        printf("3. Search Book by ID\n");
        printf("4. Issue Book\n");
        printf("5. Return Book\n");
        printf("6. Save and Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  // to consume newline character after number input

        // Calling functions based on user choice
        if (choice == 1)
            addBook();
        else if (choice == 2)
            displayBooks();
        else if (choice == 3)
            searchBook();
        else if (choice == 4)
            issueBook();
        else if (choice == 5)
            returnBook();
        else if (choice == 6) {
            saveToFile();   // save data before exiting
            printf("Data saved. Program closed.\n");
        }
        else
            printf("Invalid choice.\n");

    } while (choice != 6);

    return 0;   // end of program
}
void addBook() {

    // Check if library is full
    if (count >= 100) {
        printf("Library is full.\n");
        return;
    }

    // Take book details from user
    printf("Enter Book ID: ");
    scanf("%d", &library[count].bookID);
    getchar();  // to consume newline character

    printf("Enter Book Title: ");
    fgets(library[count].title, 50,stdin);   // reads full line

    printf("Enter Author Name: ");
    fgets(library[count].author,50, stdin);   // reads full line

    printf("Enter Number of Copies: ");
    scanf("%d", &library[count].copies);
    getchar();  // to consume newline character
    // Increase book count
    count++;

    printf("Book added successfully.\n");
}
void displayBooks() {
    int i;

    // If no books are present
    if (count == 0) {
        printf("No books available.\n");
        return;
    }

    // Loop through all books
    for (i = 0; i < count; i++) {
        printf("\nBook ID: %d", library[i].bookID);
        printf("\nTitle: %s", library[i].title);
        printf("\nAuthor: %s", library[i].author);
        printf("\nCopies: %d\n", library[i].copies);
    }
}
void searchBook() {
    int id, i;

    printf("Enter Book ID to search: ");
    scanf("%d", &id);
    getchar();  // to consume newline character

    // Search for matching Book ID
    for (i = 0; i < count; i++) {
        if (library[i].bookID == id) {
            printf("Book found.\n");
            printf("Title: %s\n", library[i].title);
            printf("Author: %s\n", library[i].author);
            printf("Copies: %d\n", library[i].copies);
            return;
        }
    }

    // If book not found
    printf("Book not found.\n");
}
void issueBook() {
    int id, i;

    printf("Enter Book ID to issue: ");
    scanf("%d", &id);

    // Search book
    for (i = 0; i < count; i++) {
        if (library[i].bookID == id) {

            // Check if copies are available
            if (library[i].copies > 0) {
                library[i].copies--;   // decrease copy count
                printf("Book issued successfully.\n");
            } else {
                printf("No copies available.\n");
            }
            return;
        }
    }

    printf("Book not found.\n");
}
void returnBook() {
    int id, i;

    printf("Enter Book ID to return: ");
    scanf("%d", &id);

    // Search book
    for (i = 0; i < count; i++) {
        if (library[i].bookID == id) {
            library[i].copies++;   // increase copy count
            printf("Book returned successfully.\n");
            return;
        }
    }

    printf("Book not found.\n");
}
void saveToFile() {
    FILE *fp;

    // Open file in write-binary mode
    fp = fopen("library.dat", "wb");

    // Check file opening
    if (fp == NULL) {
        printf("File error.\n");
        return;
    }

    // Save number of books
    fwrite(&count, sizeof(int), 1, fp);

    // Save all book records
    fwrite(library, sizeof(struct Book), count, fp);

    fclose(fp);   // close file
}
void loadFromFile() {
    FILE *fp;

    // Open file in read-binary mode
    fp = fopen("library.dat", "rb");

    // If file does not exist
    if (fp == NULL)
        return;

    // Read number of books
    fread(&count, sizeof(int), 1, fp);

    // Read all book records
    fread(library, sizeof(struct Book), count, fp);

    fclose(fp);   // close file
}
