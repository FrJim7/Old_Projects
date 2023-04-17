/**
 * Francisco Jimenez Garcia <jimenezga@esat-alumni.com>
 * 2019 - 2020
 */
#ifndef __TYPE_DEF_H__
#define __TYPE_DEF_H__ 1

#include <stdint.h>

/**
 * Declaration of types used by the ADT.
 */
typedef uint8_t         u8;
typedef int_least8_t    s8;
typedef uint16_t        u16;
typedef int_least16_t   s16;
typedef uint32_t        u32;
typedef int_least32_t   s32;
typedef uint64_t        u64;
typedef int_least64_t   s64;

/**
 * Used to avoid size parameter in set_data function.
 */
const s16 kNoSizeNeeded = -1;

/**
 * @brief      Error Codes
 *
 *             Error codes used by the functions in ADT.
 */
enum ErrorCode {
  kErrorCode_OK = 0,
  kErrorCode_NullptrNode = -1,
  kErrorCode_NullptrRefN = -2,
  kErrorCode_NewNodeFail = -3,
  ////////////////////////////
  kErrorCode_InvalidData = -5,
  kErrorCode_InvalidSize = -6,
  ////////////////////////////
  kErrorCode_NullVector    = -10,
  kErrorCode_NullptrVector = -11,
  kErrorCode_NullStorage   = -12,
  kErrorCode_NullSource    = -13,
  kErrorCode_InvalidPos    = -14,
  kErrorCode_FullVector    = -15,
};

#endif//__TYPE_DEF_H__