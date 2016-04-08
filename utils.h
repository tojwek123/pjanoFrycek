#ifndef UTILS_H_
#define UTILS_H_

static inline uint32_t usToTicks(uint32_t us, uint16_t prescaler) {return (us * (F_CPU / prescaler)) / 1000000UL;}
static inline uint32_t ticksToUs(uint32_t ticks, uint16_t prescaler) {return ticks * ((1000000UL * (uint32_t)prescaler / F_CPU));}
static inline int32_t mapValue(int32_t value, int32_t inMin, int32_t inMax, int32_t outMin, int32_t outMax) {return (value - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;}

#endif