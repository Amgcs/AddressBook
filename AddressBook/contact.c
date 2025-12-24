#include <stdio.h>  //standard input-output header
#include <stdlib.h> //standard library header 
#include <string.h> //string handling header
#include "contact.h" //user defined header file  
#include "file.h"   //user defined header file
#include "populate.h"   //user defined header file

void listContacts(AddressBook *addressBook)   //function to list the contacts  
{
    // Sort contacts based on the chosen criteria
    printf("\n---------------------------------\n");
    printf("          CONTACT LIST\n");
    printf("---------------------------------\n\n");
    printf("+----+--------------------------+----------------+-------------------------------+\n");
    printf("|%-2s |%-25s |%-15s |%-30s |\n","No.","NAME","PHONE NO","EMAIL");   
    for(int i=0;i<(addressBook->contactCount);i++)  //Loop to print the contact details
    {
        printf("+----+--------------------------+----------------+-------------------------------+\n");
        printf("|%-3d |%-25s |%-15s |%-30s |\n",i+1,
            addressBook->contacts[i].name,
            addressBook->contacts[i].phone,
            addressBook->contacts[i].email);
    }
        printf("+----+--------------------------+----------------+-------------------------------+\n");
}

int validation(AddressBook *addressBook,int op,char str_new[])  //function to check the validation of the contact details
{
    int flag=0;
    switch(op)
    {
        case 1:
                int i=0;
                while(str_new[i]!='\0')
                {
                    if(!((str_new[i]>='A'&&str_new[i]<='Z') || (str_new[i]>='a' && str_new[i]<='z') || (str_new[i]=='.') || (str_new[i]==' '))) //condition to check the name is valid or not
                    {
                        printf("Invalid!\n");
                        flag=1;
                        break;
                    }
                    i++;
                }
                return flag;
        case 2:
                if(strlen(str_new)==10) //to check the phone number consist of 10 digits
                {
                    for(int i=0;i<10;i++)  
                    {
                        if(!(str_new[i]>='0' && str_new[i]<='9'))   //to check the number consist of numbers
                        {
                            flag=1;
                            printf("Invalid\n");
                            break;
                        }
                    }
                }
                else
                {
                    printf("Invalid\n");
                    flag=1;
                }

                if(flag==0)
                {
                    for(int i=0;i<addressBook->contactCount;i++)
                    {
                        if(strcmp(addressBook->contacts[i].phone,str_new)==0)   //condition to check the number already exists or not
                        {
                            flag=1;
                            printf("Phone number already exist\nEnter invalid number\n");
                            break;
                        }   
                    }
                }
                return flag;
        case 3:
                int len =strlen(str_new);
                for(int i=0;i<len;i++)  //validation for email
                {
                    if(!((str_new[i]>='a'&& str_new[i]<='z')    //this is to check if the email not consist of captial letters and special characters
                        ||(str_new[i]>='0'&& str_new[i]<='9') 
                        ||str_new[i]=='.'
                        ||str_new[i]=='_' 
                        ||str_new[i]=='-' 
                        ||str_new[i]=='@'))
                    {
                        flag=1;
                        break;
                    }
                }
                
                char str_g[] = "@gmail.com";  //to check the email consist of @gmail.com  
                if(flag==0)
                    {
                        int j=0;
                        for(int i=len-10;i<len;i++)
                        {
                            if(str_g[j]!=str_new[i])
                            {
                                flag=1;
                                break;
                            }
                            j++;
                        }
                    }
                    if(flag==0)
                            {
                                for(int i=0;i<addressBook->contactCount;i++)
                                {
                                    if(strcmp(addressBook->contacts[i].email,str_new)==0)   //condition to check email already exist or not
                                    {
                                        flag=1;
                                        printf("Phone email already exist\nEnter invalid number\n");
                                        break;
                                    }   
                                }
                            }
                            return flag;

    }

}

void initialize(AddressBook *addressBook)   //function to initialize the contact details
{
    addressBook->contactCount = 0;
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook)  //to save the details of the contact to file
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

