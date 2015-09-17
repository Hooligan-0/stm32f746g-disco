# LED unit-tests

This unit-tests show how to blink the user LED (LD1). More than juste a blink, 
they are more usefull to see how to configure the cpu and peripheral clocks.

 * hsi-softwait: The simplest way, wait using a for() loop

 * hsi-timer: Main clock is HSI (16MHz) ; blink period use TIM2

 * hse-timer: Main clock is HSE (25MHz X2) ; blink period use TIM2

 * hse_pll-timer: Main clock is PLL ; blink period use TIM2

Note: The three "timer" tests use the same TIM2 values, the resulting speed depend of the clock source.