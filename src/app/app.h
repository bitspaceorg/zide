#pragma once

struct App {
  App();
  ~App();

  void run();
  void exit();

private:
  bool m_isRunning;

  void m_init();          // Initialize application
  void m_processEvents(); // Input polling
  void m_update();        // Update State
  void m_render();        // Render within render loop
};
