/** @file
 *  @brief Bluetooth Mesh Access Layer APIs.
 */

/*
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef ZEPHYR_INCLUDE_BLUETOOTH_MESH_ACCESS_H_
#define ZEPHYR_INCLUDE_BLUETOOTH_MESH_ACCESS_H_

#include <settings/settings.h>
#include <sys/util.h>

/* Internal macros used to initialize array members */
#define BT_MESH_KEY_UNUSED_ELT_(IDX, _) BT_MESH_KEY_UNUSED,
#define BT_MESH_ADDR_UNASSIGNED_ELT_(IDX, _) BT_MESH_ADDR_UNASSIGNED,
#define BT_MESH_MODEL_KEYS_UNUSED			\
	{ UTIL_LISTIFY(CONFIG_BT_MESH_MODEL_KEY_COUNT,	\
		       BT_MESH_KEY_UNUSED_ELT_) }
#define BT_MESH_MODEL_GROUPS_UNASSIGNED				\
	{ UTIL_LISTIFY(CONFIG_BT_MESH_MODEL_GROUP_COUNT,	\
		       BT_MESH_ADDR_UNASSIGNED_ELT_) }

/**
 * @brief Bluetooth Mesh Access Layer
 * @defgroup bt_mesh_access Bluetooth Mesh Access Layer
 * @ingroup bt_mesh
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

#define BT_MESH_ADDR_UNASSIGNED   0x0000
#define BT_MESH_ADDR_ALL_NODES    0xffff
#define BT_MESH_ADDR_PROXIES      0xfffc
#define BT_MESH_ADDR_FRIENDS      0xfffd
#define BT_MESH_ADDR_RELAYS       0xfffe

#define BT_MESH_KEY_UNUSED        0xffff
#define BT_MESH_KEY_ANY           0xffff
#define BT_MESH_KEY_DEV           0xfffe
#define BT_MESH_KEY_DEV_LOCAL     BT_MESH_KEY_DEV
#define BT_MESH_KEY_DEV_REMOTE    0xfffd
#define BT_MESH_KEY_DEV_ANY       0xfffc

#define BT_MESH_ADDR_IS_UNICAST(addr) ((addr) && (addr) < 0x8000)
#define BT_MESH_ADDR_IS_GROUP(addr) ((addr) >= 0xc000 && (addr) <= 0xff00)
#define BT_MESH_ADDR_IS_VIRTUAL(addr) ((addr) >= 0x8000 && (addr) < 0xc000)
#define BT_MESH_ADDR_IS_RFU(addr) ((addr) >= 0xff00 && (addr) <= 0xfffb)

#define BT_MESH_IS_DEV_KEY(key) (key == BT_MESH_KEY_DEV_LOCAL || \
				 key == BT_MESH_KEY_DEV_REMOTE)

/** Maximum payload size of an access message (in octets). */
#define BT_MESH_APP_SEG_SDU_MAX   12
/** Maximum possible payload size of an outgoing access message (in octets). */
#define BT_MESH_TX_SDU_MAX        (CONFIG_BT_MESH_TX_SEG_MAX * \
				  BT_MESH_APP_SEG_SDU_MAX)
/** Maximum possible payload size of an incoming access message (in octets). */
#define BT_MESH_RX_SDU_MAX        (CONFIG_BT_MESH_RX_SEG_MAX * \
				  BT_MESH_APP_SEG_SDU_MAX)

/** Helper to define a mesh element within an array.
 *
 *  In case the element has no SIG or Vendor models the helper
 *  macro BT_MESH_MODEL_NONE can be given instead.
 *
 *  @param _loc       Location Descriptor.
 *  @param _mods      Array of models.
 *  @param _vnd_mods  Array of vendor models.
 */
#define BT_MESH_ELEM(_loc, _mods, _vnd_mods)        \
{                                                   \
	.loc              = (_loc),                 \
	.model_count      = ARRAY_SIZE(_mods),      \
	.vnd_model_count  = ARRAY_SIZE(_vnd_mods),  \
	.models           = (_mods),                \
	.vnd_models       = (_vnd_mods),            \
}

