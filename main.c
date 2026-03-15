/****************************************************************************************************************************************
    Name : SAHANA S
    Date : 21/09/2025
    Description : This project is a C-based Address Book application that allows users to create, list, search, edit, and delete contacts. 
                  It validates inputs like name, mobile number, and email while ensuring uniqueness of contact details. 
                  The contacts are displayed in a neatly formatted table and sorted alphabetically by name for easy access during listing. 
                  It provides an interactive menu-driven approach for managing  contact information efficiently. 

                  *Create Contact: Allows the user to add a new contact with name, number, and email.  
                   The entered details are stored in the address book for later use.

                  *Search Contact: Lets the user search for a contact by name, number, or email.  
                   If found, the details of the contact are displayed.

                  *Edit Contact: Enables modification of an existing contact’s details.  
                    The user can update name, number, email or all details for the chosen contact.  

                  *Delete Contact: Removes a contact permanently from the address book.  
                   The record is erased, and the list is shifted to maintain order.
                   
                  *List Contacts: Displays all saved contacts in the address book in sorted order.  
                   Each contact’s name, number, and email are shown in a formatted way. 
                   
                  *Load Contacts: Reads contact data from the "contact.txt" file.  
                   It loads all saved contacts into the address book structure for use.  

                  *Save Contacts: Writes all current contact details into "contact.txt".  
                   Ensures that added, edited, or deleted contacts are saved permanently.
                   

   *************************************************************************************************************************************/

#include <stdio.h>
#include "contact.h"

//ANSI color code
#define RESET   "\x1b[0m"
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define BOLD    "\x1b[1m"


int main()  //start of the program
{
    /* Variable and structre defintion */
    int option; //stores the user's choice
    AddressBook addressbook;   //creating variable of the type AddressBook and initializing memory
    addressbook.contact_count = 0;  //initializing contact count as 0 initially
    load_contacts(&addressbook);  //call the load_contacts function


    while (1)  //loop until users choose to exit
    {
        printf(CYAN BOLD "╔════════════════════════════════╗\n" RESET);
        printf(CYAN BOLD "║       📝 ADDRESS BOOK          ║\n" RESET);

        printf(CYAN BOLD "╠════════════════════════════════╣\n" RESET);

        // Menu options
        printf(MAGENTA "║ 1. Add contact                 ║\n" RESET);
        printf(MAGENTA "║ 2. Search contact              ║\n" RESET);
        printf(MAGENTA "║ 3. Edit contact                ║\n" RESET);
        printf(MAGENTA "║ 4. Delete contact              ║\n" RESET);
        printf(MAGENTA "║ 5. Display contact             ║\n" RESET);
        printf(MAGENTA "║ 6. Save contact                ║\n" RESET);
        printf(MAGENTA "║ 7. Exit                        ║\n" RESET);
        // Box bottom
        printf(CYAN BOLD "╚════════════════════════════════╝\n" RESET);

        printf(GREEN "Enter the option : " RESET);
        scanf("%d", &option);

        switch (option) /* Based on choosed option */
        {
        case 1:
        {
            create_contact(&addressbook);  //calling create_contact function
            break;
        }

        case 2:
        {   
            search_contacts(&addressbook);  //calling search_contact function
            break;
        }
        case 3:    

            edit_contact(&addressbook);   //calling edit_contact function
            break;

        case 4:
        {

            delete_contact(&addressbook);   //calling delete_contact function
            break;
        }
        case 5:
        {
            printf(BOLD CYAN "\n--- List of Contacts ---\n" RESET);
            list_contacts(&addressbook);   //calling list_contact function
            break;
        }
        case 6:
            printf(GREEN "\nSaving contacts...\n" RESET); 
            printf("Contact Saved\n");
            save_contacts(&addressbook); //calling save_contacts function
            break;

        case 7:
            printf(BOLD MAGENTA "\nINFO: Save and Exit...\n" RESET);
            save_contacts(&addressbook);   //calling save_contacts function
            return 0;

        default:
            printf(RED "Invalid option! Please try again.\n" RESET);   //If user enters invalid option
            break;
        }
    }
    return 0;
}
