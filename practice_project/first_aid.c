#include "first_aid.h"

int mutarePers()
{
     int j;
     printf("Introduceti indicele pacientului: \n");
     scanf("%d",&j);
     return j;
}
void meniu()
{
    timp();
    printf("\n------------< MENIU >------------\n");
    puts("1. Adaugare ranit la inceputul listei");
    puts("2. Adaugare ranit la sfarsitul listei");
    puts("3. Adaugare vindecat la inceputul listei");
    puts("4. Adaugare vindecat la sfarsitul listei");
    puts("5. Afisare lista raniti");
    puts("6. Afisare lista vindecati");
    puts("7. Eliminare ranit de la inceputul listei");
    puts("8. Eliminare ranit de la sfarsitul listei");
    puts("9. Eliminare vindecat de la inceputul listei");
    puts("10. Eliminare vindecat de la sfarsitul listei");
    puts("11. Mutare pacient ranit la lista de vindecati");
    puts("12. Golire lista raniti");
    puts("13. Golire lista vindecati");
    puts("14. Deschideti un meniu cu cateva instructiuni de prim ajutor-->");
    puts("15. Terminare program");
    printf("Introduceti functia dorita: ");
}
void timp()
{
    time_t mytime = time(NULL);
    char * time_str = ctime(&mytime);
    time_str[strlen(time_str)-1] = '\0';
    printf("Ora si data deschiderii programului: %s\n", time_str);
}
LISTA newl()
{
    LISTA header = (LISTA) malloc(sizeof(Lista));
    if(header != NULL)
    {
        header->nr = 0;
        header->primul = NULL;
        header->ultimul = NULL;
    }
    return header;
}

int nrElem(LISTA l)
{
    assert(l!=NULL);
    return l->nr;
}

static ELEMENT creareElement(PERSOANA x, ELEMENT urmator)
{
    ELEMENT w =  (ELEMENT )malloc( sizeof(ELEMENT) );
    if(w!=NULL)
    {
        w->info = x;
        w->adr_urm  = urmator;
    }
    return w;
}

LISTA ins_in_fata(LISTA l, PERSOANA x)
{
    assert(l!=NULL);

    ELEMENT w = creareElement(x, l->primul);
    if (w!=NULL)
    {
        l->primul = w;
        if(l->ultimul == NULL)
            l->ultimul = w;
        l->nr++;
    }
    return  l;
}
LISTA ins_la_urma(LISTA l, PERSOANA x)
{
    assert(l!=NULL);

    ELEMENT w = creareElement(x, NULL);
    if(w!=NULL)
    {
        if(isEmptyl(l))
        {
            l->primul = l->ultimul = w;
        }
        else
        {
            l->ultimul->adr_urm = w;
            l->ultimul = w;
        }
        l->nr++;
    }
    return l;
}
LISTA sterge_ultimul(LISTA l)
{
    assert(l!=NULL);
    if(isEmptyl(l))
        return l;
    l->nr--;
    if(l->primul == l->ultimul)   //este unicul element
    {
        free(l->primul);
        l->primul = l->ultimul = NULL;
    }
    else               // sunt cel putin 2 elemente
    {
        ELEMENT p;
        for(p=l->primul; p->adr_urm!=l->ultimul; p = p->adr_urm) ;
        // p adresa penultimului element
        free(l->ultimul );  // elimina ultimul
        p->adr_urm = NULL; // penultimul devine ultimul
        l->ultimul = p;
    }
    return l;
}
PERSOANA retPersNdinLista(LISTA l, int n)
{
    assert(l!=NULL);
    ELEMENT curent = l->primul;
    int count = 0;
    while(curent != NULL)
    {
        if (count == n)
            return curent->info;
        count++;
        curent = curent->adr_urm;

    }
}

