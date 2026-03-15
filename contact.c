#include <stdio.h>
#include <string.h>
#include "contact.h"
#include <ctype.h>
// ANSI color codes for formatted output
#define RED   "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define RESET "\033[0m"
#define BLUE    "\x1b[34m"  
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define BOLD    "\x1b[1m"

/* Function definitions */

//-------------------------------CREATE CONTACT----------------------------------------

int create_contact(AddressBook *addressbook)  //create_contact function definition
{
    char choice; //this choice is for the users to continue the create_contact process or not by giving(Y/N)
    do
    {
        create_name(addressbook); //calling create_name function
        create_num(addressbook);  //calling create_num function
        create_email(addressbook);  //calling create_email function
        printf(GREEN"\n----Successfully created the Contact----\n"RESET); //print success message

        printf(YELLOW"\nDo you want to add another contact details? (y/n): "RESET); //asking the user whether to continue or not
        scanf(" %c", &choice);
    }while(choice == 'y' || choice == 'Y'); //Loop runs until user enteres 'N/n'
    
    return 0;
}

void create_name(AddressBook *addressbook){  //create_name function definition
    char temp_name[32];
    do
    {
        printf("Enter the Name : ");
        scanf(" %[^\n]",temp_name);
    }while(!valid_name(addressbook,temp_name));  //repeat until valid name is found

    strcpy(addressbook->contact_details[addressbook->contact_count].Name,temp_name); //copy the name to the structure 
}

void create_num(AddressBook *addressbook){  //create_num function definition
    char temp_num[11];
    do
    {
        printf("Enter the Mobile Number : ");
        scanf(" %[^\n]",temp_num);
    }while(!valid_num(addressbook,temp_num) || !isunique_num(addressbook,temp_num)); //repeat until valid and unique number is found

    strcpy(addressbook->contact_details[addressbook->contact_count].Mobile_number,temp_num); //copy the number to the structure
}

void create_email(AddressBook *addressbook){  //create_email function definition
    char temp_email[35];
    do
    {
        printf("Enter the Email ID : ");
        scanf(" %[^\n]",temp_email);
    }while(!valid_mail(addressbook,temp_email) || !isunique_mail(addressbook,temp_email)); //repeat until valid and unique email is found
    
    strcpy(addressbook->contact_details[addressbook->contact_count].Mail_ID,temp_email);  //copy the email to the structure

    addressbook->contact_count++;  //Increment contact count after storing the contact deatils of a person
}



//----------------------------------------LIST CONTACT---------------------------------------------------------

void list_contacts(AddressBook *addressbook)  //definition of list_contact function
{
    sort_contacts_by_name(addressbook); //calling the sort_contacts_by_name function to list contacts in alphabetical order

        printf(YELLOW"\n-----------------------------------------------------------------------------------\n"RESET);
        printf("| %-5s | %-20s | %-15s | %-30s |\n", "Sl.No", "NAME", "MOBILE NUMBER", "EMAIL ID");
        printf(YELLOW"-----------------------------------------------------------------------------------\n"RESET);
        for (int i = 0; i < addressbook->contact_count; i++) {  //run the loop until contact_count
             
            print_contact(addressbook, i, i+1);  //calling print_contact function to print the contact detail list
        }
        printf(YELLOW"-----------------------------------------------------------------------------------\n"RESET);
} 
   

//Definition of print_contact function
void print_contact(AddressBook *addressbook, int index, int sl_no) {
    printf("| %-5d | %-20s | %-15s | %-30s |\n",
       sl_no,
       addressbook->contact_details[index].Name,
       addressbook->contact_details[index].Mobile_number,
       addressbook->contact_details[index].Mail_ID);

}

//------------------------------------------------SEARCH CONTACTS--------------------------------------------

