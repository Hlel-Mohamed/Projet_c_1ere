#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct emp
{
    int id;
    char name[100];
    float salary;
    char gender[10];
    char departement[50];
    char position[10];
    char adress[200];
    char phone[8];
    char email[20];
};

// Welcome
void welcome()
{
    printf("\n\n\n\n\n\t\t\t\t[ Bienvenue ]\n\n\n\n\n\n\n\t");
    system("pause");
}

// Repeat character ch at n times

void repeatChar(char ch, int n)
{
    while (n--)
    {
        putchar(ch);
    }
}

// Printing Head Line of the program

void printHeader()
{
    system("cls");
    printf("\t");
    repeatChar('-', 65);
    printf("\n\t");
    repeatChar(' ', 22);
    printf("GESTION DES EMPLOYEES");
    printf("\n\t");
    repeatChar('-', 65);
}

// String to upper
const char *stringToUpper(char *str,int n)
{
    int i = 0;
    char *up;
    up=malloc(n*sizeof(char));
    for (int i = 0; i < n+1; i++)
    {
        up[i] = toupper(str[i]);
    }
    return up;
}

// Add new employee

void add(FILE *fp)
{
    printHeader();

    printf("\n\t\t\tAjouter Employe");
    char another = 'o';
    struct emp e;

    fseek(fp, 0, SEEK_END);
    while (another == 'o' || another == 'O')
    {
        printf("\n\n\t\tSaisir ID: ");
        scanf("%d", &e.id);

        printf("\n\n\t\tEntrez le nom de l'employe: ");
        fflush(stdin);
        fgets(e.name, 100, stdin);
        e.name[strlen(e.name) - 1] = '\0';

        printf("\n\n\t\tEntrez le sexe: ");
        fflush(stdin);
        fgets(e.gender, 10, stdin);
        e.gender[strlen(e.gender) - 1] = '\0';

        printf("\n\n\t\tEntrez le departement: ");
        fflush(stdin);
        fgets(e.departement, 50, stdin);
        e.departement[strlen(e.departement) - 1] = '\0';

        printf("\n\n\t\tEntrez le poste: ");
        fflush(stdin);
        fgets(e.position, 10, stdin);
        e.position[strlen(e.position) - 1] = '\0';

        printf("\n\n\t\tEntrez le salaire: ");
        scanf("%f", &e.salary);

        printf("\n\n\t\tEnteez l'addresse: ");
        fflush(stdin);
        fgets(e.adress, 200, stdin);
        e.adress[strlen(e.adress) - 1] = '\0';

        printf("\n\n\t\tEnteez le n° de telephone: ");
        fflush(stdin);
        fgets(e.phone, 8, stdin);
        e.phone[strlen(e.phone) - 1] = '\0';

        printf("\n\n\t\tEnteez l'adresse e-mail: ");
        fflush(stdin);
        fgets(e.email, 20, stdin);
        e.email[strlen(e.email) - 1] = '\0';

        fwrite(&e, sizeof(e), 1, fp);

        printf("\n\n\t\tVous souhaitez saisir les informations d’un autre employe ? (O/N)\t");
        fflush(stdin);
        another = getchar();
    }
}

// Delete an employee

FILE *del(FILE *fp)
{
    printHeader();
    printf("\n\t\t\tEffacer un employe");
    struct emp e;
    int flag = 0, tempid, taille = sizeof(e);
    FILE *ft;

    if ((ft = fopen("temp.txt", "wb+")) == NULL)
    {
        printf("\n\n\t\t\t\\t!! ERREUR !!\n\t\t");
        system("pause");
        return fp;
    }

    printf("\n\n\tEntrez le numero d’identification de l’employe à supprimer");
    printf("\n\n\t\t\tID N°: ");
    scanf("%d", &tempid);

    rewind(fp);

    while ((fread(&e, taille, 1, fp)) == 1)
    {
        if (e.id == tempid)
        {
            flag = 1;
            printf("\n\tEnregistrement supprime pour");
            printf("\n\n\t\t%d\n\n\t\t%s\n\n\t\t%s\n\t", e.id, e.departement, e.name);
            continue;
        }

        fwrite(&e, taille, 1, ft);
    }

    fclose(fp);
    fclose(ft);

    remove("employeeInfo.txt");
    rename("temp.txt", "employeeInfo.txt");

    if ((fp = fopen("employeeInfo.txt", "rb+")) == NULL)
    {
        printf("!!! ERREUR !!!");
        return NULL;
    }

    if (flag == 0)
        printf("\n\n\t\tEMPLOYE INTROUVABLE\n\t");

    repeatChar('-', 65);
    printf("\n\t");
    system("pause");
    return fp;
}

