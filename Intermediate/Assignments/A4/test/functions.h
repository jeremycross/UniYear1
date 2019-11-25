typedef struct linkedContact{

    unsigned long phone_number;
    char* firstName;
    char* lastName;
    char* comName;
    char* email;
    char* sortStr;

}linkCont;

typedef struct contact{

    unsigned long phone_number;
    long first_name_posn;
    long last_name_posn;
    long company_name_posn;
    long email_posn;
    long next;

}contact;

char* userInput(char*);
linkCont* deleteContact(linkCont*, int, int*);
int validAddAction(char*);
int checkPhoneNum(char*);
int emailCheck(char*);
linkCont* addContact(linkCont*, int*);
int compareStr(const void*, const void*);
int validEditAction(char *);
linkCont* editContact(linkCont*, int, int*);
int validDisplayAction(char*);
linkCont* displayContact(linkCont*, int, int*);
void saveToFile(linkCont*, int);
char* stringFromFile(FILE*);
void listAll(linkCont*, int);
