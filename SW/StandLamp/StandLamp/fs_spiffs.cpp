#include <FS.h>
bool fs_init()
{
  bool FS_result;
  FS_result = SPIFFS.begin();
#ifdef SERIAL_DEBUG
  Serial.print("FS: Initializing - ");
  Serial.println(FS_result ? "Succeded" : "Failed");
#endif
  return FS_result;
}