int search_contacts(AddressBook *addressbook)  //definition of search_contact function
{   
    int choice; //asking choice for the user to select which searching method to be used
    char cont_choice;  //asking choice for the user for continuing the search process or not 

   do{
        printf(BOLD BLUE "\n--- Search Contact Menu ---\n" RESET);
        printf("\n1.Name \n2.Mobile number\n3.Mail ID\n4.Exit\n");
        printf("Enter the choice:");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                    Search_by_Name(addressbook); //calling Search_by_Name function
                    break;
            case 2:
                    Search_by_Mobile_Num(addressbook);  //calling Search_by_Mobile_NUm function
                    break;
            case 3:
                    Search_by_Email(addressbook); //calling Search_by_Email function
                    break;
            case 4:
                    return 0;  
            default:
                    printf(RED"\nInvalid choice! please try again.\n"RESET);  //print Invalid message when user enters wrong choice

        }
        printf(YELLOW "\nDo you want to search again? (y/n): " RESET);  
        scanf(" %c", &cont_choice);      
    } while(cont_choice == 'y' || cont_choice == 'Y'); //loops until user enter n/N
    return 0;
}

int Search_by_Name(AddressBook *addressbook)    //function definition of Search_by_Name
{
    char name[50];
    int matched_index[100];     // Array to store indices of matching contacts
    int count = 0;   //To keep track of how many matches are found
 
    printf("Enter the name: ");
    scanf(" %[^\n]", name);

    // collect all contacts whose Name exactly matches
    for (int i = 0; i < addressbook->contact_count; i++) {
        if (strcmp(name, addressbook->contact_details[i].Name) == 0) {
            matched_index[count++] = i;   // Store the index if name matches
        }
    }
    
     // No matches found 
    if (count == 0) {
        printf(RED"\nContact not found.\n"RESET);
        return -1;   // Return -1 to indicate failure
    }
    
     // Exactly one match found
    if (count == 1) {
    // ---- single match ----
    printf(GREEN"\nContact found with the name '%s'.\n"RESET, name);
     // Print table header
    printf(YELLOW "-----------------------------------------------------------------------------------\n" RESET);
    printf("| %-5s | %-20s | %-15s | %-30s |\n","Sl.No","NAME", "MOBILE NUMBER", "EMAIL ID");
    printf(YELLOW "-----------------------------------------------------------------------------------\n" RESET);
    print_contact(addressbook, matched_index[0], 1);  // Print the single matched contact
    printf(YELLOW "-----------------------------------------------------------------------------------\n" RESET);
    return matched_index[0];    // Return index of the matching contact
    }
    else
    {
    // Multiple matches: list them all
    printf(GREEN"\nMultiple contacts found with the name '%s'.\n"RESET, name);
    // Print table header
    printf(YELLOW"-----------------------------------------------------------------------------------\n"RESET);
    printf("| %-5s | %-20s | %-15s | %-30s |\n", "Sl.No","NAME", "MOBILE NUMBER", "EMAIL ID");
    printf(YELLOW"-----------------------------------------------------------------------------------\n"RESET);

     // Print all matched contacts one by one
    for (int i = 0; i < count; i++) {
        
        print_contact(addressbook, matched_index[i], i+1);
    }
    printf(YELLOW"-----------------------------------------------------------------------------------\n"RESET);
    }
}

