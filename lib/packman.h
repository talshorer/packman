#ifndef __PACKMAN_H
#define __PACKMAN_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <endian.h>

enum packman_error {
	PACKMAN_ERROR_SUCCESS = 0,
	PACKMAN_ERROR_NO_SUCH_ENCODING_TYPE,
	PACKMAN_ERROR_BUF_TOO_SMALL,
	PACKMAN_ERROR_INVALID_VALUE,
};

enum packman_encoding_type {
	PACKMAN_ENCODING_INT,
	PACKMAN_ENCODING_STRUCT,
	PACKMAN_ENCODING_SWITCH,
	PACKMAN_ENCODING_ENUM,
	PACKMAN_ENCODING_MAX_VALUE,
};

struct packman_encoding_base {
	enum packman_encoding_type type;
	size_t elem_size;
};

enum packman_error packman_encode(const struct packman_encoding_base *,
		const void *, void *, size_t);

enum packman_error packman_decode(const struct packman_encoding_base *,
		void *, const void *, size_t);

enum packman_endianness {
	PACKMAN_ENDIANNESS_LITTLE,
	PACKMAN_ENDIANNESS_BIG,
};

struct packman_int_description {
	size_t size;
	enum packman_endianness endianness;
};

struct packman_encoding_int {
	struct packman_encoding_base base;
	struct packman_int_description desc;
};

struct packman_encoding_struct {
	struct packman_encoding_base base;
	const struct packman_encoding_base **fields;
	unsigned nfields;
};

struct packman_encoding_enum {
	struct packman_encoding_base base;
	struct packman_int_description desc;
	const void *values; /* should be array of uint##n##_t */
	unsigned nvalues;
};

#endif /* __PACKMAN_H */
