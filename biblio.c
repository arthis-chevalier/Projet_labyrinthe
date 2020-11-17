#include <stdio.h>
#include <stdlib.h>
#include "biblio.h"
#include <time.h>

//---------------------------------------------------------------------------------------------------------------------------------------------
SDL_Rect deplacementHaut (SDL_Rect rect)
{
    rect.y -= 20;
    return rect;
}

SDL_Rect deplacementBas (SDL_Rect rect)
{
    rect.y += 20;
    return rect;
}

SDL_Rect deplacementGauche (SDL_Rect rect)
{
    rect.x -= 20;
    return rect;
}

SDL_Rect deplacementDroite (SDL_Rect rect)
{
    rect.x += 20;
    return rect;
}

//---------------------------------------------------------------------------------------------------------------------------------------------

void drawHaut (SDL_Renderer* renderer,SDL_Rect rect)
{
    SDL_SetRenderDrawColor( renderer, 255, 165, 0, 255 );
    SDL_RenderFillRect( renderer, &rect );
    SDL_RenderPresent(renderer);
}

void drawBas (SDL_Renderer* renderer,SDL_Rect rect)
{
    SDL_SetRenderDrawColor( renderer, 255, 165, 0, 255 );
    SDL_RenderFillRect( renderer, &rect );
    SDL_RenderPresent(renderer);
}

void drawGauche (SDL_Renderer* renderer,SDL_Rect rect)
{
    SDL_SetRenderDrawColor( renderer, 255, 165, 0, 255 );
    SDL_RenderFillRect( renderer, &rect );
    SDL_RenderPresent(renderer);
}

void drawDroite (SDL_Renderer* renderer,SDL_Rect rect)
{
    SDL_SetRenderDrawColor( renderer, 255, 165, 0, 255 );
    SDL_RenderFillRect( renderer, &rect );
    SDL_RenderPresent(renderer);
}

//---------------------------------------------------------------------------------------------------------------------------------------------

int cadrillage(int numCase)
{
    int res;

    res = tab_labyrinthe[numCase];
    tab_labyrinthe[numCase] ++;
    return res;

}

int cadrillage2(int numCase)
{
    int res;

    res = tab_labyrinthe[numCase];
    return res;

}

//---------------------------------------------------------------------------------------------------------------------------------------------

int scrutation(int numCase)
{

    int orientation;
    caseHaut = numCase - 27;
    caseBas = numCase + 27;
    caseGauche = numCase - 1;
    caseDroite = numCase + 1;
    valCaseHaut = cadrillage2(caseHaut);
    valCaseBas = cadrillage2(caseBas);
    valCaseGauche = cadrillage2(caseGauche);
    valCaseDroite = cadrillage2(caseDroite);

    valCaseActuelle = cadrillage(numCase);

    printf("Haut : %ld \n",valCaseHaut);
    printf("Bas : %ld \n",valCaseBas);
    printf("Gauche : %ld \n",valCaseGauche);
    printf("Droite : %ld \n",valCaseDroite);
    if((valCaseHaut <= valCaseBas)&&(valCaseHaut <= valCaseGauche)&&(valCaseHaut <= valCaseDroite))
    {
        orientation = 1;

    }
    else
    {
        if((valCaseBas <= valCaseHaut)&&(valCaseBas <= valCaseGauche)&&(valCaseBas <= valCaseDroite))
        {
            orientation = 2;
        }
        else
        {
            if((valCaseGauche <= valCaseBas)&&(valCaseGauche <= valCaseHaut)&&(valCaseGauche <= valCaseDroite))
            {
                orientation = 3;
            }
            else
            {
                if((valCaseDroite <= valCaseBas)&&(valCaseDroite <= valCaseGauche)&&(valCaseDroite <= valCaseHaut))
                {
                    orientation = 4;
                }
            }
        }
    }
    return orientation;
}

void labyrinthe_auto (SDL_Renderer* renderer)
{
    int x=0;
    int y=0;
    int i=0;
    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );//choix de la couleur noir

    for(i=0 ; i<729 ; i++)//lecture du tableau pour l'affichage des cases
    {
        if(tab_labyrinthe[i]==999 || tab_labyrinthe[i]==1000)//change la couleur des murs en noir
        {
            SDL_Rect r = {.x = x, .y = y, .w = 20, .h = 20};
            SDL_RenderFillRect( renderer, &r );
        }
        if(x<520)//incrémentation des coordonées
        {
            x=x+20;
        }
        else
        {
            x=0;
            y=y+20;
        }

    }
}

