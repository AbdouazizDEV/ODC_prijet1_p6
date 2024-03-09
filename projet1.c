#include <stdio.h>
#include <stdbool.h>
#include "projet1F.c"
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
  
int main() {
    char username[Nom_user];
    char password[MDP_user], ch;
    char matricule[Max_Etudiant];
    int rep, cpt = 0,i;
do
{
    connect(username, password);

    printf("\nAuthentification réussie !\n");

    if (Authentification(username, password, "vigile.txt")) {
        if (!verify_id_ETU(username, password, "vigile.txt")) {
            printf("Vous êtes administrateur\n");
            do {
                rep = menuadmin();
                switch (rep) {
                    case 1:
                        
                        // Appeler la fonction GESTION DES ÉTUDIANTS
                        break;
                    case 2:
                          dessinerTableau("listPresant.txt");
                        // Appeler la fonction GÉNÉRATION DE fichier
                        break;
                    case 3:
                        do
                        {
                            do {
                                if (cpt == 1) {
                                    break;
                                } else {
                                    
                                    cpt = cpt + 1;
                                }
                                printf("Veuillez saisir la matricule de l'etudiant:\n");
                                scanf("%s", matricule);
                            } while (!trouverNomUtilisateur(matricule));

                            rep = menuadmin();    
                        } while (rep < 1 || rep > 5);
                        
                        
                        break;
                    case 4:
                        // Appeler la fonction ENVOYER UN MESSAGE
                        break;
                    case 5:
                        // Appeler la fonction
                        break;
                    default:
                        printf("choisissez un entier sur le menu\n");
                }

                printf("tapez q ou Q pour quitter\n");
                scanf(" %c", &ch);
                if (ch == 'q' || ch == 'Q') {
                    printf("donnez le mot de passe admin\n");
                    printf("Entrer votre mot de passe : \n");
                    
                    if (!verifPassword(password)) {
                        break;
                    } else {
                        continue;
                    }
                }
            } while (ch != 'q' && ch != 'Q');
        } else {
            printf("Vous êtes étudiant\n");
            do {
                rep = menuETUDIANT();
                switch (rep) {
                    case 1:
                        MPresence(username);
                        // Appeler la fonction MARQUER MA PRÉSENCE
                        break;
                    case 2:
                        // Appeler la fonction NOMBRE DE MINUTES D’ABSENCE
                        break;
                    case 3:
                        // Appeler la fonction MES MESSAGES (0)
                        break;
                    case 4:
                        // Appeler la fonction DECONNEXION
                        break;
                    default:
                        printf("choisissez un entier sur le menu\n");
                }
            } while (rep < 1 || rep > 4);
        }
    } else {
        printf("Erreur : Nom d'utilisateur ou mot de passe incorrect.\n");
    }
} while (ch=='q'||ch=='Q');
    return 0;
}
