#include "first_aid.h"

int main(int argc, char **argv)
{
    char *sir = (char*)malloc(3000*sizeof(char));
    LISTA raniti = newl();
    LISTA vindecati = newl();
    int swintch, j;
    bool running = true;
    while(running)
    {
        meniu();
        scanf("%d", &swintch);
        switch(swintch)
        {
        case 1:
            raniti = ins_in_fata(raniti, citirePersoana());
            _getch();
            system("cls");
            break;

        case 2:
            raniti = ins_la_urma(raniti, citirePersoana());
            _getch();
            system("cls");
            break;

        case 3:
            vindecati = ins_in_fata(vindecati, citirePersoana());
            _getch();
            system("cls");
            break;

        case 4:
            vindecati =  ins_la_urma(vindecati, citirePersoana());
            _getch();
            system("cls");
            break;
        case 5:
            puts("\nAfisare lista raniti:");
            printf("nr.\tNume\t\tPrenume\t\tVarsta\t\tAccident\n-------------------------------------------------------------------------\n%s",toStringl(raniti,sir));
            _getch();
            system("cls");
            break;
        case 6:
            puts("\nAfisare lista vindecati: ");
            printf("nr.\tNume\t\tPrenume\t\tVarsta\t\tAccident\n--------------------------------------------------------------------------\n%s",toStringl(vindecati,sir));
            _getch();
            system("cls");
            break;
        case 7:
            raniti = sterge_primul(raniti);
            system("cls");
            break;
        case 8:
            raniti = sterge_ultimul(raniti);
            system("cls");
            break;
        case 9:
            system("cls");
            vindecati = sterge_primul(vindecati);
            break;
        case 10:
            system("cls");
            vindecati = sterge_ultimul(vindecati);
            break;
        case 11:
            j = mutarePers();
            if (j >= nrElem(raniti))
            {
                printf("Pacientul cautat nu exista sau nu este inregistrat in baza de date!");
                _getch();
                system("cls");
                break;
            }
            vindecati = ins_in_fata(vindecati,retPersNdinLista(raniti, j));
            raniti = stergeElementN(raniti, j);
            _getch();
            system("cls");
            break;
        case 12:
            destroyl(raniti);
            raniti = newl();
            system("cls");
            break;
        case 13:
            destroyl(vindecati);
            vindecati = newl();
            system("cls");
            break;
        case 14:
            allSDL();
            secondSDL();
            system("cls");
            break;
        case 15:
            running = false;
            system("cls");
            puts("Programul s-a incheiat cu succes!");
            break;
        default:
            printf("Optiunea aleasa nu se afla in meniu!\n");
            _getch();
            system("cls");
        }
        fflush(stdin);
    }
    destroyl(raniti);
    destroyl(vindecati);
    free(sir);
    return 0;
}



