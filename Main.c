#include<stdio.h>
#include<string.h>

struct userDetail{
    char name[50], email[50], address[50], gender;
    int id;
    long contact;
};

int userNum = 0;

void signUp();
void signIn(); //+++++++++++++++++++++++++++
void save(struct userDetail *);
void createThingsToDoFile(int);
void dashboard(char []);
int checkStatus(char);
void printThingsToDo(int);
void addNewThingsToDo(int);
void deleteThingsToDo(int);


int main(){
    char existingUser, newAccount, raw;
    printf("Please enter 'Y' if you have an account else enter 'N' if you don't => ");
    scanf("%c", &existingUser);
    scanf("%c", &raw);
    printf("\n\n=========================================================================\n\n");
    if(existingUser == 'N'|| existingUser == 'n'){
        printf("Do you want to create an account?\n");
        printf("----------------------------------\n");
        printf("Enter 'Y' to create new account else 'N' to exit => ");
        scanf("%c", &newAccount);
        if(newAccount == 'Y' || newAccount == 'y'){
            signUp();
        }
        
        
    }

    return 0;
}


void signIn(){
    return;
}


// Create new account
void signUp(){
    struct userDetail user, *userPointer; 
    userPointer = &user;    //to pass the reference of the data entered by the user
    userNum++;              //increment the value of userNum everytime when a new user SignUp 
    user.id = userNum;      //assign a unique id to every user
    char raw;

    scanf("%c", &raw);
    printf("Enter user name => ");
    gets(user.name);
    printf("Enter email  => ");
    scanf("%50s", user.email);
    scanf("%c", &raw);
    printf("Enter Address  => ");
    gets(user.address);
    printf("Enter Contact number => ");
    scanf("%lu", &user.contact);
    printf("\n\n");
    printf(" __________________________________________\n");
    printf("|You have successfully Created the Account.|\n");
    printf(" ------------------------------------------\n");
    printf("\n============================================\n\n");
    save(userPointer);  //direct the data of user to store in a file
    createThingsToDoFile(user.id);      //creating a file to store the todo list of the id holder only once at the time of signUp
}


// To save the data in the file that has name of user
void save(struct userDetail *user){
    FILE *wf;           //write file
    char fileName[50];
    strcpy(fileName, user->name);
    strcat(fileName, ".txt");   //create a .txt name for storing the  user data in the name.txt file
    wf = fopen(fileName, "w");
    fprintf(wf, "%d \t%s \t%s \t%s \t%lu", user->id,  user->email, user->name, user->address, user->contact);   //store the user detail into the file pointed by wf
    fclose(wf);
    dashboard(fileName);  //Go to the main dashboard 

}


// Create file to store the list of things to do
void createThingsToDoFile(int id){
    FILE *wf;
    char fileName[50];
    sprintf(fileName, "%d", id);        //converting id from int to string
    strcat(fileName, ".txt");           //create fileName with .txt extension
    wf = fopen(fileName, "w");
    fclose(wf);
}


// main dashboard
void dashboard(char fileName[]){
    FILE *rf;       //read file
    int id = 3;
    char name[50], email[50], address[50];
    char c, status;
    // char raw;
    long contact;

    rf = fopen(fileName, "r");
    fscanf(rf, "%d%s%s%s%lu", &id, email, name, address, &contact);     //read data stored in the rf file 
    printf("\nID: %d\n", id);
    printf("Name: %s\n", name);
    printf("---------Things to Do---------\n");
    printThingsToDo(id);     //print things on the ToDo list
    
    // loop until the status is for exit i.e. 'E' or 'e'-----------------------
    while(checkStatus(status) == 0){
        printf("\nPlease enter 'A' if you want to add in the ToDo list: ");
        printf("\nPlease enter 'E' to exit the Dashboard: \n" );
        // scanf("%c", &raw);
        // fflush(stdin);
        status = getchar();
        if(status == 'A' || status == 'a'){
            addNewThingsToDo(id);
            printThingsToDo(id);
        }
        else if(status == 'E' || status == 'e'){
            signIn();
        }
        else if(status == 'D' || status == 'd'){
            deleteThingsToDo(id);
            printThingsToDo(id);
        }
        else{
            printf("Please enter valid character.\n");
            // printThingsToDo(id);
        }
    }
    
    fclose(rf);
}


// check the user status
int checkStatus(char status){
    if(status == 'E' || status == 'e'){
        return 1;
    }
    else{
        return 0;
    }
}


// Print Things to do
void printThingsToDo(int id){
    FILE *rf;
    char fileName[50];
    char c;

    sprintf(fileName, "%d", id);        //converting id from int to string
    strcat(fileName, ".txt");           //create fileName with .txt extension
    rf = fopen(fileName, "r");
    printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    while((c = getc(rf)) != EOF){
        printf("%c", c);
    }
    printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    fclose(rf);
}


// add new things in the existing list of things to do
void addNewThingsToDo(int id){
    FILE *af;
    char fileName[50], content[100];
    char raw;

    sprintf(fileName, "%d", id);        //converting id from int to string
    strcat(fileName, ".txt");           //create fileName with .txt extension
    af = fopen(fileName, "a");
    scanf("%c", &raw);
    printf("Enter what you wish to do: ");
    gets(content);
    fprintf(af, "%s\n", content);
    fclose(af);
}


// delete in the existing list of things to do
void deleteThingsToDo(int id){
    return;
}
