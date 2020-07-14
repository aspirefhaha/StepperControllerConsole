#pragma once
// MESSAGE HEARTBEAT PACKING

#define MAVLINK_MSG_ID_HEARTBEAT 0


typedef struct __mavlink_heartbeat_t {
 uint32_t tick; /*<  TICK 是开机以来经过的Tick时间，精度和操作系统有关*/
 int32_t position; /*<  */
 float dynamic; /*<  电位器值*/
 int32_t speed; /*<  */
 uint8_t stepmode; /*<  */
 uint8_t runstatus; /*<  外部PWM方式下的加减速状态*/
} mavlink_heartbeat_t;

#define MAVLINK_MSG_ID_HEARTBEAT_LEN 18
#define MAVLINK_MSG_ID_HEARTBEAT_MIN_LEN 18
#define MAVLINK_MSG_ID_0_LEN 18
#define MAVLINK_MSG_ID_0_MIN_LEN 18

#define MAVLINK_MSG_ID_HEARTBEAT_CRC 105
#define MAVLINK_MSG_ID_0_CRC 105



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_HEARTBEAT { \
    0, \
    "HEARTBEAT", \
    6, \
    {  { "tick", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_heartbeat_t, tick) }, \
         { "position", NULL, MAVLINK_TYPE_INT32_T, 0, 4, offsetof(mavlink_heartbeat_t, position) }, \
         { "dynamic", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_heartbeat_t, dynamic) }, \
         { "speed", NULL, MAVLINK_TYPE_INT32_T, 0, 12, offsetof(mavlink_heartbeat_t, speed) }, \
         { "stepmode", NULL, MAVLINK_TYPE_UINT8_T, 0, 16, offsetof(mavlink_heartbeat_t, stepmode) }, \
         { "runstatus", NULL, MAVLINK_TYPE_UINT8_T, 0, 17, offsetof(mavlink_heartbeat_t, runstatus) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_HEARTBEAT { \
    "HEARTBEAT", \
    6, \
    {  { "tick", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_heartbeat_t, tick) }, \
         { "position", NULL, MAVLINK_TYPE_INT32_T, 0, 4, offsetof(mavlink_heartbeat_t, position) }, \
         { "dynamic", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_heartbeat_t, dynamic) }, \
         { "speed", NULL, MAVLINK_TYPE_INT32_T, 0, 12, offsetof(mavlink_heartbeat_t, speed) }, \
         { "stepmode", NULL, MAVLINK_TYPE_UINT8_T, 0, 16, offsetof(mavlink_heartbeat_t, stepmode) }, \
         { "runstatus", NULL, MAVLINK_TYPE_UINT8_T, 0, 17, offsetof(mavlink_heartbeat_t, runstatus) }, \
         } \
}
#endif