LISTA stergeElementN(LISTA l, int n)
{
    assert(l!=NULL);
    ELEMENT temp = l->primul;
    if (n == 0)
    {
        l = sterge_primul(l);
        return l;
    }
    for (int i = 0; temp != NULL&& i<n-1; i++)
        temp = temp->adr_urm;
    if (temp == NULL || temp->adr_urm == NULL)
        return l;
    ELEMENT urm = temp->adr_urm->adr_urm;
    free(temp->adr_urm);
    temp->adr_urm = urm;
    return l;
}
LISTA sterge_primul(LISTA l)
{
    assert(l!=NULL);

    if(l->primul!=NULL)
    {
        l->nr--;
        ELEMENT p = l->primul->adr_urm;
        free(l->primul);
        l->primul = p;
        if(l->primul == NULL )  // lista a devenit vida
            l->primul=NULL;
    }
    return l;
}

void destroyl(LISTA l)
{
    ELEMENT e, p;
    if(l==NULL || l->primul==NULL)
        return;

    e= l->primul;
    while(e!=NULL)
    {
        p=e;
        e = e->adr_urm;
        free(p);
    }
}
bool isEmptyl(LISTA l)
{
    return nrElem(l)==0;
}

char *toStringl(LISTA l,char *s)
{
    int count = 0;
    char buf[3000];
    char bufinfo[100];
    sprintf(s, "", l);
    assert(l!=NULL);

    if(isEmptyl(l))
    {
        strcat(s, "\b Lista este vida!\n ");
    }
    else
    {
        ELEMENT p;
        for(p=l->primul; p!=NULL; p = p->adr_urm)
        {
            sprintf(buf,  "%d.\t%s%c", count,toStringPers(p->info, bufinfo),p==l->ultimul ?'\b':'\b');
            strcat(s, buf);
            count++;
        }
    }
    return s;
}

//
// COD PERSOANA
//

