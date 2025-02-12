#include "app.h"
#include "logger.h"

// APPLICATION CONSTRUCTOR
App::App(ZD::Context &ctx) : m_ctx(ctx) {};

void App::run() {
  ZD_DEBUG("Hello from Zide !\n");
  this->m_init();

  while (true) {
    this->m_processEvents();
    this->m_update();
    this->m_render();
  }

  this->exit();
}

void App::exit() { ZD_DEBUG("Bye from Zide !\n"); }

// PRIVATE
void App::m_init() {}
void App::m_processEvents() {}
void App::m_update() {}
void App::m_render() {}

// APPLICATION DESTRUCTOR
App::~App() {}
