#ifndef PROJET1F_H
#define PROJET1F_H
#include<stdbool.h>

#define Nom_user 50
#define MDP_user 15

void connect(char *username, char *password);
bool authenticate(const char *username, const char *password);
int menuadmin();
int menuETUDIANT();
int menu_admine2();
int verify_id_ADMIN();
bool verify_id_ETU(const char *username, const char *password, const char *vigile);

void ajouter_admin(const char *username, const char *password);

void ajouterEtudiant(const char *nom, const char *prenom,const char *mdp ,int age, int sexe, int id);
void supprimerEtudiant(const char *nom, const char *prenom,const char *mdp ,int age, int sexe, int id);

bool trouverNomUtilisateur(const char *mdp);
bool ajouterPresence(const char *username);
#endif /* PROJET1F_H */