// Modify an employee

void modify(FILE *fp)
{
    printHeader();
    printf("\n\t\t\tModifier un employe");
    struct emp e;
    int i, flag = 0, tempid, taille = sizeof(e);

    printf("\n\n\tEntrez le numero d'identification de l'employe pour modifier l'enregistrement : ");
    scanf("%d", &tempid);

    rewind(fp);

    while ((fread(&e, taille, 1, fp)) == 1)
    {
        if (e.id == tempid)
        {
            flag = 1;
            break;
        }
    }

    if (flag == 1)
    {
        fseek(fp, -taille, SEEK_CUR);
        printf("\n\n\t\tEmploye trouve");
        printf("\n\n\t\tEntrez les nouvelles donnees : ");

        printf("\n\n\t\tSaisir ID: ");
        scanf("%d", &e.id);

        printf("\n\n\t\tEntrez le nom de l'employe: ");
        fflush(stdin);
        fgets(e.name, 100, stdin);
        e.name[strlen(e.name) - 1] = '\0';

        printf("\n\n\t\tEntrez le sexe: ");
        fflush(stdin);
        fgets(e.gender, 10, stdin);
        e.gender[strlen(e.gender) - 1] = '\0';

        printf("\n\n\t\tEntrez le departement: ");
        fflush(stdin);
        fgets(e.departement, 50, stdin);
        e.departement[strlen(e.departement) - 1] = '\0';

        printf("\n\n\t\tEntrez le poste: ");
        fflush(stdin);
        fgets(e.position, 10, stdin);
        e.position[strlen(e.position) - 1] = '\0';

        printf("\n\n\t\tEntrez le salaire: ");
        scanf("%f", &e.salary);

        printf("\n\n\t\tEnteez l'addresse: ");
        fflush(stdin);
        fgets(e.adress, 200, stdin);
        e.adress[strlen(e.adress) - 1] = '\0';

        printf("\n\n\t\tEnteez le n° de telephone: ");
        fflush(stdin);
        fgets(e.phone, 8, stdin);
        e.phone[strlen(e.phone) - 1] = '\0';

        printf("\n\n\t\tEnteez l'adresse e-mail: ");
        fflush(stdin);
        fgets(e.email, 20, stdin);
        e.email[strlen(e.email) - 1] = '\0';

        fwrite(&e, sizeof(e), 1, fp);
    }
    else
        printf("\n\n\tEMPLOYE INTROUVABLE");

    printf("\n\n\t");
    system("pause");
}

// Display all employees
void display(FILE *fp)
{
    printHeader();
    printf("\n\t\t\tListe des employes");
    struct emp e;
    int i, taille = sizeof(e);

    rewind(fp);

    while ((fread(&e, taille, 1, fp)) == 1)
    {
        printf("\n\n\t\tID : %d", e.id);
        printf("\n\n\t\tNom : %s", e.name);
        printf("\n\n\t\tSexe : %s", e.gender);
        printf("\n\n\t\tDepartement : %s", e.departement);
        printf("\n\n\t\tPoste : %s", e.position);
        printf("\n\n\t\tSalaire : %.2f", e.salary);
        printf("\n\n\t\tAdresse : %s", e.adress);
        printf("\n\n\t\tTelephone : %s", e.phone);
        printf("\n\n\t\tE-mail : %s", e.email);
        printf("\n\n\t");
        repeatChar('-', 65);
    }
    printf("\n\n\n\t");
    printf("\n\n\t");
    system("pause");
}

