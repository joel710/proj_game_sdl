#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

// Définition des constantes
#define LARGEUR_ECRAN 800
#define HAUTEUR_ECRAN 600
#define VITESSE_BALLE 5
#define TAILLE_RAQUETTE 100

// Déclaration des structures
typedef struct {
    int x;
    int y;
} Position;

typedef struct {
    Position position;
    int direction;
} Balle;

typedef struct {
    Position position;
} Raquette;

// Déclaration des variables
SDL_Window* fenetre;
SDL_Renderer* rendu;
Balle balle;
Raquette raquette1;
Raquette raquette2;

// Fonctions
void initialiserSDL() {
    // Initialisation de la SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Erreur lors de l'initialisation de la SDL : %s\n", SDL_GetError());
        exit(1);
    }

    // Création de la fenêtre
    fenetre = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, LARGEUR_ECRAN, HAUTEUR_ECRAN, SDL_WINDOW_SHOWN);
    if (fenetre == NULL) {
        fprintf(stderr, "Erreur lors de la création de la fenêtre : %s\n", SDL_GetError());
        exit(1);
    }

    // Création du rendu
    rendu = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);
    if (rendu == NULL) {
        fprintf(stderr, "Erreur lors de la création du rendu : %s\n", SDL_GetError());
        exit(1);
    }
}

void initialiserJeu() {
    // Initialisation de la balle
    balle.position.x = LARGEUR_ECRAN / 2;
    balle.position.y = HAUTEUR_ECRAN / 2;
    balle.direction = rand() % 360;

    // Initialisation des raquettes
    raquette1.position.x = 100;
    raquette1.position.y = HAUTEUR_ECRAN / 2 - TAILLE_RAQUETTE / 2;
    raquette2.position.x = LARGEUR_ECRAN - 100;
    raquette2.position.y = HAUTEUR_ECRAN / 2 - TAILLE_RAQUETTE / 2;
}

void afficherJeu() {
    // Nettoyage du rendu
    SDL_RenderClear(rendu);

    // Affichage de la balle
    SDL_Rect balleRect = {balle.position.x, balle.position.y, 50, 50};
    SDL_SetRenderDrawColor(rendu, 255, 255, 255, 255);
    SDL_RenderFillRect(rendu, &balleRect);

    // Affichage des raquettes
    SDL_Rect raquette1Rect = {raquette1.position.x, raquette1.position.y, 20, TAILLE_RAQUETTE};
    SDL_Rect raquette2Rect = {raquette2.position.x, raquette2.position.y, 20, TAILLE_RAQUETTE};
    SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);
    SDL_RenderFillRect(rendu, &raquette1Rect);
    SDL_RenderFillRect(rendu, &raquette2Rect);

    // Mise à jour de l'écran
    SDL_RenderPresent(rendu);
}

void deplacerBalle() {
    // Déplacement de la balle
    balle.position.x += VITESSE_BALLE * cos(balle.direction * M_PI / 180);
    balle.position.y += VITESSE_BALLE * sin(balle.direction * M_PI / 180);

    // Rebond sur les murs
    if (balle.position.x < 0 || balle.position.x > LARGEUR_ECRAN) {
        balle.direction = 180 - balle.direction;
    }
    // by jojo