/**
 * @brief Pack a heartbeat message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param tick  TICK 是开机以来经过的Tick时间，精度和操作系统有关
 * @param position  
 * @param dynamic  电位器值
 * @param speed  
 * @param stepmode  
 * @param runstatus  外部PWM方式下的加减速状态
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_heartbeat_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint32_t tick, int32_t position, float dynamic, int32_t speed, uint8_t stepmode, uint8_t runstatus)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_HEARTBEAT_LEN];
    _mav_put_uint32_t(buf, 0, tick);
    _mav_put_int32_t(buf, 4, position);
    _mav_put_float(buf, 8, dynamic);
    _mav_put_int32_t(buf, 12, speed);
    _mav_put_uint8_t(buf, 16, stepmode);
    _mav_put_uint8_t(buf, 17, runstatus);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_HEARTBEAT_LEN);
#else
    mavlink_heartbeat_t packet;
    packet.tick = tick;
    packet.position = position;
    packet.dynamic = dynamic;
    packet.speed = speed;
    packet.stepmode = stepmode;
    packet.runstatus = runstatus;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_HEARTBEAT_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_HEARTBEAT;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_HEARTBEAT_MIN_LEN, MAVLINK_MSG_ID_HEARTBEAT_LEN, MAVLINK_MSG_ID_HEARTBEAT_CRC);
}

/**
 * @brief Pack a heartbeat message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param tick  TICK 是开机以来经过的Tick时间，精度和操作系统有关
 * @param position  
 * @param dynamic  电位器值
 * @param speed  
 * @param stepmode  
 * @param runstatus  外部PWM方式下的加减速状态
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_heartbeat_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint32_t tick,int32_t position,float dynamic,int32_t speed,uint8_t stepmode,uint8_t runstatus)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_HEARTBEAT_LEN];
    _mav_put_uint32_t(buf, 0, tick);
    _mav_put_int32_t(buf, 4, position);
    _mav_put_float(buf, 8, dynamic);
    _mav_put_int32_t(buf, 12, speed);
    _mav_put_uint8_t(buf, 16, stepmode);
    _mav_put_uint8_t(buf, 17, runstatus);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_HEARTBEAT_LEN);
#else
    mavlink_heartbeat_t packet;
    packet.tick = tick;
    packet.position = position;
    packet.dynamic = dynamic;
    packet.speed = speed;
    packet.stepmode = stepmode;
    packet.runstatus = runstatus;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_HEARTBEAT_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_HEARTBEAT;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_HEARTBEAT_MIN_LEN, MAVLINK_MSG_ID_HEARTBEAT_LEN, MAVLINK_MSG_ID_HEARTBEAT_CRC);
}

/**
 * @brief Encode a heartbeat struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param heartbeat C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_heartbeat_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_heartbeat_t* heartbeat)
{
    return mavlink_msg_heartbeat_pack(system_id, component_id, msg, heartbeat->tick, heartbeat->position, heartbeat->dynamic, heartbeat->speed, heartbeat->stepmode, heartbeat->runstatus);
}

/**
 * @brief Encode a heartbeat struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param heartbeat C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_heartbeat_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_heartbeat_t* heartbeat)
{
    return mavlink_msg_heartbeat_pack_chan(system_id, component_id, chan, msg, heartbeat->tick, heartbeat->position, heartbeat->dynamic, heartbeat->speed, heartbeat->stepmode, heartbeat->runstatus);
}

/**
 * @brief Send a heartbeat message
 * @param chan MAVLink channel to send the message
 *
 * @param tick  TICK 是开机以来经过的Tick时间，精度和操作系统有关
 * @param position  
 * @param dynamic  电位器值
 * @param speed  
 * @param stepmode  
 * @param runstatus  外部PWM方式下的加减速状态
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_heartbeat_send(mavlink_channel_t chan, uint32_t tick, int32_t position, float dynamic, int32_t speed, uint8_t stepmode, uint8_t runstatus)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_HEARTBEAT_LEN];
    _mav_put_uint32_t(buf, 0, tick);
    _mav_put_int32_t(buf, 4, position);
    _mav_put_float(buf, 8, dynamic);
    _mav_put_int32_t(buf, 12, speed);
    _mav_put_uint8_t(buf, 16, stepmode);
    _mav_put_uint8_t(buf, 17, runstatus);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HEARTBEAT, buf, MAVLINK_MSG_ID_HEARTBEAT_MIN_LEN, MAVLINK_MSG_ID_HEARTBEAT_LEN, MAVLINK_MSG_ID_HEARTBEAT_CRC);
#else
    mavlink_heartbeat_t packet;
    packet.tick = tick;
    packet.position = position;
    packet.dynamic = dynamic;
    packet.speed = speed;
    packet.stepmode = stepmode;
    packet.runstatus = runstatus;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HEARTBEAT, (const char *)&packet, MAVLINK_MSG_ID_HEARTBEAT_MIN_LEN, MAVLINK_MSG_ID_HEARTBEAT_LEN, MAVLINK_MSG_ID_HEARTBEAT_CRC);
#endif
}

/**
 * @brief Send a heartbeat message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_heartbeat_send_struct(mavlink_channel_t chan, const mavlink_heartbeat_t* heartbeat)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_heartbeat_send(chan, heartbeat->tick, heartbeat->position, heartbeat->dynamic, heartbeat->speed, heartbeat->stepmode, heartbeat->runstatus);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HEARTBEAT, (const char *)heartbeat, MAVLINK_MSG_ID_HEARTBEAT_MIN_LEN, MAVLINK_MSG_ID_HEARTBEAT_LEN, MAVLINK_MSG_ID_HEARTBEAT_CRC);
#endif
}

#if MAVLINK_MSG_ID_HEARTBEAT_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_heartbeat_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint32_t tick, int32_t position, float dynamic, int32_t speed, uint8_t stepmode, uint8_t runstatus)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint32_t(buf, 0, tick);
    _mav_put_int32_t(buf, 4, position);
    _mav_put_float(buf, 8, dynamic);
    _mav_put_int32_t(buf, 12, speed);
    _mav_put_uint8_t(buf, 16, stepmode);
    _mav_put_uint8_t(buf, 17, runstatus);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HEARTBEAT, buf, MAVLINK_MSG_ID_HEARTBEAT_MIN_LEN, MAVLINK_MSG_ID_HEARTBEAT_LEN, MAVLINK_MSG_ID_HEARTBEAT_CRC);
#else
    mavlink_heartbeat_t *packet = (mavlink_heartbeat_t *)msgbuf;
    packet->tick = tick;
    packet->position = position;
    packet->dynamic = dynamic;
    packet->speed = speed;
    packet->stepmode = stepmode;
    packet->runstatus = runstatus;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HEARTBEAT, (const char *)packet, MAVLINK_MSG_ID_HEARTBEAT_MIN_LEN, MAVLINK_MSG_ID_HEARTBEAT_LEN, MAVLINK_MSG_ID_HEARTBEAT_CRC);
#endif
}
#endif

#endif

// MESSAGE HEARTBEAT UNPACKING


/**
 * @brief Get field tick from heartbeat message
 *
 * @return  TICK 是开机以来经过的Tick时间，精度和操作系统有关
 */
