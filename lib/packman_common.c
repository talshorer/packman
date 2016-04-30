#include "packman_internal.h"

enum packman_error packman_do_int_desc(struct packman_int_description *desc,
		void *_target, const void *_value, size_t *count)
{
	if (*count < desc->size)
		return PACKMAN_ERROR_BUF_TOO_SMALL;
	switch (desc->size) {
	case sizeof(uint8_t):
		*(uint8_t *)_target = *(const uint8_t *)_value;
		break;
	#define PACKMAN_SET_TARGET_INT_CASE(n) \
	case sizeof(uint##n##_t): { \
		uint##n##_t value = *(uint##n##_t *)_value; \
		uint##n##_t *target = (uint##n##_t *)_target; \
		switch (desc->endianness) { \
		case PACKMAN_ENDIANNESS_BIG: \
			*target = htobe##n(value); \
			break; \
		case PACKMAN_ENDIANNESS_LITTLE: \
			*target = htole##n(value); \
			break; \
		} \
		} \
		break
	PACKMAN_SET_TARGET_INT_CASE(16);
	PACKMAN_SET_TARGET_INT_CASE(32);
	PACKMAN_SET_TARGET_INT_CASE(64);
	#undef PACKMAN_SET_TARGET_INT_CASE
	}
	*count -= desc->size;
	return PACKMAN_ERROR_SUCCESS;
}
