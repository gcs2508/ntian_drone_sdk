// MESSAGE MOUNT_GIMBAL_CONTROL PACKING

#define MAVLINK_MSG_ID_MOUNT_GIMBAL_CONTROL 156

MAVPACKED(
typedef struct __mavlink_mount_gimbal_control_t {
 int32_t stab_roll; /*< pitch(deg*100) or lat, depending on mount mode*/
 int32_t stab_pitch; /*< roll(deg*100) or lon depending on mount mode*/
 int32_t stab_yaw; /*< yaw(deg*100) or alt (in cm) depending on mount mode*/
 uint8_t target_system; /*< System ID*/
 uint8_t target_component; /*< Component ID*/
 uint8_t mount_mode; /*< mount operating mode (see NTIAN_MAVLINK_GIMBAL_CONTROL enum)*/
}) mavlink_mount_gimbal_control_t;

#define MAVLINK_MSG_ID_MOUNT_GIMBAL_CONTROL_LEN 15
#define MAVLINK_MSG_ID_MOUNT_GIMBAL_CONTROL_MIN_LEN 15
#define MAVLINK_MSG_ID_156_LEN 15
#define MAVLINK_MSG_ID_156_MIN_LEN 15

#define MAVLINK_MSG_ID_MOUNT_GIMBAL_CONTROL_CRC 40
#define MAVLINK_MSG_ID_156_CRC 40



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_MOUNT_GIMBAL_CONTROL { \
	156, \
	"MOUNT_GIMBAL_CONTROL", \
	6, \
	{  { "stab_roll", NULL, MAVLINK_TYPE_INT32_T, 0, 0, offsetof(mavlink_mount_gimbal_control_t, stab_roll) }, \
         { "stab_pitch", NULL, MAVLINK_TYPE_INT32_T, 0, 4, offsetof(mavlink_mount_gimbal_control_t, stab_pitch) }, \
         { "stab_yaw", NULL, MAVLINK_TYPE_INT32_T, 0, 8, offsetof(mavlink_mount_gimbal_control_t, stab_yaw) }, \
         { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 12, offsetof(mavlink_mount_gimbal_control_t, target_system) }, \
         { "target_component", NULL, MAVLINK_TYPE_UINT8_T, 0, 13, offsetof(mavlink_mount_gimbal_control_t, target_component) }, \
         { "mount_mode", NULL, MAVLINK_TYPE_UINT8_T, 0, 14, offsetof(mavlink_mount_gimbal_control_t, mount_mode) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_MOUNT_GIMBAL_CONTROL { \
	"MOUNT_GIMBAL_CONTROL", \
	6, \
	{  { "stab_roll", NULL, MAVLINK_TYPE_INT32_T, 0, 0, offsetof(mavlink_mount_gimbal_control_t, stab_roll) }, \
         { "stab_pitch", NULL, MAVLINK_TYPE_INT32_T, 0, 4, offsetof(mavlink_mount_gimbal_control_t, stab_pitch) }, \
         { "stab_yaw", NULL, MAVLINK_TYPE_INT32_T, 0, 8, offsetof(mavlink_mount_gimbal_control_t, stab_yaw) }, \
         { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 12, offsetof(mavlink_mount_gimbal_control_t, target_system) }, \
         { "target_component", NULL, MAVLINK_TYPE_UINT8_T, 0, 13, offsetof(mavlink_mount_gimbal_control_t, target_component) }, \
         { "mount_mode", NULL, MAVLINK_TYPE_UINT8_T, 0, 14, offsetof(mavlink_mount_gimbal_control_t, mount_mode) }, \
         } \
}
#endif

/**
 * @brief Pack a mount_gimbal_control message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param target_system System ID
 * @param target_component Component ID
 * @param mount_mode mount operating mode (see NTIAN_MAVLINK_GIMBAL_CONTROL enum)
 * @param stab_roll pitch(deg*100) or lat, depending on mount mode
 * @param stab_pitch roll(deg*100) or lon depending on mount mode
 * @param stab_yaw yaw(deg*100) or alt (in cm) depending on mount mode
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_mount_gimbal_control_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint8_t target_system, uint8_t target_component, uint8_t mount_mode, int32_t stab_roll, int32_t stab_pitch, int32_t stab_yaw)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_MOUNT_GIMBAL_CONTROL_LEN];
	_mav_put_int32_t(buf, 0, stab_roll);
	_mav_put_int32_t(buf, 4, stab_pitch);
	_mav_put_int32_t(buf, 8, stab_yaw);
	_mav_put_uint8_t(buf, 12, target_system);
	_mav_put_uint8_t(buf, 13, target_component);
	_mav_put_uint8_t(buf, 14, mount_mode);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MOUNT_GIMBAL_CONTROL_LEN);
#else
	mavlink_mount_gimbal_control_t packet;
	packet.stab_roll = stab_roll;
	packet.stab_pitch = stab_pitch;
	packet.stab_yaw = stab_yaw;
	packet.target_system = target_system;
	packet.target_component = target_component;
	packet.mount_mode = mount_mode;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MOUNT_GIMBAL_CONTROL_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_MOUNT_GIMBAL_CONTROL;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_MOUNT_GIMBAL_CONTROL_MIN_LEN, MAVLINK_MSG_ID_MOUNT_GIMBAL_CONTROL_LEN, MAVLINK_MSG_ID_MOUNT_GIMBAL_CONTROL_CRC);
}

/**
 * @brief Pack a mount_gimbal_control message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param target_system System ID
 * @param target_component Component ID
 * @param mount_mode mount operating mode (see NTIAN_MAVLINK_GIMBAL_CONTROL enum)
 * @param stab_roll pitch(deg*100) or lat, depending on mount mode
 * @param stab_pitch roll(deg*100) or lon depending on mount mode
 * @param stab_yaw yaw(deg*100) or alt (in cm) depending on mount mode
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_mount_gimbal_control_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint8_t target_system,uint8_t target_component,uint8_t mount_mode,int32_t stab_roll,int32_t stab_pitch,int32_t stab_yaw)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_MOUNT_GIMBAL_CONTROL_LEN];
	_mav_put_int32_t(buf, 0, stab_roll);
	_mav_put_int32_t(buf, 4, stab_pitch);
	_mav_put_int32_t(buf, 8, stab_yaw);
	_mav_put_uint8_t(buf, 12, target_system);
	_mav_put_uint8_t(buf, 13, target_component);
	_mav_put_uint8_t(buf, 14, mount_mode);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MOUNT_GIMBAL_CONTROL_LEN);
#else
	mavlink_mount_gimbal_control_t packet;
	packet.stab_roll = stab_roll;
	packet.stab_pitch = stab_pitch;
	packet.stab_yaw = stab_yaw;
	packet.target_system = target_system;
	packet.target_component = target_component;
	packet.mount_mode = mount_mode;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MOUNT_GIMBAL_CONTROL_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_MOUNT_GIMBAL_CONTROL;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_MOUNT_GIMBAL_CONTROL_MIN_LEN, MAVLINK_MSG_ID_MOUNT_GIMBAL_CONTROL_LEN, MAVLINK_MSG_ID_MOUNT_GIMBAL_CONTROL_CRC);
}

/**
 * @brief Encode a mount_gimbal_control struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param mount_gimbal_control C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_mount_gimbal_control_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_mount_gimbal_control_t* mount_gimbal_control)
{
	return mavlink_msg_mount_gimbal_control_pack(system_id, component_id, msg, mount_gimbal_control->target_system, mount_gimbal_control->target_component, mount_gimbal_control->mount_mode, mount_gimbal_control->stab_roll, mount_gimbal_control->stab_pitch, mount_gimbal_control->stab_yaw);
}

/**
 * @brief Encode a mount_gimbal_control struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param mount_gimbal_control C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_mount_gimbal_control_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_mount_gimbal_control_t* mount_gimbal_control)
{
	return mavlink_msg_mount_gimbal_control_pack_chan(system_id, component_id, chan, msg, mount_gimbal_control->target_system, mount_gimbal_control->target_component, mount_gimbal_control->mount_mode, mount_gimbal_control->stab_roll, mount_gimbal_control->stab_pitch, mount_gimbal_control->stab_yaw);
}

/**
 * @brief Send a mount_gimbal_control message
 * @param chan MAVLink channel to send the message
 *
 * @param target_system System ID
 * @param target_component Component ID
 * @param mount_mode mount operating mode (see NTIAN_MAVLINK_GIMBAL_CONTROL enum)
 * @param stab_roll pitch(deg*100) or lat, depending on mount mode
 * @param stab_pitch roll(deg*100) or lon depending on mount mode
 * @param stab_yaw yaw(deg*100) or alt (in cm) depending on mount mode
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_mount_gimbal_control_send(mavlink_channel_t chan, uint8_t target_system, uint8_t target_component, uint8_t mount_mode, int32_t stab_roll, int32_t stab_pitch, int32_t stab_yaw)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_MOUNT_GIMBAL_CONTROL_LEN];
	_mav_put_int32_t(buf, 0, stab_roll);
	_mav_put_int32_t(buf, 4, stab_pitch);
	_mav_put_int32_t(buf, 8, stab_yaw);
	_mav_put_uint8_t(buf, 12, target_system);
	_mav_put_uint8_t(buf, 13, target_component);
	_mav_put_uint8_t(buf, 14, mount_mode);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MOUNT_GIMBAL_CONTROL, buf, MAVLINK_MSG_ID_MOUNT_GIMBAL_CONTROL_MIN_LEN, MAVLINK_MSG_ID_MOUNT_GIMBAL_CONTROL_LEN, MAVLINK_MSG_ID_MOUNT_GIMBAL_CONTROL_CRC);
#else
	mavlink_mount_gimbal_control_t packet;
	packet.stab_roll = stab_roll;
	packet.stab_pitch = stab_pitch;
	packet.stab_yaw = stab_yaw;
	packet.target_system = target_system;
	packet.target_component = target_component;
	packet.mount_mode = mount_mode;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MOUNT_GIMBAL_CONTROL, (const char *)&packet, MAVLINK_MSG_ID_MOUNT_GIMBAL_CONTROL_MIN_LEN, MAVLINK_MSG_ID_MOUNT_GIMBAL_CONTROL_LEN, MAVLINK_MSG_ID_MOUNT_GIMBAL_CONTROL_CRC);
#endif
}

/**
 * @brief Send a mount_gimbal_control message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_mount_gimbal_control_send_struct(mavlink_channel_t chan, const mavlink_mount_gimbal_control_t* mount_gimbal_control)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_mount_gimbal_control_send(chan, mount_gimbal_control->target_system, mount_gimbal_control->target_component, mount_gimbal_control->mount_mode, mount_gimbal_control->stab_roll, mount_gimbal_control->stab_pitch, mount_gimbal_control->stab_yaw);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MOUNT_GIMBAL_CONTROL, (const char *)mount_gimbal_control, MAVLINK_MSG_ID_MOUNT_GIMBAL_CONTROL_MIN_LEN, MAVLINK_MSG_ID_MOUNT_GIMBAL_CONTROL_LEN, MAVLINK_MSG_ID_MOUNT_GIMBAL_CONTROL_CRC);
#endif
}

#if MAVLINK_MSG_ID_MOUNT_GIMBAL_CONTROL_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_mount_gimbal_control_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t target_system, uint8_t target_component, uint8_t mount_mode, int32_t stab_roll, int32_t stab_pitch, int32_t stab_yaw)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;
	_mav_put_int32_t(buf, 0, stab_roll);
	_mav_put_int32_t(buf, 4, stab_pitch);
	_mav_put_int32_t(buf, 8, stab_yaw);
	_mav_put_uint8_t(buf, 12, target_system);
	_mav_put_uint8_t(buf, 13, target_component);
	_mav_put_uint8_t(buf, 14, mount_mode);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MOUNT_GIMBAL_CONTROL, buf, MAVLINK_MSG_ID_MOUNT_GIMBAL_CONTROL_MIN_LEN, MAVLINK_MSG_ID_MOUNT_GIMBAL_CONTROL_LEN, MAVLINK_MSG_ID_MOUNT_GIMBAL_CONTROL_CRC);
#else
	mavlink_mount_gimbal_control_t *packet = (mavlink_mount_gimbal_control_t *)msgbuf;
	packet->stab_roll = stab_roll;
	packet->stab_pitch = stab_pitch;
	packet->stab_yaw = stab_yaw;
	packet->target_system = target_system;
	packet->target_component = target_component;
	packet->mount_mode = mount_mode;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MOUNT_GIMBAL_CONTROL, (const char *)packet, MAVLINK_MSG_ID_MOUNT_GIMBAL_CONTROL_MIN_LEN, MAVLINK_MSG_ID_MOUNT_GIMBAL_CONTROL_LEN, MAVLINK_MSG_ID_MOUNT_GIMBAL_CONTROL_CRC);
#endif
}
#endif

#endif

// MESSAGE MOUNT_GIMBAL_CONTROL UNPACKING


/**
 * @brief Get field target_system from mount_gimbal_control message
 *
 * @return System ID
 */
static inline uint8_t mavlink_msg_mount_gimbal_control_get_target_system(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  12);
}

/**
 * @brief Get field target_component from mount_gimbal_control message
 *
 * @return Component ID
 */
static inline uint8_t mavlink_msg_mount_gimbal_control_get_target_component(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  13);
}

/**
 * @brief Get field mount_mode from mount_gimbal_control message
 *
 * @return mount operating mode (see NTIAN_MAVLINK_GIMBAL_CONTROL enum)
 */
static inline uint8_t mavlink_msg_mount_gimbal_control_get_mount_mode(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  14);
}

