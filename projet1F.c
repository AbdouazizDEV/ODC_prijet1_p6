#include"projet1.h"    
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<termios.h>
#include<unistd.h>
#include<stdbool.h>
#include <time.h>

#define Nom_user 50
#define MDP_user 15
#define taille 200
#define Max_Etudiant 15
#define MAX_LINE_LENGTH 1000
#define MAX_STUDENTS 100

/* typedef struct {
    char nom[Nom_user];
    char prenom[Nom_user];
    char mdp[MDP_user];
    char matricula[Max_Etudiant];
    int age;
    int sexe;
    int id;
} ETUDIANT_USER; */

typedef struct  {
    char nom[Nom_user];
    char prenom[Nom_user];
    char mdp[MDP_user];
    int age;
    int sexe;
    int id;
} ADMIN_USER;

 
 int getch() {
    struct termios oldt, newt;
    int ch;

    // Enregistrer les paramètres du terminal actuel
    if (tcgetattr(STDIN_FILENO, &oldt) != 0) {
        perror("Erreur lors de la récupération des paramètres du terminal");
        return -1; // Erreur
    }

    // Copier les paramètres dans une nouvelle structure
    newt = oldt;

    // Désactiver le mode canonique (ligne par ligne) et l'écho
    newt.c_lflag &= ~(ICANON | ECHO);

    // Appliquer les nouveaux paramètres au terminal
    if (tcsetattr(STDIN_FILENO, TCSANOW, &newt) != 0) {
        perror("Erreur lors de la configuration des paramètres du terminal");
        return -1; // Erreur
    }

    // Lire un caractère de l'entrée standard
    ch = getchar();

    // Restaurer les paramètres du terminal
    if (tcsetattr(STDIN_FILENO, TCSANOW, &oldt) != 0) {
        perror("Erreur lors de la restauration des paramètres du terminal");
        return -1; // Erreur
    }

    // Retourner le caractère lu
    return ch;
}   

//verification de l'id du user
int verify_id_ADMIN() {
    ADMIN_USER user1;
    FILE *fp;
    fp = fopen("vigile.txt", "r");
    if (fp != NULL) {
        fread(&user1, sizeof(ADMIN_USER), 1, fp);
        if (user1.id == 1) {
            fclose(fp);
            return 1;
        } else {
            fclose(fp);
            return 0;
        }
    } else {
        perror("Erreur lors de l'ouverture du fichier");
        return 0;
    }
}
bool verify_id_ETU(const char *username, const char *password, const char *vigile) {
    FILE *file = fopen(vigile, "r");
    if (file == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier %s.\n", vigile);
        return false;
    }

    char line[taille];
    while (fgets(line, sizeof(line), file) != NULL) {
        char fileUsername[Nom_user], filePassword[MDP_user], role[10];
        if (sscanf(line, "%s %s %s", fileUsername, filePassword, role) == 3) {
            if (strcmp(username, fileUsername) == 0 && strcmp(password, filePassword) == 0) {
                fclose(file);
                return (strcmp(role, "1") == 0); // Vérifie si le rôle est égal à "1"
            }
        }
    }

    fclose(file);
    return false; // Aucune correspondance trouvée ou rôle différent de "1"
}

/* bool authenticate(const char *username, const char *password) {
    FILE *file = fopen("vigile.txt", "r");
    char line[taille];
    bool valid = false;
    if (file == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier de données.\n");
        return false;
    }

    // Parcourir chaque ligne du fichier de données
    while (fgets(line, taille, file) != NULL) {
        char user_name[Nom_user];
        char mdp[MDP_user];
        
        // Extraire le nom d'utilisateur et le mot de passe de la ligne
        if (sscanf(line, "%s %s", user_name, mdp) == 2) {
            // Comparer le nom d'utilisateur et le mot de passe de la ligne avec ceux saisis
            if (strcmp(user_name, username) == 0 && strcmp(mdp, password) == 0) {
                valid = true;
                break; // Correspondance trouvée, arrêter la recherche
            }
        }
    }
    
    fclose(file);
    return valid;
} */


