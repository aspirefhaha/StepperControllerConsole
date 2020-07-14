#pragma once
// MESSAGE L6474STATUS PACKING

#define MAVLINK_MSG_ID_L6474STATUS 3


typedef struct __mavlink_l6474status_t {
 uint16_t status; /*<  */
} mavlink_l6474status_t;

#define MAVLINK_MSG_ID_L6474STATUS_LEN 2
#define MAVLINK_MSG_ID_L6474STATUS_MIN_LEN 2
#define MAVLINK_MSG_ID_3_LEN 2
#define MAVLINK_MSG_ID_3_MIN_LEN 2

#define MAVLINK_MSG_ID_L6474STATUS_CRC 119
#define MAVLINK_MSG_ID_3_CRC 119



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_L6474STATUS { \
    3, \
    "L6474STATUS", \
    1, \
    {  { "status", NULL, MAVLINK_TYPE_UINT16_T, 0, 0, offsetof(mavlink_l6474status_t, status) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_L6474STATUS { \
    "L6474STATUS", \
    1, \
    {  { "status", NULL, MAVLINK_TYPE_UINT16_T, 0, 0, offsetof(mavlink_l6474status_t, status) }, \
         } \
}
#endif

/**
 * @brief Pack a l6474status message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param status  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_l6474status_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint16_t status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_L6474STATUS_LEN];
    _mav_put_uint16_t(buf, 0, status);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_L6474STATUS_LEN);
#else
    mavlink_l6474status_t packet;
    packet.status = status;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_L6474STATUS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_L6474STATUS;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_L6474STATUS_MIN_LEN, MAVLINK_MSG_ID_L6474STATUS_LEN, MAVLINK_MSG_ID_L6474STATUS_CRC);
}

/**
 * @brief Pack a l6474status message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param status  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_l6474status_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint16_t status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_L6474STATUS_LEN];
    _mav_put_uint16_t(buf, 0, status);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_L6474STATUS_LEN);
#else
    mavlink_l6474status_t packet;
    packet.status = status;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_L6474STATUS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_L6474STATUS;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_L6474STATUS_MIN_LEN, MAVLINK_MSG_ID_L6474STATUS_LEN, MAVLINK_MSG_ID_L6474STATUS_CRC);
}

/**
 * @brief Encode a l6474status struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param l6474status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_l6474status_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_l6474status_t* l6474status)
{
    return mavlink_msg_l6474status_pack(system_id, component_id, msg, l6474status->status);
}

/**
 * @brief Encode a l6474status struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param l6474status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_l6474status_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_l6474status_t* l6474status)
{
    return mavlink_msg_l6474status_pack_chan(system_id, component_id, chan, msg, l6474status->status);
}

/**
 * @brief Send a l6474status message
 * @param chan MAVLink channel to send the message
 *
 * @param status  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_l6474status_send(mavlink_channel_t chan, uint16_t status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_L6474STATUS_LEN];
    _mav_put_uint16_t(buf, 0, status);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_L6474STATUS, buf, MAVLINK_MSG_ID_L6474STATUS_MIN_LEN, MAVLINK_MSG_ID_L6474STATUS_LEN, MAVLINK_MSG_ID_L6474STATUS_CRC);
#else
    mavlink_l6474status_t packet;
    packet.status = status;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_L6474STATUS, (const char *)&packet, MAVLINK_MSG_ID_L6474STATUS_MIN_LEN, MAVLINK_MSG_ID_L6474STATUS_LEN, MAVLINK_MSG_ID_L6474STATUS_CRC);
#endif
}

/**
 * @brief Send a l6474status message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_l6474status_send_struct(mavlink_channel_t chan, const mavlink_l6474status_t* l6474status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_l6474status_send(chan, l6474status->status);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_L6474STATUS, (const char *)l6474status, MAVLINK_MSG_ID_L6474STATUS_MIN_LEN, MAVLINK_MSG_ID_L6474STATUS_LEN, MAVLINK_MSG_ID_L6474STATUS_CRC);
#endif
}

#if MAVLINK_MSG_ID_L6474STATUS_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_l6474status_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint16_t status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint16_t(buf, 0, status);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_L6474STATUS, buf, MAVLINK_MSG_ID_L6474STATUS_MIN_LEN, MAVLINK_MSG_ID_L6474STATUS_LEN, MAVLINK_MSG_ID_L6474STATUS_CRC);
#else
    mavlink_l6474status_t *packet = (mavlink_l6474status_t *)msgbuf;
    packet->status = status;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_L6474STATUS, (const char *)packet, MAVLINK_MSG_ID_L6474STATUS_MIN_LEN, MAVLINK_MSG_ID_L6474STATUS_LEN, MAVLINK_MSG_ID_L6474STATUS_CRC);
#endif
}
#endif

#endif

// MESSAGE L6474STATUS UNPACKING


/**
 * @brief Get field status from l6474status message
 *
 * @return  
 */
static inline uint16_t mavlink_msg_l6474status_get_status(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  0);
}

/**
 * @brief Decode a l6474status message into a struct
 *
 * @param msg The message to decode
 * @param l6474status C-struct to decode the message contents into
 */
static inline void mavlink_msg_l6474status_decode(const mavlink_message_t* msg, mavlink_l6474status_t* l6474status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    l6474status->status = mavlink_msg_l6474status_get_status(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_L6474STATUS_LEN? msg->len : MAVLINK_MSG_ID_L6474STATUS_LEN;
        memset(l6474status, 0, MAVLINK_MSG_ID_L6474STATUS_LEN);
    memcpy(l6474status, _MAV_PAYLOAD(msg), len);
#endif
}
