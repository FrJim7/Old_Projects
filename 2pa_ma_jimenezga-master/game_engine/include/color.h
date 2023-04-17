/**
* @file color.h
* @author Francisco Jimenez Garcia
* jimenezga@esat-alumni.com
*/
#ifndef __COLOR_H__
#define __COLOR_H__ 1

/**
* @brief Color struct
*
* Defines a basic struct to set colors in RGBA format.
*/
struct Color {
  /**
  * @brief Red Parameter
  *
  * Defines red value.
  */
  unsigned char r;

  /**
  * @brief Green Parameter
  *
  * Defines green value.
  */
  unsigned char g;

  /**
  * @brief Blue Parameter
  *
  * Defines blue value.
  */
  unsigned char b;
  
  /**
  * @brief Alpha Parameter
  *
  * Defines alpha value.
  */
  unsigned char a;
};

/** Predefined Black Color */
const Color kBlack = {0, 0, 0, 255};
/** Predefined White Color */
const Color kWhite = {255, 255, 255, 255};

/** Predefined Red Color */
const Color kRed = {255, 0, 0, 255};
/** Predefined Red Color */
const Color kOrange = {255, 155, 0, 255};
/** Predefined Green Color */
const Color kGreen = {0, 255, 0, 255};
/** Predefined Blue Color */
const Color kBlue = {0, 0, 255, 255};

#endif //__COLOR_H__