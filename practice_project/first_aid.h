#ifndef FIRST_AID_INCLUDED
#define FIRST_AID_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <SDL2/SDL_keyboard.h>
int mutarePers();
void meniu();
void timp();
struct persoana
{
    char *nume;
    char *prenume;
    int varsta;
    char *accident;
};
typedef struct persoana *PERSOANA;

struct element {
    PERSOANA info;
    struct element *adr_urm;
};
typedef struct element *ELEMENT;

struct lista
{
    int nr;
    ELEMENT primul;
    ELEMENT ultimul;
};

typedef struct lista Lista;
typedef struct lista *LISTA;


LISTA newl();
int nrElem(LISTA l);
LISTA ins_in_fata(LISTA l, PERSOANA x);
LISTA ins_la_urma(LISTA l, PERSOANA x);
PERSOANA retPersNdinLista(LISTA l, int n);
LISTA sterge_primul(LISTA l);
LISTA sterge_ultimul(LISTA l);
LISTA stergeElementN(LISTA l, int n);

bool isEmptyl(LISTA l);
char *toStringl(LISTA l, char *s);
void destroyl(LISTA l);

PERSOANA newPers();
PERSOANA newPersoana(char *nume, char *prenume, int varsta, char *accident);
char *getNume(PERSOANA p);
char *getPrenume(PERSOANA p);
int getVarsta(PERSOANA p);
char *getAccident(PERSOANA p);
void setNume(PERSOANA p, char *nume);
void setPrenume(PERSOANA p, char *prenume);
void setVarsta(PERSOANA p, int varsta);
void setAccident(PERSOANA p, char *accident);
PERSOANA citirePersoana();
void afisPersoana(PERSOANA p);

char *toStringPers(PERSOANA p, char *zona);
void deletePers(PERSOANA p);

////////////////////////////////
void secondSDL();
void resuscitare1();
void resuscitare2();
void hemoragie();
void plagi();
void sufocare1();
void sufocare2();
void sufocare3();
void inec();
void leziuni();
void muscaturi();
void inconstienta();
void allSDL();

#endif // FIRST_AID_INCLUDED