int Search_by_Name_GetIndex(AddressBook *addressbook)  //function defintion of Search_by_Name_GetIndex
{
    char name[50];
    int matched_index[100];  // Array to store indices of matching contacts
    int count = 0;    //To keep track of how many matches are found

    printf("Enter the name: ");
    scanf(" %[^\n]", name);

    // collect all contacts whose Name exactly matches
    for (int i = 0; i < addressbook->contact_count; i++) {
        if (strcmp(name, addressbook->contact_details[i].Name) == 0) {
            matched_index[count++] = i;  // Store the index if name matches
        }
    }
    
     // No matches found
    if (count == 0) {
        printf(RED"\nContact not found.\n"RESET);
        return -1;  // Return -1 to indicate failure
    }
 
    // Exactly one match found
    if (count == 1) {
            printf(GREEN"\nContact found with the name '%s'.\n"RESET, name);
            // Print table header
            printf(YELLOW "-----------------------------------------------------------------------------------\n" RESET);
            printf("| %-5s | %-20s | %-15s | %-30s |\n","Sl.No","NAME", "MOBILE NUMBER", "EMAIL ID"); 
            printf(YELLOW "-----------------------------------------------------------------------------------\n" RESET);
            print_contact(addressbook, matched_index[0], 1);
            printf(YELLOW "-----------------------------------------------------------------------------------\n" RESET);

        return matched_index[0];   // Return index of the matching contact
    }

            printf(GREEN"\nMultiple contacts found with the name '%s'.\n"RESET, name);
            printf(YELLOW"-----------------------------------------------------------------------------------\n"RESET);
            printf("| %-5s | %-20s | %-15s | %-30s |\n", "Sl.No","NAME", "MOBILE NUMBER", "EMAIL ID");
            printf(YELLOW"-----------------------------------------------------------------------------------\n"RESET);
            // Print all matched contacts one by one
            for (int i = 0; i < count; i++) {
                
                print_contact(addressbook, matched_index[i], i+1);
    }
            printf(YELLOW"-----------------------------------------------------------------------------------\n"RESET);

     //this loop is used when we find multiple contacts then to go with mobile number or email id (or)
      // Loop until the user uniquely identifies a contact among duplicates
    while (1) {  
        int choice, index = -1;  // `index` stores the chosen contact index
        printf("1. Enter Mobile Number\n");
        printf("2. Enter Email ID\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:  // Case 1: Search using Mobile Number
                      {
                        char mobile[15];
                        printf("Enter Mobile Number: ");
                        scanf("%s", mobile);

                         // Check among duplicates
                        for (int k = 0; k < count; k++) {
                        if (strcmp(addressbook->contact_details[matched_index[k]].Mobile_number, mobile) == 0) {
                         
                        printf(GREEN"\nContact found with the given mobile number.\n"RESET);
                        printf(YELLOW "-----------------------------------------------------------------------------------\n" RESET);
                        printf("| %-5s | %-20s | %-15s | %-30s |\n","Sl.No","NAME", "MOBILE NUMBER", "EMAIL ID"); 
                        printf(YELLOW "-----------------------------------------------------------------------------------\n" RESET);
                        print_contact(addressbook, matched_index[k], 1);   // Print contact found with this mobile number
                        printf(YELLOW "-----------------------------------------------------------------------------------\n" RESET);  
                        return matched_index[k]; // found inside duplicates
                      }
                     }
                     // If mobile not found among duplicates
                printf(RED"\nThe mobile number isn’t among the duplicates contact details.\n\n"RESET);
                break;
                     }
            case 2:   // Case 2: Search using Email ID
                      {
                        char email[35];
                        printf("Enter Email ID: ");
                        scanf("%s", email);
                        // Check among duplicates
                        for (int k = 0; k < count; k++) {
                        if (strcmp(addressbook->contact_details[matched_index[k]].Mail_ID, email) == 0) {
                             printf(GREEN"\nContact found with the given email.\n"RESET);
                             printf(YELLOW "-----------------------------------------------------------------------------------\n" RESET);
                             printf("| %-5s | %-20s | %-15s | %-30s |\n","Sl.No","NAME", "MOBILE NUMBER", "EMAIL ID"); 
                             printf(YELLOW "-----------------------------------------------------------------------------------\n" RESET);
                             print_contact(addressbook, matched_index[k], 1);  // Print contact found with this email ID
                             printf(YELLOW "-----------------------------------------------------------------------------------\n" RESET);

                        return matched_index[k]; // found inside duplicates
                            }
                        }
                        printf(RED"\nThe email isn’t among the duplicates contact details.\n\n"RESET);
                        break;
                     }
            case 3:  //Exit without choosing
                      printf(YELLOW"Cancelled duplicate selection.\n"RESET);
                       return -1;
            default:
                      printf(RED"Invalid choice. Try again.\n"RESET);  //print invalid choice when wrong choice is given
                      continue;   // skip the rest and go back to the top of the loop
        }
       
       // printf(RED"That contact isn’t one of the duplicates.\n"RESET); //print th invalid message like contact is not of the duplicates
    }
}


 
int Search_by_Mobile_Num(AddressBook *addressbook)  //function definition of Search_by_Mobile_Num
{
    char num[11];
    printf("Enter Mobile Number:");
    scanf(" %[^\n]",num);
    for(int i=0;i<addressbook->contact_count;i++){  //loop until contact_count
        if(strcmp(num,addressbook->contact_details[i].Mobile_number)==0)  //using strcmp compare whether the number searched is in the contact list and if present then print
        {
            printf(GREEN"\nContact found with the given mobile number.\n"RESET);
            printf(YELLOW"-----------------------------------------------------------------------------------\n"RESET);
            printf("| %-5s | %-20s | %-15s | %-30s |\n", "Sl.No","NAME", "MOBILE NUMBER", "EMAIL ID");
            printf(YELLOW"-----------------------------------------------------------------------------------\n"RESET);
            print_contact(addressbook,i, 1);
            printf(YELLOW"-----------------------------------------------------------------------------------\n"RESET);
            return i;  //return the index of first match
        }
    }
    printf(RED"\nContact not found.\n"RESET); //print invalid or Error message
    return -1;
}

