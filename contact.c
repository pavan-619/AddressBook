
#include <stdio.h>        // Standard input/output
#include <stdlib.h>       // For malloc, exit, etc.
#include <string.h>       // For string functions
#include "contact.h"      // Custom header for contact struct
#include <ctype.h>        // For isalpha, isdigit
#include "file.h"         // File handling functions
#include "populate.h"     // File population utilities

// Temporary global buffers for input
char name[50];
char phone[20];
char email[50];

//-------------------------------------//
// Validate Phone Number Function
//-------------------------------------//
int validate_phone_no(char phone[], AddressBook* addressBook)
{
    int len = 0; // Initialize length counter
    while (phone[len] != '\0')    // Loop until end of string
    {  
        len++;
    }

    if (len != 10)               // Check if phone number is exactly 10 digits
    {   
         return 0;
    }

    for (int i = 0; i < 10; i++) // Check all characters are digits
    {
        if(phone[i] < '0' || phone[i] > '9')
        {
            return 0;
        }
    }

    // Check for duplicate phone numbers
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].phone, phone) == 0)
        {
            return 0;
        }
    }

    return 1; // Phone number is valid
}

//-------------------------------------//
// Validate Email ID Function
//-------------------------------------//
int validate_email_id(char email[], AddressBook* addressBook)
{
    // Must contain '@' and ".com"
    if (!strchr(email, '@') || !strstr(email, ".com"))
    {
        return 0;
    }

    if (!isalpha(email[0]))      // Email must start with an alphabet
    {   
        return 0;
    }

    int atCount = 0, dotCount = 0;  // Counters for '@' and '.'

    for (int i = 0; email[i] != '\0'; i++)
    {
        char c = email[i];

        // Reject uppercase or invalid characters
        if (isupper(c) || !(isalnum(c) || c == '.' || c == '@'))
        {
            return 0;
        }

        if (c == '@') // Count '@' symbol
        {
            atCount++;
            if (atCount > 1 || email[i + 1] == '.') // '@' rules
                return 0;
        }

        if (c == '.') // Count '.' occurrences
        {
            dotCount++;
            if (dotCount > 1)
                return 0;
        }
    }

    // Check for duplicate emails
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].email, email) == 0)
        {
            return 0;
        }
    }

    return 1; // Email ID is valid
}

//-------------------------------------//
// List All Contacts Function
//-------------------------------------//
void listContacts(AddressBook *addressBook, int sortCriteria)
{
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        printf("\nNAME : %s\n", addressBook->contacts[i].name);
        printf("PHONE.no : %s\n", addressBook->contacts[i].phone);
        printf("EMAIL : %s\n", addressBook->contacts[i].email);
        printf("Index : %d\n", i);
        printf("\n");
    }
}

//-------------------------------------//
// Initialize Address Book Function
//-------------------------------------//
void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;      // Start count at 0
    loadContactsFromFile(addressBook);  // Load contacts if file exists
}

//-------------------------------------//
// Save and Exit Function
//-------------------------------------//
void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook);    // Save all contacts to file
    exit(EXIT_SUCCESS);                 // Exit the program
}

//-------------------------------------//
// Create New Contact Function
//-------------------------------------//
void createContact(AddressBook *addressBook)
{
    printf("name: ");
    scanf(" %[^\n]", name);   // Read name with spaces

    printf("phone: ");
    scanf("%s", phone);       // Read phone (no spaces)

    printf("email: ");
    scanf(" %[^\n]", email);  // Read email with spaces

    int val1 = validate_phone_no(phone, addressBook);  // Validate phone
    int val2 = validate_email_id(email, addressBook);  // Validate email

    if (val1 == 1 && val2 == 1) // Both valid
    {
        strcpy(addressBook->contacts[addressBook->contactCount].phone, phone);
        strcpy(addressBook->contacts[addressBook->contactCount].name, name);
        strcpy(addressBook->contacts[addressBook->contactCount].email, email);
        addressBook->contactCount++;

        printf("Successfully saved..\n");
    }
    else if (val1 != 1)
    {
        printf("invalid phone number\n");
        createContact(addressBook); // Retry input
    }
    else if (val2 != 1)
    {
        printf("invalid email id\n");
        printf("\n");
        createContact(addressBook); // Retry input
    }
}

