

#ifndef ST080Utils_H_
#define ST080Utils_H_

// Random functions
#define ABS(x)                           (x < 0) ? (-x) : x
#define MAX(a,b)                         (a < b) ? (b) : a
#define MIN(a,b)                         (a < b) ? (a) : b


// FreeRTOS stuff ============

uint64_t tickTime = 0;        // Counts OS ticks (default = 1000Hz).
uint64_t u64IdleTicks = 0;   // Value of u64IdleTicksCnt is copied once per sec.
uint64_t u64IdleTicksCnt = 0; // Counts when the OS has no task to execute.
uint16_t u16PWM1 = 0;

// This FreeRTOS callback function gets called once per tick (default = 1000Hz).
// ----------------------------------------------------------------------------
void vApplicationTickHook(void) {
	++tickTime;
}

// This FreeRTOS call-back function gets when no other task is ready to execute.
// On a completely unloaded system this is getting called at over 2.5MHz!
// ----------------------------------------------------------------------------
void vApplicationIdleHook(void) {
	++u64IdleTicksCnt;
}

// A required FreeRTOS function.
// ----------------------------------------------------------------------------
void vApplicationMallocFailedHook(void) {
	configASSERT(0);  // Latch on any failure / error.
}

// end of FreeRTOS stuff ============

// a struct for the drum kits
typedef struct {
	// pointers to arrays of samples
	// can use array declarations (prefered) if size is known and fixed for each instrument
  uint16_t *one;
  uint16_t *two;
  uint16_t *three;
  uint16_t *four;
  uint16_t *five;
  uint16_t *six;
  uint16_t *seven;
  uint16_t *eight;
  uint16_t *nine;
} DrumKit;

#endif // ST080Utils_H_
