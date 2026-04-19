#import <AppKit/AppKit.h>

@interface POCAppDelegate : NSObject<NSApplicationDelegate>
@end
@implementation POCAppDelegate
// Important if you use NSWindowStyleMaskClosable
- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)app {
  return YES;
}
@end

static void run() {
  NSWindow * w = [NSWindow new];
  w.styleMask = NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable | NSWindowStyleMaskResizable;

  NSRect crect = NSMakeRect(0, 0, 300, 200);
  NSRect frect = [w frameRectForContentRect:crect];
  [w setFrame:frect display:YES];
  [w center];
  [w makeKeyAndOrderFront:w];

  // Apple menu
  NSMenu * bar = [NSMenu new];
  NSMenuItem * app_item = [NSMenuItem new];
  NSMenu * app_menu = [NSMenu new];
  [app_menu addItem:[[NSMenuItem alloc] initWithTitle:@"Quit le app"
                                               action:@selector(terminate:)
                                        keyEquivalent:@"q"]];
  app_item.submenu = app_menu;
  [bar addItem:app_item];

  NSApplication * a = [NSApplication sharedApplication];
  a.delegate = [POCAppDelegate new];
  a.mainMenu = bar;
  [a activateIgnoringOtherApps:YES];
  [a run];
}

int main() {
  @autoreleasepool {
    run();
  }
}