PERSOANA newPers()
{
    PERSOANA p = (PERSOANA)calloc(1,sizeof(struct persoana));
    assert(p!=NULL);
    return p;
}
PERSOANA newPersoana(char *nume, char *prenume, int varsta, char *accident)
{
    PERSOANA p = newPers();
    setNume(p, nume);
    setPrenume(p, prenume);
    setVarsta(p, varsta);
    setAccident(p, accident);
    return p;
}
char *getNume(PERSOANA p)
{
    assert(p!=NULL);
    return p->nume;
}
char *getPrenume(PERSOANA p)
{
    assert(p!=NULL);
    return p->prenume;
}
int getVarsta(PERSOANA p)
{
    assert(p!=NULL);
    return p->varsta;
}
char *getAccident(PERSOANA p)
{
    assert(p!=NULL);
    return p->accident;
}
char *alocaText(char *text)
{
    char *sir = (char*)malloc(strlen(text)+1);
    assert(sir!=NULL);
    strcpy(sir, text);
    return sir;
}
void setNume(PERSOANA p, char *nume)
{
    assert(p!=NULL && nume!=NULL);
    p->nume = alocaText(nume);
}
void setPrenume(PERSOANA p, char *prenume)
{
    assert(p!=NULL && prenume!=NULL);
    p->prenume = alocaText(prenume);
}
void setVarsta(PERSOANA p, int varsta)
{
    assert(p!=NULL);
    p->varsta = varsta;
}
void setAccident(PERSOANA p, char *accident)
{
    assert(p!=NULL && accident != NULL);
    p->accident = alocaText(accident);
}
char *toStringPers(PERSOANA p, char *zona)
{
    assert(p!=NULL);
    sprintf(zona,"%s\t%s\t\t%d\t\t%s", p->nume, p->prenume, p->varsta, p->accident);
    return zona;
}
void deletePers(PERSOANA p)
{
    if(p!=NULL)
    {
        free(p->nume);
        free(p->prenume);
        free(p);
    }
}
PERSOANA citirePersoana()
{

    char nume[25];
    char prenume[25];
    int varsta;
    char accident[20];
    puts("Nume: ");
    scanf("%s", &*nume);
    puts("Prenume: ");
    scanf("%s",&*prenume);
    puts("Varsta:");
    scanf("%d",&varsta);
    fflush(stdin);
    puts("Accident:");
    fgets(accident,20,stdin);
    PERSOANA p = newPersoana(nume,prenume,varsta, accident);
    return p;
}
//////////////////////////////////////////////////////////
void secondSDL()
{
    //Initialize SDL
    SDL_Init(SDL_INIT_VIDEO);

    //Get desktop resolution
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);


    //Create an SDL window
    SDL_Window *window = SDL_CreateWindow("<Primul ajutor>", 0, 0, DM.w, DM.h, SDL_WINDOW_OPENGL);

    //Create renderer(accelerated and in sync with the display refresh rate)
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    //Initialize support for loading PNG and JPEG images
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

    //Load an image file
    SDL_Surface *image = IMG_Load("poze_proiect/menu_aid.png");
    SDL_Texture *image_texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);

    //Define where on the "screen" we want to draw the texture
    SDL_Rect texture_destination;
    texture_destination.x = 0;
    texture_destination.y = 0;
    texture_destination.w = 900;
    texture_destination.h = 800;

    bool running = true;
    SDL_Event event;
    while (running)
    {
        //process events
        while(SDL_PollEvent(&event))
        {

            if(event.type == SDL_KEYDOWN )
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_1:
                    resuscitare1();
                    break;
                case SDLK_2:
                    hemoragie();
                    break;
                case SDLK_3:
                    plagi();
                    break;
                case SDLK_4:
                    sufocare1();
                    break;
                case SDLK_5:
                    inec();
                    break;
                case SDLK_6:
                    leziuni();
                    break;
                case SDLK_7:
                    muscaturi();
                    break;
                case SDLK_8:
                    inconstienta();
                    break;
                case SDLK_i:
                    running = false;
                    break;
                }
                break;
            }

        }
        //clear screen with black
        SDL_RenderClear(renderer);

        //Draw
        SDL_RenderCopy(renderer, image_texture, NULL, &texture_destination);

        //show what was drawn
        SDL_RenderPresent(renderer);

    }
    //Release resources
    SDL_DestroyTexture(image_texture);
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
void resuscitare1()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    SDL_Window *window = SDL_CreateWindow("<Primul ajutor>", 0, 0, DM.w, DM.h, SDL_WINDOW_OPENGL);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    SDL_Surface *image = IMG_Load("poze_proiect/resuscitare1.png");
    SDL_Texture *image_texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    SDL_Rect texture_destination;
    texture_destination.x = 0;
    texture_destination.y = 0;
    texture_destination.w = DM.w;
    texture_destination.h = DM.h;
    bool running = true;
    SDL_Event event;
    while (running)
    {
        while(SDL_PollEvent(&event))
        {

            if(event.type == SDL_KEYDOWN )
            {
                resuscitare2();
                running = false;
            }
        }
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, image_texture, NULL, &texture_destination);
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyTexture(image_texture);
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);


}
void resuscitare2()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    SDL_Window *window = SDL_CreateWindow("<Primul ajutor>", 0, 0, DM.w, DM.h, SDL_WINDOW_OPENGL);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    SDL_Surface *image = IMG_Load("poze_proiect/resuscitare2.png");
    SDL_Texture *image_texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    SDL_Rect texture_destination;
    texture_destination.x = 0;
    texture_destination.y = 0;
    texture_destination.w = DM.w;
    texture_destination.h = DM.h;
    bool running = true;
    SDL_Event event;
    while (running)
    {
        while(SDL_PollEvent(&event))
        {

            if(event.type == SDL_KEYDOWN )
            {
                running = false;
            }
        }
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, image_texture, NULL, &texture_destination);
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyTexture(image_texture);
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

}
void hemoragie()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    SDL_Window *window = SDL_CreateWindow("<Primul ajutor>", 0, 0, DM.w, DM.h, SDL_WINDOW_OPENGL);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    SDL_Surface *image = IMG_Load("poze_proiect/hemoragie.png");
    SDL_Texture *image_texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    SDL_Rect texture_destination;
    texture_destination.x = 0;
    texture_destination.y = 0;
    texture_destination.w = DM.w;
    texture_destination.h = DM.h;
    bool running = true;
    SDL_Event event;
    while(running)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type==SDL_KEYDOWN)
            {
                running = false;
            }

        }
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, image_texture, NULL, &texture_destination);
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyTexture(image_texture);
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    //
}
void plagi()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    SDL_Window *window = SDL_CreateWindow("<Primul ajutor>", 0, 0, DM.w, DM.h, SDL_WINDOW_OPENGL);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    SDL_Surface *image = IMG_Load("poze_proiect/plagi.png");
    SDL_Texture *image_texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    SDL_Rect texture_destination;
    texture_destination.x = 0;
    texture_destination.y = 0;
    texture_destination.w = DM.w;
    texture_destination.h = DM.h;
    bool running = true;
    SDL_Event event;
    while(running)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type==SDL_KEYDOWN)
            {
                running = false;
            }

        }
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, image_texture, NULL, &texture_destination);
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyTexture(image_texture);
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    //
}
void sufocare1()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    SDL_Window *window = SDL_CreateWindow("<Primul ajutor>", 0, 0, DM.w, DM.h, SDL_WINDOW_OPENGL);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    SDL_Surface *image = IMG_Load("poze_proiect/sufocare1.png");
    SDL_Texture *image_texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    SDL_Rect texture_destination;
    texture_destination.x = 0;
    texture_destination.y = 0;
    texture_destination.w = DM.w;
    texture_destination.h = DM.h;
    bool running = true;
    SDL_Event event;
    while (running)
    {
        while(SDL_PollEvent(&event))
        {

            if(event.type == SDL_KEYDOWN )
            {
                sufocare2();
                running = false;
            }
        }
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, image_texture, NULL, &texture_destination);
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyTexture(image_texture);
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}
void sufocare2()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    SDL_Window *window = SDL_CreateWindow("<Primul ajutor>", 0, 0, DM.w, DM.h, SDL_WINDOW_OPENGL);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    SDL_Surface *image = IMG_Load("poze_proiect/sufocare2.png");
    SDL_Texture *image_texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    SDL_Rect texture_destination;
    texture_destination.x = 0;
    texture_destination.y = 0;
    texture_destination.w = DM.w;
    texture_destination.h = DM.h;
    bool running = true;
    SDL_Event event;
    while (running)
    {
        while(SDL_PollEvent(&event))
        {

            if(event.type == SDL_KEYDOWN )
            {
                resuscitare2();
                running = false;
            }
        }
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, image_texture, NULL, &texture_destination);
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyTexture(image_texture);
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}
void sufocare3()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    SDL_Window *window = SDL_CreateWindow("<Primul ajutor>", 0, 0, DM.w, DM.h, SDL_WINDOW_OPENGL);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    SDL_Surface *image = IMG_Load("poze_proiect/sufocare3.png");
    SDL_Texture *image_texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    SDL_Rect texture_destination;
    texture_destination.x = 0;
    texture_destination.y = 0;
    texture_destination.w = DM.w;
    texture_destination.h = DM.h;
    bool running = true;
    SDL_Event event;
    while (running)
    {
        while(SDL_PollEvent(&event))
        {

            if(event.type == SDL_KEYDOWN )
            {
                running = false;
            }
        }
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, image_texture, NULL, &texture_destination);
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyTexture(image_texture);
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}
void inec()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    SDL_Window *window = SDL_CreateWindow("<Primul ajutor>", 0, 0, DM.w, DM.h, SDL_WINDOW_OPENGL);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    SDL_Surface *image = IMG_Load("poze_proiect/inec.png");
    SDL_Texture *image_texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    SDL_Rect texture_destination;
    texture_destination.x = 0;
    texture_destination.y = 0;
    texture_destination.w = DM.w;
    texture_destination.h = DM.h;
    bool running = true;
    SDL_Event event;
    while (running)
    {
        while(SDL_PollEvent(&event))
        {

            if(event.type == SDL_KEYDOWN )
            {
                running = false;
            }
        }
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, image_texture, NULL, &texture_destination);
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyTexture(image_texture);
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}
void leziuni()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    SDL_Window *window = SDL_CreateWindow("<Primul ajutor>", 0, 0, DM.w, DM.h, SDL_WINDOW_OPENGL);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    SDL_Surface *image = IMG_Load("poze_proiect/leziuni.png");
    SDL_Texture *image_texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    SDL_Rect texture_destination;
    texture_destination.x = 0;
    texture_destination.y = 0;
    texture_destination.w = DM.w;
    texture_destination.h = DM.h;
    bool running = true;
    SDL_Event event;
    while (running)
    {
        while(SDL_PollEvent(&event))
        {

            if(event.type == SDL_KEYDOWN )
            {
                running = false;
            }
        }
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, image_texture, NULL, &texture_destination);
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyTexture(image_texture);
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}
void muscaturi()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    SDL_Window *window = SDL_CreateWindow("<Primul ajutor>", 0, 0, DM.w, DM.h, SDL_WINDOW_OPENGL);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    SDL_Surface *image = IMG_Load("poze_proiect/muscaturi.png");
    SDL_Texture *image_texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    SDL_Rect texture_destination;
    texture_destination.x = 0;
    texture_destination.y = 0;
    texture_destination.w = DM.w;
    texture_destination.h = DM.h;
    bool running = true;
    SDL_Event event;
    while (running)
    {
        while(SDL_PollEvent(&event))
        {

            if(event.type == SDL_KEYDOWN )
            {
                running = false;
            }
        }
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, image_texture, NULL, &texture_destination);
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyTexture(image_texture);
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}
void inconstienta()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    SDL_Window *window = SDL_CreateWindow("<Primul ajutor>", 0, 0, DM.w, DM.h, SDL_WINDOW_OPENGL);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    SDL_Surface *image = IMG_Load("poze_proiect/inconstienta.png");
    SDL_Texture *image_texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    SDL_Rect texture_destination;
    texture_destination.x = 0;
    texture_destination.y = 0;
    texture_destination.w = DM.w;
    texture_destination.h = DM.h;
    bool running = true;
    SDL_Event event;
    while (running)
    {
        while(SDL_PollEvent(&event))
        {

            if(event.type == SDL_KEYDOWN )
            {
                running = false;
            }
        }
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, image_texture, NULL, &texture_destination);
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyTexture(image_texture);
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}
void allSDL(void)
{

    //Initialize SDL
    SDL_Init(SDL_INIT_VIDEO);

    //Get desktop resolution
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);

    //Create an SDL window
    SDL_Window *window = SDL_CreateWindow("<Primul ajutor>", 0, 0, DM.w, DM.h, SDL_WINDOW_OPENGL);

    //Create renderer(accelerated and in sync with the display refresh rate)
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    //Initialize support for loading PNG and JPEG images
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

    //Load an image file
    SDL_Surface *image = IMG_Load("poze_proiect/first_page.png");
    SDL_Texture *image_texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);

    //Define where on the "screen" we want to draw the texture
    SDL_Rect texture_destination;
    texture_destination.x = DM.w/7;
    texture_destination.y = DM.h/7;
    texture_destination.w = DM.w/1.2;
    texture_destination.h = DM.h/1.05;



    //clear screen with blacko
    SDL_RenderClear(renderer);

    //Draw
    SDL_RenderCopy(renderer, image_texture, NULL, &texture_destination);

    //show what was drawn
    SDL_RenderPresent(renderer);

    SDL_Delay(5000);

    //Release resources
    SDL_DestroyTexture(image_texture);
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

