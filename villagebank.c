#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct bank
{
    int cid;
    char cname[30];
    char uname[30];
    char password[30];
    float balance;
    int transactionCounter;
    struct Bank *next;
    int flag;

} *head = NULL;
void createAccount();
void displayAll();
void displayParticular();
void checkBalance(struct bank *temp1);
void withdraw(struct bank *temp1);
void deposit(struct bank *temp1);
struct bank* login(char user[],char pass[]);
void del(int id);

void main()
{
    int choice, adminChoice, customerChoice;
    struct bank*temp1;
    char user[30];
    char pass[30];
    int id;
    while (1)
    {
    main:
        printf("\n1------Admin");
        printf("\n2------customer user");
        printf("\n3------exit");
        printf("\nEnter your choice");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("\nplease enter username: ");
            fflush(stdin);
            gets(user);
            printf("\n enter password: ");
            gets(pass);
            if (strcmp(user, "ad") == 0 && strcmp(pass, "ad") == 0)
            {
                printf("\n1-------create account");
                printf("\n2-------delete account");
                printf("\n3-------display all");
                printf("\n4-------display particular");
                printf("\n5-------logout");
                printf("\n enter your choice");
                scanf("%d", &adminChoice);
                switch (adminChoice)
                {
                case 1:
                    createAccount();
                    break;
                case 2:
                    // printf("\nEnter the id you want to delete");
                    // scanf("%d", &id);
                    //del(id);
                    break;
                case 3:
                    displayAll();
                    break;
                case 4:
                    // printf("\nEnter the id you want to display particular");
                    // scanf("%d", &id);
                    // displayParticular(id);
                case 5:
                    exit(0);
                default:
                    printf("\ninvalide choice");
                } //end of admin switch
            }
            else
            {
                printf("\ncheck username and password");
                getch();
            }
            break;
        case 2:
            printf("\nplease enter your username : ");
            fflush(stdin);
            gets(user);fflush(stdin);

            printf("\nplease enter your password : ");
            
            gets(pass);
           temp1 = login(user, pass);
            if (temp1!=NULL)
            {
                printf("\nSuccefully login");
                printf("\n1------check balance");
                printf("\n2-------deposit");
                printf("\n3-------withdraw");
                printf("\n4-------logout");
                printf("\nEnter the choice");
                scanf("%d", &customerChoice);
                switch (customerChoice)
                {
                case 1: checkBalance(temp1);
                    break;
                case 2:  deposit(temp1);
                    break;
                case 3: withdraw(temp1);
                    break;
                case 4:
                    exit(0);

                default:
                    printf("\ninvalide choice");

                } //end of switch of customer
            }
            else
            {

                printf("/nuser name and password incorret");
                goto main;
            } //end of else of customer
        case 3:
            exit(0);
        default:
            printf("\ninvalide choice");

        } //end of switch
        goto main;
    } //end of while

} //end of main

void checkBalance(struct bank *temp1){
    printf("\nwelcome mr. %s",temp1->cname);
    printf("\nthe balance is %f",temp1->balance);
    return;
}

void withdraw(struct bank *temp1){
    float with,tempbalance;
    FILE *fp;
    fp=fopen("villagebank.txt", "r");
    printf("\nenter the amount you want to withdraw");
    scanf("%f",&with);
    tempbalance=temp1->balance-with;
    if (tempbalance<=10000)
    {
        printf("\ninsufficient amount\n");
        return;
    }
    temp1->balance=tempbalance;
    fseek(fp,temp1->flag,SEEK_SET);
    fwrite(&temp1,sizeof(temp1),1,fp);
    fclose(fp);
    
}
void deposit(struct bank *temp1){
float dep;
FILE *fp;
 fp=fopen("villagebank.txt", "a");
    printf("\nenter the amount you want to deposit");
    scanf("%f",&dep);
    if (dep>0)
    {
         temp1->balance=temp1->balance+dep;
         fseek(fp,temp1->flag,SEEK_SET);
         fwrite(&temp1,sizeof(temp1),1,fp);
         fclose(fp);

    }else{
        printf("\nnegative deposit not possible");
        return;
    }
    
}

struct bank* login(char user[],char pass[]){
    struct bank*temp;
    int pos;
    FILE *fp;
 fp=fopen("villagebank.txt", "r");
 while ((fread(&temp,sizeof(temp),1,fp)))
 {
            if (strcmp(temp->uname, user) == 0 && strcmp(temp->password, pass) == 0){
     pos=ftell(fp);
    //  printf("\nthe location of this structrure is %d",pos);
    //  fseek(fp,pos-1,SEEK_SET);
    //  pos=ftell(fp);

    printf("\nthe location of this structrure is %d",pos);
    temp->flag=pos-1;
    return temp;
            }//end of if
 }//end of while
 
return NULL;
}// end of login function


void createAccount()
{
    FILE *fp;   //file create structer
    struct bank *temp = head, *temp1;
    if (head == NULL)
    {
        fp = fopen("villagebank.txt", "w");
        head = (struct bank *)malloc(sizeof(struct bank));
        printf("\nEnter the cid");
        scanf("%d", &head->cid);
        printf("\nEnter the customer name");
        fflush(stdin);
        scanf("%s", head->cname);
        printf("\nEnter the customeruser name");
        fflush(stdin);
        scanf("%s", head->uname);
        printf("\nEnter the customer password");
        fflush(stdin);
        scanf("%s", head->password);
        head->balance = 10000;
        head->transactionCounter = 0;
        fwrite(&head, sizeof(head), 1, fp);
        fclose(fp);
    }
    else
    {
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        fp = fopen("villagebank.txt", "a");
        temp1 = (struct bank *)malloc(sizeof(struct bank));
        printf("\nEnter the cid");
        scanf("%d", &temp1->cid);
        printf("\nEnter the customer name");
        fflush(stdin);
        scanf("%s", temp1->cname);
        printf("\nEnter the customeruser name");
        fflush(stdin);
        scanf("%s", temp1->uname);
        printf("\nEnter the customer password");
        fflush(stdin);
        scanf("%s", temp1->password);
        temp1->balance = 10000;
        temp1->transactionCounter = 0;
        fwrite(&temp1, sizeof(temp1), 1, fp);
        fclose(fp);
        temp->next = temp1;
        temp1->next = NULL;
    } //end of else
} //end of create account

void displayAll()
{
    FILE *fp;
    struct bank *temp;
    fp = fopen("villagebank.txt", "r");
    printf("\ncid\t cname\t balance\n");
        temp = (struct bank *)malloc(sizeof(struct bank));

    while (fread(&temp, sizeof(temp), 1, fp))
    {
        printf("\n%d\t%s\t%.2f", temp->cid, temp->cname, temp->balance);
    }
    fclose(fp);
}
