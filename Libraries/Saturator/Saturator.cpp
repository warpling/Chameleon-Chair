/*
  Saturator.cpp - Library for taking RGB values and
  pulling out pure bright colors. Idea for use with
  depressed color sensors that see the world in
  dark, drab colors.

  Created by Ryan McLeod, October 5, 2012.
  RGB -> HSV Conversion code adapted from http://en.literateprograms.org/index.php?title=Special:DownloadCode/RGB_to_HSV_color_space_conversion_(C)&oldid=17206
  HSV -> RGC Conversion code adapted from http://www.nunosantos.net/archives/114
*/

#include "Saturator.h";
#include <Printf.h>;
// constants here

  Saturator::Saturator()
  {
  // initialization here
  }

// saturates the passed in RGB color (0 - 255)
  rgb_color Saturator::saturate (int red, int green, int blue)
  {

    struct rgb_color rgbColor = {red, green, blue};
    struct hsv_color hsvColor = {0, 0, 0};


    hsvColor = rgb_to_hsv(rgbColor);

    //hsvColor.sat = 255;
    //hsvColor.val = 255;

    rgbColor = hsv_to_rgb(hsvColor);

    // for testing, super fucked up I know
    // rgbColor.r = hsvColor.hue;
    // rgbColor.g = hsvColor.sat;
    // rgbColor.b = hsvColor.val;

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

    Serial_printf("test");
    int hue = hsv.hue;
    int sat = hsv.sat;
    int lum = hsv.val;

    struct rgb_color rgbColor;

    int v;

    v = (lum < 128) ? (lum * (256 + sat)) / 256 :
          (((lum + sat) * 256) - lum * sat) / 256;
    Serial_printf("v: %d\n", v);

    if (v <= 0) {
        rgbColor.r = rgbColor.g = rgbColor.b = 0;
    } else {
        int m;
        int sextant;
        int fract, vsf, mid1, mid2;

        m = lum + lum - v;
        hue *= 6;
        sextant = hue >> 8;
        fract = hue - (sextant << 8);
        vsf = v * fract * (v - m) / v >> 8;
        mid1 = m + vsf;
        mid2 = v - vsf;
        Serial_printf("sextant: %d\n", sextant);
        switch (sextant) {
           case 0: rgbColor.r = v;    rgbColor.g = mid1; rgbColor.b = m;    return rgbColor;
           case 1: rgbColor.r = mid2; rgbColor.g = v;    rgbColor.b = m;    return rgbColor;
           case 2: rgbColor.r = m;    rgbColor.g = v;    rgbColor.b = mid1; return rgbColor;
           case 3: rgbColor.r = m;    rgbColor.g = mid2; rgbColor.b = v;    return rgbColor;
           case 4: rgbColor.r = mid1; rgbColor.g = m;    rgbColor.b = v;    return rgbColor;
           case 5: rgbColor.r = v;    rgbColor.g = m;    rgbColor.b = mid2; return rgbColor;
        }
    }
}

