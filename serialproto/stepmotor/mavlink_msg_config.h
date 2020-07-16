#pragma once
// MESSAGE CONFIG PACKING

#define MAVLINK_MSG_ID_CONFIG 1


typedef struct __mavlink_config_t {
 uint32_t acc; /*<  */
 uint32_t dec; /*<  */
 uint32_t maxspeed; /*<  */
 uint32_t minspeed; /*<  */
 uint32_t mark; /*<  Mark Position*/
 int32_t uppos; /*<  上限位位置*/
 int32_t downpos; /*<  下限位位置*/
 uint16_t config; /*<  */
 uint8_t stepmode; /*<  */
 uint8_t ocdth; /*<  */
 uint8_t tval; /*<  */
 uint8_t isRboot; /*<  是否刚重启*/
} mavlink_config_t;

#define MAVLINK_MSG_ID_CONFIG_LEN 34
#define MAVLINK_MSG_ID_CONFIG_MIN_LEN 34
#define MAVLINK_MSG_ID_1_LEN 34
#define MAVLINK_MSG_ID_1_MIN_LEN 34

#define MAVLINK_MSG_ID_CONFIG_CRC 230
#define MAVLINK_MSG_ID_1_CRC 230



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_CONFIG { \
    1, \
    "CONFIG", \
    12, \
    {  { "acc", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_config_t, acc) }, \
         { "dec", NULL, MAVLINK_TYPE_UINT32_T, 0, 4, offsetof(mavlink_config_t, dec) }, \
         { "maxspeed", NULL, MAVLINK_TYPE_UINT32_T, 0, 8, offsetof(mavlink_config_t, maxspeed) }, \
         { "minspeed", NULL, MAVLINK_TYPE_UINT32_T, 0, 12, offsetof(mavlink_config_t, minspeed) }, \
         { "stepmode", NULL, MAVLINK_TYPE_UINT8_T, 0, 30, offsetof(mavlink_config_t, stepmode) }, \
         { "ocdth", NULL, MAVLINK_TYPE_UINT8_T, 0, 31, offsetof(mavlink_config_t, ocdth) }, \
         { "tval", NULL, MAVLINK_TYPE_UINT8_T, 0, 32, offsetof(mavlink_config_t, tval) }, \
         { "config", NULL, MAVLINK_TYPE_UINT16_T, 0, 28, offsetof(mavlink_config_t, config) }, \
         { "mark", NULL, MAVLINK_TYPE_UINT32_T, 0, 16, offsetof(mavlink_config_t, mark) }, \
         { "isRboot", NULL, MAVLINK_TYPE_UINT8_T, 0, 33, offsetof(mavlink_config_t, isRboot) }, \
         { "uppos", NULL, MAVLINK_TYPE_INT32_T, 0, 20, offsetof(mavlink_config_t, uppos) }, \
         { "downpos", NULL, MAVLINK_TYPE_INT32_T, 0, 24, offsetof(mavlink_config_t, downpos) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_CONFIG { \
    "CONFIG", \
    12, \
    {  { "acc", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_config_t, acc) }, \
         { "dec", NULL, MAVLINK_TYPE_UINT32_T, 0, 4, offsetof(mavlink_config_t, dec) }, \
         { "maxspeed", NULL, MAVLINK_TYPE_UINT32_T, 0, 8, offsetof(mavlink_config_t, maxspeed) }, \
         { "minspeed", NULL, MAVLINK_TYPE_UINT32_T, 0, 12, offsetof(mavlink_config_t, minspeed) }, \
         { "stepmode", NULL, MAVLINK_TYPE_UINT8_T, 0, 30, offsetof(mavlink_config_t, stepmode) }, \
         { "ocdth", NULL, MAVLINK_TYPE_UINT8_T, 0, 31, offsetof(mavlink_config_t, ocdth) }, \
         { "tval", NULL, MAVLINK_TYPE_UINT8_T, 0, 32, offsetof(mavlink_config_t, tval) }, \
         { "config", NULL, MAVLINK_TYPE_UINT16_T, 0, 28, offsetof(mavlink_config_t, config) }, \
         { "mark", NULL, MAVLINK_TYPE_UINT32_T, 0, 16, offsetof(mavlink_config_t, mark) }, \
         { "isRboot", NULL, MAVLINK_TYPE_UINT8_T, 0, 33, offsetof(mavlink_config_t, isRboot) }, \
         { "uppos", NULL, MAVLINK_TYPE_INT32_T, 0, 20, offsetof(mavlink_config_t, uppos) }, \
         { "downpos", NULL, MAVLINK_TYPE_INT32_T, 0, 24, offsetof(mavlink_config_t, downpos) }, \
         } \
}
#endif

/**
 * @brief Pack a config message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param acc  
 * @param dec  
 * @param maxspeed  
 * @param minspeed  
 * @param stepmode  
 * @param ocdth  
 * @param tval  
 * @param config  
 * @param mark  Mark Position
 * @param isRboot  是否刚重启
 * @param uppos  上限位位置
 * @param downpos  下限位位置
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_config_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint32_t acc, uint32_t dec, uint32_t maxspeed, uint32_t minspeed, uint8_t stepmode, uint8_t ocdth, uint8_t tval, uint16_t config, uint32_t mark, uint8_t isRboot, int32_t uppos, int32_t downpos)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_CONFIG_LEN];
    _mav_put_uint32_t(buf, 0, acc);
    _mav_put_uint32_t(buf, 4, dec);
    _mav_put_uint32_t(buf, 8, maxspeed);
    _mav_put_uint32_t(buf, 12, minspeed);
    _mav_put_uint32_t(buf, 16, mark);
    _mav_put_int32_t(buf, 20, uppos);
    _mav_put_int32_t(buf, 24, downpos);
    _mav_put_uint16_t(buf, 28, config);
    _mav_put_uint8_t(buf, 30, stepmode);
    _mav_put_uint8_t(buf, 31, ocdth);
    _mav_put_uint8_t(buf, 32, tval);
    _mav_put_uint8_t(buf, 33, isRboot);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_CONFIG_LEN);
#else
    mavlink_config_t packet;
    packet.acc = acc;
    packet.dec = dec;
    packet.maxspeed = maxspeed;
    packet.minspeed = minspeed;
    packet.mark = mark;
    packet.uppos = uppos;
    packet.downpos = downpos;
    packet.config = config;
    packet.stepmode = stepmode;
    packet.ocdth = ocdth;
    packet.tval = tval;
    packet.isRboot = isRboot;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_CONFIG_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_CONFIG;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_CONFIG_MIN_LEN, MAVLINK_MSG_ID_CONFIG_LEN, MAVLINK_MSG_ID_CONFIG_CRC);
}

/**
 * @brief Pack a config message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param acc  
 * @param dec  
 * @param maxspeed  
 * @param minspeed  
 * @param stepmode  
 * @param ocdth  
 * @param tval  
 * @param config  
 * @param mark  Mark Position
 * @param isRboot  是否刚重启
 * @param uppos  上限位位置
 * @param downpos  下限位位置
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_config_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint32_t acc,uint32_t dec,uint32_t maxspeed,uint32_t minspeed,uint8_t stepmode,uint8_t ocdth,uint8_t tval,uint16_t config,uint32_t mark,uint8_t isRboot,int32_t uppos,int32_t downpos)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_CONFIG_LEN];
    _mav_put_uint32_t(buf, 0, acc);
    _mav_put_uint32_t(buf, 4, dec);
    _mav_put_uint32_t(buf, 8, maxspeed);
    _mav_put_uint32_t(buf, 12, minspeed);
    _mav_put_uint32_t(buf, 16, mark);
    _mav_put_int32_t(buf, 20, uppos);
    _mav_put_int32_t(buf, 24, downpos);
    _mav_put_uint16_t(buf, 28, config);
    _mav_put_uint8_t(buf, 30, stepmode);
    _mav_put_uint8_t(buf, 31, ocdth);
    _mav_put_uint8_t(buf, 32, tval);
    _mav_put_uint8_t(buf, 33, isRboot);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_CONFIG_LEN);
#else
    mavlink_config_t packet;
    packet.acc = acc;
    packet.dec = dec;
    packet.maxspeed = maxspeed;
    packet.minspeed = minspeed;
    packet.mark = mark;
    packet.uppos = uppos;
    packet.downpos = downpos;
    packet.config = config;
    packet.stepmode = stepmode;
    packet.ocdth = ocdth;
    packet.tval = tval;
    packet.isRboot = isRboot;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_CONFIG_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_CONFIG;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_CONFIG_MIN_LEN, MAVLINK_MSG_ID_CONFIG_LEN, MAVLINK_MSG_ID_CONFIG_CRC);
}

/**
 * @brief Encode a config struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param config C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_config_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_config_t* config)
{
    return mavlink_msg_config_pack(system_id, component_id, msg, config->acc, config->dec, config->maxspeed, config->minspeed, config->stepmode, config->ocdth, config->tval, config->config, config->mark, config->isRboot, config->uppos, config->downpos);
}

/**
 * @brief Encode a config struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param config C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_config_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_config_t* config)
{
    return mavlink_msg_config_pack_chan(system_id, component_id, chan, msg, config->acc, config->dec, config->maxspeed, config->minspeed, config->stepmode, config->ocdth, config->tval, config->config, config->mark, config->isRboot, config->uppos, config->downpos);
}

/**
 * @brief Send a config message
 * @param chan MAVLink channel to send the message
 *
 * @param acc  
 * @param dec  
 * @param maxspeed  
 * @param minspeed  
 * @param stepmode  
 * @param ocdth  
 * @param tval  
 * @param config  
 * @param mark  Mark Position
 * @param isRboot  是否刚重启
 * @param uppos  上限位位置
 * @param downpos  下限位位置
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_config_send(mavlink_channel_t chan, uint32_t acc, uint32_t dec, uint32_t maxspeed, uint32_t minspeed, uint8_t stepmode, uint8_t ocdth, uint8_t tval, uint16_t config, uint32_t mark, uint8_t isRboot, int32_t uppos, int32_t downpos)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_CONFIG_LEN];
    _mav_put_uint32_t(buf, 0, acc);
    _mav_put_uint32_t(buf, 4, dec);
    _mav_put_uint32_t(buf, 8, maxspeed);
    _mav_put_uint32_t(buf, 12, minspeed);
    _mav_put_uint32_t(buf, 16, mark);
    _mav_put_int32_t(buf, 20, uppos);
    _mav_put_int32_t(buf, 24, downpos);
    _mav_put_uint16_t(buf, 28, config);
    _mav_put_uint8_t(buf, 30, stepmode);
    _mav_put_uint8_t(buf, 31, ocdth);
    _mav_put_uint8_t(buf, 32, tval);
    _mav_put_uint8_t(buf, 33, isRboot);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CONFIG, buf, MAVLINK_MSG_ID_CONFIG_MIN_LEN, MAVLINK_MSG_ID_CONFIG_LEN, MAVLINK_MSG_ID_CONFIG_CRC);
#else
    mavlink_config_t packet;
    packet.acc = acc;
    packet.dec = dec;
    packet.maxspeed = maxspeed;
    packet.minspeed = minspeed;
    packet.mark = mark;
    packet.uppos = uppos;
    packet.downpos = downpos;
    packet.config = config;
    packet.stepmode = stepmode;
    packet.ocdth = ocdth;
    packet.tval = tval;
    packet.isRboot = isRboot;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CONFIG, (const char *)&packet, MAVLINK_MSG_ID_CONFIG_MIN_LEN, MAVLINK_MSG_ID_CONFIG_LEN, MAVLINK_MSG_ID_CONFIG_CRC);
#endif
}

/**
 * @brief Send a config message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_config_send_struct(mavlink_channel_t chan, const mavlink_config_t* config)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_config_send(chan, config->acc, config->dec, config->maxspeed, config->minspeed, config->stepmode, config->ocdth, config->tval, config->config, config->mark, config->isRboot, config->uppos, config->downpos);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CONFIG, (const char *)config, MAVLINK_MSG_ID_CONFIG_MIN_LEN, MAVLINK_MSG_ID_CONFIG_LEN, MAVLINK_MSG_ID_CONFIG_CRC);
#endif
}

#if MAVLINK_MSG_ID_CONFIG_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_config_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint32_t acc, uint32_t dec, uint32_t maxspeed, uint32_t minspeed, uint8_t stepmode, uint8_t ocdth, uint8_t tval, uint16_t config, uint32_t mark, uint8_t isRboot, int32_t uppos, int32_t downpos)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint32_t(buf, 0, acc);
    _mav_put_uint32_t(buf, 4, dec);
    _mav_put_uint32_t(buf, 8, maxspeed);
    _mav_put_uint32_t(buf, 12, minspeed);
    _mav_put_uint32_t(buf, 16, mark);
    _mav_put_int32_t(buf, 20, uppos);
    _mav_put_int32_t(buf, 24, downpos);
    _mav_put_uint16_t(buf, 28, config);
    _mav_put_uint8_t(buf, 30, stepmode);
    _mav_put_uint8_t(buf, 31, ocdth);
    _mav_put_uint8_t(buf, 32, tval);
    _mav_put_uint8_t(buf, 33, isRboot);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CONFIG, buf, MAVLINK_MSG_ID_CONFIG_MIN_LEN, MAVLINK_MSG_ID_CONFIG_LEN, MAVLINK_MSG_ID_CONFIG_CRC);
#else
    mavlink_config_t *packet = (mavlink_config_t *)msgbuf;
    packet->acc = acc;
    packet->dec = dec;
    packet->maxspeed = maxspeed;
    packet->minspeed = minspeed;
    packet->mark = mark;
    packet->uppos = uppos;
    packet->downpos = downpos;
    packet->config = config;
    packet->stepmode = stepmode;
    packet->ocdth = ocdth;
    packet->tval = tval;
    packet->isRboot = isRboot;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CONFIG, (const char *)packet, MAVLINK_MSG_ID_CONFIG_MIN_LEN, MAVLINK_MSG_ID_CONFIG_LEN, MAVLINK_MSG_ID_CONFIG_CRC);
#endif
}
#endif

#endif

// MESSAGE CONFIG UNPACKING


/**
 * @brief Get field acc from config message
 *
 * @return  
 */
static inline uint32_t mavlink_msg_config_get_acc(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field dec from config message
 *
 * @return  
 */
static inline uint32_t mavlink_msg_config_get_dec(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  4);
}

/**
 * @brief Get field maxspeed from config message
 *
 * @return  
 */
static inline uint32_t mavlink_msg_config_get_maxspeed(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  8);
}

