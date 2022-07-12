/*
 * Copyright (c) 2022 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-4-Clause
 */
#include <sidewalk_thread.h>

#include <zephyr.h>
#include <dk_buttons_and_leds.h>
#include <logging/log.h>
LOG_MODULE_REGISTER(sid_template, CONFIG_SIDEWALK_LOG_LEVEL);

#define IS_RESET_BTN_PRESSED(_btn)      (_btn & DK_BTN1_MSK)
#if !defined(CONFIG_SIDEWALK_LINK_MASK_FSK) && !defined(CONFIG_SIDEWALK_LINK_MASK_LORA)
#define IS_CONN_REQ_BTN_PRESSED(_btn)   (_btn & DK_BTN2_MSK)
#else /* !defined(CONFIG_SIDEWALK_LINK_MASK_FSK) && !defined(CONFIG_SIDEWALK_LINK_MASK_LORA) */
#define IS_SET_DEV_PROFILE_BTN_PRESSED(_btn)   (_btn & DK_BTN2_MSK)
#endif /* !defined(CONFIG_SIDEWALK_LINK_MASK_FSK) && !defined(CONFIG_SIDEWALK_LINK_MASK_LORA) */
#define IS_SEND_MSG_BTN_PRESSED(_btn)   (_btn & DK_BTN3_MSK)
#define IS_SET_BAT_LV_BTN_PRESSED(_btn) (_btn & DK_BTN4_MSK)

static void button_handler(uint32_t button_state, uint32_t has_changed)
{
	uint32_t button = button_state & has_changed;

	if (IS_RESET_BTN_PRESSED(button)) {
		sidewalk_thread_message_q_write(EVENT_TYPE_FACTORY_RESET);
	}

	if (IS_SET_BAT_LV_BTN_PRESSED(button)) {
		sidewalk_thread_message_q_write(EVENT_TYPE_SET_BATTERY_LEVEL);
	}

#if !defined(CONFIG_SIDEWALK_LINK_MASK_FSK) && !defined(CONFIG_SIDEWALK_LINK_MASK_LORA)
	if (IS_CONN_REQ_BTN_PRESSED(button)) {
		sidewalk_thread_message_q_write(EVENT_TYPE_CONNECTION_REQUEST);
	}

#else /* !defined(CONFIG_SIDEWALK_LINK_MASK_FSK) && !defined(CONFIG_SIDEWALK_LINK_MASK_LORA) */
	if (IS_SET_DEV_PROFILE_BTN_PRESSED(button)) {
		sidewalk_thread_message_q_write(EVENT_TYPE_SET_DEVICE_PROFILE);
	}

#endif /* !defined(CONFIG_SIDEWALK_LINK_MASK_FSK) && !defined(CONFIG_SIDEWALK_LINK_MASK_LORA) */

	if (IS_SEND_MSG_BTN_PRESSED(button)) {
		sidewalk_thread_message_q_write(EVENT_TYPE_SEND_HELLO);
	}
}

void assert_post_action(const char *file, unsigned int line)
{
	LOG_ERR("Assert in %s:%d", file, line);

	for (;;);
}

static int board_init(void)
{
	int err = dk_buttons_init(button_handler);

	if (err) {
		LOG_ERR("Failed to initialize buttons (err: %d)", err);
		return err;
	}

	err = dk_leds_init();
	if (err) {
		LOG_ERR("Failed to initialize LEDs (err: %d)", err);
		return err;
	}
	return 0;
}

void main(void)
{
	if (0 != board_init()) {
		return;
	}

	LOG_INF("Sidewalk example started!");

	sidewalk_thread_enable();
}