int menuadmin(){
    int choix;
    printf("vaillez choisir un entier dans le menue\n");
    printf("•••••••••••••••••••••MENU•••••••••••••••••••••••••••\n");
    printf("1→→GESTION DES ÉTUDIANTS\n");
    printf("2→→GÉNÉRATION DE FICHIERS\n");
    printf("3→→MARQUER LES PRÉSENCES\n");
    printf("4→→ENVOYER UN MESSAGE\n");
    printf("5→→QUITTER\n");
    printf("••••••••••••••••••••••••••••••••••••••••••••••••••••\n");
    scanf("%d",&choix);
    return choix;
}

int menuETUDIANT(){
    int choix;
    printf("vaillez choisir un entier dans le menue\n");
    printf("•••••••••••••••••••••MENU•••••••••••••••••••••••••••\n");
    printf("1→→MARQUER MA PRÉSENCE\n");
    printf("2→→NOMBRE DE MINUTES D’ABSENCE\n");
    printf("3→→MES MESSAGES (0)\n");
    printf("4→→QUITTER\n");
    printf("••••••••••••••••••••••••••••••••••••••••••••••••••••\n");
    scanf("%d",&choix);
    return choix;
}

//menu admine gestion des etudiant 
int menu_admine2()


{
    int choix;
    
    printf("Choisissez un entier dans le menu :\n");
    printf("••••••••••••••••••••• MENU ••••••••••••••••••••••\n");
    printf("1 → Marquer presant\n");
    printf("2 → Marquer absant\n");
    printf("3 → QUITTER\n");
    printf("•••••••••••••••••••••••••••••••••••••••••••••\n");
    printf("Votre choix : ");
    scanf("%d", &choix);
    
    return choix;
}

void ajouterEtudiant(const char *nom, const char *prenom,const char *mdp ,int age, int sexe, int id) {
    FILE *fp = fopen("etudiant.txt", "a");
    if (fp != NULL) {
        fprintf(fp, "%s %s %s %d %d %d\n", nom, prenom,mdp, age, sexe,1);
        fclose(fp);
        printf("Étudiant ajouté avec succès.\n");
    } else {
        printf("Erreur lors de l'ouverture du fichier.\n");
    }
}

void supprimerEtudiant(const char *nom, const char *prenom,const char *mdp ,int age, int sexe, int id) {
    FILE *lecture = fopen("temp.txt", "w");
    FILE *file = fopen("etudiant.txt", "r");
    if (file != NULL && lecture != NULL) {
        char line[100];
        while (fgets(line, sizeof(line), file) != NULL) {
            char etudiantNom[50], etudiantPrenom[50];
            int etudiantAge;
            sscanf(line, "%s %s %d", etudiantNom, etudiantPrenom, &etudiantAge);
            if (strcmp(nom, etudiantNom) != 0 || strcmp(prenom, etudiantPrenom) != 0) {
                fprintf(lecture, "%s %s %d\n", etudiantNom, etudiantPrenom, etudiantAge);
            }
        }
        fclose(file);
        fclose(lecture);
        remove("etudiant.txt");
        rename("temp.txt", "etudiant.txt");
        printf("Étudiant supprimé avec succès.\n");
    } else {
        printf("Erreur lors de l'ouverture des fichiers.\n");
    }
}

void modifierEtudiant(const char *ancienNom, const char *ancienPrenom,const char *ancienMDP, const char *nouveauNom, const char *nouveauPrenom,const char *new_mdp, int age) {
    FILE *lecture = fopen("temp.txt", "w");
    FILE *file = fopen("etudiant.txt", "r");
    if (file != NULL && lecture != NULL) {
        char line[100];
        while (fgets(line, sizeof(line), file) != NULL) {
            char etudiantNom[50], etudiantPrenom[50];
            int etudiantAge;
            sscanf(line, "%s %s %d", etudiantNom, etudiantPrenom, &etudiantAge);
            if (strcmp(ancienNom, etudiantNom) == 0 && strcmp(ancienPrenom, etudiantPrenom) == 0) {
                fprintf(lecture, "%s %s %s %d\n", nouveauNom, nouveauPrenom,new_mdp ,age);
            } else {
                fprintf(lecture, "%s %s %d\n", etudiantNom, etudiantPrenom, etudiantAge);
            }
        }
        fclose(file);
        fclose(lecture);
        remove("etudiant.txt");
        rename("temp.txt", "etudiant.txt");
        printf("Étudiant modifié avec succès.\n");
    } else {
        printf("Erreur lors de l'ouverture des fichiers.\n");
    }
}

