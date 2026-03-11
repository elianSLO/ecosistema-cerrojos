#include "fsm.h"

static tState current_state = STATE_IDLE;

static fsm_context_t ctx;

tState fsm_get_state(void)
{
    return current_state;
}

void fsm_set_state(tState state)
{
    current_state = state;
}

void fsm_init(void)
{
    current_state = STATE_IDLE;

    ctx.window_active = 0;
    ctx.penalty_active = 0;
    ctx.second_code_required = 0;
    ctx.auth_stage = 1;

    ctx.attempts = 0;
    ctx.max_attempts = 3;

    ctx.permanent_mode = 0;
    ctx.delay = 0;

    ctx.digits = 0;
    ctx.max_digits = 6;
}

void fsm_dispatch(tEvent event)
{
    switch(current_state)
    {
        case STATE_IDLE:

            switch(event)
            {
                case EVENT_KEY:

                    if(ctx.penalty_active)
                        break;

                    //start_code_entry();

                    if(ctx.window_active)
                        ctx.auth_stage = 2;
                    else
                        ctx.auth_stage = 1;

                    current_state = STATE_ENTER_CODE;

                break;


                case EVENT_MENU_KEY:

                    //enter_menu();
                    current_state = STATE_MENU;

                break;


                case EVENT_DELAY_TIMEOUT:

                    //start_window();

                break;


                case EVENT_WINDOW_TIMEOUT:

                    ctx.window_active = 0;

                break;


                case EVENT_PENALTY_TIMEOUT:

                    ctx.penalty_active = 0;
                    ctx.attempts = 0;

                break;

            }

        break;
    }
}