int Search_by_Email(AddressBook *addressbook)  //function definition of Search_by_Mobile_Num
{
    char mail[35];
    printf("Enter Mail ID:");
    scanf(" %[^\n]",mail);
    for(int i=0;i<addressbook->contact_count;i++){   //loop until contact_count
        if(strcmp(mail,addressbook->contact_details[i].Mail_ID)==0)  //using strcmp compare whether the mail id searched is in the contact list and if present then print
        {
            printf(GREEN"\nContact found with the given email ID\n"RESET);
            printf(YELLOW"-----------------------------------------------------------------------------------\n"RESET);
            printf("| %-5s | %-20s | %-15s | %-30s |\n", "Sl.No","NAME", "MOBILE NUMBER", "EMAIL ID");
            printf(YELLOW"-----------------------------------------------------------------------------------\n"RESET);
            print_contact(addressbook,i, 1);
            printf(YELLOW"-----------------------------------------------------------------------------------\n"RESET);
            return i; //return the index of first match
        }
    }
    printf(RED"\nContact not found.\n"RESET);  //print invalid or Error message
    return -1;
}


//-------------------------------------------------------EDIT CONTACT----------------------------------------------------

int edit_contact(AddressBook *addressbook)  //function definition of edit_contacts
{
    char cont_choice;  //asking choice for the user for continuing the edit process or not (y/n)

    do  // Outer loop to allow multiple edits 
    {
        
        int index= -1; 

        //This loop ensures a valid contact is selected before editing 
        //keep asking the user to search for a contact until we get a valid index
        while(index == -1) 
    { 
        printf(BOLD BLUE "\n--- Edit Contact Menu ---\n" RESET);
        printf("\n1.Search by Name \n2.Search by Mobile number\n3.Search by Mail ID\n4.Exit\n");
        int choice;
        printf("Enter the choice: ");
        scanf("%d", &choice);
        switch(choice)
    {
        case 1:index=Search_by_Name_GetIndex(addressbook);  //calling Search_by_Name_GetIndex function and also store the returned value in the index
                break;
        case 2:
                index=Search_by_Mobile_Num(addressbook);  //calling Search_by_Mobile_Num function and also store the returned value in the index
                break;
        case 3:
                index=Search_by_Email(addressbook);  //calling Search_by_Email function and also store the returned value in the index
                break;
        case 4:
                return 0; //Exit editing
        default:
                printf(RED"\nInvalid choice.\n"RESET);
    }
    // If contact not found, index remains -1 and loop repeats
    }

    
    // Once a valid contact is selected, ask which field or fields to edit
    int opt;  //asking user the option or choice for which filed to be edited 
    char t_name[30],t_num[11],t_email[30];
    printf("\nWhich field do you want to edit?\n");
    printf("1. Name\n");
    printf("2. Mobile Number\n");
    printf("3. Mail ID\n");
    printf("4. All details (Name, Mobile, Mail)\n");
    printf("Enter the choice: ");
    scanf("%d",&opt);
    switch(opt)
    {
        case 1: //Edit name
                do
                {
                printf("Enter new Name: ");
                scanf(" %[^\n]",t_name);
                } while(!valid_name(addressbook,t_name));  //until the t_name is valid loop it

                strcpy(addressbook->contact_details[index].Name,t_name);  //once the t_name is valid copy it to structure 
                break;
        case 2:  //Edit mobile number
                do
                {
                printf("Enter new Mobile Number: ");
                scanf(" %[^\n]",t_num);
                } while(!valid_num(addressbook,t_num) || !isunique_num(addressbook,t_num)); //loop until the number is valid and unique

                strcpy(addressbook->contact_details[index].Mobile_number,t_num);  //once the t_num is valid copy it to structure
                break;
        case 3:   //Edit Email ID
                do
                {
                printf("Enter new Mail ID: ");
                scanf(" %[^\n]",t_email);
                } while(!valid_mail(addressbook,t_email) || !isunique_mail(addressbook,t_email)); //loop until the email is valid

                strcpy(addressbook->contact_details[index].Mail_ID,t_email);  //once the t_email is valid copy it to structure
                break; 
        case 4:
                //For All details - Edit Name
                do
                {
                printf("Enter new Name: ");
                scanf(" %[^\n]",t_name);
                } while(!valid_name(addressbook,t_name));  //until the t_name is valid loop it
                strcpy(addressbook->contact_details[index].Name,t_name);  //once the t_name is valid copy it to structure

                //For All details - Edit Mobile Number
                do
                {
                printf("Enter new Mobile Number: ");
                scanf(" %[^\n]",t_num);
                } while(!valid_num(addressbook,t_num) || !isunique_num(addressbook,t_num));  //loop until the number is valid and unique
                strcpy(addressbook->contact_details[index].Mobile_number,t_num);  //once the t_num is valid copy it to structure

                ////For All details - Edit Mail ID
                do
                {
                printf("Enter new Mail ID: ");
                scanf(" %[^\n]",t_email);
                } while(!valid_mail(addressbook,t_email) || !isunique_mail(addressbook,t_email));  //loop until the email is valid and unique
                strcpy(addressbook->contact_details[index].Mail_ID,t_email);   //once the t_mail is valid copy it to structure
                break; 
        default:
                printf("Invalid choice.\n");  //if user enters a wrong choice then invalid
                return 0;
    }
    printf(GREEN"\n-------Contact updated successfully------\n"RESET); //print success message when contact updated 

    //Ask if user wants to edit another contact
    printf(YELLOW"\nDo you want to edit another contact? (y/n): "RESET);
    scanf(" %c", &cont_choice);
    } while(cont_choice=='y' || cont_choice=='Y');  // Repeat outer loop if user wants to edit more contacts
    return 0;
}
    