//-------------------------------------//
// Search Contact Function
//-------------------------------------//
int searchContact(AddressBook *addressBook, int *index)
{
    printf("1. Name\n2. Phone.no\n3. Email\n");             // Display search options
    int num;
    printf("Please select your Option: ");                  // Ask user how they want to search
    scanf("%d", &num);                                      // Read user’s choice

    switch (num)                                            // Perform action based on user selection
    {
        // ------------------------------------------ //
        // Case 1: Search contact by Name
        // ------------------------------------------ //
        case 1: 
        {
            char str[50];                                   // Buffer to store name input
            int flag = 0;                                   // Count how many matches found

            printf("Enter name to search: ");               // Ask for name to search
            scanf(" %[^\n]", str);                          // Read full name (including spaces)

            for (int i = 0; i < addressBook->contactCount; i++) // Loop through all contacts
            {
                if (strcmp(addressBook->contacts[i].name, str) == 0) // Compare entered name with stored name
                {
                    index[flag++] = i;                      // Store index of matched contact
                    printf("\nContact Found:\n");           // Print matching contact details
                    printf("NAME  : %s\n", addressBook->contacts[i].name);
                    printf("PHONE : %s\n", addressBook->contacts[i].phone);
                    printf("EMAIL : %s\n", addressBook->contacts[i].email);
                    printf("Index : %d\n", i);
                }
            }

            if (flag == 0)                                  // If no match found
            {
                printf("\nNo contact found with that name.\n");
            }
            return flag;                                    // Return number of matches found
        }

        // ------------------------------------------ //
        // Case 2: Search contact by Phone Number
        // ------------------------------------------ //
        case 2:
        {
            char str[15];                                   // Buffer to store phone number input
            int flag = 0;                                   // Match counter

            printf("Enter Your number to search: ");        // Ask user for phone number
            scanf(" %[^\n]", str);                          // Read phone number input

            for (int i = 0; i < addressBook->contactCount; i++) // Loop through all contacts
            {
                if (strcmp(addressBook->contacts[i].phone, str) == 0) // Compare entered phone number
                {
                    index[flag++] = i;                      // Save matched index
                    printf("\nContact Found:\n");           // Print matching contact
                    printf("NAME  : %s\n", addressBook->contacts[i].name);
                    printf("PHONE : %s\n", addressBook->contacts[i].phone);
                    printf("EMAIL : %s\n", addressBook->contacts[i].email);
                    printf("Index : %d\n", i);
                }
            }

            if (flag == 0)                                  // If no matches found
            {
                printf("\nNo contact found with that Phone.no.\n");
            }
            return flag;                                    // Return number of results
        }

        // ------------------------------------------ //
        // Case 3: Search contact by Email ID
        // ------------------------------------------ //
        case 3:
        {
            char str[50];                                   // Buffer to store email input
            int flag = 0;                                   // Match counter

            printf("Enter Your mail to search: ");          // Ask user for email
            scanf(" %[^\n]", str);                          // Read email input

            for (int i = 0; i < addressBook->contactCount; i++) // Loop through all contacts
            {
                if (strcmp(addressBook->contacts[i].email, str) == 0) // Compare entered email
                {
                    index[flag++] = i;                      // Store index of match
                    printf("\nContact Found:\n");           // Print details of matched contact
                    printf("NAME  : %s\n", addressBook->contacts[i].name);
                    printf("PHONE : %s\n", addressBook->contacts[i].phone);
                    printf("EMAIL : %s\n", addressBook->contacts[i].email);
                    printf("Index : %d\n", i);
                }
            }

            if (flag == 0)                                  // If no email matches found
            {
                printf("\nNo contact found with that Email.\n");
            }
            return flag;                                    // Return count of matches
        }

        // ------------------------------------------ //
        // Default Case: Invalid Option
        // ------------------------------------------ //
        default:
        {
            printf("Invalid Option!\n");                    // Handle wrong menu input
            return 0;                                       // Return 0 matches
        }
    }
}