void labyrinthe_auto_gen(SDL_Renderer* renderer)
{
    int i;
    int x_fin=0;
    int y_fin=0;
    int case_finale;
    int case_actuelle=364;//initalisation de la case de départ
    srand((unsigned int)time(0));   //obligatoire pour la fonction rand
    unsigned short NBrand;
    int fin_laby=0;

   for(i=0;i<729;i++)//remplisage du tableau
   {
       tab_labyrinthe[i]=999;
   }
   //initialisation du contours du labyrinthe pour ne pas en sortir
   for(i=0;i<27;i++)//contour haut
   {
       tab_labyrinthe[i]=1000;
   }
   for(i=702;i<729;i++)//contour bas
   {
       tab_labyrinthe[i]=1000;
   }
   for(i=27;i<702;i=i+27)//countour gauche
   {
       tab_labyrinthe[i]=1000;
   }
   for(i=53;i<728;i=i+27)//contour droite
   {
       tab_labyrinthe[i]=1000;
   }

   tab_labyrinthe[case_actuelle]=0;//case d'entrée au milieu


    while(fin_laby<=2)//boucle de génération

    {
    NBrand=rand()%4;//tirage d'un nombre aléatoire entre 0 et 3

    switch(NBrand)
    {
        case 0:
            if((tab_labyrinthe[(case_actuelle-54)])!=1000)//empêche la modification des cases qui forment les bors du labyrinthe pour ne pas sortir du tableau
            {
                case_actuelle=case_actuelle-27;
                tab_labyrinthe[case_actuelle]=0;//retire le mur sur la case du dessus
                case_actuelle=case_actuelle-27;
                tab_labyrinthe[case_actuelle]=0;//retire le mur sur la case du dessous
            }
            else{}
            break;

        case 1:
            if((tab_labyrinthe[(case_actuelle+54)])!=1000)
            {
                case_actuelle=case_actuelle+27;
                tab_labyrinthe[case_actuelle]=0;//retire le mur sur la case du dessous
                case_actuelle=case_actuelle+27;
                tab_labyrinthe[case_actuelle]=0;//retire le mur sur la case du dessous
            }
            else{}
            break;
        case 2:
            if((tab_labyrinthe[(case_actuelle-2)])!=1000)
            {
                case_actuelle=case_actuelle-1;
                tab_labyrinthe[case_actuelle]=0;//retire le mur sur la case de gauche
                case_actuelle=case_actuelle-1;
                tab_labyrinthe[case_actuelle]=0;//retire le mur sur la case du dessous
            }
            else{}
            break;

        case 3:
            if((tab_labyrinthe[(case_actuelle+2)])!=1000)
            {
                case_actuelle=case_actuelle+1;
                tab_labyrinthe[case_actuelle]=0;//retire le mur sur la case de droite
                case_actuelle=case_actuelle+1;
                tab_labyrinthe[case_actuelle]=0;//retire le mur sur la case de droite
            }
            else{}
            break;
        default:
            break;

    }
    //détection bord touché pour la colorier en vert et stopper la génération
    if(((tab_labyrinthe[(case_actuelle-27)])==1000) || ((tab_labyrinthe[(case_actuelle+27)])==1000) || ((tab_labyrinthe[(case_actuelle-1)])==1000) || ((tab_labyrinthe[(case_actuelle+1)])==1000))
    {
        fin_laby++;//incrémentation jusqu'a 3
        if(fin_laby<=2)
        {
            case_actuelle=364;//remise a 0 pour créer de nouvelles branches
        }
        else
        {
            case_finale=case_actuelle;
            while(case_finale>27)//récupération des coordonées pour colorier en vert la case finale
            {
                y_fin++;
                case_finale=case_finale-27;
            }
            x_fin=case_finale;
            printf("%hd | %hd",x_fin,y_fin);//affichage des coordonées de la case finale

            SDL_SetRenderDrawColor( renderer, 0, 255, 0, 100 );//choix de la couleur verte
            SDL_Rect r = {.x = 0, .y = 0, .w = 0, .h = 0};//initialisation pour l'affichage
            //coloriage de la case de fin
            r.x = x_fin*20;
            r.y = y_fin*20;
            r.w = 20;
            r.h = 20;
            SDL_RenderFillRect( renderer, &r );
            //coloriage de la case de début
            r.x = 260;
            r.y = 260;
            r.w = 20;
            r.h = 20;
            SDL_RenderFillRect( renderer, &r );
            }

        }

    }


}
