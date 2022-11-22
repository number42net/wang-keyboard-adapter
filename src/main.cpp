#include <Arduino.h>
#include <PS2Keyboard.h>
#include "scanconvert.h"
#include "config.h"

PS2Keyboard keyboard;

int customKeyUp[5];
bool allKeyUp;
int ledState;
int volumeState;
uint8_t lastScanCode;

void setup()
{
    Serial.begin(115200);
    Serial1.begin(62500);

    keyboard.begin(DATA_PIN, IRQ_PIN);

    for (int x = 0; x < 6; x++)
    {
        pinMode(ledPins[x], OUTPUT);
    }
    pinMode(PIEZO_PIN, OUTPUT);

    Serial.println("Starting Wang keyboard converter");
}

void updateLeds()
{
    for (int x = 0; x < 6; x++)
    {
        if (ledState & (1 << x))
        {
            digitalWrite(ledPins[x], HIGH);
        }
        else
        {
            digitalWrite(ledPins[x], LOW);
        }
    }
}

uint8_t getMoreScanCodes()
{
    for (int i = 0; i < 10; i++)
    {
        if (keyboard.available())
        {
            return keyboard.readScanCode();
        }
        else
        {
            delay(100);
        }
    }
    return 0;
}

uint8_t checkKeyUp(uint8_t scancode)
{
    if (allKeyUp || defaultKeyUp[0] || scancode || defaultKeyUp[1] == scancode)
    {
        return scancode | 0b10000000;
    }
    for (int i = 0; i < 5; i++)
    {
        if (customKeyUp[i] == scancode)
        {
            return scancode | 0b10000000;
        }
    }

    return 0;
}

void processCommand()
{
    int data = Serial1.read();
    switch (data)
    {
    case 0x00:
        Serial.println("No-op");
        break;
    case 0x01:
        Serial.println("Key-up config with 1 parameter");
        // Apply new parameters
        for (int x = 0; x < 1; x++)
        {
            customKeyUp[x] = getMoreScanCodes();
        }
        // Reset the others
        for (int x = 1; x < 5; x++)
        {
            customKeyUp[x] = 0;
        }
        allKeyUp = false;
        break;
    case 0x02:
        Serial.println("Key-up config with 2 parameter");
        // Apply new parameters
        for (int x = 0; x < 2; x++)
        {
            customKeyUp[x] = getMoreScanCodes();
        }
        // Reset the others
        for (int x = 2; x < 5; x++)
        {
            customKeyUp[x] = 0;
        }
        allKeyUp = false;
        break;
    case 0x03:
        Serial.println("Key-up config with 3 parameter");
        // Apply new parameters
        for (int x = 0; x < 3; x++)
        {
            customKeyUp[x] = getMoreScanCodes();
        }
        // Reset the others
        for (int x = 3; x < 5; x++)
        {
            customKeyUp[x] = 0;
        }
        allKeyUp = false;
        break;
    case 0x04:
        Serial.println("Key-up config with 4 parameter");
        // Apply new parameters
        for (int x = 0; x < 4; x++)
        {
            customKeyUp[x] = getMoreScanCodes();
        }
        // Reset the others
        for (int x = 4; x < 5; x++)
        {
            customKeyUp[x] = 0;
        }
        allKeyUp = false;
        break;
    case 0x05:
        Serial.println("Key-up config with 5 parameter");
        // Reset the others
        for (int x = 5; x < 5; x++)
        {
            customKeyUp[x] = 0;
        }
        allKeyUp = false;
        break;
    case 0x06:
        Serial.println("Key-up config - All keys");
        for (int x = 0; x < 5; x++)
        {
            customKeyUp[x] = 0;
        }
        allKeyUp = true;
        break;
    case 0x07:
        Serial.println("Key-up config - Default (only shift)");
        for (int x = 0; x < 5; x++)
        {
            customKeyUp[x] = 0;
        }
        allKeyUp = false;
        break;
    case 0x08:
        Serial.println("Reset");
        for (int x = 0; x < 5; x++)
        {
            customKeyUp[x] = 0;
        }
        allKeyUp = false;
        ledState = 0;
        volumeState = 0;
        lastScanCode = 0;
        updateLeds();
        break;
    case 0x09:
        Serial.println("Keyboard ID");
        Serial1.write(0x01);
        Serial1.write(0x33);
        break;
    case 0x0A:
        Serial.println("Key click");
        tone(PIEZO_PIN, CLICK_HERTZ, CLICK_DURATION);
        break;
    case 0x0B:
        Serial.println("Beep");
        tone(PIEZO_PIN, BEEP_HERTZ, CLICK_DURATION);
        break;
    case 0x0C:
        Serial.println("Repeat last scancode sent");
        Serial1.write(lastScanCode);
        break;
    case 0x0E:
        Serial.println("Return status of DIP switches - Not yet implemented");
        // TODO
        break;
    case 0x0F:
        Serial.println("Return beeper / keyclick volume");
        Serial1.write(0x01);
        Serial1.write(volumeState);
        break;
    case 0x10:
        Serial.println("Turn on LED 1 (Lock key)");
        ledState |= (1 << 0);
        updateLeds();
        break;
    case 0x11:
        Serial.println("Turn off LED 1");
        ledState &= ~(1 << 0);
        updateLeds();
        break;
    case 0x12:
        Serial.println("Turn on LED 2");
        ledState |= (1 << 1);
        updateLeds();
        break;
    case 0x13:
        Serial.println("Turn off LED 2");
        ledState &= ~(1 << 1);
        updateLeds();
        break;
    case 0x14:
        Serial.println("Turn on LED 3");
        ledState |= (1 << 2);
        updateLeds();
        break;
    case 0x15:
        Serial.println("Turn off LED 3");
        ledState &= ~(1 << 2);
        updateLeds();
        break;
    case 0x16:
        Serial.println("Turn on LED 4");
        ledState |= (1 << 3);
        updateLeds();
        break;
    case 0x17:
        Serial.println("Turn off LED 4");
        ledState &= ~(1 << 3);
        updateLeds();
        break;
    case 0x18:
        Serial.println("Turn on LED 5");
        ledState |= (1 << 4);
        updateLeds();
        break;
    case 0x19:
        Serial.println("Turn off LED 5");
        ledState &= ~(1 << 4);
        updateLeds();
        break;
    case 0x1A:
        Serial.println("Turn on LED 6");
        ledState |= (1 << 5);
        updateLeds();
        break;
    case 0x1B:
        Serial.println("Turn off LED 6");
        ledState &= ~(1 << 5);
        updateLeds();
        break;
    case 0x1C:
        Serial.println("Turn on all LEDs");
        ledState = 0b00111111;
        updateLeds();
        break;
    case 0x1D:
        Serial.println("Turn off all LEDs");
        ledState = 0;
        updateLeds();

        break;
    case 0x1E:
        Serial.println("Get LED status");
        Serial1.write(0x01);
        Serial1.write(ledState);
        break;
    case 0x20:
        Serial.println("Set beeper / keyclick volume");
        volumeState = getMoreScanCodes();
        getMoreScanCodes();
        break;
    case 0x31:
        Serial.println("Program the sound generator - Not implemented");
        getMoreScanCodes();
        // TODO
        break;
    case 0x32:
        Serial.println("Program the sound generator - Not implemented");
        getMoreScanCodes();
        getMoreScanCodes();
        // TODO
        break;
    default:
        Serial.print("Unknown command: ");
        Serial.println(data, HEX);
    }
}