void createContact(AddressBook *addressBook)    //function to create contact details
{
	/* Define the logic to create a Contacts */
    printf("\n---------------------------------\n");
    printf("          CREATE CONTACT\n");
    printf("---------------------------------\n\n");
    int flag=0;
    char str_new[100];
    do
    {
        printf("Enter the name: ");
        scanf(" %[^\n]",str_new);
        while (getchar() != '\n');  //to clear input buffer
        flag=validation(addressBook,1,str_new); //function calling for validation of name
        if(flag==0)
        {
            strcpy(addressBook->contacts[addressBook->contactCount].name,str_new);  //entering name details to structure
        }
    }while(flag==1);

    do
    {
        printf("Enter Phone number: ");
        scanf(" %[^\n]",str_new);
        flag=validation(addressBook,2,str_new); //function calling for validation of phone number
        if(flag==0)
        {
            strcpy(addressBook->contacts[addressBook->contactCount].phone,str_new); //entering phone number details to structure
        }
    }while(flag==1);

    do
    {
    printf("Enter email: ");
    scanf(" %[^\n]",str_new);
    flag=validation(addressBook,3,str_new); //function calling for validation of email address
    if(flag==0)
    {
    strcpy(addressBook->contacts[addressBook->contactCount].email,str_new); //entering emailaddress details to structure
    }
    else
        {
            printf("Invalid format\nEnter again\n");
        }
    }while(flag==1);

    printf("\n**CONTACT created successfully**\n");

    addressBook->contactCount++;
}

int search_edit(AddressBook *addressBook,char search_string[],int op,int arr[]) //function to search contact inside file
{
    int i;
    int count=0;    //to get the repeating contacts
    char *pos;
    switch(op)  
    {
                case 1:
                    for(i=0;i<(addressBook->contactCount);i++)
                    {
                        pos=strstr(addressBook->contacts[i].name,search_string);    //comparing name with existing name
                        if(pos!=NULL)
                        {
                            arr[count]=i;
                            count++;
                        }
                    }
                    break;
                case 2:
                        for(i=0;i<(addressBook->contactCount);i++)
                        {
                            pos=strstr(addressBook->contacts[i].phone,search_string);   //comparing  phone number with existing phone number
                            if(pos!=NULL)
                            {
                                arr[count]=i;
                                count++;
                            }
                        }
                        break;
                case 3:
                        for(i=0;i<(addressBook->contactCount);i++)
                        {
                            pos=strstr(addressBook->contacts[i].email,search_string);   //comparing email with existing email
                            if(pos!=NULL)
                            {
                                arr[count]=i;
                                count++;
                            }
                        }
                        break;
    }

            if(count>=1)
            {
                printf("\nSearch results: \n\n");   //printing the search results 
                printf("+----+--------------------------+----------------+-------------------------------+\n");
                printf("|%-2s |%-25s |%-15s |%-30s |\n","No.","NAME","PHONE NO","EMAIL");
                for(i=0;i<count;i++)
                    {
                        int j=arr[i];   //to get the index of the contact 
                        printf("+----+--------------------------+----------------+-------------------------------+\n");
                        printf("|%-3d |%-25s |%-15s |%-30s |\n",i+1,
                                addressBook->contacts[j].name,
                                addressBook->contacts[j].phone,
                                addressBook->contacts[j].email);
                    }
                        printf("+----+--------------------------+----------------+-------------------------------+\n");
            }
            
            if(count==0)    //condition for printing the message if contact not found 
                {    
                    printf("No matching contacts found. Try again.\n");
                }
            return count;
}


