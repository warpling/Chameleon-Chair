/*
  Saturator.cpp - Library for taking RGB values and
  pulling out pure bright colors. Idea for use with
  depressed color sensors that see the world in
  dark, drab colors.

  Created by Ryan McLeod, October 5, 2012.
  RGB -> HSV Conversion code adapted from http://en.literateprograms.org/index.php?title=Special:DownloadCode/RGB_to_HSV_color_space_conversion_(C)&oldid=17206
  HSV -> RGC Conversion code adapted from http://www.nunosantos.net/archives/114
*/

#include "Saturator.h"
#include <Printf.h>
#include <stdint.h>
// constants here

  Saturator::Saturator()
  {
    // initialization here
  }

  // saturates the passed in RGB color (0 - 255) using the HSV color space
  // and then converts it back to RGB.
  rgb_color Saturator::saturate (int red, int green, int blue)
  {

    struct rgb_color rgbColor = {red, green, blue};
    struct hsv_color hsvColor = {0, 0, 0};

    // Convert to HSV
    hsvColor = rgb_to_hsv(rgbColor);

    // Max out the saturation and brightness value so
    // we get a nice bright saturated color
    hsvColor.sat = 255;
    hsvColor.val = 255;

    // Convert back to RGB
    rgbColor = hsv_to_rgb(hsvColor);

    return rgbColor;
}

struct hsv_color Saturator::rgb_to_hsv (struct rgb_color rgb) {
    struct hsv_color hsv;
    unsigned char rgb_min, rgb_max;
    rgb_min = MIN3(rgb.r, rgb.g, rgb.b);
    rgb_max = MAX3(rgb.r, rgb.g, rgb.b);
    hsv.val = rgb_max;

    if (hsv.val == 0) {
      hsv.hue = hsv.sat = 0;
      return hsv;
    }
    hsv.sat = 255*long(rgb_max - rgb_min)/hsv.val;
    if (hsv.sat == 0) {
        hsv.hue = 0;
        return hsv;
    }
      /* Compute hue */
    if (rgb_max == rgb.r)
        hsv.hue = 0 + 43*(rgb.g - rgb.b)/(rgb_max - rgb_min);
    
    else if (rgb_max == rgb.g)
        hsv.hue = 85 + 43*(rgb.b - rgb.r)/(rgb_max - rgb_min);
    
    else /* rgb_max == rgb.b */ 
        hsv.hue = 171 + 43*(rgb.r - rgb.g)/(rgb_max - rgb_min);
    
    return hsv;
}

struct rgb_color Saturator::hsv_to_rgb (struct hsv_color hsv)
{

    double h = 360 * (hsv.hue/255.0);
    double s = hsv.sat / 255.0;
    double v = hsv.val / 255.0;

    struct rgb_color rgbColor;

    int i;
    float f, p, q, t;
    if( s == 0 ) {
        // achromatic (grey)
        rgbColor.r = rgbColor.g = rgbColor.b = 255 * v;
        return rgbColor;
    }
    h /= 60;            // sector 0 to 5
    i = floor( h );
    f = h - i;          // factorial part of h
    p = v * ( 1 - s );
    q = v * ( 1 - s * f );
    t = v * ( 1 - s * ( 1 - f ) );

    switch( i ) {
        case 0:
            rgbColor.r = 255 * v;
            rgbColor.g = 255 * t;
            rgbColor.b = 255 * p;
            return rgbColor;
        case 1:
            rgbColor.r = 255 * q;
            rgbColor.g = 255 * v;
            rgbColor.b = 255 * p;
            return rgbColor;
        case 2:
            rgbColor.r = 255 * p;
            rgbColor.g = 255 * v;
            rgbColor.b = 255 * t;
            return rgbColor;
        case 3:
            rgbColor.r = 255 * p;
            rgbColor.g = 255 * q;
            rgbColor.b = 255 * v;
            return rgbColor;
        case 4:
            rgbColor.r = 255 * t;
            rgbColor.g = 255 * p;
            rgbColor.b = 255 * v;
            return rgbColor;
        default:        // case 5:
            rgbColor.r = 255 * v;
            rgbColor.g = 255 * p;
            rgbColor.b = 255 * q;
            return rgbColor;
    }
}