//--------------------------------------------------DELETE CONTACT---------------------------------------------------------------

int delete_contact(AddressBook *addressbook)  //function definition of delete_contact
{
    char continue_choice; //asking choice for the user for continuing the edit process or not (y/n)
    do
    {
    int choice,index=-1;
    char confirm_delete;  //this is used for confirmation before deleting with(y/n)

    while(index == -1) //loop until a valid index is found
    {
    printf(BOLD BLUE "\n--- Delete Contact Menu ---\n" RESET);
    printf("\nFor deleting the contact which search method you want?\n");
    printf("1. By Name\n");
    printf("2. By Mobile Number\n");
    printf("3. By Mail ID\n");
    printf("4. Exit\n");
    printf("Enter the option:");
    scanf("%d", &choice);
    switch(choice)
    {
        case 1:
                index=Search_by_Name_GetIndex(addressbook);  //calling Search_by_Name_GetIndex function and storing the returned value in index
                break;
        case 2:
                index=Search_by_Mobile_Num(addressbook);  //calling Search_by_Mobile_Num function and storing the returned value in index
                break;
        case 3:
                index=Search_by_Email(addressbook);  //calling Search_by_Email function and storing the returned value in index
                break;
        case 4:
                return 0;  //exit
        default:
                printf("Invalid choice.\n");  //prints invalid if user enters wrong choice
    }
    if(index==-1)
    {
         continue; //continue the process if the index is -1 as its not valid index
    }
}

    // Confirm the deletion
    printf(YELLOW"\nAre you sure you want to delete this contact? (y/n): "RESET);
    scanf(" %c",&confirm_delete);

    if(confirm_delete == 'y' || confirm_delete == 'Y')
    {
        for(int i=index;i<addressbook->contact_count-1;i++)
        {
            addressbook->contact_details[i]= addressbook->contact_details[i+1];  //once the user confirms to delete then do shifting so that the particular index contact gets deleted
        }   
            addressbook->contact_count--; //Reduce total contacts count
            printf(GREEN"\nContact deleted successfully!\n"RESET); //print success message
    }
    else
    {
        printf(RED"\nDeletion cancelled.\n"RESET); //Deletion cancelled !
    }
    printf(YELLOW"\nDo you want to delete another contact? (y/n): "RESET); //ask the user if they want to delete one more contact
    scanf(" %c", &continue_choice);
    } while(continue_choice == 'y' || continue_choice == 'Y');  //loop until user selects n/N
    return 0;
}


