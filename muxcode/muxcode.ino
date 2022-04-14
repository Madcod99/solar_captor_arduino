#include <ArduinoJson.h>

// // Mux digital control pins for first MUX
// int s0 = 8;
// int s1 = 9;
// int s2 = 10;
// int s3 = 11;

// // Mux digital control pins for second MUX
// int m0 = 4;
// int m1 = 5;
// int m2 = 6;
// int m3 = 7;

// control pin
// int controlPin[2][4] = {
//     {s0, s1, s2, s3},
//     {m0, m1, m2, m3}
// };
int controlPin[2][4] = {
    {8, 9, 10, 11}, // digital pin for MUX 1
    {4, 5, 6, 7}    // digital pin for MUX 2
};

// each channel must be connected to an LM35
int muxChannel[16][4] = {
    {0, 0, 0, 0}, // channel 0
    {1, 0, 0, 0}, // channel 1
    {0, 1, 0, 0}, // channel 2
    {1, 1, 0, 0}, // channel 3
    {0, 0, 1, 0}, // channel 4
    {1, 0, 1, 0}, // channel 5
    {0, 1, 1, 0}, // channel 6
    {1, 1, 1, 0}, // channel 7
    {0, 0, 0, 1}, // channel 8
    {1, 0, 0, 1}, // channel 9
    {0, 1, 0, 1}, // channel 10
    {1, 1, 0, 1}, // channel 11
    {0, 0, 1, 1}, // channel 12
    {1, 0, 1, 1}, // channel 13
    {0, 1, 1, 1}, // channel 14
    {1, 1, 1, 1}  // channel 15
};

// Mux in "SIG" pin
int SIG_pin1 = A0;
int SIG_pin2 = A1;

void setup()
{
    // activer le serial
    Serial.begin(9600);

    // mettre les pins digitaux en OUTPUT.
    for (int i = 0; i < 4; i++)
    {
        pinMode(controlPin[0][i], OUTPUT);
        pinMode(controlPin[1][i], OUTPUT);
    }

    // mettres les pins en LOW
    for (int i = 0; i < 4; i++)
    {
        digitalWrite(controlPin[0][i], LOW);
        digitalWrite(controlPin[1][i], LOW);
    }
}

void loop()
{
    delay(50);
    // read the LM35 from first Mux
    for (int i = 0; i < 16; i++)
    {
        Serial.print(readMux(i, 0, SIG_pin1));
        Serial.print(" ");
    }
    // read the LM35 from second Mux
    for (int i = 0; i < 16; i++)
    {
        Serial.print(readMux(i, 1, SIG_pin2));
        Serial.print(" ");
    }
    // read the DHT22 from digital pin

    // Loop through and read all 16 values
    for (int i = 0; i < 16; i++)
    {
        Serial.print(readMux1(i));
        Serial.print(" ");
    }
    delay(30);
    Serial.println("");
}

float readMux(int channel, int pinline, int signalpin)
{
    // loop through the 4 sig
    for (int i = 0; i < 4; i++)
    {
        digitalWrite(controlPin[pinline][i], muxChannel[channel][i]);
    }
    // read the value at the SIG pin
    int val = analogRead(signalpin);
    float value = (val * 500.0) / 1024;
    return value;
}