//marquer la presance de l'etudiant 


// Fonction pour lire les informations d'authentification à partir d'un fichier

bool Authentification(const char *username, const char *password, const char *vigile) {
    char fileUsername[Nom_user], filePassword[MDP_user];
    FILE *file = fopen(vigile, "r");
    if (file == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier d'authentification.\n");
        return false;
    }

    while (fscanf(file, "%s %s", fileUsername, filePassword) == 2) {
        if (strcmp(username, fileUsername) == 0 && strcmp(password, filePassword) == 0) {
            fclose(file);
            return true; // Correspondance trouvée
        }
    }

    fclose(file);
    return false; // Aucune correspondance trouvée
}


void connect(char *username, char *password) {
    bool connexion;

    do {
        printf("Connexion :\n");
        
        do {
            printf("Entrer votre username : ");
            fgets(username, Nom_user, stdin);
            username[strcspn(username, "\n")] = '\0'; // Supprimer le retour à la ligne
        } while (strcmp(username, "") == 0); // Contrôle du login, il ne doit pas être vide
        
        printf("Entrer votre mot de passe : ");
        
        int i = 0;
        char c;
        while (i < MDP_user - 1 && (c = getch()) != '\n') {
            password[i++] = c;
            printf("*");
        }
        password[i] = '\0';
        printf("\n");
        connexion = Authentification(username, password, "vigile.txt");

        if (!connexion) {
            printf("Nom d'utilisateur ou mot de passe incorrect. Veuillez réessayer.\n");
        }
    } while (!connexion);
}


bool trouverNom(const char *username) {
    FILE *file = fopen("listPresant.txt", "r");
    if (file == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier listPresant.txt.\n");
        return false;
    }

    char line[taille];
    while (fgets(line, sizeof(line), file) != NULL) {
        char nom_utilisateur[Nom_user];
        if (sscanf(line, "%s", nom_utilisateur) == 1) {
            if ((strcmp(nom_utilisateur, username) == 0)) {
                fclose(file);
                return true;
            }
        }
    }
    fclose(file);
    return false; // Aucune correspondance trouvée
}
//fontion ajouter vers la liste de presance 
bool trouverNomUtilisateur(const char *matricule) {
    FILE *file = fopen("vigile.txt", "r");
    if (file == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier vigile.txt.\n");
        return false;
    }

    char line[taille];
    while (fgets(line, sizeof(line), file) != NULL) {
        char nom[Nom_user], mdp[MDP_user], matricule_file[10];
        int sexe, age, id;
        if (sscanf(line, "%s %s %d %s %d %d", nom, mdp, &sexe, matricule_file, &age, &id) == 6) {
            if ((strcmp(matricule_file, matricule) == 0)) {
                fclose(file);
                return ajouterPresence(nom, mdp, sexe, matricule_file, age, id);
            }
        }
    }
    fclose(file);
    return false; // Aucune correspondance trouvée
}

bool ajouterPresence(const char *nom, const char *mdp, int sexe, const char *matricule, int age, int id) {
    if (trouverNom(nom)) {
        printf("Cet utilisateur est déjà présent.\n");
        return false;
    } else {
        FILE *fp = fopen("listPresant.txt", "a");
        if (fp != NULL) {
            // Obtenir la date et l'heure actuelles
            time_t t = time(NULL);
            struct tm *tm = localtime(&t);
            char date[11];
            char heure[9];
            strftime(heure, sizeof(heure), "%H:%M:%S", tm);
            strftime(date, sizeof(date), "%d/%m/%Y", tm);

            // Écrire toutes les informations de l'étudiant dans le fichier
            fprintf(fp, "%s %s %d %s %d %d %s  %s\n", nom, mdp, sexe, matricule, age, id, heure, date);
            fclose(fp);
            printf("Présence ajoutée avec succès.\n");
            return true;
        } else {
            printf("Erreur lors de l'ouverture du fichier.\n");
            return false;
        }
    }
}