void searchContact(AddressBook *addressBook)    //function for search condact details
{
    /* Define the logic for search */
    printf("\n---------------------------------\n");
    printf("          SEARCH CONTACT\n");
    printf("---------------------------------\n\n");
    int choice;
    int count;  
    char *pos;  //to save file address
    int arr[addressBook->contactCount];   //array to save index of multiple contacts 
    char str_search[100];   //search string
    do  //loop for selecting option 
    {
        printf("Select an option to search-");
        printf("\n1-Name\n2-Phone number\n3-Email Address\n4-Exit!\n");
        scanf(" %d",&choice);   //getting choice
        printf("\nSelected Option:- %d\n\n",choice);
        switch(choice)
            {
            case 1: printf("Enter Name:-");
                    scanf(" %[^\n]",str_search);   
                    count=search_edit(addressBook,str_search,1,arr);    // calling search function for name
                    break;
            case 2: printf("Enter phone number:-");
                    scanf(" %[^\n]",str_search);
                    count=search_edit(addressBook,str_search,2,arr);    // calling search function for phone number
                    break;
            case 3: printf("Enter email:-");
                     scanf(" %[^\n]",str_search);
                    count=search_edit(addressBook,str_search,3,arr);    // calling search function for email
                    break;
            case 4:printf("Exiting....\n");
                    break;
            default :
                    printf("Invalid option!\nEnter option again....\n");
            } 
    } while(choice!=4);    //condition to break the loop whenever option 4 is enetered
    
}

void str_edit_1(int choice_1,AddressBook *addressBook,int i)    // function for string editing
{
    char str_edit[100];
    int check=0;
    int flag=0;

     switch(choice_1)
                    {
                        case 1: 
                               do
                                {
                                    printf("Enter the Name: ");
                                    scanf(" %[^\n]",str_edit);  //getting input name
                                    flag=validation(addressBook,1,str_edit);    //calling for name validation
                                    if(flag==0)
                                        {
                                            strcpy(addressBook->contacts[i].name,str_edit);   //calling function for enter name into file 
                                        }
                                }while(flag==1);
                                break;

                        case 2: 
                                do
                                {
                                    printf("Enter the Phone number: ");
                                    scanf(" %[^\n]",str_edit);  //getting new phone number
                                    flag=validation(addressBook,2,str_edit);    //calling for phone number validation
                                    if(flag==0)
                                        {
                                            strcpy(addressBook->contacts[i].phone,str_edit);    //calling function for enter phone number into file
                                        }
                                }while(flag==1);
                                break;
                        case 3:
                                do
                                {
                                    printf("Enter the Email Address: ");
                                    scanf(" %[^\n]",str_edit);  //getting new email
                                    flag=validation(addressBook,3,str_edit);    //calling for email validation
                                    if(flag==0)
                                        {
                                            strcpy(addressBook->contacts[i].email,str_edit);    //calling function for enter email into file 
                                        }
                                }while(flag==1);
                                break;
                        case 4: printf("\nCancel Editing\n");
                                            check=1;
                                            break;
                        default: printf("\nInvalid!\n");
                                            check=1;
                                            break;
                                }
    if(check==0)    //condition to print edited contact it becomes 1 if no editing is done
                        {
                            printf("+----+--------------------------+----------------+-------------------------------+\n");
                            printf("|%-2s |%-25s |%-15s |%-30s |\n","No.","NAME","PHONE NO","EMAIL");
                            printf("+----+ -------------------------+----------------+-------------------------------+\n");
                            printf("|%-3d |%-25s |%-15s |%-30s |\n",1,
                                addressBook->contacts[i].name,
                                addressBook->contacts[i].phone,
                                addressBook->contacts[i].email);
                            printf("+----+--------------------------+-----------------+------------------------------+\n\n");
                            printf("\n**Contact details updated successfully**\n");
                        }
}

