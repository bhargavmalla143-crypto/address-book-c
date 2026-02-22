#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook)
/* this function is used to save contact details into file*/
{
    FILE *fp = fopen("contacts.csv", "w");
    // open file in write mode
    if (fp == NULL)
    {
        printf("Error opening file for saving\n");
        return;
    }
    fprintf(fp, "#%d\n", addressBook->contactCount);
    // write total number of contacts to file

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(fp, "%s %s %s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
        // write name, phone and email into file
    }

    fclose(fp);
    // close the file
    printf("Contacts saved successfully\n");
}

void loadContactsFromFile(AddressBook *addressBook)
/*this function is used to load contact details from file into array*/
{
    FILE *fp = fopen("contacts.csv", "r");
    // open file in read mode
    if (fp == NULL)
    {
        printf("Error opening file for loading\n");
        return;
    }
    fscanf(fp, "#%d\n", &addressBook->contactCount);
    // read total number of contacts from file

    int i = 0;
    while (fscanf(fp, "%s %s %s\n",
                  addressBook->contacts[i].name,
                  addressBook->contacts[i].phone,
                  addressBook->contacts[i].email) != EOF)
    {
        i++;
        // store each contact into array
    }
    fclose(fp);
    // close the file
}