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
    int rep, cpt = 0,i,f;
do
{
    connect(username, password);

    printf("\nAuthentification réussie !\n");

    if (Authentification(username, password, "vigile.txt")) {
        if (!verify_id_ETU(username, password, "vigile.txt")) {
            printf("Vous êtes administrateur\n");
            do {
                cpt = 0;
                rep = menuadmin();
                switch (rep) {
                    case 1:
                        
                        // Appeler la fonction GESTION DES ÉTUDIANTS
                        break;
                    case 2:// Appeler la fonction GÉNÉRATION DE fichier
                            
                           do
                           {
                                 f=menu_fichier_present();
                                if (f==1) 
                                {
                                    dessinerTableau("listPresant.txt");
                                }else
                                {
                                     const char *filename = "listPresant.txt";
                                     char *date; // Changez cette valeur pour la date que vous souhaitez utiliser
                                    saisirDateFrancaise(date);
                                    dessinerTableauDate(filename, date);
                                }
                                if (f!=1 || f!=2) 
                                {
                                    break;
                                }
                                
                           } while (f!=1 || f!=2);
                            
                        break;
                    case 3:
                        do
                        {   
                            if (rep==5)
                            {
                                break;
                            }
                            
                            rep = menuadmin(); 
                            do {
                                
                                printf("Veuillez saisir la matricule de l'etudiant:\n");
                                scanf("%s", matricule);
                            } while (!trouverNomUtilisateur(matricule));
                            
                        } while (rep >=1 && rep < 5);
                        
                        
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
