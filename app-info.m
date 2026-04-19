#import <AppKit/AppKit.h>
#import <CoreFoundation/CoreFoundation.h>

// This is an example of how an executable behaves depending on the current
// bundle. You can test it by running in current folder or in the corresponding
// "app"
int main() {
  NSApplication * a = [NSApplication sharedApplication];
  NSLog(@"App = %@", a);

  NSBundle * b = [NSBundle mainBundle];
  NSLog(@"Bundle = %@", b);

  NSDictionary * i = [b infoDictionary];
  NSLog(@"Bundle Info = %@", i);

  NSWindow * w = [NSWindow new];
  [w makeKeyAndOrderFront:w];

  [a activateIgnoringOtherApps:YES];
  [a run];
}
