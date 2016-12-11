# What is it?
Simply put, it's a controller that drives a PCA9685 12-bit PWM driver.

# How it's made
ATmega16A programmed using modern-ish C++ fetches brightness patterns from program memory, interpolates them and sends them through I2C to two PWM drivers. Each LED can have it's pattern set individualy.

# Why have you made it?
This project started as simple lamp built from 30-50 small white LEDs.
- Then I wanted dimming.
- Then I wanted the circuit to be small.
- Then I wanted multiple patterns that can be displayed.
- Then I wanted to be able to control those patterns.
- Then I decided I will write generalised C++11(or higher) zero-cost-abstractions embedded library to help with the development. 
- Then I threw that idea out. 
- Meanwhile I started thinking about a language designed specifically for a embedded devices, something like a VHDL but more high level that could be translated to given platform C or asm.
That idea shared the fate of the previous one(but I'm still thinking about it).
Then I designed the PCB. After that an idea popped into my head that the lamp could be controlled through serial port from something like ESP8266. IoT anyone?
- The last thing I wanted is to program it using C++ so I could use some of it's nice features like namespaces and templates(used in one place, YAY!).

## Results

Something like 2 years passed from the original idea, some work was done, some was not. But the time has come. 2017 is coming and THAT ONE LITTLE CORNER IN MY HOUSE IS STILL EMPTY AND NOT LIT!
Right now, the lamp hardware is mostly made(90%). The code needs some work. I know I wont be able to finish ALL of my original plans. I just want to make it work and then it can stay in that corner for next two years. Then I could write <strike>a bootloader that would enable me to program the lamp through WiFi</strike> the rest of code needed to realise plans conceived since the work on this project begun.
