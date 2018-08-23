#include "stdafx.h"
#include "UTCTools.h"

/*********************************************************************
 * MACROS
 */

#define	YearLength(yr)	(IsLeapYear(yr) ? 366 : 365)

/*********************************************************************
 * CONSTANTS
 */

// Update every 1000ms
#define UTC_UPDATE_PERIOD  5000

#define IsLeapYear(yr)     (!((yr) % 400) || (((yr) % 100) && !((yr) % 4)))
   
#define	BEGYEAR	           2000     // UTC started at 00:00:00 January 1, 2000

#define	DAY                86400UL  // 24 hours * 60 minutes * 60 seconds

/*********************************************************************
 * TYPEDEFS
 */


// Time is the number of seconds since 0 hrs, 0 minutes, 0 seconds, on the
// 1st of January 2000 UTC.
UTCTime UTC_timeSeconds = 0;

/*********************************************************************
 * LOCAL FUNCTION PROTOTYPES
 */
static uint8_t UTC_monthLength(uint8_t lpyr, uint8_t mon);


/*********************************************************************
 * @fn      UTC_convertUTCTime
 *
 * @brief   Converts UTCTime to UTCTimeStruct (from total seconds to exact 
 *          date).
 *
 * @param   tm - pointer to breakdown struct.
 *
 * @param   secTime - number of seconds since 0 hrs, 0 minutes,
 *          0 seconds, on the 1st of January 2000 UTC.
 *
 * @return  none
 */
void UTC_convertUTCTime(UTCTime secTime, UTCTimeStruct *tm)
{
  // Calculate the time less than a day - hours, minutes, seconds.
  {
    // The number of seconds that have occured so far stoday.
    uint32_t day = secTime % DAY;
    
    // Seconds that have passed in the current minute.
    tm->seconds = day % 60UL;
    // Minutes that have passed in the current hour.
    // (seconds per day) / (seconds per minute) = (minutes on an hour boundary)
    tm->minutes = (uint8_t)((day % 3600UL) / 60UL);
    // Hours that have passed in the current day.
    tm->hour = (uint8_t)(day / 3600UL);
  }

  // Fill in the calendar - day, month, year
  {
    uint16_t numDays = (uint16_t)(secTime / DAY);
    uint8_t monthLen;
    tm->year = BEGYEAR;
    
    while (numDays >= YearLength(tm->year))
    {
      numDays -= YearLength(tm->year);
      tm->year++;
    }

    // January.
    tm->month = 0;
    
    monthLen = UTC_monthLength(IsLeapYear(tm->year), tm->month);
    
    // Determine the number of months which have passed from remaining days.
    while (numDays >= monthLen)
    {
      // Subtract number of days in month from remaining count of days.
      numDays -= monthLen;
      tm->month++;
      
      // Recalculate month length.
      monthLen = UTC_monthLength(IsLeapYear(tm->year), tm->month);
    }
    
    // Store the remaining days.
    tm->day = (uint8_t)numDays;
  }
}

/*********************************************************************
 * @fn      UTC_monthLength
 *
 * @param   lpyr - 1 for leap year, 0 if not
 *
 * @param   mon - 0 - 11 (jan - dec)
 *
 * @return  number of days in specified month
 */
static uint8_t UTC_monthLength(uint8_t lpyr, uint8_t mon)
{
  uint8_t days = 31;

  if (mon == 1) // feb
  {
    days = (28 + lpyr);
  }
  else
  {
    if (mon > 6) // aug-dec
    {
      mon--;
    }

    if (mon & 1)
    {
      days = 30;
    }
  }

  return (days);
}

/*********************************************************************
 * @fn      UTC_convertUTCSecs
 *
 * @brief   Converts a UTCTimeStruct to UTCTime (from exact date to total 
 *          seconds).
 *
 * @param   tm - pointer to provided struct.
 *
 * @return  number of seconds since 00:00:00 on 01/01/2000 (UTC).
 */
UTCTime UTC_convertUTCSecs(UTCTimeStruct *tm)
{
  uint32_t seconds;

  // Seconds for the partial day.
  seconds = (((tm->hour * 60UL) + tm->minutes) * 60UL) + tm->seconds;

  // Account for previous complete days.
  {
    // Start with complete days in current month.
    uint16_t days = tm->day;

    // Next, complete months in current year.
    {
      int8 month = tm->month;
      while (--month >= 0)
      {
        days += UTC_monthLength(IsLeapYear(tm->year), month);
      }
    }

    // Next, complete years before current year.
    {
      uint16_t year = tm->year;
      while (--year >= BEGYEAR)
      {
        days += YearLength(year);
      }
    }

    // Add total seconds before partial day.
    seconds += (days * DAY);
  }

  return (seconds);
}