/**
 * @brief Get field minspeed from config message
 *
 * @return  
 */
static inline uint32_t mavlink_msg_config_get_minspeed(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  12);
}

/**
 * @brief Get field stepmode from config message
 *
 * @return  
 */
static inline uint8_t mavlink_msg_config_get_stepmode(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  30);
}

/**
 * @brief Get field ocdth from config message
 *
 * @return  
 */
static inline uint8_t mavlink_msg_config_get_ocdth(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  31);
}

/**
 * @brief Get field tval from config message
 *
 * @return  
 */
static inline uint8_t mavlink_msg_config_get_tval(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  32);
}

/**
 * @brief Get field config from config message
 *
 * @return  
 */
static inline uint16_t mavlink_msg_config_get_config(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  28);
}

/**
 * @brief Get field mark from config message
 *
 * @return  Mark Position
 */
static inline uint32_t mavlink_msg_config_get_mark(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  16);
}

/**
 * @brief Get field isRboot from config message
 *
 * @return  是否刚重启
 */
static inline uint8_t mavlink_msg_config_get_isRboot(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  33);
}

/**
 * @brief Get field uppos from config message
 *
 * @return  上限位位置
 */
static inline int32_t mavlink_msg_config_get_uppos(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  20);
}

/**
 * @brief Get field downpos from config message
 *
 * @return  下限位位置
 */
