#include <stdint.h>

#include <libopencm3/lm4f/gpio.h>
#include <libopencm3/lm4f/systemcontrol.h>

static void delay(volatile uint32_t count)
{
    while (count--)
    {
        __asm__("nop");
    }
}

int main(void)
{
    /*
     * Enable GPIO Port F clock.
     *
     * SYSCTL_RCGCGPIO:
     * Bit 5 = GPIO Port F
     */
    SYSCTL_RCGCGPIO |= (1U << 5);

    /*
     * Wait for the peripheral clock to become available.
     */
    while ((SYSCTL_PRGPIO & (1U << 5)) == 0)
    {
    }

    /*
     * Configure PF1, PF2 and PF3 as GPIO outputs.
     */
    gpio_mode_setup(
        GPIOF,
        GPIO_MODE_OUTPUT,
        GPIO_PUPD_NONE,
        GPIO1 | GPIO2 | GPIO3
    );

    /*
     * RGB LED is active-low.
     * Set all three pins HIGH → LEDs OFF.
     */
    gpio_set(GPIOF, GPIO1 | GPIO2 | GPIO3);

    while (1)
    {
        /* RED */
        gpio_clear(GPIOF, GPIO1);
        delay(1000000);
        gpio_set(GPIOF, GPIO1);

        /* GREEN */
        gpio_clear(GPIOF, GPIO3);
        delay(1000000);
        gpio_set(GPIOF, GPIO3);

        /* BLUE */
        gpio_clear(GPIOF, GPIO2);
        delay(1000000);
        gpio_set(GPIOF, GPIO2);
    }

    return 0;
}