/*
 * macros for compatibility (PHP4/ZendEngine1)
 */
#ifndef PHP_MECAB_ZE_H
#define PHP_MECAB_ZE_H

#define PHP_MECAB_RSRC_FROM_PARAMETER() { \
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &zmecab) == FAILURE) { \
		return; \
	} \
	ZEND_FETCH_RESOURCE(xmecab, php_mecab *, &zmecab, -1, "mecab", le_mecab); \
	mecab = xmecab->ptr; \
}

#define PHP_MECAB_RSRC_FROM_PARAMETER2(name) { \
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &z##name) == FAILURE) { \
		return; \
	} \
	ZEND_FETCH_RESOURCE(x##name, php_mecab_##name *, &z##name, -1, "mecab_" #name, le_mecab_##name); \
	name = x##name->ptr; \
}

#define PHP_MECAB_PARSE_PARAMETERS(fmt, ...) { \
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r" fmt, &zmecab, __VA_ARGS__) == FAILURE) { \
		return; \
	} \
	ZEND_FETCH_RESOURCE(xmecab, php_mecab *, &zmecab, -1, "mecab", le_mecab); \
	mecab = xmecab->ptr; \
}

#define PHP_MECAB_PARSE_PARAMETERS2(name, fmt, ...) { \
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r" fmt, &z##name, __VA_ARGS__) == FAILURE) { \
		return; \
	} \
	ZEND_FETCH_RESOURCE(x##name, php_mecab_##name *, &z##name, -1, "mecab_" #name, le_mecab_##name); \
	name = x##name->ptr; \
}

#define PHP_MECAB_RETURN_PROPERTY(name, type, ...) { \
	zval *z##name = NULL; \
	php_mecab_##name *x##name = NULL; \
	const mecab_##name##_t *name = NULL; \
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &z##name) == FAILURE) { \
		return; \
	} \
	ZEND_FETCH_RESOURCE(x##name, php_mecab_##name*, &z##name, -1, "mecab_" #name, le_mecab_##name); \
	name = x##name->ptr; \
	RETURN_##type(__VA_ARGS__); \
}

#endif /* PHP_MECAB_ZE_H */