int valid_name(AddressBook *addressbook,char temp_name[]){  //function definition of valid_name 
    int i=0;
    while(temp_name[i])  // Loop until null terminator '\0' is reached
    {
        if(!(isalpha(temp_name[i]) || temp_name[i]==' '))  // Check if current character is NOT an alphabet and NOT a space 
        {
            printf(RED"\nInvalid Name! Name should contain only Alphabets.\n\n"RESET);  //print invalid message
            return 0;  //invalid name found
            break;
        }
    i++;
    }
    return 1; //valid name
}

int valid_num(AddressBook *addressbook,char temp_num[])  //function definition of valid_num
{
    int i=0;
    if(strlen(temp_num)!=10) // Check if the length of the input number is exactly 10 digits,if not then invalid
        {
            printf(RED"\nInvalid number! Number should contain only 10 digits.\n\n"RESET);
            return 0;
        }
        // Check if the first digit is 6, 7, 8, or 9 (valid starting digits for mobile numbers in India)
    if (!(temp_num[0] == '6' || temp_num[0] == '7' ||
          temp_num[0] == '8' || temp_num[0] == '9')) {
          printf(RED"\nInvalid number! Mobile number must start with 6, 7, 8, or 9.\n\n"RESET);
          return 0;  //return 0 -> invalid number
    }
    while(temp_num[i])
    {
        if(!(isdigit(temp_num[i]))) // Check if the current character is not a digit
        {
            printf(RED"\nInvalid number! Mobile number should contain only digits.\n\n"RESET);
            return 0;   // Return 0 → invalid number
        }
    i++;
    }
    return 1; //valid number entered
}

