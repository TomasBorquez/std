#include "base/base.h"

int main(void) {
  std.Begin();
  // Start
  {
    Arena arena = ArenaInit(8080);

    char buffer[PATH_MAX];
    GetCwd(buffer, sizeof(buffer));
    logger.Info("%s", buffer);

    arena.Free(&arena);
  }
  std.End();
}
