#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100
// maximum number of contacts

typedef struct
{
    char name[50];
    char phone[11];
    char email[50];
} Contact;
// structure to store contact details

typedef struct
{
    Contact contacts[MAX_CONTACTS];
    int contactCount;
} AddressBook;
// structure to store all contacts

/* contact operations */
void createContact(AddressBook *addressBook); // create new contact
void searchContact(AddressBook *addressBook); // search contact
void editContact(AddressBook *addressBook);   // edit contact
void deleteContact(AddressBook *addressBook); // delete contact
void listContacts(AddressBook *addressBook);  // display all contacts
void initialize(AddressBook *addressBook);    // initialize address book

/* validation functions */
int validateName(char name[]);
// validate name

int validatePhone(char phone[], AddressBook *addressBook);
// validate phone number

int validateEmail(char email[], AddressBook *addressBook);
// validate email id

#endif