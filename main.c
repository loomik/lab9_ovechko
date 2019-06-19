#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#define LEN 90
#define N 255

typedef struct GameDev {
    char *name;                 // Name of Game
    char *chapter;              // Type of Chapter
    char *developer;            // Developer of Game
    int date[3];                // Release date
    float Publisherrate;       // Publisher rate of Game
    int Gamersrate;             // Gamers rate of Game
    float bothrate;            // Both rate of Game(gamers and Publishers)
    int Publisher1;             // First Publisher
    int Publisher2;             // Second Publisher
} GameDev;

///////////////////////////////////////////////////////////////////////

int menu();  /// �������� ����
char* newChar(); /// ������������ ������ ��� ����������� �������
int read(GameDev *);   /// ���������� � �����
void output(GameDev *, int ); /// ����� ���������
GameDev* newStruct();  /// �������� ��������� (��������� ������)
void sort_masInt(GameDev *mas, int k, int (*StructName)(GameDev*, int));  /// ���������� 
int menu_char(); /// ���� ��� ������ ����������� ����
int menu_sort(); /// ���� ��� ����������
void function(GameDev *mas, int k); /// ������� ��� ������ ��������� ������
int entry(); /// ������ � ����
void ClearStruct(GameDev *mas); /// ������� ������ ���������

/// ������������� ���������� �� ������� ///

int date1(GameDev *mas, int k); // ����
int date2(GameDev *mas, int k); // �����
int date3(GameDev *mas, int k); // ���


/// �������� ��� ///


int main()
{
    SetConsoleCP(1251); // ��������� ������� �������� win-cp 1251 � ����� �����
    SetConsoleOutputCP(1251); // ��������� ������� �������� win-cp 1251 � ����� ������
    GameDev *Game = NULL;
    int k;
    int menu_ = menu();
    Game = newStruct();
    while (menu_ != 0)
    {
        k = read(Game);
        if (menu_ == 1)
        {
            puts("\n������� ���������: ");
            output(Game, k);
        }
        else if (menu_ == 2)
        {
            function(Game, k);
        }
        else if (menu_ == 3)
        {
            entry();
        }
        else if (menu_ == 4)
        {
            system("cls");
        }
        menu_ = menu();
    }
    ClearStruct(Game);
    puts("\n������� �� �������������!");
    return 0;
}




/// �������: ///

///////////////////////////////////////////////////////////////////////

int menu() // �������� ����
{
    int c = 0;
    puts("\n\n�������� ��������:\n\n1 - ������� ������� ��������\n2 - ������� ��������� �������� "
         "� ��������������� �� ���������� �������� ��������\n"
         "3 - �������� ���������� � ����\n4 - �������� �������\n0 - ��������� �����");
    printf("\n������� ��������: ");
    scanf("%d", &c);
    while ((c != 0) && (c != 1) && (c != 2) && (c != 3) && (c != 4))
    {
        printf("\n������ �����!!! ������� �������� ������: ");
        scanf("%d", &c);
    }
    return c;
}

///////////////////////////////////////////////////////////////////////

char* newChar() // �������� ������ ����������� �������
{
    char* string;
    if((string = (char*)malloc(sizeof(char)*N)) == NULL)
    {
        puts("������ ��������� ������!");
        free(string);
        return 0;
    }
    string[0] = '\0';
    return string;
}

///////////////////////////////////////////////////////////////////////

int read(GameDev *current) // ���������� � �����
{
    FILE *in;
    int k = 0;
    if ((in = fopen("rates.csv", "r")) == NULL)
        printf("������ �������� �����\n");
    else
    {
        while (EOF != fscanf(in, "%[^;];%[^;];%[^;];%d,%d,%d;%f;%d;%f;%d;%d[^\n]", current[k].name, current[k].chapter,
                             current[k].developer, &(current[k].date[0]), &(current[k].date[1]), &(current[k].date[2]),
                             &(current[k].Publisherrate), &(current[k].Gamersrate), &(current[k].bothrate),
                             &(current[k].Publisher1), &(current[k].Publisher2)))
        {
            fgetc(in); //C��������� c ����� ������ � �����
            k++;
        }
        fclose(in);
    }
    return k;
}

///////////////////////////////////////////////////////////////////////

void output(GameDev *current, int k) {  // ����� ���������
    int i;
    printf("______________________________________________________________________________"
           "_______________________________________________________________________________"
           "__________________________________________________\n");
    printf(" Id |Game\t\t|  Chapter\t\t  |  Developer\t\t    |Release date "
           "|Publishers average rating|Gamers average rating|Both average rating|"
           "Rate of first Publisher|Rate of second Publisher|\n");
    printf("___________________________________________________________________________"
           "________________________________________________________________________________"
           "____________________________________________________\n");
    for (i = 0; i < k; i++) {
        printf("|%-3d|%-20s|%-25s|%-25s|%d.%d.%d\t|%-25.2f|%-21d|%-19.2f|%-23d|%-23d|\n", i+1,
               current[i].name, current[i].chapter, current[i].developer, current[i].date[0], current[i].date[1],
               current[i].date[2], current[i].Publisherrate, current[i].Gamersrate, current[i].bothrate,
               current[i].Publisher1, current[i].Publisher2);
        printf("---+--------------------+-------------------------+-------------------------+----"
               "---------+-------------------------+---------------------+-------------------+-----"
               "------------------+-----------------------+\n");
    }
}

///////////////////////////////////////////////////////////////////////

GameDev* newStruct() // �������� ��������� (��������� ������)
{
    GameDev* temp = NULL;
    temp = (GameDev*)malloc(LEN * sizeof(GameDev));
    for (int i = 0; i<LEN; i++) {
        temp[i].name = (char *) malloc(N * sizeof(char));
        temp[i].chapter = (char *) malloc(N * sizeof(char));
        temp[i].developer = (char *) malloc(N * sizeof(char));
    }
    return temp;
}

