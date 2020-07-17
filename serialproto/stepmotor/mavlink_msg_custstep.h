#pragma once
// MESSAGE CUSTSTEP PACKING

#define MAVLINK_MSG_ID_CUSTSTEP 4


typedef struct __mavlink_custstep_t {
 uint32_t step1; /*<  */
 uint32_t step2; /*<  */
 uint32_t step3; /*<  */
 uint32_t step4; /*<  */
 uint32_t step5; /*<  */
 uint32_t wait1; /*<  */
 uint32_t wait2; /*<  */
 uint32_t wait3; /*<  */
 uint32_t wait4; /*<  */
 uint32_t wait5; /*<  */
} mavlink_custstep_t;

#define MAVLINK_MSG_ID_CUSTSTEP_LEN 40
#define MAVLINK_MSG_ID_CUSTSTEP_MIN_LEN 40
#define MAVLINK_MSG_ID_4_LEN 40
#define MAVLINK_MSG_ID_4_MIN_LEN 40

#define MAVLINK_MSG_ID_CUSTSTEP_CRC 160
#define MAVLINK_MSG_ID_4_CRC 160



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_CUSTSTEP { \
    4, \
    "CUSTSTEP", \
    10, \
    {  { "step1", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_custstep_t, step1) }, \
         { "step2", NULL, MAVLINK_TYPE_UINT32_T, 0, 4, offsetof(mavlink_custstep_t, step2) }, \
         { "step3", NULL, MAVLINK_TYPE_UINT32_T, 0, 8, offsetof(mavlink_custstep_t, step3) }, \
         { "step4", NULL, MAVLINK_TYPE_UINT32_T, 0, 12, offsetof(mavlink_custstep_t, step4) }, \
         { "step5", NULL, MAVLINK_TYPE_UINT32_T, 0, 16, offsetof(mavlink_custstep_t, step5) }, \
         { "wait1", NULL, MAVLINK_TYPE_UINT32_T, 0, 20, offsetof(mavlink_custstep_t, wait1) }, \
         { "wait2", NULL, MAVLINK_TYPE_UINT32_T, 0, 24, offsetof(mavlink_custstep_t, wait2) }, \
         { "wait3", NULL, MAVLINK_TYPE_UINT32_T, 0, 28, offsetof(mavlink_custstep_t, wait3) }, \
         { "wait4", NULL, MAVLINK_TYPE_UINT32_T, 0, 32, offsetof(mavlink_custstep_t, wait4) }, \
         { "wait5", NULL, MAVLINK_TYPE_UINT32_T, 0, 36, offsetof(mavlink_custstep_t, wait5) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_CUSTSTEP { \
    "CUSTSTEP", \
    10, \
    {  { "step1", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_custstep_t, step1) }, \
         { "step2", NULL, MAVLINK_TYPE_UINT32_T, 0, 4, offsetof(mavlink_custstep_t, step2) }, \
         { "step3", NULL, MAVLINK_TYPE_UINT32_T, 0, 8, offsetof(mavlink_custstep_t, step3) }, \
         { "step4", NULL, MAVLINK_TYPE_UINT32_T, 0, 12, offsetof(mavlink_custstep_t, step4) }, \
         { "step5", NULL, MAVLINK_TYPE_UINT32_T, 0, 16, offsetof(mavlink_custstep_t, step5) }, \
         { "wait1", NULL, MAVLINK_TYPE_UINT32_T, 0, 20, offsetof(mavlink_custstep_t, wait1) }, \
         { "wait2", NULL, MAVLINK_TYPE_UINT32_T, 0, 24, offsetof(mavlink_custstep_t, wait2) }, \
         { "wait3", NULL, MAVLINK_TYPE_UINT32_T, 0, 28, offsetof(mavlink_custstep_t, wait3) }, \
         { "wait4", NULL, MAVLINK_TYPE_UINT32_T, 0, 32, offsetof(mavlink_custstep_t, wait4) }, \
         { "wait5", NULL, MAVLINK_TYPE_UINT32_T, 0, 36, offsetof(mavlink_custstep_t, wait5) }, \
         } \
}
#endif

/**
 * @brief Pack a custstep message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param step1  
 * @param step2  
 * @param step3  
 * @param step4  
 * @param step5  
 * @param wait1  
 * @param wait2  
 * @param wait3  
 * @param wait4  
 * @param wait5  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_custstep_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint32_t step1, uint32_t step2, uint32_t step3, uint32_t step4, uint32_t step5, uint32_t wait1, uint32_t wait2, uint32_t wait3, uint32_t wait4, uint32_t wait5)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_CUSTSTEP_LEN];
    _mav_put_uint32_t(buf, 0, step1);
    _mav_put_uint32_t(buf, 4, step2);
    _mav_put_uint32_t(buf, 8, step3);
    _mav_put_uint32_t(buf, 12, step4);
    _mav_put_uint32_t(buf, 16, step5);
    _mav_put_uint32_t(buf, 20, wait1);
    _mav_put_uint32_t(buf, 24, wait2);
    _mav_put_uint32_t(buf, 28, wait3);
    _mav_put_uint32_t(buf, 32, wait4);
    _mav_put_uint32_t(buf, 36, wait5);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_CUSTSTEP_LEN);
#else
    mavlink_custstep_t packet;
    packet.step1 = step1;
    packet.step2 = step2;
    packet.step3 = step3;
    packet.step4 = step4;
    packet.step5 = step5;
    packet.wait1 = wait1;
    packet.wait2 = wait2;
    packet.wait3 = wait3;
    packet.wait4 = wait4;
    packet.wait5 = wait5;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_CUSTSTEP_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_CUSTSTEP;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_CUSTSTEP_MIN_LEN, MAVLINK_MSG_ID_CUSTSTEP_LEN, MAVLINK_MSG_ID_CUSTSTEP_CRC);
}

/**
 * @brief Pack a custstep message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param step1  
 * @param step2  
 * @param step3  
 * @param step4  
 * @param step5  
 * @param wait1  
 * @param wait2  
 * @param wait3  
 * @param wait4  
 * @param wait5  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_custstep_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint32_t step1,uint32_t step2,uint32_t step3,uint32_t step4,uint32_t step5,uint32_t wait1,uint32_t wait2,uint32_t wait3,uint32_t wait4,uint32_t wait5)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_CUSTSTEP_LEN];
    _mav_put_uint32_t(buf, 0, step1);
    _mav_put_uint32_t(buf, 4, step2);
    _mav_put_uint32_t(buf, 8, step3);
    _mav_put_uint32_t(buf, 12, step4);
    _mav_put_uint32_t(buf, 16, step5);
    _mav_put_uint32_t(buf, 20, wait1);
    _mav_put_uint32_t(buf, 24, wait2);
    _mav_put_uint32_t(buf, 28, wait3);
    _mav_put_uint32_t(buf, 32, wait4);
    _mav_put_uint32_t(buf, 36, wait5);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_CUSTSTEP_LEN);
#else
    mavlink_custstep_t packet;
    packet.step1 = step1;
    packet.step2 = step2;
    packet.step3 = step3;
    packet.step4 = step4;
    packet.step5 = step5;
    packet.wait1 = wait1;
    packet.wait2 = wait2;
    packet.wait3 = wait3;
    packet.wait4 = wait4;
    packet.wait5 = wait5;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_CUSTSTEP_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_CUSTSTEP;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_CUSTSTEP_MIN_LEN, MAVLINK_MSG_ID_CUSTSTEP_LEN, MAVLINK_MSG_ID_CUSTSTEP_CRC);
}

/**
 * @brief Encode a custstep struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param custstep C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_custstep_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_custstep_t* custstep)
{
    return mavlink_msg_custstep_pack(system_id, component_id, msg, custstep->step1, custstep->step2, custstep->step3, custstep->step4, custstep->step5, custstep->wait1, custstep->wait2, custstep->wait3, custstep->wait4, custstep->wait5);
}

/**
 * @brief Encode a custstep struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param custstep C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_custstep_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_custstep_t* custstep)
{
    return mavlink_msg_custstep_pack_chan(system_id, component_id, chan, msg, custstep->step1, custstep->step2, custstep->step3, custstep->step4, custstep->step5, custstep->wait1, custstep->wait2, custstep->wait3, custstep->wait4, custstep->wait5);
}

/**
 * @brief Send a custstep message
 * @param chan MAVLink channel to send the message
 *
 * @param step1  
 * @param step2  
 * @param step3  
 * @param step4  
 * @param step5  
 * @param wait1  
 * @param wait2  
 * @param wait3  
 * @param wait4  
 * @param wait5  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_custstep_send(mavlink_channel_t chan, uint32_t step1, uint32_t step2, uint32_t step3, uint32_t step4, uint32_t step5, uint32_t wait1, uint32_t wait2, uint32_t wait3, uint32_t wait4, uint32_t wait5)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_CUSTSTEP_LEN];
    _mav_put_uint32_t(buf, 0, step1);
    _mav_put_uint32_t(buf, 4, step2);
    _mav_put_uint32_t(buf, 8, step3);
    _mav_put_uint32_t(buf, 12, step4);
    _mav_put_uint32_t(buf, 16, step5);
    _mav_put_uint32_t(buf, 20, wait1);
    _mav_put_uint32_t(buf, 24, wait2);
    _mav_put_uint32_t(buf, 28, wait3);
    _mav_put_uint32_t(buf, 32, wait4);
    _mav_put_uint32_t(buf, 36, wait5);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CUSTSTEP, buf, MAVLINK_MSG_ID_CUSTSTEP_MIN_LEN, MAVLINK_MSG_ID_CUSTSTEP_LEN, MAVLINK_MSG_ID_CUSTSTEP_CRC);
#else
    mavlink_custstep_t packet;
    packet.step1 = step1;
    packet.step2 = step2;
    packet.step3 = step3;
    packet.step4 = step4;
    packet.step5 = step5;
    packet.wait1 = wait1;
    packet.wait2 = wait2;
    packet.wait3 = wait3;
    packet.wait4 = wait4;
    packet.wait5 = wait5;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CUSTSTEP, (const char *)&packet, MAVLINK_MSG_ID_CUSTSTEP_MIN_LEN, MAVLINK_MSG_ID_CUSTSTEP_LEN, MAVLINK_MSG_ID_CUSTSTEP_CRC);
#endif
}

/**
 * @brief Send a custstep message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_custstep_send_struct(mavlink_channel_t chan, const mavlink_custstep_t* custstep)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_custstep_send(chan, custstep->step1, custstep->step2, custstep->step3, custstep->step4, custstep->step5, custstep->wait1, custstep->wait2, custstep->wait3, custstep->wait4, custstep->wait5);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CUSTSTEP, (const char *)custstep, MAVLINK_MSG_ID_CUSTSTEP_MIN_LEN, MAVLINK_MSG_ID_CUSTSTEP_LEN, MAVLINK_MSG_ID_CUSTSTEP_CRC);
#endif
}

#if MAVLINK_MSG_ID_CUSTSTEP_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_custstep_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint32_t step1, uint32_t step2, uint32_t step3, uint32_t step4, uint32_t step5, uint32_t wait1, uint32_t wait2, uint32_t wait3, uint32_t wait4, uint32_t wait5)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint32_t(buf, 0, step1);
    _mav_put_uint32_t(buf, 4, step2);
    _mav_put_uint32_t(buf, 8, step3);
    _mav_put_uint32_t(buf, 12, step4);
    _mav_put_uint32_t(buf, 16, step5);
    _mav_put_uint32_t(buf, 20, wait1);
    _mav_put_uint32_t(buf, 24, wait2);
    _mav_put_uint32_t(buf, 28, wait3);
    _mav_put_uint32_t(buf, 32, wait4);
    _mav_put_uint32_t(buf, 36, wait5);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CUSTSTEP, buf, MAVLINK_MSG_ID_CUSTSTEP_MIN_LEN, MAVLINK_MSG_ID_CUSTSTEP_LEN, MAVLINK_MSG_ID_CUSTSTEP_CRC);
#else
    mavlink_custstep_t *packet = (mavlink_custstep_t *)msgbuf;
    packet->step1 = step1;
    packet->step2 = step2;
    packet->step3 = step3;
    packet->step4 = step4;
    packet->step5 = step5;
    packet->wait1 = wait1;
    packet->wait2 = wait2;
    packet->wait3 = wait3;
    packet->wait4 = wait4;
    packet->wait5 = wait5;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CUSTSTEP, (const char *)packet, MAVLINK_MSG_ID_CUSTSTEP_MIN_LEN, MAVLINK_MSG_ID_CUSTSTEP_LEN, MAVLINK_MSG_ID_CUSTSTEP_CRC);
#endif
}
#endif

#endif

// MESSAGE CUSTSTEP UNPACKING


/**
 * @brief Get field step1 from custstep message
 *
 * @return  
 */
static inline uint32_t mavlink_msg_custstep_get_step1(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field step2 from custstep message
 *
 * @return  
 */
static inline uint32_t mavlink_msg_custstep_get_step2(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  4);
}

/**
 * @brief Get field step3 from custstep message
 *
 * @return  
 */
static inline uint32_t mavlink_msg_custstep_get_step3(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  8);
}