void editContact(AddressBook *addressBook)  //contact edit function
{
	/* Define the logic for Editcontact */
    printf("\n---------------------------------\n");
    printf("          EDIT CONTACT\n");
    printf("---------------------------------\n\n");
    char search_string[100];
    int count=0;
    int option;
    int i=0;
    int arr[addressBook->contactCount];
    char choice;
    int choice_1;
    char str_edit[100];
    do
    {
        count=0;
        printf("Search contact to edit by:\n");
        printf("\n1-Name\n2-Phone number\n3-Email Address\n4-Return to main menu\n");
        scanf(" %c",&choice);
        printf("\nSelected Option:- %c\n",choice);


        switch(choice)
        {
            case '1':
                    printf("\nEnter Name: \n");
                    scanf(" %[^\n]",search_string); //getting name for searching
                    count=search_edit(addressBook,search_string,1,arr); //getting count if more than 1 contacts are found in search results
                        if(count>1) //only works if any one contacts found
                        {
                        printf("Enter the number of the contact you want to edit:\n");
                        do
                        {
                                scanf("%d",&option);    //for getting index
                                if(option > count || option <= 0)   //condition for entering only valid index
                                {
                                    printf("Invalid option\nEnter option again: ");
                                }
                        }while(option > count || option <= 0);

                        i=arr[option-1];    
                        }
                        else
                        {
                            i=arr[0];   // works only if only 1 contact is found
                        }
                        if(count>=1)    //to ask the field to edit
                        {
                        do
                            {
                              
                                printf("Select the field to edit:");
                                printf("\n1.Name\n2.Phone number\n3.Email Address\n4.Cancel Editing\n");
                                scanf("%d",&choice_1);
                                str_edit_1(choice_1,addressBook,i); //calling for editing contact
                            } while(choice_1!=4);
                        }
                        break;
            case '2':
                    printf("\nEnter Phone number: \n");
                    scanf(" %[^\n]",search_string);
                    count=search_edit(addressBook,search_string,2,arr);
                        if(count>1)
                        {
                        printf("Enter the number of the contact you want to edit:\n");
                        do
                        {
                                scanf("%d",&option);
                                if(option > count || option <= 0)
                                {
                                    printf("Invalid option\nEnter option again: ");
                                }
                        }while(option > count || option <= 0);

                        i=arr[option-1];
                        }
                        else
                        {
                            i=arr[0];
                        }
                        if(count>=1)
                        {
                        do
                            {
                            
                               printf("Select the field to edit:");
                                printf("\n1.Name\n2.Phone no\n3.email\n4.Cancel Editing\n");
                                scanf("%d",&choice_1);
                                str_edit_1(choice_1,addressBook,i);    //calling for editing contact
                            } while(choice_1!=4);
                        }
                        break;
                    
            case '3':
                    printf("\nEnter Email Address: \n");
                    scanf(" %[^\n]",search_string);
                    count=search_edit(addressBook,search_string,3,arr);
                        if(count>1)
                        {
                        printf("Enter the number of the contact you want to edit:\n");
                        do
                        {
                                scanf("%d",&option);
                                if(option > count || option <= 0)
                                {
                                    printf("Invalid option\nEnter option again: ");
                                }
                        }while(option > count || option <= 0);

                        i=arr[option-1];
                        }
                        else
                        {
                            i=arr[0];
                        }
                        if(count>=1)
                        {
                        do
                            {
                               printf("Select the field to edit:");
                                printf("\n1.Name\n2.Phone number\n3.Email Address\n4.Cancel Editing\n");
                                scanf("%d",&choice_1);
                                str_edit_1(choice_1,addressBook,i);
                            } while(choice_1!=4);
                        }
                        break;
                     
            case '4':printf("Exiting....");
                    break;
            default: printf("\nInvalid option\n");
        }
    }while(choice!='4');
}

void dlt_1(int i,AddressBook *addressBook)  //function for delete contact
{
    for(i;i<(addressBook->contactCount)-1;i++)  //loop for moving adjacent node to previous one
    {
        addressBook->contacts[i]=addressBook->contacts[i+1];    //moving i+1 node to i node
    }
    addressBook->contactCount=(addressBook->contactCount)-1;    //decrementing count 
    printf("\n**DELETION successfull**\n");
}

