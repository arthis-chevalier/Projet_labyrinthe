#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <SDL.h>
#include "biblio.h"
#include <time.h>

//d�finition de la position de d�part et de la taille de l'IA
SDL_Rect rect = {.x = 264, .y = 264, .w = 12, .h = 12};
SDL_Rect r = {.x = 264, .y = 264, .w = 12, .h = 12};
int dep;

int caseActuelle = 364;
int valCaseActuelle;

int caseHaut;
int caseBas;
int caseGauche;
int caseDroite;

int valCaseHaut;
int valCaseBas;
int valCaseGauche;
int valCaseDroite;

int tab_labyrinthe[729] = {0};
//initialisation de la fen�tre
int WINAPI WinMain(
  HINSTANCE hInstance,
  HINSTANCE hPrevInstance,
  LPSTR     lpCmdLine,
  int       nShowCmd
)
{
    SDL_Window *window = NULL;
    SDL_Surface *windowSurface = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Init(SDL_INIT_VIDEO);


    window = SDL_CreateWindow("SDL Labyrinthe", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,540,540,SDL_WINDOW_SHOWN );
    windowSurface = SDL_GetWindowSurface(window);

    renderer =  SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
    SDL_RenderClear( renderer );

 SDL_SetRenderDrawColor( renderer, 255, 165, 0, 255 );

 SDL_RenderFillRect( renderer, &r );

//-------------------------------------------------------------------------------------------------------------------------------------------------

    int isRunning = 1;
    SDL_Event ev;

//g�n�ration et rendu du labyrinthe
labyrinthe_auto_gen(renderer);
labyrinthe_auto(renderer);

    while(isRunning)
    {
        while(SDL_PollEvent(&ev) != 0)//d�tection d'un appui clavier ou souris
        {
            if(ev.type == SDL_QUIT)
            {
                isRunning = 0;
            }
            else if(ev.type == SDL_KEYDOWN)//test d'un appui clavier
            {

                switch(ev.key.keysym.sym)//gestion de l'action � r�aliser en fonction de la touche appuy�
                    {
                    case SDLK_UP:
                        printf("UP \n");
                        dep = 1;

                        break;
                    case SDLK_DOWN:
                        printf("DOWN \n");
                        dep = 2;

                        break;
                    case SDLK_LEFT:
                        printf("LEFT \n");
                        dep = 3;

                        break;
                    case SDLK_RIGHT:
                        printf("RIGHT \n");
                        dep = 4;

                        break;
//---------------------------------------------------------------------------------------------------------------------------------------------
                    case SDLK_i:
                        printf("IA Go ! \n");
                        dep = 5;



                        break;
//---------------------------------------------------------------------------------------------------------------------------------------------
                    }

                    ////d�placement manuel(utilis� pour le d�bogage)
                    if(dep == 1)//d�placement manuel en haut
                    {
                        caseActuelle = caseActuelle - 27;
                        valCaseActuelle = cadrillage(caseActuelle);
                        if(valCaseActuelle >= 999)
                        {
                            printf("pas possible ");
                            printf("%d \n",valCaseActuelle);
                        }

                        SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
                        SDL_RenderFillRect( renderer, &rect );

                        rect = deplacementHaut(rect);
                        drawHaut(renderer,rect);

                        printf("%d \n",valCaseActuelle);
                        dep = 0;
                    }
                    if(dep == 2)//d�placement manuel en bas
                    {
                        caseActuelle = caseActuelle + 27;
                        valCaseActuelle = cadrillage(caseActuelle);
                        if(valCaseActuelle >= 999)
                        {
                            printf("pas possible ");
                            printf("%d \n",valCaseActuelle);
                        }

                        SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
                        SDL_RenderFillRect( renderer, &rect );

                        rect = deplacementBas(rect);
                        drawBas(renderer,rect);

                        printf("%d \n",valCaseActuelle);
                        dep = 0;
                    }
                    if(dep == 3)//d�placement manuel � gauche
                    {
                        caseActuelle = caseActuelle - 1;
                        valCaseActuelle = cadrillage(caseActuelle);
                        if(valCaseActuelle >= 999)
                        {
                            printf("pas possible ");
                            printf("%d \n",valCaseActuelle);
                        }

                        SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
                        SDL_RenderFillRect( renderer, &rect );

                        rect = deplacementGauche(rect);
                        drawGauche(renderer,rect);

                        printf("%d \n",valCaseActuelle);
                        dep = 0;
                    }
                    if(dep == 4)//d�placement manuel � droite
                    {
                        caseActuelle = caseActuelle + 1;
                        valCaseActuelle = cadrillage(caseActuelle);
                        if(valCaseActuelle >= 999)
                        {
                            printf("pas possible ");
                            printf("%d \n",valCaseActuelle);
                        }

                        SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
                        SDL_RenderFillRect( renderer, &rect );

                        rect = deplacementDroite(rect);
                        drawDroite(renderer,rect);


                        printf("%d \n",valCaseActuelle);
                        dep = 0;
                    }

//---------------------------------------------------------------------------------------------------------------------------------------------

                    if(dep == 5)//d�placement de l'IA
                    {
                        int direction;
                        direction = scrutation(caseActuelle);
                        switch(direction)
                        {
                            case 1:
                            printf("UP \n");

                            SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );//efface le carr� orange
                            SDL_RenderFillRect( renderer, &rect );

                            rect = deplacementHaut(rect);
                            drawHaut(renderer,rect);//affiche le carr� orange sur la case du dessus

                            caseActuelle = caseActuelle-27;//rafraichis la variable de position


                            break;

                            case 2:
                            printf("DOWN \n");

                            SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );//efface le carr� orange
                            SDL_RenderFillRect( renderer, &rect );

                            rect = deplacementBas(rect);
                            drawBas(renderer,rect);//affiche le carr� orange sur la case du dessous

                            caseActuelle = caseActuelle+27;//rafraichis la variable de position


                            break;

                            case 3:
                            printf("LEFT \n");

                            SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
                            SDL_RenderFillRect( renderer, &rect );

                            rect = deplacementGauche(rect);
                            drawGauche(renderer,rect);//affiche le carr� orange sur la case de gauche

                            caseActuelle = caseActuelle-1;//rafraichis la variable de position


                            break;

                            case 4:
                            printf("RIGHT \n");

                            SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
                            SDL_RenderFillRect( renderer, &rect );

                            rect = deplacementDroite(rect);
                            drawDroite(renderer,rect);//affiche le carr� orange sur la case de droite

                            caseActuelle = caseActuelle+1;//rafraichis la variable de position


                            break;
                        }
                        dep = 0;
                    }

//---------------------------------------------------------------------------------------------------------------------------------------------
            }

        SDL_RenderPresent(renderer);//rafraichissemnt de l'interface graphique
        }

    }

    //destruction de la fen�tre lors de sa fermeture
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_Quit();

    return 0;
}

