#include "grenadehandler.h"
#include "movementhandler.h"

int rotate_up_grenade_released = 1; // 1 means the key has been released
int rotate_down_grenade_released = 1;
int throw_grenade_released = 1;

double grenade_user_angle = 0;
double grenade_user_power = 0;



void initializeGrenade(Grenade* grenade, int x, int y, short int* asset, double angle, double power){

    // grenade->x = malloc(sizeof(int));
    // grenade->y = malloc(sizeof(int));
    // grenade->velocityX = malloc(sizeof(double));
    // grenade->velocityY = malloc(sizeof(double));
    // grenade->collidable = malloc(sizeof(int));
    // grenade->isGroundedBool = 0;
    // grenade->isExplodedBool = 0;
    // grenade->width = GRENADE_WIDTH;
    // grenade->height = GRENADE_HEIGHT;

    grenade->grenadeObj = malloc(sizeof(GameObject));
    grenade->grenadeObj->x = malloc(sizeof(int));
    grenade->grenadeObj->y = malloc(sizeof(int));
    grenade->grenadeObj->velocityX = malloc(sizeof(double));
    grenade->grenadeObj->velocityY = malloc(sizeof(double));
    grenade->grenadeObj->collidable = malloc(sizeof(int));
    grenade->grenadeObj->width = GRENADE_WIDTH;
    grenade->grenadeObj->height = GRENADE_HEIGHT;
    grenade->grenadeObj->asset = asset;
    grenade->grenadeObj->prevPixelData = malloc(GRENADE_HEIGHT * GRENADE_WIDTH * sizeof(short int));
    
    grenade->angle = malloc(sizeof(double));
    grenade->power = malloc(sizeof(double));

    
    double cosAngle = getCosRatio(angle);
    printf("cosAngle is %lf\n", cosAngle);
    double sinAngle = getSinRatio(angle);
    printf("sinAngle is %lf\n", sinAngle);


    // Populate gameObject data
    *(grenade->grenadeObj->x) = x;
    *(grenade->grenadeObj->y) = y;

    // flip x velocity logic depending on user facing left or right
    *(grenade->grenadeObj->velocityX) = 1.5 * power * cosAngle; // We can update the 1 as we go (scaling factor)
    printf("Upon Grenade Init VELOCITY X is: %lf\n", *(grenade->grenadeObj->velocityX));
    *(grenade->grenadeObj->velocityY) = -1.0 * power * sinAngle; // We can update the 1 as we go (scaling factor)
    printf("Upon Grenade Init VELOCITY Y is: %lf\n\n", *(grenade->grenadeObj->velocityY));
    *(grenade->grenadeObj->collidable) = 1;

    // Populate Grenade extra Grenade struct fields
    grenade->isExplodedBool = 0;
    grenade->isGroundedBool = 0;
    *(grenade->angle) = angle;
    *(grenade->power) = power;

    if (x < SCREEN_WIDTH) {
        grenade->grenadeView = LEFTVIEW;
    }
    else if ((SCREEN_WIDTH <= x) && (x < SCREEN_WIDTH*2)) {
        grenade->grenadeView = MIDDLEVIEW;
    }
    else if (SCREEN_WIDTH*2 <= x) {
        grenade->grenadeView = RIGHTVIEW;
    }
}

void destroyGrenade(Grenade* grenade){
    free(grenade->grenadeObj->x);
    free(grenade->grenadeObj->y);
    free(grenade->grenadeObj->velocityX);
    free(grenade->grenadeObj->velocityY);
    free(grenade->grenadeObj->collidable);
    free(grenade->grenadeObj->prevPixelData);

    free(grenade->angle);
    free(grenade->power);

    free(grenade->grenadeObj);
}   

double getCosRatio(int angle){
    switch(angle) {
        case 0: return COS_0;
        case 10: return COS_10;
        case 20: return COS_20;
        case 30: return COS_30;
        case 40: return COS_40;
        case 50: return COS_50;
        case 60: return COS_60;
        case 70: return COS_70;
        case 80: return COS_80;
        case 90: return COS_90;
        default: return -1;
    }
}

double getSinRatio(int angle){
    switch(angle) {
        case 0: return SIN_0;
        case 10: return SIN_10;
        case 20: return SIN_20;
        case 30: return SIN_30;
        case 40: return SIN_40;
        case 50: return SIN_50;
        case 60: return SIN_60;
        case 70: return SIN_70;
        case 80: return SIN_80;
        case 90: return SIN_90;
        default: return -1;
    }
}

void updateGrenadePosition(Grenade* grenade){
    // Update positions
    
    // if directionBool is equal to 1, then it's positive acceleration, otherwise negative acceleration

        // velocity is bounded by 1 m/s and 4m/s and we update velocity by adding acceleration*dt
        
        
        *(grenade->grenadeObj->x) = *(grenade->grenadeObj->x) + *(grenade->grenadeObj->velocityX);
        *(grenade->grenadeObj->y) = *(grenade->grenadeObj->y) + *(grenade->grenadeObj->velocityY);

    
    //Update Y velocity (we can update the 1 accordingly)

    *(grenade->grenadeObj->velocityY) += (GRAVITY * DELTATIME) / 5.0;

    // Checking which screen the grenade is on.
    if (*(grenade->grenadeObj->x) < SCREEN_WIDTH) {
        grenade->grenadeView = LEFTVIEW;
    }
    else if ((SCREEN_WIDTH <= *(grenade->grenadeObj->x)) && (*(grenade->grenadeObj->x) < SCREEN_WIDTH*2)) {
        grenade->grenadeView = MIDDLEVIEW;
    }
    else if (SCREEN_WIDTH*2 <= *(grenade->grenadeObj->x)) {
        grenade->grenadeView = RIGHTVIEW;
    }
}


