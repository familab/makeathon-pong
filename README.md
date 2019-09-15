# makeathon-pong
Code for the Commander Keen Pong game we are making for the Maker Effect Foundation Makeathon 0.0

# Description

Score is shown on the analog volt display using a formula of Team 1 - Team 2 + 3 and then mapping that to 0 to 3 volts. Scoring is detected using the ultrasonic sensors. When the sensor detects an item less than the winDistance it marks a score in favour of the other team. Once a point is added the system does not score again until the ball is removed and placed back on the playing field. The game ends when a team has 4 more points than the other team. 

# Pin Out for Arduino UNO

## Ultrasonic Sensor 1
- Echo: Digital 2 (Orange)
- Trig: Digital 3 (Green)

## Ultrasonic Sensor 2
- Echo: Digital 7 (Grey)
- Trig: Digital 6 (White)

## DC Volt Analog Meter
- Input: Digital ~11
- Output: GND

## Neopixels
- Data: Digital ~9 (Blue)
