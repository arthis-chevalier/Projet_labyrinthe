#ifndef BIBLIO_H_INCLUDED
#define BIBLIO_H_INCLUDED
#include <SDL.h>
#include <time.h>
extern int tab_labyrinthe[729];

extern int casa;

extern int caseHaut;
extern int caseBas;
extern int caseGauche;
extern int caseDroite;

extern int valCaseHaut;
extern int valCaseBas;
extern int valCaseGauche;
extern int valCaseDroite;
extern int valCaseActuelle;

//fonction de déplacement du carré orange
SDL_Rect deplacementHaut (SDL_Rect rect);
SDL_Rect deplacementBas (SDL_Rect rect);
SDL_Rect deplacementGauche (SDL_Rect rect);
SDL_Rect deplacementDroite (SDL_Rect rect);

//fonction de rafraichissement de l'affichage du carré
void drawHaut (SDL_Renderer* renderer,SDL_Rect rect);
void drawBas (SDL_Renderer* renderer,SDL_Rect rect);
void drawGauche (SDL_Renderer* renderer,SDL_Rect rect);
void drawDroite (SDL_Renderer* renderer,SDL_Rect rect);

//fonction d'incrémentation de la variable de tab_labyrinthe[numCase] lors du passage dans une case et qui retourne cette valeur
int cadrillage(int numCase);

//fonction qui retourne la valeur de la case de tab_labyrinthe[numCase]
int cadrillage2(int numCase);

//fonction de scrutation des cases autour de celles sur laquelle se trouve le carré orange pour renvoyer la position de la case qui a été le moins visité
int scrutation(int numCase);

//fonction de rendu du labyrinthe
void labyrinthe_auto (SDL_Renderer* renderer);

//fonction de génération du labyrinthe
void labyrinthe_auto_gen(SDL_Renderer* renderer);




#endif // BIBLIO_H_INCLUDED