int isunique_num(AddressBook *addressbook,char temp_num[])  //function definition of isunique_num
{
    // Loop through all existing contacts in the address book
    for(int i=0;i<addressbook->contact_count;i++)
    {
         // Compare the mobile number of the current contact with temp_num
        if(strcmp(addressbook->contact_details[i].Mobile_number,temp_num)==0)
        {
             // If a match is found, number is not unique
                printf(RED"\nMobile Number already exists!, Enter new number.\n\n"RESET);
                return 0;
        }
    }
    return 1; // If no match found, return 1 → unique number entered
}

int valid_mail(AddressBook *addressbook,char temp_email[]) //function definition of valid_mail
{
    int i=0,len=strlen(temp_email);
    int at_count= 0, dot_count= 0, at_pos= -1;

    if(!islower(temp_email[0]))  //first character of Email should always be a lowerscase letter only.Else its Invalid Email
    {
        printf(RED"\nInvalid Email ID. Mail ID must start with a lowercase letter.\n\n"RESET);
        return 0;
    }
    while(temp_email[i]) 
    {
        if(temp_email[i] == '@')  
        {
            at_count++;   //increment the count whenever '@' encountered
            at_pos = i;
        }
        else if(temp_email[i] == '.')  
        {
            dot_count++;  //increment the count whenever '.' encountered
        }
        else if(temp_email[i] == ' ')  //If the Email ID is having space , then that's invalid
        {
            printf(RED"\nInvalid Email ID. Mail ID cannot have spaces.\n\n"RESET);
            return 0;
        }
        else if(!(islower(temp_email[i]) || isdigit(temp_email[i]) || temp_email[i] == '@' || temp_email[i] == '.')) // the Email ID should contain characters like '@' , lowercase letters , digits , '.' only
        {
            printf(RED"\nInvalid Email ID.Mail ID must contain only lowercase letters, digits, one '@' and one '.' allowed.\n\n"RESET);
            return 0;
        }
        i++;
    }
    if(at_count!=1 || dot_count!=1)   // to check whether there is only one '@' in the entire Email ID
    {
        printf(RED"\nInvalid Email ID. Mail ID must contain exactly one '@' and one '.com' \n\n"RESET);
        return 0;
    }

    if(strcmp(temp_email+len-4,".com")!=0)  // to check whether .com is at the end
    {
        printf(RED"\nInvalid Email ID. All Email ID must end with '.com' \n\n"RESET);
        return 0;
    }
    int dot_start_pos= len-4;
    if(dot_start_pos - at_pos <= 1) //there should be atleast 1 character between '@' and ".com"
    {
        printf(RED"\nInvalid Email ID. Email ID shoud contain atleast 1 character between '@' and '.com'\n\n"RESET);
        return 0;
    }
    return 1; //valid Email ID
}


int isunique_mail(AddressBook *addressbook,char temp_email[])  //function definition of isunique_mail
{
    // Loop through all existing contacts in the address book
    for(int i=0;i<addressbook->contact_count;i++)
    {
        // Compare the mail ID of the current contact with temp_email
        if(strcmp(addressbook->contact_details[i].Mail_ID,temp_email)==0)
        {
            // If a match is found, mail ID is not unique
                printf(RED"\nMail ID already exists!, Enter new Mail ID.\n\n"RESET);
                return 0;
        }
    }
    return 1; // If no match found, return 1 → unique mail ID entered
}


void sort_contacts_by_name(AddressBook *addressbook) {
    //  Get the number of contacts in the address book
    int n = addressbook->contact_count;
    for (int i = 0; i < n - 1; i++) {  // Outer loop for bubble sort (runs n-1 times)
        for (int j = 0; j < n - i - 1; j++) {  // Inner loop for comparing adjacent contacts
            if (strcasecmp(addressbook->contact_details[j].Name,
                       addressbook->contact_details[j + 1].Name) > 0) 
            {
                // Swap the entire Contacts structure if names are out of order
                Contacts temp = addressbook->contact_details[j];
                addressbook->contact_details[j] = addressbook->contact_details[j + 1];
                addressbook->contact_details[j + 1] = temp;
            }
        }
    }
}