//marquer presence.
bool marquerPresence(const char *username) {
    FILE *fp = fopen("listPresant.txt", "a");
    if (fp!= NULL) {
        fprintf(fp, "%s\n", username);
        fclose(fp);
        printf("Présence marquée avec succès.\n");
        return true;
    } else {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return false;
    }
}

void MPresence(const char *username) {
    if (trouverNom(username)) {
        printf("Vous êtes déjà présent.\n");
    } else {
        FILE *fp = fopen("listPresant.txt", "a");
        if (fp != NULL) {
            fprintf(fp, "%s\n", username);
            fclose(fp);
            printf("Présence marquée avec succès.\n");
        } else {
            printf("Erreur lors de l'ouverture du fichier.\n");
        }
    }
}

bool verifPassword(const char *mdp) {
    FILE *file = fopen("vigile.txt", "r");
    if (file == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier vigile.txt.\n");
        return false;
    }

    char line[taille];
    while (fgets(line, sizeof(line), file) != NULL) {
        char nom_utilisateur[Nom_user], mdp_utilisateur[MDP_user];
        if (sscanf(line, "%s %s", nom_utilisateur, mdp_utilisateur) == 2) {
            if ((strcmp(mdp_utilisateur, mdp) == 0)) {
                fclose(file);
            
                return true;
            }
        }
    }

    fclose(file);
    return false; // Aucune correspondance trouvée
}

void connect2( char *password) {
    bool connexion;

    do {
     
        printf("Entrer le matricule l'etudiant :\n ");
        
        int i = 0;
        char c;
        while (i < MDP_user - 1 && (c = getch()) != '\n') {
            password[i++] = c;
            printf("*");
        }
        password[i] = '\0';
        printf("\n");
       /*  connexion = Authentification(username, password, "vigile.txt"); */

        
    } while (!connexion);
}

//++++++++++++++++++++++++++++++++++++++++++++++++

// menu de geration de fichier des presentes
int menu_fichier_present(){
    int choix;
    
    printf("••••••••••••••••••••• MENU ••••••••••••••••••••••\n");
    printf("1 → liste de presant\n");
    printf("2 → liste de presence par date\n");
    printf("•••••••••••••••••••••••••••••••••••••••••••••\n");
    printf("Votre choix : ");
    scanf("%d", &choix);
    return choix;
}

void dessinerTableau(const char *filename) {
    FILE *fp_in = fopen(filename, "r");
    FILE *fp_out = fopen("tableau.txt", "w");

    if (fp_in == NULL || fp_out == NULL) {
        printf("Erreur lors de l'ouverture des fichiers.\n");
        return;
    }

    // Dessiner la ligne horizontale supérieure
    fprintf(fp_out, "┌──────────┬───────────────────┬───────────────────┬───────┬─────────────┬─────┬───────┐\n");

    // En-têtes des colonnes
    fprintf(fp_out, "│ Heure    │ Utilisateur       │ Mot de passe       │ Sexe  │ Matricule   │ Age │ ID    │\n");

    // Dessiner la ligne de séparation entre les en-têtes et les données
    fprintf(fp_out, "├──────────┼───────────────────┼───────────────────┼───────┼─────────────┼─────┼───────┤\n");

    char ligne[100];
    char heure[20], utilisateur[50], mdp[20], sexe[10], matricule[15], age[5], id[5];

    while (fgets(ligne, sizeof(ligne), fp_in) != NULL) {
        // Extraire les informations de l'étudiant de la ligne
        sscanf(ligne, "%s %s %s %s %s %s %s", utilisateur, mdp, sexe, matricule, age, id, heure);

        // Afficher les données de l'étudiant dans une nouvelle ligne du tableau
        fprintf(fp_out, "│ %-8s │ %-17s │ %-17s │ %-5s │ %-11s │ %-4s │ %-5s │\n", heure, utilisateur, mdp, sexe, matricule, age, id);
    }

    // Dessiner la ligne horizontale inférieure
    fprintf(fp_out, "└──────────┴───────────────────┴───────────────────┴───────┴─────────────┴─────┴───────┘\n");

    fclose(fp_in);
    fclose(fp_out);
    printf("Le tableau a été dessiné avec succès dans le fichier tableau.txt.\n");
}