/** Abstraction that describes a Mesh Element */
struct bt_mesh_elem {
	/** Unicast Address. Set at runtime during provisioning. */
	uint16_t addr;

	/** Location Descriptor (GATT Bluetooth Namespace Descriptors) */
	const uint16_t loc;
	/** The number of SIG models in this element */
	const uint8_t model_count;
	/** The number of vendor models in this element */
	const uint8_t vnd_model_count;

	/** The list of SIG models in this element */
	struct bt_mesh_model * const models;
	/** The list of vendor models in this element */
	struct bt_mesh_model * const vnd_models;
};

/* Foundation Models */
#define BT_MESH_MODEL_ID_CFG_SRV                   0x0000
#define BT_MESH_MODEL_ID_CFG_CLI                   0x0001
#define BT_MESH_MODEL_ID_HEALTH_SRV                0x0002
#define BT_MESH_MODEL_ID_HEALTH_CLI                0x0003

/* Models from the Mesh Model Specification */
#define BT_MESH_MODEL_ID_GEN_ONOFF_SRV             0x1000
#define BT_MESH_MODEL_ID_GEN_ONOFF_CLI             0x1001
#define BT_MESH_MODEL_ID_GEN_LEVEL_SRV             0x1002
#define BT_MESH_MODEL_ID_GEN_LEVEL_CLI             0x1003
#define BT_MESH_MODEL_ID_GEN_DEF_TRANS_TIME_SRV    0x1004
#define BT_MESH_MODEL_ID_GEN_DEF_TRANS_TIME_CLI    0x1005
#define BT_MESH_MODEL_ID_GEN_POWER_ONOFF_SRV       0x1006
#define BT_MESH_MODEL_ID_GEN_POWER_ONOFF_SETUP_SRV 0x1007
#define BT_MESH_MODEL_ID_GEN_POWER_ONOFF_CLI       0x1008
#define BT_MESH_MODEL_ID_GEN_POWER_LEVEL_SRV       0x1009
#define BT_MESH_MODEL_ID_GEN_POWER_LEVEL_SETUP_SRV 0x100a
#define BT_MESH_MODEL_ID_GEN_POWER_LEVEL_CLI       0x100b
#define BT_MESH_MODEL_ID_GEN_BATTERY_SRV           0x100c
#define BT_MESH_MODEL_ID_GEN_BATTERY_CLI           0x100d
#define BT_MESH_MODEL_ID_GEN_LOCATION_SRV          0x100e
#define BT_MESH_MODEL_ID_GEN_LOCATION_SETUPSRV     0x100f
#define BT_MESH_MODEL_ID_GEN_LOCATION_CLI          0x1010
#define BT_MESH_MODEL_ID_GEN_ADMIN_PROP_SRV        0x1011
#define BT_MESH_MODEL_ID_GEN_MANUFACTURER_PROP_SRV 0x1012
#define BT_MESH_MODEL_ID_GEN_USER_PROP_SRV         0x1013
#define BT_MESH_MODEL_ID_GEN_CLIENT_PROP_SRV       0x1014
#define BT_MESH_MODEL_ID_GEN_PROP_CLI              0x1015
#define BT_MESH_MODEL_ID_SENSOR_SRV                0x1100
#define BT_MESH_MODEL_ID_SENSOR_SETUP_SRV          0x1101
#define BT_MESH_MODEL_ID_SENSOR_CLI                0x1102
#define BT_MESH_MODEL_ID_TIME_SRV                  0x1200
#define BT_MESH_MODEL_ID_TIME_SETUP_SRV            0x1201
#define BT_MESH_MODEL_ID_TIME_CLI                  0x1202
#define BT_MESH_MODEL_ID_SCENE_SRV                 0x1203
#define BT_MESH_MODEL_ID_SCENE_SETUP_SRV           0x1204
#define BT_MESH_MODEL_ID_SCENE_CLI                 0x1205
#define BT_MESH_MODEL_ID_SCHEDULER_SRV             0x1206
#define BT_MESH_MODEL_ID_SCHEDULER_SETUP_SRV       0x1207
#define BT_MESH_MODEL_ID_SCHEDULER_CLI             0x1208
#define BT_MESH_MODEL_ID_LIGHT_LIGHTNESS_SRV       0x1300
#define BT_MESH_MODEL_ID_LIGHT_LIGHTNESS_SETUP_SRV 0x1301
#define BT_MESH_MODEL_ID_LIGHT_LIGHTNESS_CLI       0x1302
#define BT_MESH_MODEL_ID_LIGHT_CTL_SRV             0x1303
#define BT_MESH_MODEL_ID_LIGHT_CTL_SETUP_SRV       0x1304
#define BT_MESH_MODEL_ID_LIGHT_CTL_CLI             0x1305
#define BT_MESH_MODEL_ID_LIGHT_CTL_TEMP_SRV        0x1306
#define BT_MESH_MODEL_ID_LIGHT_HSL_SRV             0x1307
#define BT_MESH_MODEL_ID_LIGHT_HSL_SETUP_SRV       0x1308
#define BT_MESH_MODEL_ID_LIGHT_HSL_CLI             0x1309
#define BT_MESH_MODEL_ID_LIGHT_HSL_HUE_SRV         0x130a
#define BT_MESH_MODEL_ID_LIGHT_HSL_SAT_SRV         0x130b
#define BT_MESH_MODEL_ID_LIGHT_XYL_SRV             0x130c
#define BT_MESH_MODEL_ID_LIGHT_XYL_SETUP_SRV       0x130d
#define BT_MESH_MODEL_ID_LIGHT_XYL_CLI             0x130e
#define BT_MESH_MODEL_ID_LIGHT_LC_SRV              0x130f
#define BT_MESH_MODEL_ID_LIGHT_LC_SETUPSRV         0x1310
#define BT_MESH_MODEL_ID_LIGHT_LC_CLI              0x1311

