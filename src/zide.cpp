#include "app.h"

int main() {            // Zide Entry Point
  App *app = new App(); // Main Application Instance

  app->run();
  app->exit();

  return 0;
};
