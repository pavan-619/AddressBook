#ifndef CONTACT_H                // Header guard start – prevents multiple inclusions of this file
#define CONTACT_H

#define MAX_CONTACTS 100          // Maximum number of contacts that can be stored in the address book

//-------------------------------//
// Structure to store one contact
//-------------------------------//
typedef struct {
    char name[50];                // Stores contact's name
    char phone[20];               // Stores contact's phone number
    char email[50];               // Stores contact's email address
} Contact;

//-----------------------------------------//
// Structure to store all contacts together
//-----------------------------------------//
typedef struct {
    Contact contacts[MAX_CONTACTS]; // Array of Contact structures
    int contactCount;               // Number of contacts currently stored
} AddressBook;

//-------------------------------//
// Function Declarations (Prototypes)
//-------------------------------//
void createContact(AddressBook *addressBook);                 // Adds a new contact to the address book
int  searchContact(AddressBook *addressBook, int *index);     // Searches for a contact (by name, phone, or email)
void editContact(AddressBook *addressBook, int *index);       // Edits contact details
void deleteContact(AddressBook *addressBook);                 // Deletes a contact by name, phone, or email
void listContacts(AddressBook *addressBook, int sortCriteria);// Lists all contacts (can be extended to sort)
void initialize(AddressBook *addressBook);                    // Initializes address book (loads from file)
void saveContactsToFile(AddressBook *addressBook);            // Saves all contacts to a file

#endif // CONTACT_H            // End of header guard