/** Model opcode handler. */
struct bt_mesh_model_op {
	/** OpCode encoded using the BT_MESH_MODEL_OP_* macros */
	const uint32_t  opcode;

	/** Minimum required message length */
	const size_t min_len;

	/** @brief Handler function for this opcode.
	 *
	 *  @param model Model instance receiving the message.
	 *  @param ctx   Message context for the message.
	 *  @param buf   Message buffer containing the message payload, not
	 *               including the opcode.
	 */
	void (*const func)(struct bt_mesh_model *model,
			   struct bt_mesh_msg_ctx *ctx,
			   struct net_buf_simple *buf);
};

#define BT_MESH_MODEL_OP_1(b0) (b0)
#define BT_MESH_MODEL_OP_2(b0, b1) (((b0) << 8) | (b1))
#define BT_MESH_MODEL_OP_3(b0, cid) ((((b0) << 16) | 0xc00000) | (cid))

/** End of the opcode list. Must always be present. */
#define BT_MESH_MODEL_OP_END { 0, 0, NULL }
/** Helper to define an empty opcode list. */
#define BT_MESH_MODEL_NO_OPS ((struct bt_mesh_model_op []) \
			      { BT_MESH_MODEL_OP_END })

/** Helper to define an empty model array */
#define BT_MESH_MODEL_NONE ((struct bt_mesh_model []){})

/** @def BT_MESH_MODEL_CB
 *
 *  @brief Composition data SIG model entry with callback functions.
 *
 *  @param _id        Model ID.
 *  @param _op        Array of model opcode handlers.
 *  @param _pub       Model publish parameters.
 *  @param _user_data User data for the model.
 *  @param _cb        Callback structure, or NULL to keep no callbacks.
 */
#define BT_MESH_MODEL_CB(_id, _op, _pub, _user_data, _cb)                    \
{                                                                            \
	.id = (_id),                                                         \
	.pub = _pub,                                                         \
	.keys = BT_MESH_MODEL_KEYS_UNUSED,                                   \
	.groups = BT_MESH_MODEL_GROUPS_UNASSIGNED,                           \
	.op = _op,                                                           \
	.cb = _cb,                                                           \
	.user_data = _user_data,                                             \
}

