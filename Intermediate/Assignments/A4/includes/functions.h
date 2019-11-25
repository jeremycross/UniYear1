

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
int validListAction(char* act, int upperbound, long int *num);