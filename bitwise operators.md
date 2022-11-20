### Bitwise AND &
Word A - 0011
Word B - 1001
Result - 0001

### Bitwise OR |
Word A - 0011
Word B - 1001
Result - 1011

### Bitwise XOR ^
Word A - 0011
Word B - 1001
Result - 1010

### Bitwise Not ~
Word A - 0011
Result - 1100

### Bitwise shift left <<
0011 << 2 = 1100
0011 << 1 = 0110

### Bitwise shift right >>
0011 >> 2 = 0000
0011 >> 1 = 0001

# Examples

Set or clear a specific bit:
```c
    byte value = 0b10000000;

    Serial.print("Start value: ");
    Serial.println(value, BIN);

    value |= 0b00001000; // for setting the bit

    Serial.print("Operation A: ");
    Serial.println(value, BIN);
    
    value &= ~(1 << 7); // for clearing the bit

    Serial.print("Operation B: ");
    Serial.println(value, BIN);

    // Output
    // Start value: 10000000
    // Operation A: 10001000
    // Operation B: 1000
```

Test is a specific bit is set:

```c
    byte value_a = 0b10001000;
    byte test_a  = 0b00001000;

    if ( value_a & test_a ) {
      Serial.println("True");
    } else {
      Serial.println("False");
    }

    byte value_b = 0b10010000;
    byte test_b  = 0b00001000;

    if ( value_b & test_b ) {
      Serial.println("True");
    } else {
      Serial.println("False");
    }

    // Output:
    // True
    // False
```