/** @def BT_MESH_MODEL_VND_CB
 *
 *  @brief Composition data vendor model entry with callback functions.
 *
 *  @param _company   Company ID.
 *  @param _id        Model ID.
 *  @param _op        Array of model opcode handlers.
 *  @param _pub       Model publish parameters.
 *  @param _user_data User data for the model.
 *  @param _cb        Callback structure, or NULL to keep no callbacks.
 */
#define BT_MESH_MODEL_VND_CB(_company, _id, _op, _pub, _user_data, _cb)      \
{                                                                            \
	.vnd.company = (_company),                                           \
	.vnd.id = (_id),                                                     \
	.op = _op,                                                           \
	.pub = _pub,                                                         \
	.keys = BT_MESH_MODEL_KEYS_UNUSED,                                   \
	.groups = BT_MESH_MODEL_GROUPS_UNASSIGNED,                           \
	.user_data = _user_data,                                             \
	.cb = _cb,                                                           \
}


/** @def BT_MESH_MODEL
 *
 *  @brief Composition data SIG model entry.
 *
 *  @param _id        Model ID.
 *  @param _op        Array of model opcode handlers.
 *  @param _pub       Model publish parameters.
 *  @param _user_data User data for the model.
 */
#define BT_MESH_MODEL(_id, _op, _pub, _user_data)                              \
	BT_MESH_MODEL_CB(_id, _op, _pub, _user_data, NULL)

/** @def BT_MESH_MODEL_VND
 *
 *  @brief Composition data vendor model entry.
 *
 *  @param _company   Company ID.
 *  @param _id        Model ID.
 *  @param _op        Array of model opcode handlers.
 *  @param _pub       Model publish parameters.
 *  @param _user_data User data for the model.
 */
#define BT_MESH_MODEL_VND(_company, _id, _op, _pub, _user_data)                \
	BT_MESH_MODEL_VND_CB(_company, _id, _op, _pub, _user_data, NULL)

/** @def BT_MESH_TRANSMIT
 *
 *  @brief Encode transmission count & interval steps.
 *
 *  @param count   Number of retransmissions (first transmission is excluded).
 *  @param int_ms  Interval steps in milliseconds. Must be greater than 0,
 *                 less than or equal to 320, and a multiple of 10.
 *
 *  @return Mesh transmit value that can be used e.g. for the default
 *          values of the configuration model data.
 */
#define BT_MESH_TRANSMIT(count, int_ms) ((count) | (((int_ms / 10) - 1) << 3))

/** @def BT_MESH_TRANSMIT_COUNT
 *
 *  @brief Decode transmit count from a transmit value.
 *
 *  @param transmit Encoded transmit count & interval value.
 *
 *  @return Transmission count (actual transmissions is N + 1).
 */
#define BT_MESH_TRANSMIT_COUNT(transmit) (((transmit) & (uint8_t)BIT_MASK(3)))

/** @def BT_MESH_TRANSMIT_INT
 *
 *  @brief Decode transmit interval from a transmit value.
 *
 *  @param transmit Encoded transmit count & interval value.
 *
 *  @return Transmission interval in milliseconds.
 */
#define BT_MESH_TRANSMIT_INT(transmit) ((((transmit) >> 3) + 1) * 10)

/** @def BT_MESH_PUB_TRANSMIT
 *
 *  @brief Encode Publish Retransmit count & interval steps.
 *
 *  @param count  Number of retransmissions (first transmission is excluded).
 *  @param int_ms Interval steps in milliseconds. Must be greater than 0 and a
 *                multiple of 50.
 *
 *  @return Mesh transmit value that can be used e.g. for the default
 *          values of the configuration model data.
 */
#define BT_MESH_PUB_TRANSMIT(count, int_ms) BT_MESH_TRANSMIT(count,           \
							     (int_ms) / 5)

/** @def BT_MESH_PUB_TRANSMIT_COUNT
 *
 *  @brief Decode Publish Retransmit count from a given value.
 *
 *  @param transmit Encoded Publish Retransmit count & interval value.
 *
 *  @return Retransmission count (actual transmissions is N + 1).
 */
