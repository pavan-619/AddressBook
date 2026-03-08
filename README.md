**A console-based Address Book application written in C that allows users to manage contacts efficiently.**
  The application provides a simple menu-driven interface to create, search, edit, delete, and list contacts.
All contacts are stored in a file so that data persists between program executions

## Key Features

Create new contacts with name, phone number, and email

Search contacts by name, phone number, or email

Edit existing contact details

Delete contacts from the address book

Display all stored contacts

Save contacts to a file and load them on program start

Input validation for phone numbers and email IDs.
The program stores contacts using structures and maintains them in an array inside an address book structure. 

## Technologies Used

C Programming Language


Structures and Arrays

File Handling

String Handling

Modular Programming with Header Files

## Project Files

main.c        - Main program and menu interface

contact.c     - Contact management functions

contact.h     - Structure definitions and prototypes

file.c        - File save and load functions

file.h        - File handling declarations

populate.c    - Dummy data population

populate.h    - Populate function declaration

contacts.txt  - Stored contact data

The program loads contacts from contacts.txt at startup and saves them back when the user chooses to save and exit.

## Compile:
gcc main.c contact.c file.c populate.c -o addressbook
