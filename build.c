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

static int compile(char * name) {
  char src[1024];
  sprintf(src, "%s.c", name);

  char * args[] = {
    "clang", "-Wall", "-g",
    "-framework", "AppKit",
    "-o", name, src, 0 };
  if (run(args)) return 1;

  return 0;
}

static int appinfo_example() {
  { char * args[] = {
      "clang", "-Wall", "-g",
      "-framework", "AppKit",
      "-o", "app-info", "app-info.m", 0 };
    if (run(args)) return 1; }

  { char * args[] = { "cp", "app-info", "app-info.app/Contents/MacOS/", 0 };
    if (run(args)) return 1; }

  return 0;
}

int main(int argc, char ** argv) {
  if (argc != 1) return (usage(), 1);

  if (compile("build"       )) return 1;
  if (compile("objc-runtime")) return 1;

  if (appinfo_example()) return 1;

  return 0;
}
