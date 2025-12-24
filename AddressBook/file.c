#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) 
{
    FILE *fp=fopen("contacts.txt","w"); //file pointer  /opening in write mode
    fprintf(fp,"%d\n",addressBook->contactCount);   //to save contactcount into file
    for(int i=0;i<addressBook->contactCount;i++)       //to save the contact details to file
    {
        fprintf(fp,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fp); 
}

void loadContactsFromFile(AddressBook *addressBook)     //function for load contacts
{
    int i;
    FILE *fp=fopen("contacts.txt","r"); //opening file in read mode
    fscanf(fp,"%d\n",&addressBook->contactCount);   //to read contacts count from the file
    for(i=0;i<addressBook->contactCount;i++)    //to read the contact details from the file
    {
        fscanf(fp,"%[^,],%[^,],%[^\n]\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fp);
}