//-------------------------------------//
// Edit Contact Function
//-------------------------------------//
void editContact(AddressBook *addressBook, int index[])
{
    int res = searchContact(addressBook, index);       // Search for contact(s) and store matching indices in 'index' array
    if (res == 0)                                     // If no contact found, exit function
        return;

    int contact_idx = -1;                             // Variable to hold the index of the contact to edit

    if (res > 1) // Multiple matches found
    {
        printf("\nMultiple matches found!\n");
        printf("Please select your index value: ");
        int num;
        if (scanf("%d", &num) != 1)                   // Read user’s chosen index; if invalid input
        {
            while (getchar() != '\n');                // Clear invalid input buffer
            printf("Invalid input!\n");
            return;
        }

        // Validate user's chosen index
        for (int i = 0; i < res; i++)
        {
            if (num == index[i])                      // Check if user input matches one of the found indices
            {
                contact_idx = index[i];               // Store that contact's index
                break;
            }
        }

        if (contact_idx == -1)                        // If entered index is not valid
        {
            printf("Enter a proper Index Value to edit details!\n");
            return;
        }
    }
    else                                               // Only one contact found
    {
        contact_idx = index[0];                        // Use the first match
    }

    // Ask user what they want to edit
    printf("\nSelect Edit criteria:\n");
    printf("1. Edit Name\n2. Edit Phone Number\n3. Edit Email ID\n");
    printf("Enter your choice: ");
    int choice;
    if (scanf("%d", &choice) != 1)                     // Read choice safely
    {
        while (getchar() != '\n');                     // Clear invalid input
        printf("Invalid input!\n");
        return;
    }

    switch (choice)
    {
        // -------------------------- //
        // CASE 1: Edit Contact Name  //
        // -------------------------- //
        case 1:
        {
            char str[50];
            printf("Enter new Name: ");
            scanf(" %[^\n]", str);                     // Read full name (allows spaces)

            int valid = 1;
            for (int i = 0; str[i] != '\0'; i++)       // Validate each character
            {
                if (!((str[i] >= 'a' && str[i] <= 'z') ||
                      (str[i] >= 'A' && str[i] <= 'Z') ||
                       str[i] == ' '))                 // Only alphabets and spaces are allowed
                {
                    valid = 0;
                    break;
                }
            }

            if (!valid)                                // Invalid name input
            {
                printf("Name should contain only alphabets and spaces!\n");
                return;
            }

            strcpy(addressBook->contacts[contact_idx].name, str); // Update name
            break;
        }

        // -------------------------- //
        // CASE 2: Edit Phone Number  //
        // -------------------------- //
        case 2:
        {
            char str[20];
            printf("Enter new Phone Number: ");
            scanf("%s", str);                          // Read phone number (digits only)

            int n = strlen(str);                       // Get length of number
            int valid = (n == 10);                     // Must be exactly 10 digits
            for (int i = 0; i < n && valid; i++)
            {
                if (!(str[i] >= '0' && str[i] <= '9')) // Check all are digits
                    valid = 0;
            }

            if (!valid)                                // Invalid phone number
            {
                printf("Phone number must contain exactly 10 digits!\n");
                return;
            }

            strcpy(addressBook->contacts[contact_idx].phone, str); // Update phone number
            break;
        }

        // ------------------------ //
        // CASE 3: Edit Email ID    //
        // ------------------------ //
        case 3:
        {
            char str[50];
            printf("Enter new Email ID: ");
            scanf("%s", str);                          // Read email (no spaces)

            // Basic email validation: must have '@' and '.com'
            if (strstr(str, "@") == NULL || strstr(str, ".com") == NULL)
            {
                printf("Email must contain '@' and end with '.com'!\n");
                return;
            }

            strcpy(addressBook->contacts[contact_idx].email, str); // Update email
            break;
        }

        // ------------------------ //
        // INVALID CHOICE HANDLER   //
        // ------------------------ //
        default:
        {
            printf("Invalid choice!\n");               // Handle invalid option
            return;
        }
    }

    // Display modified contact after editing
    printf("\nModified Contact:\n");
    printf("NAME  : %s\n", addressBook->contacts[contact_idx].name);
    printf("PHONE : %s\n", addressBook->contacts[contact_idx].phone);
    printf("EMAIL : %s\n", addressBook->contacts[contact_idx].email);
}

