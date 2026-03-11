#ifndef _STATES_H_
#define _STATES_H_

#include <inttypes.h>

typedef enum
{
	STATE_IDLE,
	STATE_ENTER_CODE,
	STATE_VERIFY,
	STATE_UNLOCKED,
    STATE_MENU,
	STATE_CONFIG
} tState;

typedef enum
{
    EVENT_NONE,
    EVENT_KEY,
    EVENT_MENU_KEY,
    EVENT_KEY_TIMEOUT,
    EVENT_DELAY_TIMEOUT,
    EVENT_WINDOW_TIMEOUT,
    EVENT_PENALTY_TIMEOUT,
    EVENT_VERIFY_OK,
    EVENT_VERIFY_FAIL,
    EVENT_UNLOCK_TIMEOUT,
    EVENT_CANCEL_KEY,
    EVENT_MENU_EXIT
}tEvent;

typedef struct
{
    uint8_t window_active;
    uint8_t penalty_active;
    uint8_t second_code_required;
    uint8_t auth_stage;

    uint8_t attempts;
    uint8_t max_attempts;

    uint8_t permanent_mode;
    uint32_t delay;

    uint8_t digits;
    uint8_t max_digits;

} fsm_context_t;


void fsm_dispatcher(tEvent event);

tState fsm_get_state(void);


void handle_idle(void);
void handle_enter_code(void);
void handle_validation(void);
void handle_unlock(void);
void handle_config(void);
void handle_error(void);
void handle_delay(void);
void handle_window(void);
void handle_penalty(void);
void handle_state_locked(void);
void changeState(tState next);


#endif