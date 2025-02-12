#include "app.h"

int main() {                             // Zide Entry Point
  ZD::Context &ctx = ZD::Context::get(); // Application Context
  App *app = new App(ctx);               // Main Application Instance

  app->run();
  app->exit();

  return 0;
};
