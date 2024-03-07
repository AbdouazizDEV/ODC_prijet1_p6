#include"projet1.h"    
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<termios.h>
#include<unistd.h>
#include<stdbool.h>

#define Nom_user 50
#define MDP_user 15
#define taille 200

typedef struct {
    char nom[Nom_user];
    char prenom[Nom_user];
    char mdp[MDP_user];
    int age;
    int sexe;
    int id;
} ETUDIANT_USER;

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

//fontion ajouter vers la liste de presance 
bool trouverNomUtilisateur(const char *mdp) {
    FILE *file = fopen("vigile.txt", "r");
    if (file == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier vigile.txt.\n");
        return false;
    }

    char line[taille];
    while (fgets(line, sizeof(line), file) != NULL) {
        char fileUsername[Nom_user], filePassword[MDP_user];
        if (sscanf(line, "%s %s", fileUsername, filePassword) == 2) {
            if (strcmp(filePassword, mdp) == 0) {
                fclose(file);
                return ajouterPresence(fileUsername);
            }
        }
    }

    fclose(file);
    return false; // Aucune correspondance trouvée
}

bool ajouterPresence(const char *username) {
    FILE *fp = fopen("listPresant.txt", "a");
    if (fp != NULL) {
        fprintf(fp, "%s\n", username);
        fclose(fp);
        printf("Présence ajoutée avec succès.\n");
        return true;
    } else {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return false;
    }
}