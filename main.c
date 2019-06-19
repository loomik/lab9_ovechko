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

int menu();  /// Основное меню
char* newChar(); /// Освобождение памяти для символьного массива
int read(GameDev *);   /// Считывание с файла
void output(GameDev *, int ); /// Вывод структуры
GameDev* newStruct();  /// Создание структуры (выделение памяти)
void sort_masInt(GameDev *mas, int k, int (*StructName)(GameDev*, int));  /// Сортировка 
int menu_char(); /// Меню для выбора символьного поля
int menu_sort(); /// Меню для сортировки
void function(GameDev *mas, int k); /// Функция для поиска введенных данных
int entry(); /// Запись в файл
void ClearStruct(GameDev *mas); /// Очистка памяти структуры

/// Использование указателей на функции ///

int date1(GameDev *mas, int k); // день
int date2(GameDev *mas, int k); // месяц
int date3(GameDev *mas, int k); // год


/// Основной код ///


int main()
{
    SetConsoleCP(1251); // установка кодовой страницы win-cp 1251 в поток ввода
    SetConsoleOutputCP(1251); // установка кодовой страницы win-cp 1251 в поток вывода
    GameDev *Game = NULL;
    int k;
    int menu_ = menu();
    Game = newStruct();
    while (menu_ != 0)
    {
        k = read(Game);
        if (menu_ == 1)
        {
            puts("\nТекущая структура: ");
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
    puts("\nСпасибо за использование!");
    return 0;
}




/// Функции: ///

///////////////////////////////////////////////////////////////////////

int menu() // Основное меню
{
    int c = 0;
    puts("\n\nВыберите действие:\n\n1 - Вывести текущую стуктуру\n2 - Вывести выбранные элементы "
         "в отсортированной по выбранному элементу стуктуры\n"
         "3 - Дописать информацию в файл\n4 - Очистить консоль\n0 - Закончить сеанс");
    printf("\nВведите параметр: ");
    scanf("%d", &c);
    while ((c != 0) && (c != 1) && (c != 2) && (c != 3) && (c != 4))
    {
        printf("\nОшибка ввода!!! Введите параметр заново: ");
        scanf("%d", &c);
    }
    return c;
}

///////////////////////////////////////////////////////////////////////

char* newChar() // Создание нового символьного массива
{
    char* string;
    if((string = (char*)malloc(sizeof(char)*N)) == NULL)
    {
        puts("Ошибка выделения памяти!");
        free(string);
        return 0;
    }
    string[0] = '\0';
    return string;
}

///////////////////////////////////////////////////////////////////////

int read(GameDev *current) // Считывание с файла
{
    FILE *in;
    int k = 0;
    if ((in = fopen("rates.csv", "r")) == NULL)
        printf("Ошибка открытия файла\n");
    else
    {
        while (EOF != fscanf(in, "%[^;];%[^;];%[^;];%d,%d,%d;%f;%d;%f;%d;%d[^\n]", current[k].name, current[k].chapter,
                             current[k].developer, &(current[k].date[0]), &(current[k].date[1]), &(current[k].date[2]),
                             &(current[k].Publisherrate), &(current[k].Gamersrate), &(current[k].bothrate),
                             &(current[k].Publisher1), &(current[k].Publisher2)))
        {
            fgetc(in); //Cчитывания c новой строки в файле
            k++;
        }
        fclose(in);
    }
    return k;
}

///////////////////////////////////////////////////////////////////////

void output(GameDev *current, int k) {  // Вывод структуры
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

GameDev* newStruct() // Создание структуры (выделение памяти)
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

int menu_char() // Меню для выбора символьного поля
{
    int c;
    printf("Выберите символьное поле \n1 - Название игры\n2 - Часть игры из серии\n3 - Разработчик"
           "\nВведите параметр: ");
    scanf("%d", &c);
    while ((c != 3) && (c != 1) && (c != 2))
    {
        printf("\nОшибка ввода!!! Введите параметр заново: ");
        scanf("%d", &c);
    }
    return c;
}

///////////////////////////////////////////////////////////////////////

int menu_sort() // Меню для сортировки
{
    int c;
    printf("Выберите числовое поле массива \n1 - День выпуска игры\n2 - Месяц выпуска игры"
           "\n3 - Год выпуска игры\nВведите параметр: ");
    scanf("%d", &c);
    while ((c != 1) && (c != 2) && (c != 3))
    {
        printf("\nОшибка ввода!!! Введите параметр заново: ");
        scanf("%d", &c);
    }
    return c;
}

///////////////////////////////////////////////////////////////////////

void sort_masInt(GameDev *current, int k, int (*StructName)(GameDev*, int)) // сортировка
{
    GameDev temp;
    printf("\nОтсортированная по возрастанию структура, в которой присутствуют "
           "только элементы с выбранным значением:\n");
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

void function(GameDev *current, int k) // функция для поиска введенных данных
{
    char *for_search = newChar();
    int h = menu_char(), i, j=0;
    printf("Введите значение выбранного символьного поля, которое вы хотите найти: ");
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
        printf("Введенное значение не найдено");
}

///////////////////////////////////////////////////////////////////////

int entry() // запись новой игры в файл
{
    FILE *in;
    char *name = newChar(), *chapter = newChar(), *dev = newChar(), *date = newChar();
    char *Publ = newChar(), *both = newChar(), *gamer = newChar(), *publ1= newChar(), *publ2= newChar();
    in = fopen("rates.csv","a");
    if (in!=NULL)
    {
        printf("\nВведите название игры: ");
        scanf("%s", name);
        printf("Введите часть или серию игры: ");
        scanf("%s", chapter);
        printf("Введите разработчика: ");
        scanf("%s", dev);
        printf("Введите дату выпуска (Пример 01,03,2012(через запятую)): ");
        scanf("%s", date);
        printf("Введите оценки популярных изданий (через точку): ");
        scanf("%s", Publ);
        printf("Введите оценки игроков: ");
        scanf("%s", gamer);
        printf("Введите средние оценке игре (точку): ");
        scanf("%s", both);
        printf("Введите оценку первого популярного издания: ");
        scanf("%s", publ1);
        printf("Введите оценку второго популярного издания: ");
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
    puts("Запись в файл прошла успешно!\n");
    free(name);
}

///////////////////////////////////////////////////////////////////////


void ClearStruct(GameDev *current) // Очистка структуры
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

int date1(GameDev *current, int k) // указатель на день
{
    return current[k].date[0];
}

///////////////////////////////////////////////////////////////////////

int date2(GameDev *current, int k) // указатель на месяц
{
    return current[k].date[1];
}

///////////////////////////////////////////////////////////////////////

int date3(GameDev *current, int k) // указатель на год
{
    return current[k].date[2];
}

///////////////////////////////////////////////////////////////////////






