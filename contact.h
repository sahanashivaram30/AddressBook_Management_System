#ifndef CONTACT_H
#define CONTACT_H

typedef struct Contact_data
{
    char Name[32];
    char Mobile_number[11];
    char Mail_ID[35];
} Contacts;

typedef struct AddressBook_Data
{
    Contacts contact_details[100];
    int contact_count;
} AddressBook;

/* Function declarations */
void init_intitalization(AddressBook *);
int create_contact(AddressBook *);
void list_contacts(AddressBook *);
int search_contacts(AddressBook *);
int edit_contact(AddressBook *);
int delete_contact(AddressBook *);
void save_contacts(AddressBook *);
void create_name(AddressBook *);
void create_num(AddressBook *);
void create_email(AddressBook *);
int Search_by_Name(AddressBook *);
int Search_by_Mobile_Num(AddressBook *);
int Search_by_Email(AddressBook *);
int valid_name(AddressBook *,char *);
int valid_num(AddressBook *,char *);
int isunique_num(AddressBook *,char *);
int isunique_mail(AddressBook *,char *);
int valid_mail(AddressBook *,char *);
void sort_contacts_by_name(AddressBook *);
void print_contact(AddressBook *,int, int);
int Search_by_Name_GetIndex(AddressBook *);
void load_contacts(AddressBook *);

#endif // CONTACT_H
       // CONTACT_H