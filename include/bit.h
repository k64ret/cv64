#define BIT(num) (1 << (num))
/**
 * Apply `mask` on top of `value`.
 */
#define BITS_MASK(value, mask) ((value) & (mask))
/**
 * Apply `mask` on top of `value` and assign result to `value`.
 */
#define BITS_ASSIGN_MASK(value, mask) ((value) &= (mask))
/**
 * Check if `bits` is set in `value`.
 */
#define BITS_HAS(value, bits) BITS_MASK(value, bits)
/**
 * Check if `bits` is set in `value`.
 */
#define BITS_NOT_HAS(value, bits) !BITS_HAS(value, bits)
/**
 * Set `bits` in `value`.
 */
#define BITS_SET(value, bits) ((value) |= (bits))
/**
 * Unset `bits` in `value`.
 */
#define BITS_UNSET(value, bits) ((value) &= ~(bits))
