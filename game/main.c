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
  initializeGeneralObject(&grenadeControlBannerObj1, &grenadecontrolbanner, 0, 0, SCREEN_HEIGHT - BANNER_HEIGHT, BANNER_WIDTH, BANNER_HEIGHT);
  
  
  
  initializeGeneralObject(&moveOrStayBannerObj2, &moveorstaybanner, 0, SCREEN_WIDTH, SCREEN_HEIGHT - BANNER_HEIGHT, BANNER_WIDTH, BANNER_HEIGHT);
  initializeGeneralObject(&grenadeOrStayBannerObj2, &grenadeorstaybanner, 0, SCREEN_WIDTH, SCREEN_HEIGHT - BANNER_HEIGHT, BANNER_WIDTH, BANNER_HEIGHT);
  initializeGeneralObject(&movementControlBannerObj2, &movementcontrolbanner, 0, SCREEN_WIDTH, SCREEN_HEIGHT - BANNER_HEIGHT, BANNER_WIDTH, BANNER_HEIGHT);
  initializeGeneralObject(&grenadeControlBannerObj2, &grenadecontrolbanner, 0, SCREEN_WIDTH, SCREEN_HEIGHT - BANNER_HEIGHT, BANNER_WIDTH, BANNER_HEIGHT);
  
  
  
  initializeGeneralObject(&moveOrStayBannerObj3, &moveorstaybanner, 0, SCREEN_WIDTH*2, SCREEN_HEIGHT - BANNER_HEIGHT, BANNER_WIDTH, BANNER_HEIGHT);
  initializeGeneralObject(&grenadeOrStayBannerObj3, &grenadeorstaybanner, 0, SCREEN_WIDTH*2, SCREEN_HEIGHT - BANNER_HEIGHT, BANNER_WIDTH, BANNER_HEIGHT);
  initializeGeneralObject(&movementControlBannerObj3, &movementcontrolbanner, 0, SCREEN_WIDTH*2, SCREEN_HEIGHT - BANNER_HEIGHT, BANNER_WIDTH, BANNER_HEIGHT);
  initializeGeneralObject(&grenadeControlBannerObj3, &grenadecontrolbanner, 0, SCREEN_WIDTH*2, SCREEN_HEIGHT - BANNER_HEIGHT, BANNER_WIDTH, BANNER_HEIGHT);

  
  // Game Title Screen
  initializeGeneralObject(&main_menu_background_1Obj, &main_menu_background_1, 0, 0, 0, MAIN_MENU_BACKGROUND_1_WIDTH, MAIN_MENU_BACKGROUND_1_HEIGHT);
  renderIn(main_menu_background_1Obj);
  // destroyGeneralObject(main_menu_background_1Obj);
  initializeGeneralObject(&main_menu_background_2Obj, &main_menu_background_1, 0, SCREEN_WIDTH/2, 0, MAIN_MENU_BACKGROUND_1_WIDTH, MAIN_MENU_BACKGROUND_1_HEIGHT);
  renderIn(main_menu_background_2Obj);
  // destroyGeneralObject(main_menu_background_2Obj);
  initializeGeneralObject(&main_menu_background_3Obj, &main_menu_background_1, 0, 0, SCREEN_HEIGHT/2, MAIN_MENU_BACKGROUND_1_WIDTH, MAIN_MENU_BACKGROUND_1_HEIGHT);
  renderIn(main_menu_background_3Obj);
  // destroyGeneralObject(main_menu_background_3Obj);
  initializeGeneralObject(&main_menu_background_4Obj, &main_menu_background_1, 0, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, MAIN_MENU_BACKGROUND_1_WIDTH, MAIN_MENU_BACKGROUND_1_HEIGHT);
  renderIn(main_menu_background_4Obj);
  // destroyGeneralObject(main_menu_background_4Obj);

  initializeGeneralObject(&mainMenuTitleObj, &main_menu_title, 0, (SCREEN_WIDTH / 2) - (MAIN_MENU_TITLE_WIDTH / 2), 30, MAIN_MENU_TITLE_WIDTH, MAIN_MENU_TITLE_HEIGHT);
  renderIn(mainMenuTitleObj);
  destroyGeneralObject(mainMenuTitleObj);
  initializeGeneralObject(&main_menu_enterObj, &main_menu_enter, 0, (SCREEN_WIDTH / 2) - (MAIN_MENU_ENTER_WIDTH / 2), 200, MAIN_MENU_ENTER_WIDTH, MAIN_MENU_ENTER_HEIGHT);
  renderIn(main_menu_enterObj);
  destroyGeneralObject(main_menu_enterObj);

  
  
  // Start the game!
  startGame();

  return 0;

}
