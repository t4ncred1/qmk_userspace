#pragma once

// Turn the right half's OLED off or back on. Call it on the left (master)
// half, where keys are processed; the state is sent to the right half.
void oled_user_toggle(void);
