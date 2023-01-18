/*
 * Copyright (c) 2023 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-4-Clause
 */

#ifndef SM_EVENTS_H
#define SM_EVENTS_H

enum event_type {
	EVENT_TYPE_SIDEWALK,
	EVENT_FACTORY_RESET,
	EVENT_BUTTON_PRESS,
	EVENT_CONNECT_LINK_TYPE_1,
	EVENT_SET_DEVICE_PROFILE_LINK_TYPE_2,
	EVENT_NOTIFICATION_TIMER_FIRED,
	EVENT_BUTTON_PRESS_TIMER_FIRED,
};

enum btn_event {
	BTN_EVENT_KEY_0 = 0,
	BTN_EVENT_KEY_1,
	BTN_EVENT_KEY_2,
	BTN_EVENT_KEY_3,
	BTN_EVENT_RESET_KEY,
};

#endif /* SM_EVENTS_H */
