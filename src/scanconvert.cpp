#include <Arduino.h>
#include "scanconvert.h"

uint8_t convertScanCode(unsigned int scancode)
{
    for (int i = 0; i < KEY_MAP_SIZE; i++)
    {
        if (keymap[i][1] == scancode)
        {
            return keymap[i][0];
        }
    }
    return false;
}
