#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<time.h>
int cnt=0;
struct Admin
{
    char name[50];
    char password[50];
}ad;
struct date
{
    int day;
    int month;
    int year;
};
struct pdtdet
{
    int id;
    char name[50];
    float price;
    int quantity;
    struct date mfg;
}prdt,s[5]={{1001,"Pendrive",250,92,{12,3,2012}},{1002,"Headphones",599,84,{12,4,2012}},{1003,"Speaker",1500,70,{12,5,2012}},{1004,"Printer",6000,56,{12,6,2012}},{1005,"Wireless mouse",400,65,{12,7,2012}}};;
struct Ord
{
    char unm[50];
    int quantity;
    char prdnm[50];
    int prc;
}o[];
void printHeading()
{
    printf("\n----------------------------------------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t\tONLINE SHOPPING PORTAL\n");
    printf("\n----------------------------------------------------------------------------------------------------------------------\n");

}
void order()
{
    int y;
    int quant,z;

    printf("Do you want to purchase the item?");
    printf("\nEnter \n1-Yes \n2-No\n3-End Purchase\n");
    scanf("%d",&y);
    switch(y)
    {
    case 1:
        printf("Enter Quantity:");
        scanf("%d",&quant);
        o[cnt].quantity=quant;
        printf("\nPress 1 to place order\n");
        cnt++;
        scanf("%d",&z);
        if(z==1)
        {
            system("cls");
            printf("\n\t\tORDER ADDED TO CART\n\n");
            printf("Do you want to continue purchase?");
            int pur;
            printf("\nEnter \n1-Continue purchase \n2-End purchase\n");
            scanf("%d",&pur);
            switch(pur)
            {
            case 1:
                portal();
                break;
            case 2:
                bill();
                break;
            }
        }
        break;

    case 2:
        portal();
       break;
    case 3:
        bill();
        break;
    default:
        printf("Invalid input");
    }
}

void bill()
{
    system("cls");
    int i, j;
    int sum = 0;

    printf("--------------------------------------------------------------------------\n");
    printf("|                             CUSTOMER BILL                               |\n");
    printf("--------------------------------------------------------------------------\n");

    printf("| Customer Name: %s", o[i].unm);
    for (i = 0; i < 49; i++) {
        printf(" ");
    }
    printf("\t|\n");

    printf("--------------------------------------------------------------------------\n");
    printf("| S.No | Quantity |   Product Name   | Product Price  |  Total Price     |\n");
    printf("--------------------------------------------------------------------------\n");

    int serial = 1;
    for (i = 0; i < cnt; i++)
    {
        printf("| %4d. | %8d | %16s | %14d|  %14d  |\n", serial, o[i].quantity, o[i].prdnm, o[i].prc, o[i].quantity * o[i].prc);
        printf("--------------------------------------------------------------------------\n");
        serial++;
        sum += o[i].quantity * o[i].prc;
    }
    printf("|                                                    Grand Total:%7d |\n", sum);
    printf("--------------------------------------------------------------------------\n");
}