//-------------------------------------//
// Delete Contact Function
//-------------------------------------//
void deleteContact(AddressBook *addressBook)
{
    if (addressBook->contactCount == 0)                           // Check if there are any contacts to delete
    {
        printf("No contacts to delete.\n");                       // Inform user if list is empty
        return;                                                   // Exit function
    }

    printf("Delete by:\n1. Name\n2. Phone\n3. Email\n");          // Display delete options
    printf("Enter your choice: ");
    int choice;                                                   // Variable to store user's choice
    scanf("%d", &choice);                                         // Read user input

    char key[50];                                                 // Buffer to store search key (name/phone/email)
    int found = -1;                                               // Variable to hold index of found contact

    switch (choice)                                               // Handle user choice
    {
        case 1: // Delete by Name
        {
            printf("Enter Name: ");                               // Ask for name
            scanf(" %[^\n]", key);                                // Read full name (including spaces)
            for (int i = 0; i < addressBook->contactCount; i++)   // Loop through all contacts
            {
                if (strcmp(addressBook->contacts[i].name, key) == 0) // Compare entered name with contact name
                {
                    found = i;                                    // Store index of matching contact
                    break;                                        // Stop after finding first match
                }
            }
            break;                                                // Exit case 1
        }

        case 2: // Delete by Phone
        {
            printf("Enter Phone: ");                              // Ask for phone number
            scanf(" %s", key);                                  // Read phone number (no spaces)
            for (int i = 0; i < addressBook->contactCount; i++)   // Loop through contacts
            {
                if (strcmp(addressBook->contacts[i].phone, key) == 0) // Compare entered phone with stored phone
                {
                    found = i;                                    // Save found index
                    break;                                        // Stop searching
                }
            }
            break;                                                // Exit case 2
        }

        case 3: // Delete by Email
        {
            printf("Enter Email: ");                              // Ask for email
            scanf(" %s", key);                                  // Read email (no spaces)
            for (int i = 0; i < addressBook->contactCount; i++)   // Loop through all contacts
            {
                if (strcmp(addressBook->contacts[i].email, key) == 0) // Compare entered email with stored email
                {
                    found = i;                                    // Save the found index
                    break;                                        // Stop search after first match
                }
            }
            break;                                                // Exit case 3
        }

        default:                                                  // Handle invalid option
        {
            printf("Invalid choice!\n");                          // Notify user
            return;                                               // Exit function
        }
    }

    if (found == -1)                                              // If no match found
    {
        printf("No matching contact found.\n");                   // Inform user
        return;                                                   // Exit function
    }

    // Shift remaining contacts left to overwrite deleted one
    for (int i = found; i < addressBook->contactCount - 1; i++)   // Start shifting from deleted contact index
    {
        addressBook->contacts[i] = addressBook->contacts[i + 1];  // Copy next contact into current position
    }

    addressBook->contactCount--;                                  // Decrease contact count after deletion
    printf("Contact deleted successfully!\n");                    // Confirm successful deletion

    // Display updated contact list
    printf("\nUpdated Contact List:\n");
    for (int i = 0; i < addressBook->contactCount; i++)           // Loop to print all remaining contacts
    {
        printf("NAME  : %s\n", addressBook->contacts[i].name);    // Print name
        printf("PHONE : %s\n", addressBook->contacts[i].phone);   // Print phone number
        printf("EMAIL : %s\n\n", addressBook->contacts[i].email); // Print email
    }
}

