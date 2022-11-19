#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

int roomAmount(void);
void header(void);
int signIn(void);
void get_hotel(void);
void delay(int sec);
void go_back(void);

char hotel[256];
char tmp[256];

int main(void)
{
    while (true)
    {
        //clear terminal
        system("clear");

        //show header
        header();

        //ask user for num (1 || 2)
        int num = signIn();

        //via Hotel
        if (num == 1)
        {
            //get hotel name
            get_hotel();

            //if doesn't exit create
            fopen("Hotel.txt", "a+");
            FILE *file = fopen("Hotel.txt", "r");
            char line[100];
            char words[100];
            bool found = false;
            char hotelcheck[100];
            strcpy(hotelcheck,hotel);
            strcat(hotelcheck,"\n");
            int hotelRoom = 0;
            char delete;
            char hoteltmp[100];
            strcpy(hoteltmp,hotel);

            //Is hotel name already there?
            while (fgets(line, 100, file))
            {
                if(strcmp(line,hotelcheck) == 0)
                {
                    //if existed do you want to delete it?
                    printf(" Delete all reservation?\n");
                    do
                    {
                        printf(" < Y / N > : ");
                        scanf(" %c", &delete);
                        delete = toupper(delete);
                        if (delete == 'N')
                        {
                            break;
                        }
                        else if (delete == 'Y')
                        {
                            break;
                        }
                    } while (true);

                    //if Y re-write all hotel room to '0' (0 mean vacant)
                    if (delete == 'Y')
                    {
                        file = fopen(strcat(hoteltmp,".txt"),"r");
                        while (fgets(line, 100, file))
                        {
                            hotelRoom++;
                        }
                        fclose(file);

                        file = fopen(hoteltmp,"w");
                        fclose(file);
                        file = fopen(hoteltmp,"a");
                        for (int i = 0; i < hotelRoom; i++)
                        {
                            fputc('0',file);
                            fputs("\n",file);
                        }
                        printf(" Delete all data...\n\n");
                    }
                    else if (delete == 'N')
                    {
                        printf("\n");
                    }

                    found = true;
                }
            }
            fclose(file);

            //if hotelname don't exist
            if (found == false)
            {
                char text[100];
                strcpy(text,hotel);
                strcat(text,".txt");
                fopen(text, "w");

                file = fopen("Hotel.txt", "a");
                fputs(hotel, file);
                fputs("\n", file);
                rewind(file);
                fclose(file);

                int roomQuantity = roomAmount();

                file = fopen(text, "a");
                for(int i = 0; i < roomQuantity; i++)
                {
                    fputc('0', file);
                    fputs("\n", file);
                }
                fclose(file);
                printf("Hotel %s registered.\n\n",hotel);
            }

            go_back();
        }

        //via Guest
        else if (num == 2)
        {
            //get hotelname
            get_hotel();

            FILE *file = fopen("Hotel.txt", "r");
            char line[100];
            char words[100];
            bool found = false;
            char hotelcheck[100];
            bool stop = false;
            strcpy(hotelcheck,hotel);
            strcat(hotelcheck,"\n");

            //Is hotel name already there?
            while (fgets(line, 100, file))
            {
                if(strcmp(line,hotelcheck) == 0)
                {
                    found = true;
                }
            }
            rewind(file);
            fclose(file);

            //if hotelname doesn't exist
            if (found == false)
            {
                printf(" Error This hotel name does not exist.\n");
            }

            //if existed
            else if (found == true)
            {
                char text1[100];
                strcpy(text1,hotel);
                strcat(text1,".txt");
                file = fopen(text1, "r");
                int vacant = 0;
                int room = 0;
                while (fgets(line, 100, file))
                {
                    if(strcmp(line,"0\n") == 0)
                    {
                        //get all vacant room
                        vacant++;
                    }

                    //get all room
                    room++;
                }
                int allRoom = room;
                room -= vacant;
                printf("Room available: %d\n", vacant);
                if (vacant == 0)
                {
                    stop = true;
                    printf("\n");
                }
                fclose(file);

                if (stop == false)
                {
                    char type[100];
                    int roomReserved;
                    do
                    {
                        //get user reserved
                        printf("How many reservation: ");
                        fgets(type, 100, stdin);
                        roomReserved = atoi(type);
                        rewind(stdin);

                        //check range
                        if (roomReserved <= 0 || roomReserved > vacant)
                        {
                            printf("Out of room range...\n");
                        }
                    } while (roomReserved <= 0 || roomReserved > vacant);
                    rewind(stdin);

                    //clear file with w
                    file = fopen(text1, "w");
                    fclose(file);

                    //then append new data
                    file = fopen(text1, "a");
                    num = 0;
                    int num1 = 0;
                    for (int i = 0; i < allRoom; i++)
                    {
                        //unvacant room
                        if (num < roomReserved)
                        {
                            if (num1 < room)
                            {
                                fputc('1',file);
                                fputs("\n",file);
                                num1++;
                            }
                            else
                            {
                                fputc('1',file);
                                fputs("\n",file);
                                num++;
                            }
                        }
                        else
                        {
                            fputc('0',file);
                            fputs("\n",file);
                        }
                    }
                    rewind(file);
                    fclose(file);
                    printf("%d rooms registered\n\n", roomReserved);
                }

                go_back();
            }
        }
        delay(4);
    }

}

void go_back()
{
    delay(3);
    printf("Going back...\n");
    delay(4);
}

void get_hotel(void)
{
    do
    {
        bool check = true;
        printf("\n");
        do
        {
            printf("Enter Hotel name: ");
            fgets(tmp, 256, stdin);

            if (strlen(tmp) >= 3)
            {
                break;
            }
            else
            {
                printf(" Error Hotel name must longer than 2\n\n");
            }
        }
        while(true);


        for(int i = 0; i < strlen(tmp); i++)
        {
            if (i == strlen(tmp) - 1)
            {
                hotel[i] = '\0';
            }
            else
            {
                hotel[i] = toupper(tmp[i]);
            }
            if(hotel[i] == ' ')
            {
                printf("Input Error!!! [No whitespace]\n");
                check = false;
                break;
            }
        }
        if (check == true)
        {
            break;
        }
    } while (true);
}

void delay(int sec)
{
    int add = 0;
    int time;
    time = sec * 100000000;
    for(int i = 0; i < time; i++)
    {
        add+=i;
        add++;
        add++;
    }
}

int signIn(void)
{
    char type[100];
    int num = 0;
    bool sign_count = true;

    do
    {
        //clear terminal
        system("clear");

        //show header
        header();

        if ((num != 1 && num != 2))
        {
            printf(" Sign in as: ");
        }

        fgets(type, 100, stdin);
        num = atoi(type);
        rewind(stdin);
    }
    while(num != 1 && num != 2);

    return num;
}
void header(void)
{
    printf("\n");
    printf("+===============================+\n");
    printf("|                               |\n");
    printf("|        HOTEL-RESERVATION      |\n");
    printf("|                               |\n");
    printf("+===============================+\n\n");
    printf("|     HOTEL > 1    GUEST > 2    |\n\n");
}

int roomAmount(void)
{
    char str[100];
    int amount;
    while (true)
    {
        printf("Room amount: ");
        scanf(" %s", str);
        amount = atoi(str);
        if (amount <= 0)
        {
            printf("Input Error\n");
        }
        else
        {
            break;
        }
    }
    return amount;
}
