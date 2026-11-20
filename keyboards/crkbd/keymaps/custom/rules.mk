LTO_ENABLE = yes

# No RGB LEDs used for now; frees about 2.5 KB of flash.
RGB_MATRIX_ENABLE = no

# Words per minute, drives the bongo cat animation on the OLED.
WPM_ENABLE = yes

SRC += oled.c
