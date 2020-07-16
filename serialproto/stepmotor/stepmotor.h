/** @file
 *  @brief MAVLink comm protocol generated from stepmotor.xml
 *  @see http://mavlink.org
 */
#pragma once
#ifndef MAVLINK_STEPMOTOR_H
#define MAVLINK_STEPMOTOR_H

#ifndef MAVLINK_H
    #error Wrong include order: MAVLINK_STEPMOTOR.H MUST NOT BE DIRECTLY USED. Include mavlink.h from the same directory instead or set ALL AND EVERY defines from MAVLINK.H manually accordingly, including the #define MAVLINK_H call.
#endif

#undef MAVLINK_THIS_XML_IDX
#define MAVLINK_THIS_XML_IDX 0

#ifdef __cplusplus
extern "C" {
#endif

// MESSAGE LENGTHS AND CRCS

#ifndef MAVLINK_MESSAGE_LENGTHS
#define MAVLINK_MESSAGE_LENGTHS {}
#endif

#ifndef MAVLINK_MESSAGE_CRCS
#define MAVLINK_MESSAGE_CRCS {{0, 62, 18, 18, 0, 0, 0}, {1, 230, 34, 34, 0, 0, 0}, {2, 34, 12, 12, 0, 0, 0}, {3, 119, 2, 2, 0, 0, 0}, {300, 217, 22, 22, 0, 0, 0}}
#endif

#include "../protocol.h"

#define MAVLINK_ENABLED_STEPMOTOR

// ENUM DEFINITIONS


/** @brief StepMotor Command ENUMS */
#ifndef HAVE_ENUM_SMCMD
#define HAVE_ENUM_SMCMD
typedef enum SMCMD
{
   SMCMD_GETCONFIG=0, /* Get Motor Stepper Controller configs | */
   SMCMD_SOFTSTOP=1, /* Reserved for future use. | */
   SMCMD_MOVEFWD=2, /*  | */
   SMCMD_MOVEBWD=3, /*  | */
   SMCMD_SETHOME=4, /*  | */
   SMCMD_SETMARK=5, /*  | */
   SMCMD_HARDSTOP=6, /*  | */
   SMCMD_MOVESTEP=7, /*  | */
   SMCMD_SETMAXSPEED=8, /*  | */
   SMCMD_GOMARK=9, /*  | */
   SMCMD_RUNPROG1=10, /*  | */
   SMCMD_SETACC=11, /*  | */
   SMCMD_SETDEC=12, /*  | */
   SMCMD_GOPOS=13, /*  | */
   SMCMD_SETOC=14, /*  | */
   SMCMD_GETSTATUS=15, /*  | */
   SMCMD_SETTVAL=16, /*  | */
   SMCMD_SETMINSPEED=17, /*  | */
   SMCMD_ENABLE=18, /*  | */
   SMCMD_DISABLE=19, /*  | */
   SMCMD_SETSTEPMODE=20, /*  | */
   SMCMD_UNLOCKUP=21, /*  | */
   SMCMD_UNLOCKDOWN=22, /*  | */
   SMCMD_SCANUPDOWNLOCK=23, /*  | */
   SMCMD_SETUPLOCKPOS=24, /*  | */
   SMCMD_SETDOWNLOCKPOS=25, /*  | */
   SMCMD_ENUM_END=26, /*  | */
} SMCMD;
#endif

/** @brief 外部PWM情况 */
#ifndef HAVE_ENUM_EMOTORSTATE
#define HAVE_ENUM_EMOTORSTATE
typedef enum EMOTORSTATE
{
   EMS_ACCELERATING=0, /*  | */
   EMS_DECELERATING=1, /*  | */
   EMS_STEADY=2, /*  | */
   EMS_INACTIVE=3, /*  | */
   EMOTORSTATE_ENUM_END=4, /*  | */
} EMOTORSTATE;
#endif

// MAVLINK VERSION

#ifndef MAVLINK_VERSION
#define MAVLINK_VERSION 3
#endif

#if (MAVLINK_VERSION == 0)
#undef MAVLINK_VERSION
#define MAVLINK_VERSION 3
#endif

// MESSAGE DEFINITIONS
#include "./mavlink_msg_heartbeat.h"
#include "./mavlink_msg_config.h"
#include "./mavlink_msg_runcmd.h"
#include "./mavlink_msg_l6474status.h"
#include "./mavlink_msg_protocol_version.h"

// base include


#undef MAVLINK_THIS_XML_IDX
#define MAVLINK_THIS_XML_IDX 0

#if MAVLINK_THIS_XML_IDX == MAVLINK_PRIMARY_XML_IDX
# define MAVLINK_MESSAGE_INFO {MAVLINK_MESSAGE_INFO_HEARTBEAT, MAVLINK_MESSAGE_INFO_CONFIG, MAVLINK_MESSAGE_INFO_RUNCMD, MAVLINK_MESSAGE_INFO_L6474STATUS, MAVLINK_MESSAGE_INFO_PROTOCOL_VERSION}
# define MAVLINK_MESSAGE_NAMES {{ "CONFIG", 1 }, { "HEARTBEAT", 0 }, { "L6474STATUS", 3 }, { "PROTOCOL_VERSION", 300 }, { "RUNCMD", 2 }}
# if MAVLINK_COMMAND_24BIT
#  include "../mavlink_get_info.h"
# endif
#endif

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MAVLINK_STEPMOTOR_H
