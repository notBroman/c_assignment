#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/*
 * a minigolf game in one dimension
 *
 * the target distance is randomly generated (40-60 m)
 * each round a force is input by the player and the new distance is calculated
 * the friction is a random number 0.25-0.75 generated each round
 *
 * when the game is done the user is asked if they want to play again
 *
 * ----------------------------------------------------------------------------------------------------------|
 * Part 1:
 *
 * every round:
 *  display state of the game
 *  read input from player
 *  calculate the new position
 *  check if at the target (wiithin 1m of target)
 *
 *
 *
 */

#define TARGET_MIN 40.0
#define TARGET_MAX 60.0

typedef struct {
    char name[20];
    double score;
} user;

double next_pos(double impulse, double pos) { //task 1.4
    double next_pos = 0.0;
    double friction_coeff;
    friction_coeff = 0.25 + drand48()*0.5; // generate random number between 0.25:0.75

    next_pos = pos + impulse/friction_coeff;

    return next_pos;
}

void draw_court(double ball, double target) { // task 1.5
    int placement_ball;
    int placement_target;

    placement_ball = (int)ball;
    placement_target = (int)target;

    for(int i = 0; i<120; i++)
    {
        if(i == placement_ball){
            printf("o");
        }
        else if(i == placement_target){
            printf("T");
        }
        else{
            printf(" ");
        }
    }
    printf("\n");
    for(int i = 0; i<120; i++)
    {
        printf("-");
    }
    printf("\n");
}

int main( int argv, char *argc[] )
{
    srand48(time(NULL));
    int exit = 0;
    double impulse = 0.0;
    char exit_char = 'x';
    double pos;
    double target;
    int round;
    FILE *fptr;
    user top_scores[3];
    char username[20];
    user tmp_score;

    while(!exit)
    {
        printf("*** Mini Golf ***\n");
        exit_char = 'x';
        pos = 0.0;
        target = 40.0 + drand48()*20;
        printf("target:\t%.2lf m\n\n",target);
        round = 0;
        while(pos < target - 1 || pos > target + 1) // within 1m of the target (task 1.6)
        {
            round++;
            printf("<Round %d>\n",round);
            draw_court(pos, target);
            printf("Impulse [N*s]: ");
            scanf("%lf",&impulse);
            printf("\n");

            pos = next_pos(impulse, pos);

        }
        // part 2
        printf("Target hit, your score: %.2lf\n\n",target/round); // task 2.1

        printf("Best scores:\n");

        // task 2.2
        fptr = fopen("minigolf.scores", "r");
        /*
         * create an empty file and open it
         */
        if(fptr == NULL){
            fptr = fopen("minigolf.scores", "w");
            fclose(fptr);
            fptr = fopen("minigolf.scores", "r");
        }

        for( int i = 0; i < 3; i++ )
        {
            if(fscanf(fptr, "%19s", &top_scores[i].name[0]) == EOF){
                printf("################\n");
                top_scores[i].score = 0;
            }
            else{
                fscanf(fptr, "%lf", &top_scores[i].score);
                printf("%s %.2lf\n",top_scores[i].name,top_scores[i].score);
            }
        }
        printf("\n");
        fclose(fptr);

        /*
         * Open file if the player is in the top 3
         * Insert it in the right spot
         */
        if(target/round > top_scores[2].score){
            scanf("%19s",&username[0]);
            fopen("minigolf.scores","w");
            for( int i = 2; i > 0; i-- ){
                /*
                 * start from smallest score
                 * if the score is between the current score and the next highest score replace current score
                 * otherwise copy the next bigger score into the current spot
                 * move to next bigger score as current score
                 * repeat until the score is between current and next bigger score
                 */
                if(target/round > top_scores[i].score && target/round < top_scores[i-1].score){
                    top_scores[i].score = target/round;
                    strcpy(top_scores[i].name, &username[0]);
                    break;
                }
                else{

                    top_scores[i].score = top_scores[i-1].score;
                    strcpy(top_scores[i].name, top_scores[i-1].name);
                }

                if(i == 1){

                    top_scores[0].score = target/round;
                    strcpy(top_scores[0].name, &username[0]);
                }
            }
            for( int i = 0; i < 3;i++){
                fprintf(fptr,"%s %.2lf\n",top_scores[i].name,top_scores[i].score);
            }
            fclose(fptr);
        }



        //task 1.7 exiting
        while(exit_char != 'y' && exit_char != 'n')
        {
            printf("Play again y/n? ");
            scanf("%c",&exit_char);
        }

        if(exit_char == 'n'){
            break;
        }
    }

    return 0;
}
