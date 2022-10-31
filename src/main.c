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

    while(!exit)
    {
        printf("*** Mini Golf ***\n");
        pos = 0.0;
        target = 40.0 + drand48()*20;
        printf("target:\t%.2lf m\n\n",target);
        round = 0;
        while(pos < target - 1 || pos > target + 1) // within 1m of the target
        {
            round++;
            printf("<Round %d>\n",round);
            draw_court(pos, target);
            printf("Impulse [N*s]: ");
            scanf("%lf",&impulse);
            printf("\n");

            pos = next_pos(impulse, pos);

        }
        printf("Target hit, your score: %.2lf\n",target/round);

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