///////////////////////////////////////////////////////////////////////

int menu_char() // ���� ��� ������ ����������� ����
{
    int c;
    printf("�������� ���������� ���� \n1 - �������� ����\n2 - ����� ���� �� �����\n3 - �����������"
           "\n������� ��������: ");
    scanf("%d", &c);
    while ((c != 3) && (c != 1) && (c != 2))
    {
        printf("\n������ �����!!! ������� �������� ������: ");
        scanf("%d", &c);
    }
    return c;
}

///////////////////////////////////////////////////////////////////////

int menu_sort() // ���� ��� ����������
{
    int c;
    printf("�������� �������� ���� ������� \n1 - ���� ������� ����\n2 - ����� ������� ����"
           "\n3 - ��� ������� ����\n������� ��������: ");
    scanf("%d", &c);
    while ((c != 1) && (c != 2) && (c != 3))
    {
        printf("\n������ �����!!! ������� �������� ������: ");
        scanf("%d", &c);
    }
    return c;
}

///////////////////////////////////////////////////////////////////////

void sort_masInt(GameDev *current, int k, int (*StructName)(GameDev*, int)) // ����������
{
    GameDev temp;
    printf("\n��������������� �� ����������� ���������, � ������� ������������ "
           "������ �������� � ��������� ���������:\n");
    for (int i = 0; i < k - 1; i++) {
        for (int j = 0; j < k - i - 1; j++)
            if (StructName(current, j) > StructName(current, j + 1)) {
                temp = current[j];
                current[j] = current[j + 1];
                current[j + 1] = temp;
            }
    }
    output(current, k);
}

///////////////////////////////////////////////////////////////////////

void function(GameDev *current, int k) // ������� ��� ������ ��������� ������
{
    char *for_search = newChar();
    int h = menu_char(), i, j=0;
    printf("������� �������� ���������� ����������� ����, ������� �� ������ �����: ");
    scanf("%s", for_search);
    GameDev* temp = newStruct();
    if (h == 1)
    {
        for (i=0; i < k; i++)
        {

            if (strcmp(for_search, current[i].name) == 0)
            {
                temp[j] = current[i];

                j++;
            }
        }
    }
    else if (h == 2)
    {
        for (i=0; i < k; i++)
        {
            if (strcmp(for_search, current[i].chapter) == 0)
            {
                temp[j] = current[i];
                j++;
            }
        }
    }
    else if (h == 3)
    {
        for (i=0; i < k; i++)
        {
            if (strcmp(for_search, current[i].developer) == 0)
            {
                temp[j] = current[i];
                j++;
            }
        }
    }
    if (j > 1) {
        int (*pointer[5])(GameDev *, int);
        int m = menu_sort();
        pointer[1] = date1;
        pointer[2] = date2;
        pointer[3] = date3;
        sort_masInt(temp, j, pointer[m]);
        ClearStruct(temp);
    } else if (j == 1)
        output(temp, j);
    else if(j == 0)
        printf("��������� �������� �� �������");
}

///////////////////////////////////////////////////////////////////////

int entry() // ������ ����� ���� � ����
{
    FILE *in;
    char *name = newChar(), *chapter = newChar(), *dev = newChar(), *date = newChar();
    char *Publ = newChar(), *both = newChar(), *gamer = newChar(), *publ1= newChar(), *publ2= newChar();
    in = fopen("rates.csv","a");
    if (in!=NULL)
    {
        printf("\n������� �������� ����: ");
        scanf("%s", name);
        printf("������� ����� ��� ����� ����: ");
        scanf("%s", chapter);
        printf("������� ������������: ");
        scanf("%s", dev);
        printf("������� ���� ������� (������ 01,03,2012(����� �������)): ");
        scanf("%s", date);
        printf("������� ������ ���������� ������� (����� �����): ");
        scanf("%s", Publ);
        printf("������� ������ �������: ");
        scanf("%s", gamer);
        printf("������� ������� ������ ���� (�����): ");
        scanf("%s", both);
        printf("������� ������ ������� ����������� �������: ");
        scanf("%s", publ1);
        printf("������� ������ ������� ����������� �������: ");
        scanf("%s", publ2);
        strcat(name, ";");
        strcat(name, chapter);
        strcat(name, ";");
        strcat(name, dev);
        strcat(name, ";");
        strcat(name, date);
        strcat(name, ";");
        strcat(name, Publ);
        strcat(name, ";");
        strcat(name, gamer);
        strcat(name, ";");
        strcat(name, both);
        strcat(name, ";");
        strcat(name, publ1);
        strcat(name, ";");
        strcat(name, publ2);
        fputs(name, in);
        fputc('\n',in);
    }
    fclose(in);
    puts("������ � ���� ������ �������!\n");
    free(name);
}

///////////////////////////////////////////////////////////////////////


void ClearStruct(GameDev *current) // ������� ���������
{
    free(current->name);
    free(current->chapter);
    free(current->developer);
    current->name=NULL;
    current->chapter=NULL;
    current->developer=NULL;
    free(current);
    current=NULL;
}

///////////////////////////////////////////////////////////////////////

int date1(GameDev *current, int k) // ��������� �� ����
{
    return current[k].date[0];
}

///////////////////////////////////////////////////////////////////////

int date2(GameDev *current, int k) // ��������� �� �����
{
    return current[k].date[1];
}

///////////////////////////////////////////////////////////////////////

int date3(GameDev *current, int k) // ��������� �� ���
{
    return current[k].date[2];
}

///////////////////////////////////////////////////////////////////////






