#include "history.h"
namespace ZD {
void CommandHistory::execute(Command *cmd) {
  if (!cmd)
    return;
  cmd->redo();
  m_undoStack.push(cmd);
  m_clearRedo();
};

bool CommandHistory::m_canUndo() { return !m_undoStack.empty(); }
bool CommandHistory::m_canRedo() { return !m_redoStack.empty(); }

void CommandHistory::undo() {
  if (!m_canUndo())
    return;
  Command *cmd = m_undoStack.top();
  m_undoStack.pop();
  cmd->undo();
  m_redoStack.push(cmd);
};

void CommandHistory::redo() {
  if (!m_canRedo())
    return;
  Command *cmd = m_redoStack.top();
  m_redoStack.pop();
  cmd->undo();
  m_undoStack.push(cmd);
};

void CommandHistory::m_clearUndo() {
  while (!m_undoStack.empty())
    m_undoStack.pop();
}

void CommandHistory::m_clearRedo() {
  while (!m_redoStack.empty())
    m_redoStack.pop();
}

void CommandHistory::clear() {
  m_clearRedo();
  m_clearUndo();
}
} // namespace ZD
