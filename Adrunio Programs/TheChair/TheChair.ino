// The Chair's main code

// Globals
//   - ALL PINS
//   - target color
//   - light intensity
//   - person sitting?

// Setup
//   Main Calibration
//   - we should be setting all values here in constants (eg. person heat, sensitivity, pins, etc)
//   - calibrate person detection code (currently set to a three second calibration) it would
//     be good to flash the LEDs somehow to let us know not to sit on the chair at this time.
//  - calibrate any other libraries with sensitivites, pins, etc

// Loop

//
//   Check if person is detected
//   If person detected and wasn't there before, take color reading (do colorspace calculations, etc)
//   If person is sitting incremement brightness
//   If person no longer sitting, decrement brightness
//   Set LEDs to new target color/brightness

