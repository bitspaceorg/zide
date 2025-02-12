#pragma once
#include "context.h"

struct App {
  App(ZD::Context &ctx);
  ~App();

  void run();
  void exit();

private:
  ZD::Context &m_ctx;

  bool m_isRunning;

  void m_init();          // Initialize application
  void m_processEvents(); // Input polling
  void m_update();        // Update State
  void m_render();        // Render within render loop
};