static inline int32_t mavlink_msg_config_get_downpos(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  24);
}

/**
 * @brief Decode a config message into a struct
 *
 * @param msg The message to decode
 * @param config C-struct to decode the message contents into
 */
static inline void mavlink_msg_config_decode(const mavlink_message_t* msg, mavlink_config_t* config)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    config->acc = mavlink_msg_config_get_acc(msg);
    config->dec = mavlink_msg_config_get_dec(msg);
    config->maxspeed = mavlink_msg_config_get_maxspeed(msg);
    config->minspeed = mavlink_msg_config_get_minspeed(msg);
    config->mark = mavlink_msg_config_get_mark(msg);
    config->uppos = mavlink_msg_config_get_uppos(msg);
    config->downpos = mavlink_msg_config_get_downpos(msg);
    config->config = mavlink_msg_config_get_config(msg);
    config->stepmode = mavlink_msg_config_get_stepmode(msg);
    config->ocdth = mavlink_msg_config_get_ocdth(msg);
    config->tval = mavlink_msg_config_get_tval(msg);
    config->isRboot = mavlink_msg_config_get_isRboot(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_CONFIG_LEN? msg->len : MAVLINK_MSG_ID_CONFIG_LEN;
        memset(config, 0, MAVLINK_MSG_ID_CONFIG_LEN);
    memcpy(config, _MAV_PAYLOAD(msg), len);
#endif
}
