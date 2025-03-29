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
  initializeGeneralObject(&moveOrStayBannerObj1, &moveorstaybanner, 0, 0, SCREEN_HEIGHT - BANNER_HEIGHT, BANNER_WIDTH, BANNER_HEIGHT);
  initializeGeneralObject(&grenadeOrStayBannerObj1, &grenadeorstaybanner, 0, 0, SCREEN_HEIGHT - BANNER_HEIGHT, BANNER_WIDTH, BANNER_HEIGHT);
  initializeGeneralObject(&movementControlBannerObj1, &movementcontrolbanner, 0, 0, SCREEN_HEIGHT - BANNER_HEIGHT, BANNER_WIDTH, BANNER_HEIGHT);
  initializeGeneralObject(&moveOrStayBannerObj2, &moveorstaybanner, 0, SCREEN_WIDTH, SCREEN_HEIGHT - BANNER_HEIGHT, BANNER_WIDTH, BANNER_HEIGHT);
  initializeGeneralObject(&grenadeOrStayBannerObj2, &grenadeorstaybanner, 0, SCREEN_WIDTH, SCREEN_HEIGHT - BANNER_HEIGHT, BANNER_WIDTH, BANNER_HEIGHT);
  initializeGeneralObject(&movementControlBannerObj2, &movementcontrolbanner, 0, SCREEN_WIDTH, SCREEN_HEIGHT - BANNER_HEIGHT, BANNER_WIDTH, BANNER_HEIGHT);
  initializeGeneralObject(&moveOrStayBannerObj3, &moveorstaybanner, 0, SCREEN_WIDTH*2, SCREEN_HEIGHT - BANNER_HEIGHT, BANNER_WIDTH, BANNER_HEIGHT);
  initializeGeneralObject(&grenadeOrStayBannerObj3, &grenadeorstaybanner, 0, SCREEN_WIDTH*2, SCREEN_HEIGHT - BANNER_HEIGHT, BANNER_WIDTH, BANNER_HEIGHT);
  initializeGeneralObject(&movementControlBannerObj3, &movementcontrolbanner, 0, SCREEN_WIDTH*2, SCREEN_HEIGHT - BANNER_HEIGHT, BANNER_WIDTH, BANNER_HEIGHT);
  
  // Game Title Screen
  initializeGeneralObject(&mainMenuTitleObj, &main_menu_title, 0, (SCREEN_WIDTH / 2) - (MAIN_MENU_TITLE_WIDTH / 2), 30, MAIN_MENU_TITLE_WIDTH, MAIN_MENU_TITLE_HEIGHT);
  
  //----- RENDER IN START SCREEN AND INITIALIZE GAME
  initializeBackground(&menuBackground, &background, BACKGROUND_WIDTH, BACKGROUND_HEIGHT);
  placeBackground(&menuBackground);
  
  // Rendering Main Menu Title
  renderIn(mainMenuTitleObj);
  destroyGeneralObject(mainMenuTitleObj);
  
  GameObject* gunObject;
  
  initializeGeneralObject(&gunObject, &gunAsset, 0, 80, 80, GUNASSET_WIDTH, GUNASSET_HEIGHT);
  renderIn(gunObject);
  
  // Start the game!
  startGame();

  return 0;

}
