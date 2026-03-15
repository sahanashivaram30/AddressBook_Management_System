#include "contact.h"
#include<stdio.h>

// ANSI color codes for formatted output
#define RESET   "\x1b[0m"
#define RED     "\x1b[31m"

void load_contacts(AddressBook *addressbook)
{
    FILE *fptr =fopen("contact.txt","r");  // Open file in read mode
    if(fptr==NULL)  // Check if file exists
    { 
        printf(RED"Error: File not found\n"RESET);
        return;
    }
     // Read the total number of contacts (first line starting with #)
    fscanf(fptr,"#%d\n", &addressbook->contact_count);

     // Read each contact's details from the file
    for(int i=0;i<(addressbook->contact_count);i++)
    {
        // Read name, mobile number, and email separated by commas
        fscanf(fptr,"%[^,],%[^,],%[^\n]\n",addressbook->contact_details[i].Name,addressbook->contact_details[i].Mobile_number,addressbook->contact_details[i].Mail_ID);
        
    }
    fclose(fptr);  // Close the file
}


void save_contacts(AddressBook *addressbook)
{
    FILE *fptr =fopen("contact.txt","w");  // Open file in write mode
    if(fptr==NULL)  // Check if file can be opened
    {
        printf(RED"Error: File not found\n"RESET);
        return;
    }
     // Write the total number of contacts as the first line
    fprintf(fptr,"#%d\n",addressbook->contact_count);
    // Write each contact's details in the file
    for(int i=0;i<(addressbook->contact_count);i++)
    {
        fprintf(fptr,"%s,%s,%s\n",addressbook->contact_details[i].Name,addressbook->contact_details[i].Mobile_number,addressbook->contact_details[i].Mail_ID);
        
    }

    fclose(fptr);  // Close the file after writing

}