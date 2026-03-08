#include <stdio.h>                    // For file handling (FILE, fopen, fprintf, fscanf, etc.)
#include "file.h"                     // Custom header containing AddressBook structure definition
#include <string.h>                   // For string operations (used implicitly in struct fields)

//-----------------------------------------//
// Function to save all contacts to a file
//-----------------------------------------//
void saveContactsToFile(AddressBook *addressBook)
{
    FILE *fptr = fopen("contacts.txt", "w");       // Open file in write mode (overwrites existing file)
    fprintf(fptr, "#%d\n", addressBook->contactCount);  // Write the total number of contacts at the top (with a # for easy identification)

    for (int i = 0; i < addressBook->contactCount; i++) // Loop through all contacts
    {
        // Write each contact in comma-separated format: name,phone,email
        fprintf(fptr, "%s,%s,%s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }

    fclose(fptr);                                      // Close the file after writing
}

//-----------------------------------------//
// Function to load contacts from the file
//-----------------------------------------//
void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fptr = fopen("contacts.txt", "r");           // Open file in read mode
    if (fptr == NULL)                                  // Check if file does not exist
    {
        addressBook->contactCount = 0;                 // If no file, start with zero contacts
        return;
    }

    fscanf(fptr, "#%d\n", &addressBook->contactCount);  // Read the number of contacts stored in file

    for (int i = 0; i < addressBook->contactCount; i++) // Loop to read each contact
    {
        // Read line in comma-separated format: name,phone,email
        fscanf(fptr, "%[^,],%[^,],%[^\n]\n",
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }

    fclose(fptr);                                      // Close the file after reading
}
