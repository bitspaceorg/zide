#include "app.h"
#include "logger.h"

// Application Constructor
App::App() {};

void App::run() {
  ZD::Logger::get()->setLogFile("../../logs");
  ZD_DEBUG("Hello from Zide !\n");
}
void App::exit() {}

// Private
void App::m_init() {}

// Application Destructor
App::~App() {}
