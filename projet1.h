#ifndef PROJET1F_H
#define PROJET1F_H
#include<stdbool.h>

#define Nom_user 50
#define MDP_user 15
#define Max_Etudiant 15

typedef struct {
    char prenom[Nom_user];
    char mdp[MDP_user];
    int sexe;
    char matricula[Max_Etudiant];
    int age;
    int id;
} ETUDIANT_USER;

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
bool ajouterPresence(const char *username, const char *password, int sexe, const char *matricule, int age, int id);
bool marquerPresence(const char *username);
void listPres(const char *username);
bool verifPassword(const char *mdp) ;
void connect2( char *password);
void MPresence(const char *username);

int menu_fichier_present();
void dessinerTableauDate(const char *filename, const char *date) ;
#endif /* PROJET1F_H */
