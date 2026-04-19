#import <AppKit/AppKit.h>
#import <CoreFoundation/CoreFoundation.h>

// Not really needed until you want to listen for NSApplication events
@interface App : NSApplication
@end
@implementation App
@end

int main() {
  NSWindow * w = [NSWindow new];
  [w makeKeyAndOrderFront:w];

  // You have to call using the custom class
  NSApplication * a = [App sharedApplication];
  [a activateIgnoringOtherApps:YES];
  [a run];
}
