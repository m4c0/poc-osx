#include <CoreFoundation/CoreFoundation.h>
#include <objc/message.h>
#include <objc/runtime.h>

void NSLog(const void *, ...);

int main() {
  NSLog(CFSTR("Hello"));

  Class nsapp = objc_getClass("NSApplication");
  SEL sel = sel_getUid("sharedApplication");
  id shrapp = ((id (*)(Class, SEL))objc_msgSend)(nsapp, sel);
  NSLog(CFSTR("%@"), shrapp);
}