// Search for employee
void searchRecord(FILE *fp)
{
    printHeader();
    printf("\n\t\t\tRecherche un employe");
    int tempid, flag;
    struct emp e;
    char another = 'o';

    while (another == 'o' || another == 'O')
    {
        rewind(fp);

        printf("\n\n\tEntrez le numero d'identification pour effectuer une recherche : ");
        scanf("%d", &tempid);

        while ((fread(&e, sizeof(e), 1, fp)) == 1)
        {
            if (e.id == tempid)
            {
                flag = 1;
                break;
            }
        }

        if (flag == 1)
        {
            printf("\n\n\t\tID : %d", e.id);
            printf("\n\n\t\tNom : %s", e.name);
            printf("\n\n\t\tSexe : %s", e.gender);
            printf("\n\n\t\tDepartement : %s", e.departement);
            printf("\n\n\t\tPoste : %s", e.position);
            printf("\n\n\t\tSalaire : %.2f", e.salary);
            printf("\n\n\t\tAdresse : %s", e.adress);
            printf("\n\n\t\tTelephone : %s", e.phone);
            printf("\n\n\t\tE-mail : %s", e.email);
            printf("\n\n\t");
            repeatChar('-', 65);
        }
        else
            printf("\n\n\t\tEMPLOYE INTROUVABLE");

        printf("\n\n\t\tVous souhaitez effectuer une autre recherche ? (O/N)");
        fflush(stdin);
        another = getchar();
    }
}

// Display male
void displayMale(FILE *fp)
{
    printHeader();
    printf("\n\t\t\tListe des employes masculins");
    struct emp e;

    rewind(fp);

    while ((fread(&e, sizeof(e), 1, fp)) == 1)
    {
        char* sexe=stringToUpper(e.gender,10);
        if ((strcmp(sexe, "HOMME") == 0))
        {

            printf("\n\n\t\tID : %d", e.id);
            printf("\n\n\t\tNom : %s", e.name);
            printf("\n\n\t\tPoste : %s", e.position);
            printf("\n\n\t\tTelephone : %s", e.phone);
            printf("\n\t");
            repeatChar('-', 65);
        }
    }
    printf("\n\n\n\t");
    repeatChar('*', 65);
    printf("\n\n\t");
    system("pause");
}

//Display female

void displayFemale(FILE *fp)
{
    printHeader();
    printf("\n\t\t\tList des employe feminins");
    struct emp e;

    rewind(fp);

    while ((fread(&e, sizeof(e), 1, fp)) == 1)
    {
        char* sexe=stringToUpper(e.gender,10);
        if ((strcmp(sexe, "FEMME") == 0))
        {

            printf("\n\n\t\tID : %d", e.id);
            printf("\n\n\t\tNom : %s", e.name);
            printf("\n\n\t\tPoste : %s", e.position);
            printf("\n\n\t\tTelephone : %s", e.phone);
            printf("\n\t");
            repeatChar('-', 65);
        }
    }
    printf("\n\n\n\t");
    repeatChar('*', 65);
    printf("\n\n\t");
    system("pause");
}

//Display contact

void displayContact(FILE *fp)
{
    printHeader();
    printf("\n\t\t\tCoordonnees des employes");
    struct emp e;

    rewind(fp);

    while ((fread(&e, sizeof(e), 1, fp)) == 1)
    {
        printf("\n\n\t\tID : %d", e.id);
        printf("\n\n\t\tNom : %s", e.name);
        printf("\n\n\t\tTelephone : %s", e.phone);
        printf("\n\n\t\tE-mail : %s\n\n\t", e.email);
        repeatChar('-', 65);
    }
    printf("\n\n\n\t");
    printf("\n\n\t");
    system("pause");
}

//Display by departement

void displayBranch(FILE *fp)
{
    printHeader();
    printf("\n\t\t\tAffichage par departement");
    struct emp e;
    char temp[50];
    int test = 1;

    rewind(fp);

    printf("\n\n\t\tEntrez le departement: ");
    fflush(stdin);
    fgets(temp, 50, stdin);
    temp[strlen(temp) - 1] = '\0';
    char* tempDep=stringToUpper(temp,10);

    while ((fread(&e, sizeof(e), 1, fp)) == 1)
    {
        char* dep=stringToUpper(e.departement,10);
        if (strcmp(dep, tempDep) == 0)
        {
            printf("\n\n\t\tID : %d", e.id);
            printf("\n\n\t\tNom : %s", e.name);
            printf("\n\n\t\tPoste : %s", e.position);
            printf("\n\n\t\tTelephone : %s", e.phone);
            printf("\n\n\t\tE-mail : %s", e.email);
            printf("\n\n\t");
            repeatChar('-', 65);
            test = 0;
        }
    }
    if (test)
    {
        printf("\n\t\tIl n'y a personne dans le departement %s!!!", temp);
    }
    printf("\n\n\n\t");
    printf("\n\n\t");
    system("pause");
}

//Display by position

