
#ifndef ST080Utils_H_
#define ST080Utils_H_

#define ABS(x)                           (x < 0) ? (-x) : x
#define MAX(a,b)                         (a < b) ? (b) : a
#define MIN(a,b)                         (a < b) ? (a) : b

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
