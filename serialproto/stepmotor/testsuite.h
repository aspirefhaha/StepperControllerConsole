/** @file
 *    @brief MAVLink comm protocol testsuite generated from stepmotor.xml
 *    @see http://qgroundcontrol.org/mavlink/
 */
#pragma once
#ifndef STEPMOTOR_TESTSUITE_H
#define STEPMOTOR_TESTSUITE_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef MAVLINK_TEST_ALL
#define MAVLINK_TEST_ALL

static void mavlink_test_stepmotor(uint8_t, uint8_t, mavlink_message_t *last_msg);

static void mavlink_test_all(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{

    mavlink_test_stepmotor(system_id, component_id, last_msg);
}
#endif




static void mavlink_test_heartbeat(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_HEARTBEAT >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_heartbeat_t packet_in = {
        963497464,963497672,73.0,963498088,53,120
    };
    mavlink_heartbeat_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.tick = packet_in.tick;
        packet1.position = packet_in.position;
        packet1.dynamic = packet_in.dynamic;
        packet1.speed = packet_in.speed;
        packet1.lockstate = packet_in.lockstate;
        packet1.runstatus = packet_in.runstatus;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_HEARTBEAT_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_HEARTBEAT_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_heartbeat_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_heartbeat_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_heartbeat_pack(system_id, component_id, &msg , packet1.tick , packet1.position , packet1.dynamic , packet1.speed , packet1.lockstate , packet1.runstatus );
    mavlink_msg_heartbeat_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_heartbeat_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.tick , packet1.position , packet1.dynamic , packet1.speed , packet1.lockstate , packet1.runstatus );
    mavlink_msg_heartbeat_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_heartbeat_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_heartbeat_send(MAVLINK_COMM_1 , packet1.tick , packet1.position , packet1.dynamic , packet1.speed , packet1.lockstate , packet1.runstatus );
    mavlink_msg_heartbeat_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_config(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_CONFIG >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_config_t packet_in = {
        963497464,963497672,963497880,963498088,963498296,963498504,963498712,18691,223,34,101,168
    };
    mavlink_config_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.acc = packet_in.acc;
        packet1.dec = packet_in.dec;
        packet1.maxspeed = packet_in.maxspeed;
        packet1.minspeed = packet_in.minspeed;
        packet1.mark = packet_in.mark;
        packet1.uppos = packet_in.uppos;
        packet1.downpos = packet_in.downpos;
        packet1.config = packet_in.config;
        packet1.stepmode = packet_in.stepmode;
        packet1.ocdth = packet_in.ocdth;
        packet1.tval = packet_in.tval;
        packet1.isRboot = packet_in.isRboot;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_CONFIG_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_CONFIG_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_config_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_config_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_config_pack(system_id, component_id, &msg , packet1.acc , packet1.dec , packet1.maxspeed , packet1.minspeed , packet1.stepmode , packet1.ocdth , packet1.tval , packet1.config , packet1.mark , packet1.isRboot , packet1.uppos , packet1.downpos );
    mavlink_msg_config_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_config_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.acc , packet1.dec , packet1.maxspeed , packet1.minspeed , packet1.stepmode , packet1.ocdth , packet1.tval , packet1.config , packet1.mark , packet1.isRboot , packet1.uppos , packet1.downpos );
    mavlink_msg_config_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_config_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_config_send(MAVLINK_COMM_1 , packet1.acc , packet1.dec , packet1.maxspeed , packet1.minspeed , packet1.stepmode , packet1.ocdth , packet1.tval , packet1.config , packet1.mark , packet1.isRboot , packet1.uppos , packet1.downpos );
    mavlink_msg_config_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_runcmd(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_RUNCMD >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_runcmd_t packet_in = {
        963497464,963497672,963497880
    };
    mavlink_runcmd_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.cmd = packet_in.cmd;
        packet1.dir = packet_in.dir;
        packet1.distance = packet_in.distance;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_RUNCMD_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_RUNCMD_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_runcmd_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_runcmd_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_runcmd_pack(system_id, component_id, &msg , packet1.cmd , packet1.dir , packet1.distance );
    mavlink_msg_runcmd_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_runcmd_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.cmd , packet1.dir , packet1.distance );
    mavlink_msg_runcmd_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_runcmd_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_runcmd_send(MAVLINK_COMM_1 , packet1.cmd , packet1.dir , packet1.distance );
    mavlink_msg_runcmd_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_l6474status(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_L6474STATUS >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_l6474status_t packet_in = {
        17235
    };
    mavlink_l6474status_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.status = packet_in.status;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_L6474STATUS_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_L6474STATUS_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_l6474status_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_l6474status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_l6474status_pack(system_id, component_id, &msg , packet1.status );
    mavlink_msg_l6474status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_l6474status_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.status );
    mavlink_msg_l6474status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_l6474status_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_l6474status_send(MAVLINK_COMM_1 , packet1.status );
    mavlink_msg_l6474status_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_custstep(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_CUSTSTEP >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_custstep_t packet_in = {
        963497464,963497672,963497880,963498088,963498296,963498504,963498712,963498920,963499128,963499336
    };
    mavlink_custstep_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.step1 = packet_in.step1;
        packet1.step2 = packet_in.step2;
        packet1.step3 = packet_in.step3;
        packet1.step4 = packet_in.step4;
        packet1.step5 = packet_in.step5;
        packet1.wait1 = packet_in.wait1;
        packet1.wait2 = packet_in.wait2;
        packet1.wait3 = packet_in.wait3;
        packet1.wait4 = packet_in.wait4;
        packet1.wait5 = packet_in.wait5;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_CUSTSTEP_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_CUSTSTEP_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_custstep_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_custstep_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_custstep_pack(system_id, component_id, &msg , packet1.step1 , packet1.step2 , packet1.step3 , packet1.step4 , packet1.step5 , packet1.wait1 , packet1.wait2 , packet1.wait3 , packet1.wait4 , packet1.wait5 );
    mavlink_msg_custstep_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_custstep_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.step1 , packet1.step2 , packet1.step3 , packet1.step4 , packet1.step5 , packet1.wait1 , packet1.wait2 , packet1.wait3 , packet1.wait4 , packet1.wait5 );
    mavlink_msg_custstep_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_custstep_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_custstep_send(MAVLINK_COMM_1 , packet1.step1 , packet1.step2 , packet1.step3 , packet1.step4 , packet1.step5 , packet1.wait1 , packet1.wait2 , packet1.wait3 , packet1.wait4 , packet1.wait5 );
    mavlink_msg_custstep_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_protocol_version(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_PROTOCOL_VERSION >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_protocol_version_t packet_in = {
        17235,17339,17443,{ 151, 152, 153, 154, 155, 156, 157, 158 },{ 175, 176, 177, 178, 179, 180, 181, 182 }
    };
    mavlink_protocol_version_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.version = packet_in.version;
        packet1.min_version = packet_in.min_version;
        packet1.max_version = packet_in.max_version;
        
        mav_array_memcpy(packet1.spec_version_hash, packet_in.spec_version_hash, sizeof(uint8_t)*8);
        mav_array_memcpy(packet1.library_version_hash, packet_in.library_version_hash, sizeof(uint8_t)*8);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_PROTOCOL_VERSION_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_PROTOCOL_VERSION_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_protocol_version_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_protocol_version_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_protocol_version_pack(system_id, component_id, &msg , packet1.version , packet1.min_version , packet1.max_version , packet1.spec_version_hash , packet1.library_version_hash );
    mavlink_msg_protocol_version_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_protocol_version_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.version , packet1.min_version , packet1.max_version , packet1.spec_version_hash , packet1.library_version_hash );
    mavlink_msg_protocol_version_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_protocol_version_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_protocol_version_send(MAVLINK_COMM_1 , packet1.version , packet1.min_version , packet1.max_version , packet1.spec_version_hash , packet1.library_version_hash );
    mavlink_msg_protocol_version_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_stepmotor(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
    mavlink_test_heartbeat(system_id, component_id, last_msg);
    mavlink_test_config(system_id, component_id, last_msg);
    mavlink_test_runcmd(system_id, component_id, last_msg);
    mavlink_test_l6474status(system_id, component_id, last_msg);
    mavlink_test_custstep(system_id, component_id, last_msg);
    mavlink_test_protocol_version(system_id, component_id, last_msg);
}

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // STEPMOTOR_TESTSUITE_H
