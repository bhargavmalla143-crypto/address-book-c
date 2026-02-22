#ifndef FILE_H
#define FILE_H

#include "contact.h"

void saveContactsToFile(AddressBook *addressBook);
/*function used to save all contacts into file*/
void loadContactsFromFile(AddressBook *addressBook);
/*function used to load contacts from file into array*/

#endif