void deleteContact(AddressBook *addressBook)    //function for deleting contact
{
	/* Define the logic for deletecontact */
    printf("\n---------------------------------\n");
    printf("          DELETE CONTACT\n");
    printf("---------------------------------\n\n");
    int i=0;
    char op;
    int arr[addressBook->contactCount]; //to save contacts if multiple search results are found
    int count=0;
    char *pos;  //to get file base address
    int option;
    char op_inner;
    char dlt_contact[100];  //to get the string for deletion operatin(used for search operation)
   do
   {
        printf("Enter the search method:");
        printf("\n1.Name\n2.Phone number\n3.Email Address\n4.Back to main menu\n");
        scanf(" %c",&op);
        switch(op)
        {
            case '1':printf("Enter the Name:\n");
                    scanf(" %[^\n]",dlt_contact);
                    count=search_edit(addressBook,dlt_contact,1,arr);   //calling search function
                        if(count>1) //if more than one contacts is found in search result 
                        {
                        printf("Enter the number of the contact you want to delete:\n");
                            do
                            {
                                scanf("%d",&option);
                                if(option > count || option <= 0)
                                {
                                    printf("Invalid option\nEnter option again: ");
                                }
                            }while(option > count || option <= 0);

                        i=arr[option-1];    //save the index value
                        }
                        else
                        {
                            i=arr[0];   //if only one contact is present 
                        }
                        if(count>=1)    
                        {
                                printf("\nTo confirm press Y\nTo cancel press N\n");    
                                do
                                {
                                    scanf(" %c",&op_inner);
                                    if(op_inner=='Y' || op_inner=='y')  //to confirm the deletion operation
                                    {
                                        dlt_1(i,addressBook);   //calling delete function for deletion
                                    }
                                    else if(op_inner=='N' || op_inner=='n')
                                    {
                                        printf("\nGoing back to search menu\n");
                                    }
                                    else
                                        printf("Wrong option!\nEnter again\n");
                                }while (op_inner != 'Y' && op_inner != 'y' && op_inner != 'N' && op_inner != 'n');  //condtion to check you entered correct option or not
                        }
                        break;
            case '2':printf("Enter the Phone number:\n");
                    scanf(" %[^\n]",dlt_contact);
                    count=search_edit(addressBook,dlt_contact,2,arr);
                        if(count>1)
                        {
                        printf("Enter the number of the contact you want to delete:\n");
                            do
                            {
                                scanf("%d",&option);
                                if(option > count || option <= 0)
                                {
                                    printf("Invalid option\nEnter option again: ");
                                }
                            }while(option > count || option <= 0);

                        i=arr[option-1];
                        }
                        else
                        {
                            i=arr[0];
                        }
                        if(count>=1)
                        {
                                printf("\nTo confirm press Y\nTo cancel press N\n");
                                do
                                {
                                    scanf(" %c",&op_inner);
                                    if(op_inner=='Y' || op_inner=='y')
                                    {
                                        dlt_1(i,addressBook);
                                    }
                                    else if(op_inner=='N' || op_inner=='n')
                                    {
                                        printf("\nGoing back to search menu\n");
                                    }
                                    else
                                        printf("Wrong option!\nEnter again\n");
                                }while (op_inner != 'Y' && op_inner != 'y' && op_inner != 'N' && op_inner != 'n');
                        }
                        break;
            case '3':printf("Enter the Email Address:\n");
                    scanf(" %[^\n]",dlt_contact);
                    count=search_edit(addressBook,dlt_contact,3,arr);
                        if(count>1)
                        {
                        printf("Enter the number of the contact you want to delete:\n");
                            do
                            {
                                scanf("%d",&option);
                                if(option > count || option <= 0)
                                {
                                    printf("Invalid option\nEnter option again: ");
                                }
                            }while(option > count || option <= 0);

                        i=arr[option-1];
                        }
                        else
                        {
                            i=arr[0];
                        }
                        if(count>=1)
                        {
                                printf("\nTo confirm press Y\nTo cancel press N\n");
                                do
                                {
                                    scanf(" %c",&op_inner);
                                    if(op_inner=='Y' || op_inner=='y')
                                    {
                                        dlt_1(i,addressBook);
                                    }
                                    else if(op_inner=='N' || op_inner=='n')
                                    {
                                        printf("\nGoing back to search menu\n");
                                    }
                                    else
                                        printf("Wrong option!\nEnter again\n");
                                }while (op_inner != 'Y' && op_inner != 'y' && op_inner != 'N' && op_inner != 'n');
                        }
                    break;
            case '4':printf("Exiting....\n");
                        break;
            default:
                        printf("Wrong input!\n");
        }
   }while(op!='4');
}