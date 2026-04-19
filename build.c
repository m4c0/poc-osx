#include <sys/stat.h>
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void usage() {
  fprintf(stderr, "just call 'build' without arguments\n");
}

static int run(char ** args) {
  assert(args && args[0]);

  pid_t pid = fork();
  if (pid == 0) {
    execvp(args[0], args);
    abort();
  } else if (pid > 0) {
    int sl = 0;
    assert(0 <= waitpid(pid, &sl, 0));
    if (WIFEXITED(sl)) return WEXITSTATUS(sl);
  }

  fprintf(stderr, "failed to run child process: %s\n", args[0]);
  return 1;
}

static int cc(char * src, char * exe) {
  char * args[] = {
    "clang", "-Wall", "-g",
    "-framework", "AppKit",
    "-o", exe, src, 0 };
  return run(args);
}
#define compile(S) cc(S ".c", S)

int main(int argc, char ** argv) {
  if (argc != 1) return (usage(), 1);

  if (compile("objc-runtime")) return 1;

  // Use this example to see the different behaviour between running inside or
  // outside a bundle. Mainly, notice how Cmd-Q propagates to terminal when you
  // run outside the bundle
  if (cc("app-info.m", "app-info")) return 1;
  if (cc("app-info.m", "app-info.app/Contents/MacOS/app-info")) return 1;

  mkdir("standalone.app", 0777);
  mkdir("standalone.app/Contents", 0777);
  mkdir("standalone.app/Contents/MacOS", 0777);
  if (cc("standalone.m", "standalone.app/Contents/MacOS/standalone")) return 1;

  return 0;
}
