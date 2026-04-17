#include <CoreFoundation/CoreFoundation.h>
#include <objc/message.h>
#include <objc/runtime.h>

void NSLog(const void *, ...);

void create_window() {
  Class nswnd = objc_getClass("NSWindow");
  SEL sel = sel_getUid("new");
  id wnd = ((id (*)(Class, SEL))objc_msgSend)(nswnd, sel);

  sel = sel_getUid("setAcceptsMouseMovedEvents:");
  ((void (*)(id, SEL, int))objc_msgSend)(wnd, sel, 1);

  // NSWindowCollectionBehaviorFullScreenPrimary);
  sel = sel_getUid("setCollectionBehavior:");
  ((void (*)(id, SEL, int))objc_msgSend)(wnd, sel, 128);

  // NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable | NSWindowStyleMaskResizable
  sel = sel_getUid("setStyleMask:");
  ((void (*)(id, SEL, int))objc_msgSend)(wnd, sel, 15);

  CGRect rect = (CGRect) {{ 0, 0 }, { 800, 600 }};
  sel = sel_getUid("frameRectForContentRect:");
  rect = ((CGRect (*)(id, SEL, CGRect))objc_msgSend)(wnd, sel, rect);

  sel = sel_getUid("setFrame:display:");
  ((void (*)(id, SEL, CGRect, int))objc_msgSend)(wnd, sel, rect, 1);
 
  //wnd.contentView = [CASView new];

  sel = sel_getUid("makeKeyAndOrderFront:");
  ((void (*)(id, SEL, id))objc_msgSend)(wnd, sel, wnd);
}

int main() {
  NSLog(CFSTR("Hello"));

  Class nsapp = objc_getClass("NSApplication");
  SEL sel = sel_getUid("sharedApplication");
  id shrapp = ((id (*)(Class, SEL))objc_msgSend)(nsapp, sel);

  create_window();

  sel = sel_getUid("activateIgnoringOtherApps:");
  ((void (*)(id, SEL, int))objc_msgSend)(shrapp, sel, 1);

  sel = sel_getUid("run");
  ((void (*)(id, SEL))objc_msgSend)(shrapp, sel);
}
