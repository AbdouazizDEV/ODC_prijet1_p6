#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "projet1F.c"

int main(){

    char username[Nom_user];
    char password[MDP_user], ch;
    int rep,cpt=0;

    connect(username, password);

    printf("\nAuthentification réussie !\n");
    // Vérifier si le fichier de données existe
    // Authentifier l'utilisateur
    if (Authentification(username,password,"vigile.txt")) {
        if (!verify_id_ETU(username,password,"vigile.txt")) {

            printf("Vous êtes administrateur\n");
            do
            {
                rep = menuadmin();
                switch (rep)
                {
                    case 1:
                        //appelle fonction GESTION DES ÉTUDIANTS
                        break;
                    case 2:
                        //appelle fonction GÉNÉRATION DE fichier
                        break;
                    case 3:
                        do
                        {
                            printf("donnez le mot de passe\n");
                            scanf("%s", password);
                        } while (!trouverNomUtilisateur(password));
                        break;
                    case 4:
                        // appelle fonction ENVOYER UN MESSAGE
                        break;
                    case 5:
                        // appelle fonction 
                        break;
                    default:
                        printf("choisisez un entier sur le menu\n");
                }
                
                printf("tappez q ou Q pour quitter\n");
                scanf(" %c", &ch);
                
            } while (ch != 'q' && ch != 'Q');
        } else {
            printf("Vous êtes étudiant\n");
            do
            {
                rep=menuETUDIANT();
                switch (rep)
                {
                    case 1:
                        // appelle fonction MARQUER MA PRÉSENCE
                        break;
                    case 2:
                        // appelle fonction NOMBRE DE MINUTES D’ABSENCE
                        break;
                    case 3:
                        // appelle fonction MES MESSAGES (0)
                        break;
                    case 4:
                        // appelle fonction DECONNEXION
                        break;
                    default:
                        printf("choisisez un entier sur le menu\n");
                }
            } while (rep<1 || rep>4);   
        }
    } else {
        printf("Erreur : Nom d'utilisateur ou mot de passe incorrect.\n");

    } 

    return 0;
}