static inline uint32_t mavlink_msg_heartbeat_get_tick(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field position from heartbeat message
 *
 * @return  
 */
static inline int32_t mavlink_msg_heartbeat_get_position(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  4);
}

/**
 * @brief Get field dynamic from heartbeat message
 *
 * @return  电位器值
 */
static inline float mavlink_msg_heartbeat_get_dynamic(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field speed from heartbeat message
 *
 * @return  
 */
static inline int32_t mavlink_msg_heartbeat_get_speed(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  12);
}

/**
 * @brief Get field stepmode from heartbeat message
 *
 * @return  
 */
static inline uint8_t mavlink_msg_heartbeat_get_stepmode(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  16);
}

/**
 * @brief Get field runstatus from heartbeat message
 *
 * @return  外部PWM方式下的加减速状态
 */
static inline uint8_t mavlink_msg_heartbeat_get_runstatus(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  17);
}

/**
 * @brief Decode a heartbeat message into a struct
 *
 * @param msg The message to decode
 * @param heartbeat C-struct to decode the message contents into
 */
static inline void mavlink_msg_heartbeat_decode(const mavlink_message_t* msg, mavlink_heartbeat_t* heartbeat)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    heartbeat->tick = mavlink_msg_heartbeat_get_tick(msg);
    heartbeat->position = mavlink_msg_heartbeat_get_position(msg);
    heartbeat->dynamic = mavlink_msg_heartbeat_get_dynamic(msg);
    heartbeat->speed = mavlink_msg_heartbeat_get_speed(msg);
    heartbeat->stepmode = mavlink_msg_heartbeat_get_stepmode(msg);
    heartbeat->runstatus = mavlink_msg_heartbeat_get_runstatus(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_HEARTBEAT_LEN? msg->len : MAVLINK_MSG_ID_HEARTBEAT_LEN;
        memset(heartbeat, 0, MAVLINK_MSG_ID_HEARTBEAT_LEN);
    memcpy(heartbeat, _MAV_PAYLOAD(msg), len);
#endif
}
