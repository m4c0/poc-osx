#import <AppKit/AppKit.h>
#import <CoreFoundation/CoreFoundation.h>

@interface POCAppDelegate : NSObject<NSApplicationDelegate>
@end
@implementation POCAppDelegate
- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)app {
  return YES;
}
@end

@interface POCViewController : NSViewController
@end
@implementation POCViewController
- (void)viewDidAppear {
  NSLog(@"view did appear");
}
@end

static void run() {
  POCViewController * vc = [POCViewController new];

  NSWindow * w = [NSWindow windowWithContentViewController:vc];
  w.styleMask = NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable | NSWindowStyleMaskResizable;

  NSRect crect = NSMakeRect(0, 0, 600, 600);
  NSRect frect = [w frameRectForContentRect:crect];
  [w setFrame:frect display:YES];
  [w center];
  [w makeKeyAndOrderFront:w];

  NSApplication * a = [NSApplication sharedApplication];
  a.delegate = [POCAppDelegate new];
  [a activateIgnoringOtherApps:YES];
  [a run];
}

int main() {
  @autoreleasepool {
    run();
  }
}
