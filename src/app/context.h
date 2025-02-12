#include "history.h"

namespace ZD {
struct Context {
  CommandHistory history;

  static Context &get() {
    static Context ctx;
    return ctx;
  }

private:
  Context() = default;

  Context(const Context &) = delete;
  Context &operator=(const Context &) = delete;
};
} // namespace ZD
