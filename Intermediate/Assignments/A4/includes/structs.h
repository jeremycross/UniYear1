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