/**
 * @brief Get field step4 from custstep message
 *
 * @return  
 */
static inline uint32_t mavlink_msg_custstep_get_step4(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  12);
}

/**
 * @brief Get field step5 from custstep message
 *
 * @return  
 */
static inline uint32_t mavlink_msg_custstep_get_step5(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  16);
}

/**
 * @brief Get field wait1 from custstep message
 *
 * @return  
 */
static inline uint32_t mavlink_msg_custstep_get_wait1(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  20);
}

/**
 * @brief Get field wait2 from custstep message
 *
 * @return  
 */
static inline uint32_t mavlink_msg_custstep_get_wait2(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  24);
}

/**
 * @brief Get field wait3 from custstep message
 *
 * @return  
 */
static inline uint32_t mavlink_msg_custstep_get_wait3(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  28);
}

/**
 * @brief Get field wait4 from custstep message
 *
 * @return  
 */
static inline uint32_t mavlink_msg_custstep_get_wait4(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  32);
}

/**
 * @brief Get field wait5 from custstep message
 *
 * @return  
 */
static inline uint32_t mavlink_msg_custstep_get_wait5(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  36);
}

/**
 * @brief Decode a custstep message into a struct
 *
 * @param msg The message to decode
 * @param custstep C-struct to decode the message contents into
 */
static inline void mavlink_msg_custstep_decode(const mavlink_message_t* msg, mavlink_custstep_t* custstep)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    custstep->step1 = mavlink_msg_custstep_get_step1(msg);
    custstep->step2 = mavlink_msg_custstep_get_step2(msg);
    custstep->step3 = mavlink_msg_custstep_get_step3(msg);
    custstep->step4 = mavlink_msg_custstep_get_step4(msg);
    custstep->step5 = mavlink_msg_custstep_get_step5(msg);
    custstep->wait1 = mavlink_msg_custstep_get_wait1(msg);
    custstep->wait2 = mavlink_msg_custstep_get_wait2(msg);
    custstep->wait3 = mavlink_msg_custstep_get_wait3(msg);
    custstep->wait4 = mavlink_msg_custstep_get_wait4(msg);
    custstep->wait5 = mavlink_msg_custstep_get_wait5(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_CUSTSTEP_LEN? msg->len : MAVLINK_MSG_ID_CUSTSTEP_LEN;
        memset(custstep, 0, MAVLINK_MSG_ID_CUSTSTEP_LEN);
    memcpy(custstep, _MAV_PAYLOAD(msg), len);
#endif
}