/**
 * @brief Get field stab_roll from mount_gimbal_control message
 *
 * @return pitch(deg*100) or lat, depending on mount mode
 */
static inline int32_t mavlink_msg_mount_gimbal_control_get_stab_roll(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int32_t(msg,  0);
}

/**
 * @brief Get field stab_pitch from mount_gimbal_control message
 *
 * @return roll(deg*100) or lon depending on mount mode
 */
static inline int32_t mavlink_msg_mount_gimbal_control_get_stab_pitch(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int32_t(msg,  4);
}

/**
 * @brief Get field stab_yaw from mount_gimbal_control message
 *
 * @return yaw(deg*100) or alt (in cm) depending on mount mode
 */
static inline int32_t mavlink_msg_mount_gimbal_control_get_stab_yaw(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int32_t(msg,  8);
}

/**
 * @brief Decode a mount_gimbal_control message into a struct
 *
 * @param msg The message to decode
 * @param mount_gimbal_control C-struct to decode the message contents into
 */
static inline void mavlink_msg_mount_gimbal_control_decode(const mavlink_message_t* msg, mavlink_mount_gimbal_control_t* mount_gimbal_control)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	mount_gimbal_control->stab_roll = mavlink_msg_mount_gimbal_control_get_stab_roll(msg);
	mount_gimbal_control->stab_pitch = mavlink_msg_mount_gimbal_control_get_stab_pitch(msg);
	mount_gimbal_control->stab_yaw = mavlink_msg_mount_gimbal_control_get_stab_yaw(msg);
	mount_gimbal_control->target_system = mavlink_msg_mount_gimbal_control_get_target_system(msg);
	mount_gimbal_control->target_component = mavlink_msg_mount_gimbal_control_get_target_component(msg);
	mount_gimbal_control->mount_mode = mavlink_msg_mount_gimbal_control_get_mount_mode(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_MOUNT_GIMBAL_CONTROL_LEN? msg->len : MAVLINK_MSG_ID_MOUNT_GIMBAL_CONTROL_LEN;
        memset(mount_gimbal_control, 0, MAVLINK_MSG_ID_MOUNT_GIMBAL_CONTROL_LEN);
	memcpy(mount_gimbal_control, _MAV_PAYLOAD(msg), len);
#endif
}