void processScanCode()
{
    uint8_t more;
    // Read the scan code
    unsigned int PS2scanCode = keyboard.readScanCode();
    switch (PS2scanCode)
    {
    case 0:
        // Don't do anything if the value is zero
        return;
        break;

    case 0xF0:
        //     // Key up code, try to fetch the 2nd part and ignore it
        more = getMoreScanCodes();
        if (more)
        {
            uint8_t wangScanCode = convertScanCode(more);
            if (wangScanCode)
            {
                uint8_t keyup = checkKeyUp(wangScanCode);
                if (keyup)
                {
                    Serial.print("Converted PS/2 key-up scan code: ");
                    Serial.print(more, HEX);
                    Serial.print(" to Wang key-up scan code: ");
                    Serial.println(keyup, HEX);
                    Serial1.write(keyup);
                    lastScanCode = keyup;
                }
            }
        }
        return;
        break;

    case 0xE0:
        // 16 bit scan code, try to fetch the 2nd part and combine them
        more = getMoreScanCodes();
        // Ignore key-up events for now
        if (more == 0xF0)
        {
            more = getMoreScanCodes();
            if (more)
            {
                uint8_t wangScanCode = convertScanCode(word(0xE0, more));
                if (wangScanCode)
                {
                    uint8_t keyup = checkKeyUp(wangScanCode);
                    if (keyup)
                    {
                        Serial.print("Converted PS/2 key-up scan code: ");
                        Serial.print(word(0xE0, more), HEX);
                        Serial.print(" to Wang key-up scan code: ");
                        Serial.println(keyup, HEX);
                        Serial1.write(keyup);
                        lastScanCode = keyup;
                    }
                }
            }

            return;
        }

        PS2scanCode = word(0xE0, more);
        break;
    }

    // Attempt to convert the scan code
    uint8_t wangScanCode = convertScanCode(PS2scanCode);
    if (wangScanCode)
    {
        Serial.print("Converted PS/2 scan code: ");
        Serial.print(PS2scanCode, HEX);
        Serial.print(" to Wang scan code: ");
        Serial.println(wangScanCode, HEX);
        // Sent to Wang if successful:
        Serial1.write(wangScanCode);
        lastScanCode = wangScanCode;
    }
    else
    {
        Serial.print("Could not convert PS/2 scan code: ");
        Serial.println(PS2scanCode, HEX);
    }
}

void loop()
{
    // Check if any commands from the Wang need to be processed
    if (Serial1.available())
    {
        processCommand();
    }
    // Check if any keyboard scan codes are available
    if (keyboard.available())
    {
        processScanCode();
    }
}
