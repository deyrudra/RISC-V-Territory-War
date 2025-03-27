#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "inputhandler.h"
#include "loadAssets.c"
#include "movementhandler.h"
#include "objecthandler.h"
#include "gamelogic.h"
#include "renderhandler.h"

// Screen Functions

//----------------------------------------------------------------------------------------

int main(void) {
  /* set front pixel buffer to Buffer 1 */
  *(buffer_register + 1) =
      (int)&Buffer1;  // first store the address in the  back buffer
  /* now, swap the front/back buffers, to set the front buffer location */
  wait_for_vsync();
  // after this functin the back_buffer register content,
  // has swapped with the front_buffer register content

  /* initialize a pointer to the pixel buffer, used by drawing functions */
  pixel_buffer_start = *buffer_register;
  clear_screen();  // pixel_buffer_start points to the pixel buffer

  /* set back pixel buffer to Buffer 2 */
  *(buffer_register + 1) = (int)&Buffer2;
  // *(buffer_register + 1) = (int) &Buffer1; // Making it one buffer only.
  pixel_buffer_start = *(buffer_register + 1);  // we draw on the back buffer
  clear_screen();  // pixel_buffer_start points to the pixel buffer

  initializeGame();

  // 40x40 brick wall,
  backgroundObj = (GameObject*)malloc(sizeof(GameObject));
  int backgroundPrevData[BACKGROUND_HEIGHT][BACKGROUND_WIDTH];
  backgroundObj->asset = &background;
  backgroundObj->collidable = &(int){0};
  backgroundObj->height = BACKGROUND_HEIGHT;
  backgroundObj->width = BACKGROUND_WIDTH;
  backgroundObj->prevPixelData = &backgroundPrevData;
  backgroundObj->isGround = 0;

  // 40x40 sky block
  skyObj = (GameObject*)malloc(sizeof(GameObject));
  int skyPrevData[SKY_HEIGHT][SKY_WIDTH];
  skyObj->asset = &sky;
  skyObj->collidable = &(int){0};
  skyObj->height = SKY_HEIGHT;
  skyObj->width = SKY_WIDTH;
  skyObj->prevPixelData = &skyPrevData;
  skyObj->isGround = 0;

  // 320 x 40 move or stay banner
  moveOrStayBannerObj = (GameObject*)malloc(sizeof(GameObject));
  int moveOrStayBannerPrevData[BANNER_HEIGHT][BANNER_WIDTH];
  moveOrStayBannerObj->asset = &moveorstaybanner;
  moveOrStayBannerObj->x = &(int){0};  // casting to addr since x and y as ptrs
  moveOrStayBannerObj->y = &(int){SCREEN_HEIGHT - BANNER_HEIGHT};   
  moveOrStayBannerObj->collidable = &(int){0};
  moveOrStayBannerObj->height = BANNER_HEIGHT;
  moveOrStayBannerObj->width = BANNER_WIDTH;
  moveOrStayBannerObj->prevPixelData = &moveOrStayBannerPrevData;
  moveOrStayBannerObj->isGround = 0;


  // 320 x 40 move or stay banner
  grenadeOrStayBannerObj = (GameObject*)malloc(sizeof(GameObject));
  int grenadeOrStayBannerPrevData[BANNER_HEIGHT][BANNER_WIDTH];
  grenadeOrStayBannerObj->asset = &grenadeorstaybanner;
  grenadeOrStayBannerObj->x = &(int){0};  // casting to addr since x and y as ptrs
  grenadeOrStayBannerObj->y = &(int){SCREEN_HEIGHT - BANNER_HEIGHT};   
  grenadeOrStayBannerObj->collidable = &(int){0};
  grenadeOrStayBannerObj->height = BANNER_HEIGHT;
  grenadeOrStayBannerObj->width = BANNER_WIDTH;
  grenadeOrStayBannerObj->prevPixelData = &grenadeOrStayBannerPrevData;
  grenadeOrStayBannerObj->isGround = 0;


  // game title screen
  mainMenuTitleObj = (GameObject*)malloc(sizeof(GameObject));
  int mainMenuTitlePrevData[MAIN_MENU_TITLE_HEIGHT][MAIN_MENU_TITLE_WIDTH];
  mainMenuTitleObj->x = &(int){SCREEN_WIDTH - MAIN_MENU_TITLE_WIDTH - 40};  // casting to addr since x and y as ptrs
  mainMenuTitleObj->y = &(int){10};
  mainMenuTitleObj->asset = &main_menu_title;
  mainMenuTitleObj->collidable = &(int){0};
  mainMenuTitleObj->height = MAIN_MENU_TITLE_HEIGHT;
  mainMenuTitleObj->width = MAIN_MENU_TITLE_WIDTH;
  mainMenuTitleObj->prevPixelData = &mainMenuTitlePrevData;  // prev data for keeping track of background
  mainMenuTitleObj->isGround = 0;

  // pass in assets and prev backgrounds


  //----- RENDER IN START SCREEN AND INITIALIZE GAME

  // Rendering Background
  for (int ypos = 0; ypos < SCREEN_HEIGHT; ypos += 40) {
    for (int xpos = 0; xpos < SCREEN_WIDTH; xpos += 40) {
      backgroundObj->x = &xpos;
      backgroundObj->y = &ypos;
      renderIn(backgroundObj);
    }
  }

  // Rendering Main Menu Title
  renderIn(mainMenuTitleObj);  

  startGame();

}

// make new .c file platformhandler
// make GameObject* platform
// copy rudra code commented out testing __code_model_medium
// xy tracking top left
// once done in main

// go to while loop
// render in (GameObject* platform)
