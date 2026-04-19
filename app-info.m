#import <AppKit/AppKit.h>
#import <CoreFoundation/CoreFoundation.h>

int main() {
  NSApplication * a = [NSApplication sharedApplication];
  NSLog(@"App = %@", a);

  NSBundle * b = [NSBundle mainBundle];
  NSLog(@"Bundle = %@", b);

  NSDictionary * i = [b infoDictionary];
  NSLog(@"Bundle Info = %@", i);
}
