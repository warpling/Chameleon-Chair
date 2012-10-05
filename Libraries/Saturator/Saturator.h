/*
  Saturator.h - Library for taking RGB values and
  pulling out pure bright colors. Idea for use with
  depressed color sensors that see the world in
  dark, drab colors.

  Created by Ryan McLeod, October 5, 2012.
  RGB -> HSV Conversion code adapted from http://en.literateprograms.org/index.php?title=Special:DownloadCode/RGB_to_HSV_color_space_conversion_(C)&oldid=17206
  HSV -> RGC Conversion code adapted from http://www.nunosantos.net/archives/114
*/

#ifndef Saturator_h
#define Saturator_h

#define MIN3(x,y,z)  ((y) <= (z) ? \
                         ((x) <= (y) ? (x) : (y)) \
                     : \
                         ((x) <= (z) ? (x) : (z)))

#define MAX3(x,y,z)  ((y) >= (z) ? \
                         ((x) >= (y) ? (x) : (y)) \
                     : \
                         ((x) >= (z) ? (x) : (z)))

struct rgb_color {
    int r, g, b;    /* Channel intensities between 0 and 255 */
};

struct hsv_color {
    int hue;        /* Hue degree between 0 and 255 */
    int sat;        /* Saturation between 0 (gray) and 255 */
    int val;        /* Value between 0 (black) and 255 */
};

class Saturator
{
  public:
    Saturator();
    rgb_color saturate (int red, int green, int blue);
    struct hsv_color rgb_to_hsv (struct rgb_color rgb);
	struct rgb_color hsv_to_rgb (struct hsv_color hsv);
};	

#endif

