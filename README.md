🎨 Color Recognition System with Voice Output
Assistive Device for the Visually Impaired using Arduino Nano

📌 Overview
This project presents a low-cost, portable color recognition system designed to assist visually impaired users in identifying object colors independently.

The device uses:
>  Arduino Nano as the main controller
>  TCS34725 color sensor for RGB detection
>  k-Nearest Neighbor (k-NN) algorithm for color classification
>  DFPlayer Mini for voice output

When the user presses a button, the device detects the color of an object and announces it through a speaker.

🎯 Objectives
>  Develop a compact and affordable assistive device
>  Implement lightweight color classification directly on a microcontroller
>  Provide real-time voice feedback
>  Ensure portability using rechargeable batteries

🛠 Hardware Components
Component	                      Function
Arduino Nano	                  Main microcontroller
TCS34725 RGB Sensor	            Captures object color in RGB
DFPlayer Mini	                  Plays audio feedback
8Ω Speaker	                    Outputs voice
Push Button                    	Triggers detection
2x 18650 Batteries	            Power supply
3D Printed Case (PLA)	          Enclosure

⚙️ System Architecture
System Flow
1. User presses push button
2. Sensor reads RGB values
3. RGB converted to HSV
4. HSV normalized
5. 1-NN classification applied
6. Corresponding audio file played
7. System returns to idle state

🧠 Algorithm Implementation
1️⃣ RGB to HSV Conversion
Steps:
>  Normalize R, G, B to [0,1]
>  Compute:
    >  Max = max(R,G,B)
    >  Min = min(R,G,B)
    >  V = Max
    >  S = (Max − Min) / Max
>  Compute Hue based on dominant channel

2️⃣ Normalization
Each HSV component normalized:
x' = (x − xmin) / (xmax − xmin)

3️⃣ k-NN Classification (k = 1)
Euclidean distance:
d = √((H1−H2)² + (S1−S2)² + (V1−V2)²)

Nearest HSV reference determines the color label.
The dataset is stored directly in the Arduino code as:
{H, S, V, "color.mp3"}

🔊 Audio Output
>  Pre-recorded color names stored in microSD card
>  DFPlayer Mini plays matching .mp3 file
>  Example files:
  >  red.mp3
  >  blue.mp3
  >  green.mp3
  >  etc.

🔬 Testing & Results
The system was tested under:
>  Different lighting conditions
>  Object distances (0 cm and 3 cm)
>  Challenging colors (black, gray, white)

Results show reliable recognition of basic colors under stable lighting.

📦 Physical Design
>  3D printed PLA casing
>  Approximate dimensions: 10 cm × 6 cm × 5.5 cm
>  Front sensor opening
>  Top push button
>  Speaker vent holes
>  Portable and standalone

🚀 Features
✔ Portable
✔ Low-cost components
✔ Standalone (no external display needed)
✔ Real-time voice feedback
✔ Lightweight classification algorithm

📈 Possible Improvements
>  Expand dataset for more color variations
>  Add adaptive lighting compensation
>  Implement k > 1 voting
>  Add rechargeable charging circuit (TP4056)
>  Add haptic feedback option

📚 Keywords
Color Recognition, Assistive Technology, Arduino Nano, TCS34725, k-NN, Voice Output, Embedded System

👨‍💻 Authors
Ivan Alexander
Marcel Saputra
Arizal Ismoyo Wijanarko
