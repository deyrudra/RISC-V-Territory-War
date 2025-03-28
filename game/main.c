#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "inputhandler.h"
#include "loadAssets.c"
#include "movementhandler.h"
#include "objecthandler.h"
#include "gamelogic.h"
#include "renderhandler.h"
#include "backgroundhandler.h"

// Screen Functions

//----------------------------------------------------------------------------------------

int main(void) {
  initializeBuffers();
  initializeWorld();
  initializeGame();

  // Banners
  initializeGeneralObject(&moveOrStayBannerObj, &moveorstaybanner, 0, 0, SCREEN_HEIGHT - BANNER_HEIGHT, BANNER_WIDTH, BANNER_HEIGHT);
  initializeGeneralObject(&grenadeOrStayBannerObj, &grenadeorstaybanner, 0, 0, SCREEN_HEIGHT - BANNER_HEIGHT, BANNER_WIDTH, BANNER_HEIGHT);
  initializeGeneralObject(&movementControlBannerObj, &movementcontrolbanner, 0, 0, SCREEN_HEIGHT - BANNER_HEIGHT, BANNER_WIDTH, BANNER_HEIGHT);
  
  // Game Title Screen
  initializeGeneralObject(&mainMenuTitleObj, &main_menu_title, 0, (SCREEN_WIDTH / 2) - (MAIN_MENU_TITLE_WIDTH / 2), 30, MAIN_MENU_TITLE_WIDTH, MAIN_MENU_TITLE_HEIGHT);
  
  //----- RENDER IN START SCREEN AND INITIALIZE GAME
  initializeBackground(&menuBackground, &background, BACKGROUND_WIDTH, BACKGROUND_HEIGHT);
  placeBackground(&menuBackground);
  
  // Rendering Main Menu Title
  renderIn(mainMenuTitleObj);
  destroyGeneralObject(mainMenuTitleObj);
  
  // Start the game!
  startGame();



}