void displayPosition(FILE *fp)
{
    printHeader();
    printf("\n\t\t\tAffichage par poste");
    struct emp e;
    char temp[50];
    int test = 1;

    rewind(fp);

    printf("\n\n\t\tEntrez Poste: ");
    fflush(stdin);
    fgets(temp, 50, stdin);
    temp[strlen(temp) - 1] = '\0';
    char* tempPos=stringToUpper(temp,10);

    while ((fread(&e, sizeof(e), 1, fp)) == 1)
    {
        char* pos=stringToUpper(e.departement,10);
        if (strcmp(pos, tempPos) == 0)
        {
            printf("\n\n\t\tID : %d", e.id);
            printf("\n\n\t\tNom : %s", e.name);
            printf("\n\n\t\tDepartement : %s", e.departement);
            printf("\n\n\t\tTelephone : %s", e.phone);
            printf("\n\n\t\tE-mail : %s", e.email);
            printf("\n\n\t");
            repeatChar('-', 65);
            test = 0;
        }
    }
    if (test)
    {
        printf("\n\t\tIl n'y a personne qui travaille comme %s!!!", temp);
    }
    printf("\n\n\n\t");
    printf("\n\n\t");
    system("pause");
}

//Number of employees

void numEmp(FILE *fp)
{
    printHeader();
    fseek(fp, 0, SEEK_END);

    int n = ftell(fp) / sizeof(struct emp);

    printf("Nombre des employees est %d.", n);
    printf("\n\n\t");
    system("pause");
}

//Main

int main()
{
    FILE *fp;
    struct emp e;
    int option;
    char another;

    if ((fp = fopen("employeeInfo.txt", "rb+")) == NULL)
    {
        if ((fp = fopen("employeeInfo.txt", "wb+")) == NULL)
        {
            printf("Le fichier ne peut pas être ouvert");
            system("pause");
            return 0;
        }
    }
    char username[10], password[10];
    printHeader();
    welcome();
    printHeader();
    printf("\n\t\t\t\t  Ecran de connexion");
    printf("\n\t\t\t      Entrez votre information");
    printf("\n\n\n\t\tNom d'utilisateur: ");
    scanf("%s", username);
    printf("\n\t\tMot de passe: ");
    int i = 0;
    do
    {
        password[i] = getch();
        if (password[i] == 13)
        {
            break;
        }
        else if (password[i] == 8 && i > 0)
        {
            printf("%c%c%c", 8, 32, 8);
            i--;
        }
        else
        {
            printf("*");
            i++;
        }
    } while (password[i] != 13);
    password[i] = '\0';

    if (((strcasecmp(username, "admin")) == 0) && ((strcasecmp(password, "admin") == 0)))
    {
        while (1)
        {
            printHeader();
            printf("\n\t\t\t\tMenu principal");
            printf("\n\n\n");

            printf("\n\n\t\t\t1.  Ajouter un emplye");
            printf("\n\n\t\t\t2.  Effacer un mploye");
            printf("\n\n\t\t\t3.  Modifier un employe");
            printf("\n\n\t\t\t4.  Afficher les employes");
            printf("\n\n\t\t\t5.  Recherche un emplyes");
            printf("\n\n\t\t\t6.  Afficher les coordonnees");
            printf("\n\n\t\t\t7.  Afficher les employes masculins");
            printf("\n\n\t\t\t8.  Afficher les employes feminins");
            printf("\n\n\t\t\t9.  Afficher par departement");
            printf("\n\n\t\t\t10. Afficher par poste");
            printf("\n\n\t\t\t11. Afficher le nombre des employes");
            printf("\n\n\t\t\t0. Sortir");

            printf("\n\n\t\tEntrez votre option :--> ");
            scanf("%d", &option);

            switch (option)
            {
            case 0:
                return 1;
                break;
            case 1:
                add(fp);
                break;
            case 2:
                fp = del(fp);
                break;
            case 3:
                modify(fp);
                break;
            case 4:
                display(fp);
                break;
            case 5:
                searchRecord(fp);
                break;
            case 6:
                displayContact(fp);
                break;
            case 7:
                displayMale(fp);
                break;
            case 8:
                displayFemale(fp);
                break;
            case 9:
                displayBranch(fp);
                break;
            case 10:
                displayPosition(fp);
                break;
            case 11:
                numEmp(fp);
                break;
            default:
                printf("\n\t\tChoix incorrecte");
                printf("\n\t\tProgramme termine");
                sleep(1);
                exit(0);
            }
        }
    }
    else
    {
        printf("\n\t\t\t\tEchec de la connexion");
        sleep(1);
    }

    return 1;
}
