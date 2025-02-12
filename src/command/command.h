#pragma once

namespace ZD {
struct Command;

/*
 * Make the constructors of the
 * derived commands private
 * and make the factory as
 * the friend class to them.
 */

struct Command {
  virtual ~Command() {}
  virtual void undo() = 0;
  virtual void redo() = 0;
};
} // namespace ZD
