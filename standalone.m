#import <AppKit/AppKit.h>
#import <CoreFoundation/CoreFoundation.h>

@interface POCAppDelegate : NSObject<NSApplicationDelegate>
@end
@implementation POCAppDelegate
// Important if you use NSWindowStyleMaskClosable
- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)app {
  return YES;
}
@end

static void run() {
  NSDictionary * info = [[NSBundle mainBundle] infoDictionary];
  NSString * name = info[@"CFBundleDisplayName"];
  if (!name) name = info[@"CFBundleName"];
  if (!name) name = @"App";

  NSWindow * w = [NSWindow new];
  w.styleMask = NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable | NSWindowStyleMaskResizable;

  NSRect crect = NSMakeRect(0, 0, 300, 200);
  NSRect frect = [w frameRectForContentRect:crect];
  [w setFrame:frect display:YES];
  [w center];
  [w makeKeyAndOrderFront:w];

  // Apple menu
  NSMenu * menu = [NSMenu new];
  [menu       addItem:[[NSMenuItem alloc]
        initWithTitle:[@"Quit " stringByAppendingString:name]
               action:@selector(terminate:)
        keyEquivalent:@"q"]];

  NSMenuItem * item = [NSMenuItem new];
  item.submenu = menu;

  NSMenu * bar = [NSMenu new];
  [bar addItem:item];

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