void setGrenadeAngleAndPower(Grenade* grenade, double angle, double power){
    *(grenade->angle) = angle;
    *(grenade->power) = power;
}

void checkGrenadeGrounded(Grenade* grenade){
    if (grenade == NULL) {
        printf("Grenade does not exist...\n");
    }
    int right_char = *(grenade->grenadeObj->x) + GRENADE_WIDTH;
    int left_char = *(grenade->grenadeObj->x);
    int top_char = *(grenade->grenadeObj->y);
    int bottom_char = *(grenade->grenadeObj->y) + GRENADE_HEIGHT;

    int top_plat;
    int bottom_plat;
    int right_plat;
    int left_plat;

    BoundingBox *boxNode = groundBoxHead;
    int index = 0;

    while (boxNode) {
        top_plat = boxNode->y1;
        bottom_plat = boxNode->y2;
        right_plat = boxNode->x2;
        left_plat = boxNode->x1;


        // Character is between the platform, we check this b/c acceleration logic may skip pixels as it is double math
        if ((bottom_char >= top_plat) && (bottom_char <= bottom_plat)) { 
            if ((left_char <= right_plat) && (right_char >= left_plat)) {
                grenade->isGroundedBool = 1;
                printf("GRENADE HIT GROUND!----\n");
                        
                if (*(grenade->grenadeObj->velocityX) > 3) {
                    *(grenade->grenadeObj->velocityX) = 3; // Max Velocity
                }
                else if (*(grenade->grenadeObj->velocityX) < 1) {
                    *(grenade->grenadeObj->velocityX) = 0; // Min Velocity
                }
                else {
                    *(grenade->grenadeObj->velocityX) = *(grenade->grenadeObj->velocityX) *= 0.7;
                }


                if (*(grenade->grenadeObj->velocityY) > 3) {
                    *(grenade->grenadeObj->velocityY) = 3; // Max Velocity
                }
                else if (*(grenade->grenadeObj->velocityY) < 1) {
                    *(grenade->grenadeObj->velocityY) = 0; // Min Velocity
                }
                else {
                    printf("HEHE%d\n", *(grenade->grenadeObj->velocityY));
                    *(grenade->grenadeObj->velocityY) = *(grenade->grenadeObj->velocityY) *= -0.5;
                }
                

                
                
                // *(grenade->grenadeObj->velocityY) = 0.0;
                // *(character->y) = top_plat - character->height;
                return;     
            }
        }
        
        // Otherwise
        boxNode = boxNode->next;
    }
    // If not on ground.
    grenade->isGroundedBool = 0;
    return;
}

// not sure if pointer arithmetic is working pls doublecheck, we need to make sure that
void checkWithinBlastRadius(Grenade* grenade, Character** team_a, Character** team_b){
    for(int i = 0; i < NUM_CHARACTERS_PER_TEAM; i++){
        if(team_a[i]->state != DEAD){
            continue;
        }
        else{
            

            //cog is center fo gravity of characters
            int cog_x = *(team_a[i]->x) + PLAYER_WIDTH/2;
            int cog_y = *(team_a[i]->x) + PLAYER_HEIGHT/2;
            int left_bound = *(grenade->grenadeObj->x) - BLAST_RADIUS;
            int right_bound = *(grenade->grenadeObj->x) + BLAST_RADIUS;
            int bottom_bound = *(grenade->grenadeObj->y) + BLAST_RADIUS;
            int top_bound = *(grenade->grenadeObj->y) - BLAST_RADIUS;


            if(cog_x >= left_bound && cog_x <= right_bound && cog_y >= top_bound && cog_y <= bottom_bound){
                //set to within radius
                team_a[i]->withinBlastRadiusBool = 1;
            }
        }
    }

    for(int i = 0; i < NUM_CHARACTERS_PER_TEAM; i++){
        if(team_b[i]->state != DEAD){
            continue;
        }
        else{
            

            //cog is center fo gravity of characters
            int cog_x = *(team_b[i]->x) + PLAYER_WIDTH/2;
            int cog_y = *(team_b[i]->x) + PLAYER_HEIGHT/2;
            int left_bound = *(grenade->grenadeObj->x) - BLAST_RADIUS;
            int right_bound = *(grenade->grenadeObj->x) + BLAST_RADIUS;
            int bottom_bound = *(grenade->grenadeObj->y) + BLAST_RADIUS;
            int top_bound = *(grenade->grenadeObj->y) - BLAST_RADIUS;


            if(cog_x >= left_bound && cog_x <= right_bound && cog_y >= top_bound && cog_y <= bottom_bound){
                //set to within radius
                team_b[i]->withinBlastRadiusBool = 1;
            }
        }
    }
}
