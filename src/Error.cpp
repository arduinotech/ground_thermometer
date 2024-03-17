#include "Error.h"
#include <Streaming.h>
#include "hardware/Display.h"

// =================================================================
// ========================= PUBLIC ================================
// =================================================================

void Error::throwError(String message)
{
    Serial << "ERROR: " << message << endl;
    Display::getInstance()->error(message.c_str());
    delay(5000);
    exit(1);
}
