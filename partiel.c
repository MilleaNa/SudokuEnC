#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Je n'ai pas réussi à générer des nombres aléatoire de depart dans la grille.. les nombres se suivent donc de 1 à 9.
//Écrire la fonction generer() qui prend en paramètre une grille de sudoku et qui affiche la grille de sudoku

void generer(int grid[9][9]) {
    int ligne, colonne;
    int numberNotNull = 0;
    int areaRegion = 3;
    printf("+---------------------+\n");
    printf("|       GRILLE        |\n");
    printf("+---------------------+\n\n");
    for (int i = 0; i < 9; i++) {
        printf(" ");
        for (int j = 0; j < 9; j++) {
            printf("%d ", grid[i][j]);
            if ((j+1) % areaRegion == 0){
                printf("");
            }
            if ((j+1) % areaRegion == 0){
                printf(" ");
            }
        }
        printf("\n");
        if ((i+1) % areaRegion == 0) {
            printf("\n");
        }
    }

    for (ligne = 0; ligne < 9; ligne++) {
        for (colonne = 0; colonne < 9; colonne++) {
            if (grid[ligne][colonne] != 0) {
                numberNotNull++;
            }
        }
    }

    printf("+-------------------------+\n");
    printf("| Nombres non nul : %d/81 |\n", numberNotNull);
    printf("+-------------------------+\n");
}

// Écrire la fonction saisir() qui prend en paramètre une grille de sudoku et qui demande à l’utilisateur de saisir

void saisir(int grid[9][9]) {
    int i,
            j,
            v;
    printf("Pour jouer, veuillez suivre les instructions : \n\n");
    printf("Choisissez votre ligne (entre 0 & 8): \n");
    scanf("%d", &i);
    printf("Choisissez votre colonne (entre 0 & 8): \n");
    scanf("%d", &j);
    printf("Choisissez la valeur (entre 1 & 9): \n");
    scanf("%d", &v);

    if(i < 0 || i > 8 || j < 0 || j > 8 || v < 1 || v > 9) {
        printf("Erreur ! Valeurs fausses.\n");
    }
    else {
        if(grid[i][j] == 0) {
            grid[i][j] = v;
        } else {
            printf("Erreur ! Cette case est déjà prise.\n");
        }
    }
}

// Écrire la fonction verifierLigneColonne() qui prend en paramètre une grille de sudoku, une valeur et un sens

int verifierLigneColonne(int grid[9][9], int value, int sens) {
    int i;
    int array[9];
    if(sens == 0) {
        for(i = 0; i < 9; i++) {
            array[i] = grid[i][value];
        }
    } else if(sens == 1) {
        for(i = 0; i < 9; i++) {
            array[i] = grid[value][i];
        }
    }

    int sum = 0;
    for(i = 0; i < 9; i++) {
        sum += array[i];
    }

    if(sum == 45) {
        return 0;
    } else {
        return 1;
    }
}

// Écrire la fonction verifierRegion() qui prend en paramètre une grille de sudoku, une ligne et une colonne

int verifierRegion(int grid[9][9], int k, int l) {
    int i, j;
    int array[9];
    int index = 0;

    for(i = 0; i < 3; i++) {
        for(j = 0; j < 3; j++) {
            array[index] = grid[i + k][j + l];
            index++;
        }
    }

    int sum = 0;
    for(i = 0; i < 9; i++) {
        sum += array[i];
    }

    if(sum == 45) {
        return 0;
    } else {
        return 1;
    }
}

// Écrire la fonction verifierGrille() qui prend en paramètre une grille de sudoku

int verifierGrille(int grid[9][9]) {
    bool area = false;
    bool line = false;
    bool column = false;
    for (int i = 3; i < 9; i += 3) {
        for(int j = 3; j < 9; j += 3) {
            if (verifierRegion(grid, i, j) == 0) {
                area = true;
            }
        }
    }

    for(int i = 0; i < 9; i++) {
        if(verifierLigneColonne(grid, i, 0) == 0) {
            line = true;
        }
        if(verifierLigneColonne(grid, i, 1) == 0) {
            column = true;
        }
    }
    if (area && line && column) {
        return 0;
    } else {
        return 1;
    }
}

// Écrire la fonction main() qui ne prend pas de paramètre et qui affiche le menu du jeu

int main(){
    srand(time(NULL));
    int i, j;
    int solution[9][9];
    printf("\n");
    for(j=0;j<9; ++j) {
        for(i=0; i<9; ++i) solution[j][i] = (i + j*3 +j /3) % 9 +1 ;
    }

    int num_to_remove  = 30;
    while (num_to_remove > 0) {
        int row = rand() % 9;
        int col = rand() % 9;
        if (solution[row][col] != 0) {
            solution[row][col] = 0;
            num_to_remove--;
        }
    }
    printf("+-----------------------------------+\n");
    printf("| Bienvenue sur le jeux du Sudoku ! |\n");
    printf("+-----------------------------------+\n\n");

    generer(solution);

    printf("\n");

    // Tant que la grille n'est pas valide, on continue de jouer

    int valid = 1;
    while(valid == 1) {
        saisir(solution);
        valid = verifierGrille(solution);
        generer(solution);
    }

    // Si la grille est valide, on affiche un message de victoire

    printf("Bien joué, vous avez gagné !\n");
    system("pause");
    return 0;
}
