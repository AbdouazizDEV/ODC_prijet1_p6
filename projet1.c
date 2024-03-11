#include <stdio.h>
#include <stdbool.h>
#include "projet1F.c"
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#define MAX_DATE_LENGTH 20

int main()
{
    char username[Nom_user];
    char password[MDP_user], ch;
    char matricule[Max_Etudiant];
    int rep, cpt = 0, i, f;
    
    clearScreen();
    
    do
    {
        connect(username, password);
        printf("\nAuthentification réussie !\n");

        if (Authentification(username, password, "vigile.txt"))
        {
            if (!verify_id_ETU(username, password, "vigile.txt"))
            {
                printf("Vous êtes administrateur\n");
                do
                {
                    rep = menuadmin(); // Afficher le menu et obtenir le choix de l'utilisateur
                    switch (rep)
                    {
                    case 1:
                        // Code pour la gestion des étudiants
                        break;
                    case 2:
                        do
                        {
                            clearScreen();
                            f = menu_fichier_present();
                            if (f == 1)
                            {
                                dessinerTableau("listPresant.txt");
                            }
                            else if (f == 2)
                            {
                                const char *filename = "listPresant.txt";
                                char date[MAX_DATE_LENGTH];
                                saisirDateFrancaise(date);
                                clearScreen();
                                dessinerTableauDate(filename, date);
                            }
                            else
                            {
                                break;
                            }
                        } while (f != 1 && f != 2); // Sortir de la boucle lorsque f est 1 ou 2
                        break;
                    case 3:
                        clearScreen();
                        do
                        {
                            printf("Veuillez saisir la matricule de l'étudiant ou q/Q pour quitter:\n");
                            scanf("%s", matricule);
                            if (matricule[0] == 'q' || matricule[0] == 'Q')
                            {
                                printf("Veuillez saisir le mot de passe de l'administrateur :\n");
                                char admin_password[MDP_user];
                                int i = 0;
                                getchar(); // Capture le caractère de nouvelle ligne après la saisie précédente
                                while (1)
                                {
                                    ch = getch();

                                    if (ch == '\n')
                                    {
                                        admin_password[i] = '\0';
                                        break;
                                    }
                                    else if (ch == '\b' && i > 0)
                                    {
                                        i--;
                                        printf("\b \b");
                                    }
                                    else if (i < MDP_user - 1)
                                    {
                                        admin_password[i] = ch;
                                        printf("*");
                                        i++;
                                    }
                                }
                                if (verifPassword(admin_password))
                                {
                                    return 0; // Quitter la fonction si le mot de passe est correct
                                }
                                else
                                {
                                    printf("Mot de passe incorrect. Veuillez réessayer.\n");
                                }
                            }
                            else if (!trouverNomUtilisateur(matricule))
                            {
                                printf("L'étudiant n'existe pas\n");
                            }

                        } while (matricule[0] != 'q' && matricule[0] != 'Q');

                        break;
                    case 4:
                        int k;
                        do
                        {
                           // k = menuMessage(); // Code pour envoyer un message
                            if (k == 1)
                            {
                                /* code */
                            }
                            else if (k == 2)
                            {
                                /* code */
                            }
                            else
                            {
                                printf("choisisez un entier dans le menu\n");
                            }
                        } while (k != 1 || k != 2);

                        break;
                    case 5:
                        // Code pour quitter
                        break;
                    default:
                        printf("Choix invalide. Veuillez choisir une option valide.\n");
                        break;
                    }
                    if (rep == 5)
                    {
                        printf("au revoire\n\n");
                        break;
                    }

                } while (ch != 'q' && ch != 'Q');
            }
            else
            {
                printf("Vous êtes étudiant\n");
                do
                {
                    clearScreen();
                    rep = menuETUDIANT();
                    switch (rep)
                    {
                    case 1:
                        clearScreen();
                        MPresence(username); // Appeler la fonction MARQUER MA PRÉSENCE

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
        }
        else
        {
            printf("Erreur : Nom d'utilisateur ou mot de passe incorrect.\n");
        }
    } while (ch == 'q' || ch == 'Q');
    
    return 0;
}
