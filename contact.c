#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "file.h"

int validateName(char name[])
/*function used to validate name (only alphabets allowed)*/
{

    if (strlen(name) < 3) // name must have at least 3 characters
        return 0;

    if (isdigit(name[0])) // name should not start with digit
        return 0;

    for (int i = 0; name[i]; i++)
    {
        if (!isalpha(name[i]) && name[i] != ' ') // allow alphabets and space
            return 0;
    }
    return 1;
}

int validatePhone(char phone[], AddressBook *addressBook)
/*function used to validate phone number (10 digits and no duplicates)*/
{
    if (strlen(phone) != 10) // phone must be 10 digits
        return 0;

    if (phone[0] < '6' || phone[0] > '9') // first digit must be 6 to 9
        return 0;

    for (int i = 0; phone[i]; i++)
    {
        if (!isdigit(phone[i])) // only digits allowed
            return 0;
    }

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(phone, addressBook->contacts[i].phone) == 0) // duplicate check
            return 0;
    }

    return 1;
}

int validateEmail(char email[], AddressBook *addressBook)
/* function used to validate email id(lowercase, one @and.com) */
{
    int atCount = 0;
    char *at = strchr(email, '@');
    char *dot = strrchr(email, '.');

    if (!at || !dot || dot < at + 2) // characters must exist between @ and .
        return 0;

    for (int i = 0; email[i]; i++)
    {
        if (email[i] == '@')
            atCount++;
        else if (!islower(email[i]) && email[i] != '.' && email[i] != '@')
            return 0;
    }

    if (atCount != 1) // only one '@'
        return 0;

    if (strcmp(dot, ".com") != 0)
        return 0;

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(email, addressBook->contacts[i].email) == 0) // duplicate email
            return 0;
    }

    return 1;
}

void listContacts(AddressBook *addressBook)
/*function used to display all contacts on screen*/
{
    if (addressBook->contactCount == 0)
    {
        printf("No contacts available\n");
        return;
    }

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        printf("Contact %d:\n", i + 1);
        printf("Name: %s\n", addressBook->contacts[i].name);
        printf("Phone: %s\n", addressBook->contacts[i].phone);
        printf("Email: %s\n", addressBook->contacts[i].email);
        printf("-----------------------\n");
    }
}

void initialize(AddressBook *addressBook)
/*function used to initialize address book and load data from file*/
{
    addressBook->contactCount = 0; // set count to zero

    loadContactsFromFile(addressBook); // load data from file
}

void saveAndExit(AddressBook *addressBook)
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS);              // Exit the program
}

void createContact(AddressBook *addressBook)
/*function used to create a new contact by taking name, phone and email*/
{
    /* Define the logic to create a Contacts */
    int att, max_att = 3;
    Contact *c = &addressBook->contacts[addressBook->contactCount];
    att = 0;
    // Name
    while (att < max_att)
    {
        printf("Enter Name:\n");

        scanf(" %[^\n]", c->name);
        if (validateName(c->name))
            break;
        else
        {
            printf("Invalid Name\n");
            att++;
            printf("Attempts left: %d\n", max_att - att);
        }
    }
    if (att == max_att)
    {
        printf("Maximum attempts reached\n");
        printf("Failed to create contact\n");
        return;
    }

    // phone
    att = 0;
    while (att < max_att)
    {
        printf("Enter Phone:\n");

        scanf("%s", c->phone);
        if (validatePhone(c->phone, addressBook))
            break;
        else
        {
            printf("Invalid Phone\n");
            att++;
            printf("Attempts left: %d\n", max_att - att);
        }
    }

    if (att == max_att)
    {
        printf("Maximum attempts reached\n");
        printf("Failed to create contact\n");
        return;
    }

    // email
    att = 0;
    while (att < max_att)
    {
        printf("Enter Email:\n");

        scanf("%s", c->email);
        if (validateEmail(c->email, addressBook))
            break;
        else
        {
            printf("Invalid Email\n");
            att++;
            printf("Attempts left: %d\n", max_att - att);
        }
    }
    if (att == max_att)
    {
        printf("Maximum attempts reached\n");
        printf("Failed to create contact\n");
        return;
    }
    addressBook->contactCount++; // increment contact count
    printf("Contact created successfully\n");
}
void searchContact(AddressBook *addressBook)
/*function used to search contact by name / phone / email*/
{
    int found = 0;
    char key[50];

    printf("Enter name / phone / email to search:\n");
    scanf(" %[^\n]", key);

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].name, key) == 0 ||
            strcmp(addressBook->contacts[i].phone, key) == 0 ||
            strcmp(addressBook->contacts[i].email, key) == 0)
        {
            printf("\nContact Found (%d)\n", i);
            printf("Name  : %s\n", addressBook->contacts[i].name);
            printf("Phone : %s\n", addressBook->contacts[i].phone);
            printf("Email : %s\n", addressBook->contacts[i].email);
            found = 1;
        }
    }

    if (!found)
        printf("Contact Not Found\n");
}

void editContact(AddressBook *addressBook)
{
    char name[50];
    int index, found = 0;

    printf("Enter name to edit:\n");
    scanf(" %[^\n]", name);

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].name, name) == 0)
        {
            printf("%d. %s %s %s\n",
                   i,
                   addressBook->contacts[i].name,
                   addressBook->contacts[i].phone,
                   addressBook->contacts[i].email);
            found = 1;
        }
    }

    if (!found)
    {
        printf("Contact not found\n");
        return;
    }

    printf("Enter index to edit:\n");
    scanf("%d", &index);

    if (index < 0 || index >= addressBook->contactCount)
    {
        printf("Invalid index\n");
        return;
    }

    /* Temporary variables */
    char newName[50];
    char newPhone[11];
    char newEmail[50];

    printf("Enter new name: ");
    scanf(" %[^\n]", newName);
    if (!validateName(newName))
    {
        printf("Invalid name\n");
        return;
    }

    printf("Enter new phone: ");
    scanf("%s", newPhone);
    if (!validatePhone(newPhone, addressBook))
    {
        printf("Invalid phone\n");
        return;
    }

    printf("Enter new email: ");
    scanf("%s", newEmail);
    if (!validateEmail(newEmail, addressBook))
    {
        printf("Invalid email\n");
        return;
    }

    /* If all validations passed → copy values */
    strcpy(addressBook->contacts[index].name, newName);
    strcpy(addressBook->contacts[index].phone, newPhone);
    strcpy(addressBook->contacts[index].email, newEmail);

    printf("Contact updated successfully\n");
}
void deleteContact(AddressBook *addressBook)
/*function used to delete contact by selecting index*/
{
    char name[50];
    int index, found = 0;

    printf("Enter the name to delete:\n");
    scanf(" %[^\n]", name);

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].name, name) == 0)
        {
            printf("%d. %s %s %s\n",
                   i,
                   addressBook->contacts[i].name,
                   addressBook->contacts[i].phone,
                   addressBook->contacts[i].email);
            found = 1;
        }
    }

    if (!found)
    {
        printf("Contact Not Found\n");
        return;
    }

    printf("Please enter the choice to delete:\n");
    scanf("%d", &index);

    if (index < 0 || index >= addressBook->contactCount)
    {
        printf("Invalid choice Please enter valid\n");
        return;
    }

    for (int i = index; i < addressBook->contactCount - 1; i++)
    {
        addressBook->contacts[i] = addressBook->contacts[i + 1];
    }

    addressBook->contactCount--;
    printf("Contact deleted successfully\n");
}