void login()
{
    int c;
    printf("\t\t\t\t\tEnter: \n\t\t\t\t\t1-for Admin \n\t\t\t\t\t2-for User:\n\n");
    scanf("%d",&c);
    system("cls");
    switch(c)
    {
    case 1:
        admin(s);
        break;
    case 2:
        usr();
        break;
    default:
        printf("invalid input");
        break;
    }
}
void admin(struct pdtdet s[])
{
     FILE *fptr;
     int av;
    fptr=fopen("Admin.bin","wb");
    struct Admin adm[4]={{"Admin1","Password1"},{"Admin2","Password2"},{"Admin3","Password3"},{"Admin4","Password4"}};
    fwrite(&adm,sizeof(struct Admin),4,fptr);
    fclose(fptr);
    FILE *fpa;
    fpa=fopen("Admin.bin","rb");
    FILE *fpd;
    fpd=fopen("abc.bin","wb");
    int i;
    char inm[50],ips[50];
    fseek(fpa,0,SEEK_SET);
    printf("\n\t\t\t\t\tUsername: ");
    scanf("%s",inm);
    printf("\n\t\t\t\t\tPassword: ");
    scanf("%s",ips);
    fread(&ad,sizeof(struct Admin),4,fpa);
    for(i=0;i<4;i++)
    {
        if(strcmp(adm[i].name,inm)==0 && strcmp(adm[i].password,ips)==0)
        {
            system("cls");
            printf("\t\t\t\t\tEnter\n\t\t\t\t\t1- To view product details\n\t\t\t\t\t2-To view stock unavailabe\n");
            scanf("%d",&av);
            switch(av)
            {
            case 1:
                system("cls");
            fread(&s,sizeof(struct pdtdet),5,fpd);
            printf("\n\n");
            for(i=0;i<5;i++)
            {
                if(i==4)
                printf("\t\t%d \t\t %s \t %.2f \t\t %d\n",s[i].id,s[i].name,s[i].price,s[i].quantity);
                else
                printf("\t\t%d \t\t %s \t\t %.2f \t\t %d\n",s[i].id,s[i].name,s[i].price,s[i].quantity);

            }
            case 2:
                break;
            default :
                printf("Invalid Input");
                break;
            }
        }
    }
    fclose(fpa);
}
void usr()
{
    char un[50];
    printf("Username: ");
    scanf("%s",un);
    strcpy(o[cnt].unm,un);
    captcha();
}
void captcha()
{
     char text[6],ip[6];
    srand(time(0));
    for (int i = 0; i < 6; i++) {
        text[i] = rand() % 60 + '0';
    }
    text[5] = '\0';
    printf("%s\n", text);
    int i;
    printf("\nEnter captcha: ");
    scanf("%s",ip);
    if(strcmp(text,ip)==0)
    {
        portal();
    }
    else
        {
           printf("Wrong captcha!") ;
        }
}
void portal()
{
    FILE *fp;
    fp=fopen("abc.bin","wb");
    fwrite(&s,sizeof(struct pdtdet),5,fp);
    fclose(fp);
    system("cls");
    printf("\n --------------- \t --------------- \n");
    printf("|\t\t|\t|\t\t|");
    printf("\n|  1-Pendrives\t|\t|  2-Headphones\t|");
    printf("\n --------------- \t --------------- \n");

    printf("\n --------------- \t --------------- \n");
    printf("|\t\t|\t|\t\t|");
    printf("\n|  3-Speakers\t|\t|  4-Printers\t|");
    printf("\n --------------- \t --------------- \n");

    printf("\n\t  ------------------- \n");
    printf("\t |\t\t     |");
    printf("\n\t | 5-Wireless mouse  |");
    printf("\n\t  ------------------- \n");

    int x;
    printf("Enter:");
    scanf("%d",&x);
    system("cls");
    switch(x)
    {
    case 1:
        product1(s);

        break;
    case 2:
        product2(s);

        break;
    case 3:
        product3(s);

        break;
    case 4:
        product4(s);

        break;
    case 5:
        product5(s);

        break;
    default:
        printf("Invalid input");
        break;
    }

}

void product1(struct pdtdet x[])
{

    printf("\t\t\t\tPRODUCT SPECIFICATIONS");
    printf("\nName \t\t\t:%s\nStorage\t\t\t:32GB\nHardware Interface\t:2.0 Flash Drive\n\n\tPRICE RS.%.2f\n",x[0].name,x[0].price);
    strcpy( o[cnt].prdnm,x[0].name);
    o[cnt].prc=x[0].price;
    order();

}

void product2(struct pdtdet x[])
{

    printf("\t\t\t\tPRODUCT SPECIFICATIONS");
    printf("\nName \t\t\t:%s\nColour\t\t\t:Blue\nConnector Type\t\t:3.5mm Jack\nSpecial Feature\t\t:Microphone included\n\n\tPRICE RS.%.2f\n",x[1].name,x[1].price);
    strcpy( o[cnt].prdnm,x[1].name);
    o[cnt].prc=x[1].price;
    order();

}

void product3(struct pdtdet x[])
{
    printf("\t\t\t\tPRODUCT SPECIFICATIONS");
    printf("\nName \t\t\t:%s\nType\t\t\t:Outdoor\nConnector Type\t\t:Bluetooth, Auxilary, Wireless\nCompatible Devices\t:Laptop, Tablet, Smartphone\n\n\tPRICE RS.%.2f\n",x[2].name,x[2].price);
      strcpy( o[cnt].prdnm,x[2].name);
      o[cnt].prc=x[2].price;
      order();

}

void product4(struct pdtdet x[])
{
     printf("\t\t\t\tPRODUCT SPECIFICATIONS");
    printf("\nName \t\t\t:%s\nType\t\t\t:Inkjet\nPrint Speed(colour)\t:4 ppm\nColour\t\t\t:White\n\n\tPRICE RS.%.2f\n",x[3].name,x[3].price);
     strcpy( o[cnt].prdnm,x[3].name);
     o[cnt].prc=x[3].price;
     order();

}

void product5(struct pdtdet x[])
{
     printf("\t\t\t\tPRODUCT SPECIFICATIONS");
    printf("\nName \t\t\t:%s\nColour\t\t\t:Black\nConnector Type\t\t:USB\nMovement Detection \nTechnology\t\t:Optical\n\n\tPRICE RS.%.2f\n",x[4].name,x[4].price);
    strcpy( o[cnt].prdnm,x[4].name);
    o[cnt].prc=x[4].price;
    order();

}

int main()
{
    printHeading();
    login();

}
