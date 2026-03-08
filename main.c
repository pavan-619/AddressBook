#include <stdio.h>              // For printf, scanf, etc.
#include "contact.h"            // Header file that includes AddressBook structure and function declarations

int main() {
    int choice;                 // Stores user's menu choice
    AddressBook addressBook;    // Create an AddressBook variable to hold all contacts
    initialize(&addressBook);   // Initialize the address book (loads existing contacts from file)
    int index[50];              // Array used for temporary search results (stores matching indices)

    do {
        // Display main menu options
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");       // Option to add a new contact
        printf("2. Search contact\n");       // Option to search for existing contact
        printf("3. Edit contact\n");         // Option to edit a contact
        printf("4. Delete contact\n");       // Option to delete a contact
        printf("5. List all contacts\n");    // Option to list all saved contacts
        printf("6. Save & Exit\n");          // Option to save all data to file and exit
        printf("7. Exit\n");                 // Exit without saving
        printf("Enter your choice: ");
        scanf("%d", &choice);                // Read user's menu choice
        
        switch (choice)                      // Perform actions based on choice
        {
            case 1: // Create new contact
                createContact(&addressBook); // Call function to create and add a new contact
                break;

            case 2: // Search for contact
                searchContact(&addressBook, index); // Search contact by name, phone, or email
                break;

            case 3: // Edit contact
                editContact(&addressBook, index);   // Modify name, phone, or email of a contact
                break;

            case 4: // Delete contact
                deleteContact(&addressBook);        // Remove a contact from the address book
                break;

            case 5: // List contacts
                printf("Select sort criteria:\n");
                printf("1. Sort by name\n");
                printf("2. Sort by phone\n");
                printf("3. Sort by email\n");
                printf("Enter your choice: ");
                int sortChoice;                     // Variable for sorting choice
                scanf("%d", &sortChoice);
                listContacts(&addressBook, sortChoice); // Display all contacts
                break;

            case 6: // Save and exit
                printf("Saving and Exiting...\n");
                saveContactsToFile(&addressBook);   // Save contacts to file before exit
                break;

            default: // Handle invalid input
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);                          // Loop until user chooses to save and exit
    
    return 0;                                       // End of program
}