void demanderDate(char *date) {
    printf("Veuillez saisir une date au format français (jour/mois/année) : \n");
    fgets(date, 11, stdin);
    // Supprimer le caractère de nouvelle ligne s'il est présent
    if (date[strlen(date) - 1] == '\n') {
        date[strlen(date) - 1] = '\0';
    }
}
void dessinerTableauDate(const char *filename, const char *date) {
    FILE *fp_in = fopen(filename, "r");
    FILE *fp_out = fopen("tableauDate.txt", "w");

    if (fp_in == NULL || fp_out == NULL) {
        printf("Erreur lors de l'ouverture des fichiers.\n");
        return;
    }

    // Écrire la date fournie par l'utilisateur dans le fichier de sortie
    fprintf(fp_out, "Liste des étudiants présents le %s :\n", date);

    // Dessiner la ligne horizontale supérieure
    fprintf(fp_out, "┌───────────────────┬───────────────────┬───────┬─────────────┬─────┬───────┬──────────┐\n");

    // En-têtes des colonnes
    fprintf(fp_out, "│ Utilisateur       │ Mot de passe      │ Sexe  │ Matricule   │ Age │ ID    │ Heure    │\n");

    // Dessiner la ligne de séparation entre les en-têtes et les données
    fprintf(fp_out, "├───────────────────┼───────────────────┼───────┼─────────────┼─────────────┼──────────┤\n");

    char line[MAX_LINE_LENGTH];
    char utilisateur[20], mdp[20], sexe[5], matricule[10], age[5], id[5], heure[10], current_date[20];
    int items_read;

    while (fgets(line, sizeof(line), fp_in)) {
        // Lire les données de la ligne
        items_read = sscanf(line, "%s %s %s %s %s %s %s %s", utilisateur, mdp, sexe, matricule, age, id, heure, current_date);

        // Vérifier si les données ont été lues avec succès et si la date correspond
        if (items_read == 8 && strcmp(current_date, date) == 0) {
            // Afficher les données dans les colonnes correspondantes
            fprintf(fp_out, "│ %-17s │ %-17s │ %-5s │ %-11s │ %-3s │ %-5s │ %-8s │\n", utilisateur, mdp, sexe, matricule, age, id, heure);
        }
    }

    // Dessiner la ligne horizontale inférieure
    fprintf(fp_out, "└───────────────────┴───────────────────┴───────┴─────────────┴─────┴───────┴──────────┘\n");

    fclose(fp_in);
    fclose(fp_out);
    printf("Le tableau a été dessiné avec succès dans le fichier tableauDate.txt.\n");
}
//control de date saisie
bool estAnneeBissextile(int annee) {
    return (annee % 4 == 0 && annee % 100 != 0) || (annee % 400 == 0);
}

bool estDateValide(int jour, int mois, int annee) {
    if (mois < 1 || mois > 12) return false;

    int joursDansLeMois;
    switch (mois) {
        case 4:
        case 6:
        case 9:
        case 11:
            joursDansLeMois = 30;
            break;
        case 2:
            joursDansLeMois = estAnneeBissextile(annee) ? 29 : 28;
            break;
        default:
            joursDansLeMois = 31;
    }

    return jour >= 1 && jour <= joursDansLeMois;
}

bool estDateFrancaiseValide(const char *date) {
    int jour, mois, annee;
    if (sscanf(date, "%d/%d/%d", &jour, &mois, &annee) != 3) {
        return false; // Mauvais format de saisie
    }
    return estDateValide(jour, mois, annee);
}

void saisirDateFrancaise(char *date) {
    printf("Veuillez saisir une date au format français (jour/mois/année) :\n ");
    scanf("%s", date);
    while (!estDateFrancaiseValide(date)) {
        printf("Format de date incorrect.\n Veuillez saisir une date valide au format français (jour/mois/année) : \n");
        scanf("%s", date);
    }
}