#define BT_MESH_PUB_TRANSMIT_COUNT(transmit) BT_MESH_TRANSMIT_COUNT(transmit)

/** @def BT_MESH_PUB_TRANSMIT_INT
 *
 *  @brief Decode Publish Retransmit interval from a given value.
 *
 *  @param transmit Encoded Publish Retransmit count & interval value.
 *
 *  @return Transmission interval in milliseconds.
 */
#define BT_MESH_PUB_TRANSMIT_INT(transmit) ((((transmit) >> 3) + 1) * 50)

/** Model publication context.
 *
 *  The context should primarily be created using the
 *  BT_MESH_MODEL_PUB_DEFINE macro.
 */
struct bt_mesh_model_pub {
	/** The model the context belongs to. Initialized by the stack. */
	struct bt_mesh_model *mod;

	uint16_t addr;         /**< Publish Address. */
	uint16_t key:12,       /**< Publish AppKey Index. */
	      cred:1,       /**< Friendship Credentials Flag. */
	      send_rel:1;   /**< Force reliable sending (segment acks) */

	uint8_t  ttl;          /**< Publish Time to Live. */
	uint8_t  retransmit;   /**< Retransmit Count & Interval Steps. */
	uint8_t  period;       /**< Publish Period. */
	uint8_t  period_div:4, /**< Divisor for the Period. */
	      fast_period:1,/**< Use FastPeriodDivisor */
	      count:3;      /**< Retransmissions left. */

	uint32_t period_start; /**< Start of the current period. */

	/** @brief Publication buffer, containing the publication message.
	 *
	 *  This will get correctly created when the publication context
	 *  has been defined using the BT_MESH_MODEL_PUB_DEFINE macro.
	 *
	 *	BT_MESH_MODEL_PUB_DEFINE(name, update, size);
	 */
	struct net_buf_simple *msg;

	/** @brief Callback for updating the publication buffer.
	 *
	 *  When set to NULL, the model is assumed not to support
	 *  periodic publishing. When set to non-NULL the callback
	 *  will be called periodically and is expected to update
	 *  @ref bt_mesh_model_pub.msg with a valid publication
	 *  message.
	 *
	 *  If the callback returns non-zero, the publication is skipped
	 *  and will resume on the next periodic publishing interval.
	 *
	 *  @param mod The Model the Publication Context belogs to.
	 *
	 *  @return Zero on success or (negative) error code otherwise.
	 */
	int (*update)(struct bt_mesh_model *mod);

	/** Publish Period Timer. Only for stack-internal use. */
	struct k_delayed_work timer;
};

/** @def BT_MESH_MODEL_PUB_DEFINE
 *
 *  Define a model publication context.
 *
 *  @param _name Variable name given to the context.
 *  @param _update Optional message update callback (may be NULL).
 *  @param _msg_len Length of the publication message.
 */
