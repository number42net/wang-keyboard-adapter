#include <Arduino.h>

#define KEY_MAP_SIZE 101

inline const unsigned int keymap[KEY_MAP_SIZE][2] = {
    // Wang PS/2          Wang        PS/2
    //----------------------------------------
    {0x36, 0x76},   //    HELP        ESC
    {0x7E, 0x05},   //    INDENT      F1
    {0x7D, 0x06},   //    PAGE        F2
    {0x7C, 0x04},   //    CENTER      F3
    {0x7B, 0x0C},   //    DECTAB      F4
    {0x7A, 0x03},   //    FORMAT      F5
    {0x79, 0x0B},   //    MERGE       F6
    {0x78, 0x83},   //    NOTE        F7
    {0x77, 0x0A},   //    STOP        F8
    {0x7A, 0x01},   //    SRCH        F9
    {0x79, 0x09},   //    REPLC       F10
    {0x78, 0x78},   //    COPY        F11
    {0x77, 0x07},   //    MOVE        F12
    {0x72, 0x00},   //    COMMAND     Unassigned
    {0x71, 0x00},   //    ↑↓          Unassigned
    {0x70, 0x00},   //    Unmarked    Unassigned
    {0x11, 0x00},   //    GOTO        Unassigned
    {0x12, 0x00},   //    Cancel      Unassigned
    {0x1F, 0x0E},   //    Reverse TAB `
    {0x6E, 0x16},   //    1           1
    {0x6D, 0x1E},   //    2           2
    {0x6C, 0x26},   //    3           3
    {0x6B, 0x25},   //    4           4
    {0x6A, 0x2E},   //    5           5
    {0x69, 0x36},   //    6           6
    {0x68, 0x3D},   //    7           7
    {0x67, 0x3E},   //    8           8
    {0x66, 0x46},   //    9           9
    {0x65, 0x45},   //    0           0
    {0x2F, 0x4E},   //    -           -
    {0x64, 0x55},   //    =           =
    {0x2B, 0x66},   //    Backspace   Backspace
    {0x6F, 0x0D},   //    TAB         TAB
    {0x5F, 0x15},   //    Q           Q
    {0x5E, 0x1D},   //    W           W
    {0x5D, 0x24},   //    E           E
    {0x5C, 0x2D},   //    R           R
    {0x5B, 0x2C},   //    T           T
    {0x5A, 0x35},   //    Y           Y
    {0x59, 0x3C},   //    U           U
    {0x58, 0x43},   //    I           I
    {0x57, 0x44},   //    O           O
    {0x56, 0x4D},   //    P           P
    {0x55, 0x54},   //    []          [
    {0x54, 0x5B},   //    GL          ]
    {0x1E, 0x58},   //    Caps lock   Caps Lock
    {0x4F, 0x1C},   //    A           A
    {0x4E, 0x1B},   //    S           S
    {0x4D, 0x23},   //    D           D
    {0x4C, 0x2B},   //    F           F
    {0x4B, 0x34},   //    G           G
    {0x4A, 0x33},   //    H           H
    {0x49, 0x3B},   //    J           J
    {0x48, 0x42},   //    K           K
    {0x47, 0x4B},   //    L           L
    {0x46, 0x4C},   //    ;           ;
    {0x45, 0x52},   //    "           '
    {0x44, 0x5A},   //    Enter       Enter
    {0x1B, 0x12},   //    L SHIFT     Shift (Left)
    {0x3F, 0x1A},   //    Z           Z
    {0x3E, 0x22},   //    X           X
    {0x3D, 0x21},   //    C           C
    {0x3C, 0x2A},   //    V           V
    {0x3B, 0x32},   //    B           B
    {0x3A, 0x31},   //    N           N
    {0x39, 0x3A},   //    M           M
    {0x38, 0x41},   //    <           ,
    {0x2A, 0x49},   //    >           .
    {0x37, 0x4A},   //    ?           /
    {0x35, 0x59},   //    R SHIFT     Shift (Right)
    {0x24, 0x14},   //    Control L   Control L
    {0x2C, 0x29},   //    Space       Space
    {0x25, 0xE014}, //    Control R   Control R
    {0x62, 0xE070}, //    Insert      Insert
    {0x61, 0xE07D}, //    Prev        Page Up
    {0x53, 0xE07D}, //    Exec        Page Up
    {0x52, 0xE071}, //    Delete      Delete
    {0x51, 0xE07A}, //    Next        Page down
    {0x29, 0xE075}, //    Up          Up Arrow
    {0x2D, 0xE06B}, //    Left        Left Arrow
    {0x26, 0x00},   //    Diagonal    Unassigned
    {0x2E, 0xE072}, //    Right       Down Arrow
    {0x28, 0xE074}, //    Down        Right Arrow
    {0x60, 0x77},   //    + (Numpad)  Numlock
    {0x13, 0xE04A}, //    - (Numpad)  /
    {0x14, 0x7C},   //    x (Numpad)  *
    {0x18, 0x7B},   //    ÷ (Numpad)  -
    {0x50, 0x6C},   //    7 (Numpad)  7
    {0x15, 0x75},   //    8 (Numpad)  8
    {0x16, 0x7D},   //    9 (Numpad)  9
    {0x19, 0x79},   //    Print       +
    {0x41, 0x6B},   //    4 (Numpad)  4
    {0x40, 0x73},   //    5 (Numpad)  5
    {0x17, 0x74},   //    6 (Numpad)  6
    {0x1A, 0x00},   //    Erase       Unassigned
    {0x31, 0x69},   //    1 (Numpad)  1
    {0x30, 0x72},   //    2 (Numpad)  2
    {0x10, 0x7A},   //    3 (Numpad)  3
    {0x34, 0x70},   //    0 (Numpad)  0
    {0x32, 0x72},   //    . (Numpad)  .
    {0x1C, 0xE05A}, //    Enter       Enter
};

uint8_t convertScanCode(unsigned int scancode);
