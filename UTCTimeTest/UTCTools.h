
#ifndef UTC_CLOCK_H
#define UTC_CLOCK_H

#ifdef __cplusplus
extern "C"
{
#endif

typedef unsigned char uint8_t;
typedef char int8;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

/*********************************************************************
 * INCLUDES
 */

/*********************************************************************
 * MACROS
 */

/*********************************************************************
 * CONSTANTS
 */

/*********************************************************************
 * TYPEDEFS
 */

 #define MIN_UTC_SECONDS (536112000)

// number of seconds since 0 hrs, 0 minutes, 0 seconds, on the
// 1st of January 2000 UTC
typedef uint32_t UTCTime;

// UTC time structs broken down until standard components.
typedef struct
{
  uint8_t seconds;  // 0-59
  uint8_t minutes;  // 0-59
  uint8_t hour;     // 0-23
  uint8_t day;      // 0-30
  uint8_t month;    // 0-11
  uint16_t year;    // 2000+ 
} UTCTimeStruct;

/*
 * Converts UTCTime to UTCTimeStruct
 *
 * secTime - number of seconds since 0 hrs, 0 minutes,
 *          0 seconds, on the 1st of January 2000 UTC
 * tm - pointer to breakdown struct
 */
extern void UTC_convertUTCTime(UTCTime secTime, UTCTimeStruct *tm);

/*
 * Converts UTCTimeStruct to UTCTime (seconds since 00:00:00 01/01/2000)
 *
 * tm - pointer to UTC time struct
 */
extern UTCTime UTC_convertUTCSecs( UTCTimeStruct *tm );


/*********************************************************************
*********************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* UTC_CLOCK_H */
