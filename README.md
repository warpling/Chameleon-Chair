Chameleon Chair  *(Previously: Presence Bench Lighting)*
================

Our project morphed a lot over the past few weeks. We went from wanting to make a public installation in a bustling subway to realizing we had neither the time nor resources to do something so ambitious without at least first creating a small scale prototype. Our original idea was to create a subway bench installment that would light bright RGB LEDs under the seat the longer a user sat and slowly fad away after they left, leaving a sort of mark representing their past presence in time. We intended to study how people interacted with the bench and discovered what was happening as well as how people entering the station right after a subway has left, would react the slowly fading out light left behind.

This chair prototype demonstrates the main action of the bench on a small scale and also adds an additional feature: matching the color of the wearer’s shirt/jacket. This video demonstrates the desired action of the chair but is not the final working version.

<a href="http://player.vimeo.com/video/51299789" target="blank" alt="Chameleon Chair"><img src="http://f.cl.ly/items/03261m202s1g1m2r2H1y/Screen%20Shot%202012-10-13%20at%2011.22.49%20PM.png"></a>


Original Concept
================
<img src="https://a248.e.akamai.net/camo.github.com/366636e34f37729fca803dff9aaf9ef3b5cc0be2/687474703a2f2f662e636c2e6c792f6974656d732f306d30743335304e32443269325132423046304f2f42656e6368253230436f6e636570742e706e67">


The Code
================

Like all good school projects, we tried to the best of our ability to keep the code clean, well managed, and basically not a disgusting pile of stale spaghetti kludge, but like all good school projects we had a deadline and other classes so somethings are not as nice as we'd like them to be. Please keep in mind this project is a prototype and our main goal was making something that demonstrated both the actions of the chair and that it was possible in both hardware and software.

How is it broken up?

The code is broken up into **Libraries** and **Ardunio Programs**. The [Printf](https://code.google.com/p/ardurct/downloads/detail?name=Printf-v1.0.zip) and [RGBLEDControl](https://github.com/amthenia/LED) libraries are from their respective owners and the **ColorDetector**, **PersonDetector**, and **Saturator** libraries were created by us for this project. Feel free to try to use them in your own projects, but be warned although we tried to make them independent and modular, they were ultimately created with this project in mind. The Ardunio Programs are esentially testing programs for the libraries. The main code for our project is in *The Chair*.

Our libraries
--------------

**PersonDetector**: Uses a basic thermistor analog temperature sensor and 10k Ohm resistor to attempt to detect if a person is sitting on it or not. During calibration it takes readings to form a baseline and then uses a provided threshold value (varries based on resistor but usually a value of 15-40 is safe) to determine if a person is sitting on the sensor. The sensor is wired so that one lead gets 5v and the other lead is grounded through the resistor *and* the same lead goes to an analog-in port on the Arduino.

**ColorDetector**: Allows us to digital read color values from [this sensor](http://proddownloads.vertmarkets.com/download/d05d21e3/d05d21e3-42be-456c-b68d-a5a91a4245d4/original/s9706_kpic1060e08.pdf). Pinouts are in the library. Values are read in the 0-4095 range. Sensitivity can be adjusted. With more time we would have liked to have made this library fully featured for others to use, but we ran out of time. :( Please feel free to use it as a starting ground for your own library.

**Saturator**: This class does some interesting color conversions. Since we were getting very muddy dark colors from the sensor and we needed bright vibrant colors for the RGB LEDs we created this library. It takes an input color in RGB space (0-255 range), converts it into HSV space, and maxes out the saturation and value while maintaining the hue. It then converts this color back to RGB for the LED to use. The formulas used are based on [various](http://www.cs.rit.edu/~ncs/color/t_convert.html) [online](http://qscribble.blogspot.se/2008/06/integer-conversion-from-hsl-to-rgb.html) [sources](http://www.nunosantos.net/archives/114). Save yourself a lot of headache by remembering that HSL != HSV and some algorithms and online converters use different ranges (eg. 0-1.0, 0-255, 0-360).


The Hardware
===============
<ul>
	<li>RGB LED Strips</li>
	<li>Spotlight RGBW LED with heatsink</li>
	<li>Small Thermistor Sensor</li>
	<li>Color Sensor (Hamamatsu S9706)</li>
	<li>Ultra-bright white LEDs (act as a flash for the color sensor)</li>
	<li>Arduino Uno</li>
	<li>Custom built power-supply and LED drivers</li>
</ul>
