#pragma once
#include "command.h"
#include <stack>

namespace ZD {
struct CommandHistory {
  void execute(Command *cmd);

  void undo();
  void redo();

  void clear();

private:
  std::stack<Command *> m_undoStack, m_redoStack;

  bool m_canUndo();
  bool m_canRedo();

  void m_clearRedo();
  void m_clearUndo();
};
} // namespace ZD
