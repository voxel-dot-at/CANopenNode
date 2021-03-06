/**
 * Application interface for CANopenNode stack.
 *
 * @file        application.h
 * @ingroup     CO_application
 * @author      Janez Paternoster
 * @copyright   2012 - 2013 Janez Paternoster
 *
 * This file is part of CANopenNode, an opensource CANopen Stack.
 * Project home page is <https://github.com/CANopenNode/CANopenNode>.
 * For more information on CANopen see <http://www.can-cia.org/>.
 *
 * CANopenNode is free and open source software: you can redistribute
 * it and/or modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation, either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * Following clarification and special exception to the GNU General Public
 * License is included to the distribution terms of CANopenNode:
 *
 * Linking this library statically or dynamically with other modules is
 * making a combined work based on this library. Thus, the terms and
 * conditions of the GNU General Public License cover the whole combination.
 *
 * As a special exception, the copyright holders of this library give
 * you permi#include "application.h"
ssion to link this library with independent modules to
 * produce an executable, regardless of the license terms of these
 * independent modules, and to copy and distribute the resulting
 * executable under terms of your choice, provided that you also meet,
 * for each linked independent module, the terms and conditions of the
 * license of that module. An independent module is a module which is
 * not derived from or based on this library. If you modify this
 * library, you may extend this exception to your version of the
 * library, but you are not obliged to do so. If you do not wish
 * to do so, delete this exception statement from your version.
 */


#ifndef CO_APPLICATION_H
#define CO_APPLICATION_H

//#define USE_EEPROM 1
//#define CO_DEBUG 1

#include <mbed.h>
//#include <mbed_events.h>

//extern EventQueue queue;

#ifdef USE_EEPROM
    #include "eeprom.h"            /* 25LC08C eeprom chip connected to SPI2A port. */
    extern CO_EE_t                     CO_EEO;         /* Eeprom object */
#endif

#ifdef __cplusplus
extern "C"{
#endif

#include <CANopen.h>
#include <CO_driver.h>

#ifdef __cplusplus
} // extern "C"
#endif

extern CO_NMT_reset_cmd_t reset;

/**
 * @defgroup CO_application Application interface
 * @ingroup CO_CANopen
 * @{
 *
 * Application interface for CANopenNode stack. Function is called
 * from file main_xxx.c (if implemented).
 *
 * ###Main program flow chart
 *
 * @code
               (Program Start)
                      |
                      V
    +------------------------------------+
    |           programStart()           |
    +------------------------------------+
                      |
                      |<-------------------------+
                      |                          |
                      V                          |
             (Initialze CANopen)                 |
                      |                          |
                      V                          |
    +------------------------------------+       |
    |        communicationReset()        |       |
    +------------------------------------+       |
                      |                          |
                      V                          |
         (Enable CAN and interrupts)             |
                      |                          |
                      |<----------------------+  |
                      |                       |  |
                      V                       |  |
    +------------------------------------+    |  |
    |           programAsync()           |    |  |
    +------------------------------------+    |  |
                      |                       |  |
                      V                       |  |
        (Process CANopen asynchronous)        |  |
                      |                       |  |
                      +- infinite loop -------+  |
                      |                          |
                      +- reset communication ----+
                      |
                      V
    +------------------------------------+
    |            programEnd()            |
    +------------------------------------+
                      |
                      V
              (delete CANopen)
                      |
                      V
                (Program end)
   @endcode
 *
 *
 * ###Timer program flow chart
 *
 * @code
        (Timer interrupt 1 millisecond)
                      |
                      V
              (CANopen read RPDOs)
                      |
                      V
    +------------------------------------+
    |           program1ms()             |
    +------------------------------------+
                      |
                      V
              (CANopen write TPDOs)
   @endcode
 *
 *
 * ###Receive and transmit high priority interrupt flow chart
 *
 * @code
           (CAN receive event or)
      (CAN transmit buffer empty event)
                      |
                      V
       (Process received CAN message or)
   (copy next message to CAN transmit buffer)
   @endcode
 */

 //#define TMR_TASK_INTERVAL   (1000)          /* Interval of tmrTask thread in microseconds */
 //#define INCREMENT_1MS(var)  (var++)         /* Increment 1ms variable in tmrTask */
 //volatile uint16_t   CO_timer1ms = 0U;       /* variable increments each millisecond */
 //Thread processThread, tmrThread;

/**
 * Called after microcontroller reset.
 */
void programStart(mbed::CAN *can = NULL);


/**
 * Called after communication reset.
 */
void communicationReset(mbed::CAN *can = NULL);


/**
 * Called before program end.
 */
void programEnd(void);


/**
 * Called cyclically from main.
 *
 * @param timer1msDiff Time difference since last call
 */
//void programAsync(uint16_t timer1msDiff);
//static void processTask_thread(void);

//uint16_t timerNext_ms = 50;
/**
 * Called cyclically from 1ms timer task.
 */
//static void tmrTask_thread(void);
//void program1ms(void);

/*******************************************************************************/
void processTask_thread(void);


/*******************************************************************************/
/* timer thread executes in constant intervals ********************************/
void tmrTask_thread(void);

/** @} */
#endif
