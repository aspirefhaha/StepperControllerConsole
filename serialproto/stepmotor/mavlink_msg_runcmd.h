#pragma once
// MESSAGE RUNCMD PACKING

#define MAVLINK_MSG_ID_RUNCMD 2


typedef struct __mavlink_runcmd_t {
 uint32_t cmd; /*<  */
 uint32_t dir; /*<   0-fwd 1-bwd */
 int32_t distance; /*<   distance */
} mavlink_runcmd_t;

#define MAVLINK_MSG_ID_RUNCMD_LEN 12
#define MAVLINK_MSG_ID_RUNCMD_MIN_LEN 12
#define MAVLINK_MSG_ID_2_LEN 12
#define MAVLINK_MSG_ID_2_MIN_LEN 12

#define MAVLINK_MSG_ID_RUNCMD_CRC 34
#define MAVLINK_MSG_ID_2_CRC 34



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_RUNCMD { \
    2, \
    "RUNCMD", \
    3, \
    {  { "cmd", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_runcmd_t, cmd) }, \
         { "dir", NULL, MAVLINK_TYPE_UINT32_T, 0, 4, offsetof(mavlink_runcmd_t, dir) }, \
         { "distance", NULL, MAVLINK_TYPE_INT32_T, 0, 8, offsetof(mavlink_runcmd_t, distance) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_RUNCMD { \
    "RUNCMD", \
    3, \
    {  { "cmd", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_runcmd_t, cmd) }, \
         { "dir", NULL, MAVLINK_TYPE_UINT32_T, 0, 4, offsetof(mavlink_runcmd_t, dir) }, \
         { "distance", NULL, MAVLINK_TYPE_INT32_T, 0, 8, offsetof(mavlink_runcmd_t, distance) }, \
         } \
}
#endif

/**
 * @brief Pack a runcmd message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param cmd  
 * @param dir   0-fwd 1-bwd 
 * @param distance   distance 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_runcmd_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint32_t cmd, uint32_t dir, int32_t distance)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_RUNCMD_LEN];
    _mav_put_uint32_t(buf, 0, cmd);
    _mav_put_uint32_t(buf, 4, dir);
    _mav_put_int32_t(buf, 8, distance);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_RUNCMD_LEN);
#else
    mavlink_runcmd_t packet;
    packet.cmd = cmd;
    packet.dir = dir;
    packet.distance = distance;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_RUNCMD_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_RUNCMD;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_RUNCMD_MIN_LEN, MAVLINK_MSG_ID_RUNCMD_LEN, MAVLINK_MSG_ID_RUNCMD_CRC);
}

/**
 * @brief Pack a runcmd message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param cmd  
 * @param dir   0-fwd 1-bwd 
 * @param distance   distance 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_runcmd_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint32_t cmd,uint32_t dir,int32_t distance)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_RUNCMD_LEN];
    _mav_put_uint32_t(buf, 0, cmd);
    _mav_put_uint32_t(buf, 4, dir);
    _mav_put_int32_t(buf, 8, distance);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_RUNCMD_LEN);
#else
    mavlink_runcmd_t packet;
    packet.cmd = cmd;
    packet.dir = dir;
    packet.distance = distance;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_RUNCMD_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_RUNCMD;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_RUNCMD_MIN_LEN, MAVLINK_MSG_ID_RUNCMD_LEN, MAVLINK_MSG_ID_RUNCMD_CRC);
}

/**
 * @brief Encode a runcmd struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param runcmd C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_runcmd_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_runcmd_t* runcmd)
{
    return mavlink_msg_runcmd_pack(system_id, component_id, msg, runcmd->cmd, runcmd->dir, runcmd->distance);
}

/**
 * @brief Encode a runcmd struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param runcmd C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_runcmd_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_runcmd_t* runcmd)
{
    return mavlink_msg_runcmd_pack_chan(system_id, component_id, chan, msg, runcmd->cmd, runcmd->dir, runcmd->distance);
}

/**
 * @brief Send a runcmd message
 * @param chan MAVLink channel to send the message
 *
 * @param cmd  
 * @param dir   0-fwd 1-bwd 
 * @param distance   distance 
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_runcmd_send(mavlink_channel_t chan, uint32_t cmd, uint32_t dir, int32_t distance)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_RUNCMD_LEN];
    _mav_put_uint32_t(buf, 0, cmd);
    _mav_put_uint32_t(buf, 4, dir);
    _mav_put_int32_t(buf, 8, distance);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_RUNCMD, buf, MAVLINK_MSG_ID_RUNCMD_MIN_LEN, MAVLINK_MSG_ID_RUNCMD_LEN, MAVLINK_MSG_ID_RUNCMD_CRC);
#else
    mavlink_runcmd_t packet;
    packet.cmd = cmd;
    packet.dir = dir;
    packet.distance = distance;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_RUNCMD, (const char *)&packet, MAVLINK_MSG_ID_RUNCMD_MIN_LEN, MAVLINK_MSG_ID_RUNCMD_LEN, MAVLINK_MSG_ID_RUNCMD_CRC);
#endif
}

/**
 * @brief Send a runcmd message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_runcmd_send_struct(mavlink_channel_t chan, const mavlink_runcmd_t* runcmd)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_runcmd_send(chan, runcmd->cmd, runcmd->dir, runcmd->distance);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_RUNCMD, (const char *)runcmd, MAVLINK_MSG_ID_RUNCMD_MIN_LEN, MAVLINK_MSG_ID_RUNCMD_LEN, MAVLINK_MSG_ID_RUNCMD_CRC);
#endif
}

#if MAVLINK_MSG_ID_RUNCMD_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_runcmd_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint32_t cmd, uint32_t dir, int32_t distance)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint32_t(buf, 0, cmd);
    _mav_put_uint32_t(buf, 4, dir);
    _mav_put_int32_t(buf, 8, distance);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_RUNCMD, buf, MAVLINK_MSG_ID_RUNCMD_MIN_LEN, MAVLINK_MSG_ID_RUNCMD_LEN, MAVLINK_MSG_ID_RUNCMD_CRC);
#else
    mavlink_runcmd_t *packet = (mavlink_runcmd_t *)msgbuf;
    packet->cmd = cmd;
    packet->dir = dir;
    packet->distance = distance;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_RUNCMD, (const char *)packet, MAVLINK_MSG_ID_RUNCMD_MIN_LEN, MAVLINK_MSG_ID_RUNCMD_LEN, MAVLINK_MSG_ID_RUNCMD_CRC);
#endif
}
#endif

#endif

// MESSAGE RUNCMD UNPACKING


/**
 * @brief Get field cmd from runcmd message
 *
 * @return  
 */
static inline uint32_t mavlink_msg_runcmd_get_cmd(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field dir from runcmd message
 *
 * @return   0-fwd 1-bwd 
 */
static inline uint32_t mavlink_msg_runcmd_get_dir(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  4);
}

/**
 * @brief Get field distance from runcmd message
 *
 * @return   distance 
 */
static inline int32_t mavlink_msg_runcmd_get_distance(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  8);
}

/**
 * @brief Decode a runcmd message into a struct
 *
 * @param msg The message to decode
 * @param runcmd C-struct to decode the message contents into
 */
static inline void mavlink_msg_runcmd_decode(const mavlink_message_t* msg, mavlink_runcmd_t* runcmd)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    runcmd->cmd = mavlink_msg_runcmd_get_cmd(msg);
    runcmd->dir = mavlink_msg_runcmd_get_dir(msg);
    runcmd->distance = mavlink_msg_runcmd_get_distance(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_RUNCMD_LEN? msg->len : MAVLINK_MSG_ID_RUNCMD_LEN;
        memset(runcmd, 0, MAVLINK_MSG_ID_RUNCMD_LEN);
    memcpy(runcmd, _MAV_PAYLOAD(msg), len);
#endif
}