#define BT_MESH_MODEL_PUB_DEFINE(_name, _update, _msg_len) \
	NET_BUF_SIMPLE_DEFINE_STATIC(bt_mesh_pub_msg_##_name, _msg_len); \
	static struct bt_mesh_model_pub _name = { \
		.msg = &bt_mesh_pub_msg_##_name, \
		.update = _update, \
	}

/** Model callback functions. */
struct bt_mesh_model_cb {
	/** @brief Set value handler of user data tied to the model.
	 *
	 *  @sa settings_handler::h_set
	 *
	 *  @param model   Model to set the persistent data of.
	 *  @param name    Name/key of the settings item.
	 *  @param len_rd  The size of the data found in the backend.
	 *  @param read_cb Function provided to read the data from the backend.
	 *  @param cb_arg  Arguments for the read function provided by the
	 *                 backend.
	 *
	 *  @return 0 on success, error otherwise.
	 */
	int (*const settings_set)(struct bt_mesh_model *model,
				  const char *name, size_t len_rd,
				  settings_read_cb read_cb, void *cb_arg);

	/** @brief Callback called when the mesh is started.
	 *
	 *  This handler gets called after the node has been provisioned, or
	 *  after all mesh data has been loaded from persistent storage.
	 *
	 *  When this callback fires, the mesh model may start its behavior,
	 *  and all Access APIs are ready for use.
	 *
	 *  @param model      Model this callback belongs to.
	 *
	 *  @return 0 on success, error otherwise.
	 */
	int (*const start)(struct bt_mesh_model *model);

	/** @brief Model init callback.
	 *
	 *  Called on every model instance during mesh initialization.
	 *
	 *  If any of the model init callbacks return an error, the Mesh
	 *  subsystem initialization will be aborted, and the error will be
	 *  returned to the caller of @ref bt_mesh_init.
	 *
	 *  @param model Model to be initialized.
	 *
	 *  @return 0 on success, error otherwise.
	 */
	int (*const init)(struct bt_mesh_model *model);

	/** @brief Model reset callback.
	 *
	 *  Called when the mesh node is reset. All model data is deleted on
	 *  reset, and the model should clear its state.
	 *
	 *  @note If the model stores any persistent data, this needs to be
	 *  erased manually.
	 *
	 *  @param model Model this callback belongs to.
	 */
	void (*const reset)(struct bt_mesh_model *model);
};

/** Vendor model ID */
struct bt_mesh_mod_id_vnd {
	/** Vendor's company ID */
	uint16_t company;
	/** Model ID */
	uint16_t id;
};

/** Abstraction that describes a Mesh Model instance */
struct bt_mesh_model {
	union {
		/** SIG model ID */
		const uint16_t id;
		/** Vendor model ID */
		const struct bt_mesh_mod_id_vnd vnd;
	};

	/* Internal information, mainly for persistent storage */
	uint8_t  elem_idx;   /* Belongs to Nth element */
	uint8_t  mod_idx;    /* Is the Nth model in the element */
	uint16_t flags;      /* Model flags for internal bookkeeping */

	/** Model Publication */
	struct bt_mesh_model_pub * const pub;

	/** AppKey List */
	uint16_t keys[CONFIG_BT_MESH_MODEL_KEY_COUNT];

	/** Subscription List (group or virtual addresses) */
	uint16_t groups[CONFIG_BT_MESH_MODEL_GROUP_COUNT];

	/** Opcode handler list */
	const struct bt_mesh_model_op * const op;

	/** Model callback structure. */
	const struct bt_mesh_model_cb * const cb;

#ifdef CONFIG_BT_MESH_MODEL_EXTENSIONS
	/* Pointer to the next model in a model extension tree. */
	struct bt_mesh_model *next;
	/* Pointer to the first model this model extends. */
	struct bt_mesh_model *extends;
#endif
	/** Model-specific user data */
	void *user_data;
};

/** Callback structure for monitoring model message sending */
struct bt_mesh_send_cb {
	/** @brief Handler called at the start of the transmission.
	 *
	 *  @param duration The duration of the full transmission.
	 *  @param err      Error occurring during sending.
	 *  @param cb_data  Callback data, as passed to the send API.
	 */
	void (*start)(uint16_t duration, int err, void *cb_data);
	/** @brief Handler called at the end of the transmission.
	 *
	 *  @param err     Error occurring during sending.
	 *  @param cb_data Callback data, as passed to the send API.
	 */
	void (*end)(int err, void *cb_data);
};


/** Special TTL value to request using configured default TTL */
#define BT_MESH_TTL_DEFAULT 0xff

/** Maximum allowed TTL value */
#define BT_MESH_TTL_MAX     0x7f

/** @brief Send an Access Layer message.
 *
 *  @param model   Mesh (client) Model that the message belongs to.
 *  @param ctx     Message context, includes keys, TTL, etc.
 *  @param msg     Access Layer payload (the actual message to be sent).
 *  @param cb      Optional "message sent" callback.
 *  @param cb_data User data to be passed to the callback.
 *
 *  @return 0 on success, or (negative) error code on failure.
 */
int bt_mesh_model_send(struct bt_mesh_model *model,
		       struct bt_mesh_msg_ctx *ctx,
		       struct net_buf_simple *msg,
		       const struct bt_mesh_send_cb *cb,
		       void *cb_data);

/** @brief Send a model publication message.
 *
 *  Before calling this function, the user needs to ensure that the model
 *  publication message (@ref bt_mesh_model_pub.msg) contains a valid
 *  message to be sent. Note that this API is only to be used for
 *  non-period publishing. For periodic publishing the app only needs
 *  to make sure that @ref bt_mesh_model_pub.msg contains a valid message
 *  whenever the @ref bt_mesh_model_pub.update callback is called.
 *
 *  @param model Mesh (client) Model that's publishing the message.
 *
 *  @return 0 on success, or (negative) error code on failure.
 */
int bt_mesh_model_publish(struct bt_mesh_model *model);

/** @brief Get the element that a model belongs to.
 *
 *  @param mod Mesh model.
 *
 *  @return Pointer to the element that the given model belongs to.
 */
struct bt_mesh_elem *bt_mesh_model_elem(struct bt_mesh_model *mod);

/** @brief Find a SIG model.
 *
 *  @param elem Element to search for the model in.
 *  @param id   Model ID of the model.
 *
 *  @return A pointer to the Mesh model matching the given parameters, or NULL
 *          if no SIG model with the given ID exists in the given element.
 */
struct bt_mesh_model *bt_mesh_model_find(const struct bt_mesh_elem *elem,
					 uint16_t id);

/** @brief Find a vendor model.
 *
 *  @param elem    Element to search for the model in.
 *  @param company Company ID of the model.
 *  @param id      Model ID of the model.
 *
 *  @return A pointer to the Mesh model matching the given parameters, or NULL
 *          if no vendor model with the given ID exists in the given element.
 */
struct bt_mesh_model *bt_mesh_model_find_vnd(const struct bt_mesh_elem *elem,
					     uint16_t company, uint16_t id);

/** @brief Get whether the model is in the primary element of the device.
 *
 *  @param mod Mesh model.
 *
 *  @return true if the model is on the primary element, false otherwise.
 */
static inline bool bt_mesh_model_in_primary(const struct bt_mesh_model *mod)
{
	return (mod->elem_idx == 0);
}

/** @brief Immediately store the model's user data in persistent storage.
 *
 *  @param mod      Mesh model.
 *  @param vnd      This is a vendor model.
 *  @param name     Name/key of the settings item.
 *  @param data     Model data to store, or NULL to delete any model data.
 *  @param data_len Length of the model data.
 *
 *  @return 0 on success, or (negative) error code on failure.
 */
int bt_mesh_model_data_store(struct bt_mesh_model *mod, bool vnd,
			 const char *name, const void *data,
			 size_t data_len);

/** @brief Let a model extend another.
 *
 *  Mesh models may be extended to reuse their functionality, forming a more
 *  complex model. A Mesh model may extend any number of models, in any element.
 *  The extensions may also be nested, ie a model that extends another may
 *  itself be extended. Extensions may not be cyclical, and a model can only be
 *  extended by one other model.
 *
 *  A set of models that extend each other form a model extension tree.
 *
 *  All models in an extension tree share one subscription list per element. The
 *  access layer will utilize the combined subscription list of all models in an
 *  extension tree and element, giving the models extended subscription list
 *  capacity.
 *
 *  @param mod      Mesh model.
 *  @param base_mod The model being extended.
 *
 *  @retval 0 Successfully extended the base_mod model.
 *  @retval -EALREADY The base_mod model is already extended.
 */
int bt_mesh_model_extend(struct bt_mesh_model *mod,
			 struct bt_mesh_model *base_mod);

/** Node Composition */
struct bt_mesh_comp {
	uint16_t cid; /**< Company ID */
	uint16_t pid; /**< Product ID */
	uint16_t vid; /**< Version ID */

	size_t elem_count; /**< The number of elements in this device. */
	struct bt_mesh_elem *elem; /**< List of elements. */
};

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* ZEPHYR_INCLUDE_BLUETOOTH_MESH_ACCESS_H_ */
