/*
 * macros for compatibility
 */
#ifndef PHP_MECAB_COMPAT_H
#define PHP_MECAB_COMPAT_H

#define PHP_MECAB_FETCH_OBJECT(ptr, type, zv) ptr = (type)zend_object_store_get_object((zv) TSRMLS_CC)

#define PHP_MECAB_INTERNAL_RSRC_FROM_PARAMETER() { \
	if (object) { \
		zmecab = object; \
		if (ZEND_NUM_ARGS() != 0) { \
			WRONG_PARAM_COUNT; \
		} else { \
			php_mecab_object *intern; \
			PHP_MECAB_FETCH_OBJECT(intern, php_mecab_object *, object); \
			xmecab = intern->ptr; \
		} \
	} else { \
		if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &zmecab) == FAILURE) { \
			return; \
		} \
		ZEND_FETCH_RESOURCE(xmecab, php_mecab *, &zmecab, -1, "mecab", le_mecab); \
	} \
}

#define PHP_MECAB_RSRC_FROM_PARAMETER() \
	PHP_MECAB_INTERNAL_RSRC_FROM_PARAMETER() \
	mecab = xmecab->ptr; \

#define PHP_MECAB_INTERNAL_RSRC_FROM_PARAMETER2(name) { \
	if (object) { \
		z##name = object; \
		if (ZEND_NUM_ARGS() != 0) { \
			WRONG_PARAM_COUNT; \
		} else { \
			php_mecab_##name##_object *intern; \
			PHP_MECAB_FETCH_OBJECT(intern, php_mecab_##name##_object *, object); \
			x##name = intern->ptr; \
		} \
	} else { \
		if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &z##name) == FAILURE) { \
			return; \
		} \
		ZEND_FETCH_RESOURCE(x##name, php_mecab_##name *, &z##name, -1, "mecab_" #name, le_mecab_##name); \
	} \
}

#define PHP_MECAB_RSRC_FROM_PARAMETER2(name) \
	PHP_MECAB_INTERNAL_RSRC_FROM_PARAMETER2(name) \
	name = x##name->ptr;

#define PHP_MECAB_PARSE_PARAMETERS(fmt, ...) { \
	if (object) { \
		zmecab = object; \
		if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, fmt, __VA_ARGS__) == FAILURE) { \
			return; \
		} else { \
			php_mecab_object *intern; \
			PHP_MECAB_FETCH_OBJECT(intern, php_mecab_object *, object); \
			xmecab = intern->ptr; \
		} \
	} else { \
		if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r" fmt, &zmecab, __VA_ARGS__) == FAILURE) { \
			return; \
		} \
		ZEND_FETCH_RESOURCE(xmecab, php_mecab *, &zmecab, -1, "mecab", le_mecab); \
	} \
	mecab = xmecab->ptr; \
}

#define PHP_MECAB_PARSE_PARAMETERS2(name, fmt, ...) { \
	if (object) { \
		z##name = object; \
		if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, fmt, __VA_ARGS__) == FAILURE) { \
			return; \
		} else { \
			php_mecab_##name##_object *intern; \
			PHP_MECAB_FETCH_OBJECT(intern, php_mecab_##name##_object *, object); \
			x##name = intern->ptr; \
		} \
	} else { \
		if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r" fmt, &z##name, __VA_ARGS__) == FAILURE) { \
			return; \
		} \
		ZEND_FETCH_RESOURCE(x##name, php_mecab_##name *, &z##name, -1, "mecab_" #name, le_mecab_##name); \
	} \
	name = x##name->ptr; \
}

#define PHP_MECAB_RETURN_PROPERTY(name, type, ...) { \
	zval *object = getThis(); \
	php_mecab_##name *x##name = NULL; \
	const mecab_##name##_t *name = NULL; \
	if (object) { \
		if (ZEND_NUM_ARGS() != 0) { \
			WRONG_PARAM_COUNT; \
		} else { \
			php_mecab_##name##_object *intern; \
			intern = (php_mecab_##name##_object *)zend_object_store_get_object(object TSRMLS_CC); \
			x##name = intern->ptr; \
		} \
	} else { \
		zval *z##name = NULL; \
		if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &z##name) == FAILURE) { \
			return; \
		} \
		ZEND_FETCH_RESOURCE(x##name, php_mecab_##name*, &z##name, -1, "mecab_" #name, le_mecab_##name); \
	} \
	name = x##name->ptr; \
	RETURN_##type(__VA_ARGS__); \
}

#define PHP_MECAB_FROM_PARAMETER()	PHP_MECAB_RSRC_FROM_PARAMETER()
#define PHP_MECAB_NODE_FROM_PARAMETER()	PHP_MECAB_RSRC_FROM_PARAMETER2(node)
#define PHP_MECAB_PATH_FROM_PARAMETER()	PHP_MECAB_RSRC_FROM_PARAMETER2(path)

#define PHP_MECAB_INTERNAL_FROM_PARAMETER()	PHP_MECAB_INTERNAL_RSRC_FROM_PARAMETER()
#define PHP_MECAB_NODE_INTERNAL_FROM_PARAMETER()	PHP_MECAB_INTERNAL_RSRC_FROM_PARAMETER2(node)
#define PHP_MECAB_PATH_INTERNAL_FROM_PARAMETER()	PHP_MECAB_INTERNAL_RSRC_FROM_PARAMETER2(path)

#define PHP_MECAB_NODE_PARSE_PARAMETERS(fmt, ...)	PHP_MECAB_PARSE_PARAMETERS2(node, fmt, __VA_ARGS__)
#define PHP_MECAB_PATH_PARSE_PARAMETERS(fmt, ...)	PHP_MECAB_PARSE_PARAMETERS2(path, fmt, __VA_ARGS__)

#define PHP_MECAB_NODE_RETURN_PROPERTY(type, ...) PHP_MECAB_RETURN_PROPERTY(node, type, __VA_ARGS__)
#define PHP_MECAB_PATH_RETURN_PROPERTY(type, ...) PHP_MECAB_RETURN_PROPERTY(path, type, __VA_ARGS__)

#define PHP_MECAB_REGISTER_CONSTANT(name) \
	REGISTER_LONG_CONSTANT(#name, name, CONST_PERSISTENT | CONST_CS)

#define PHP_MECAB_REGISTER_NS_CONSTANT(name) \
	REGISTER_NS_LONG_CONSTANT("MeCab", #name, MECAB_##name, CONST_PERSISTENT | CONST_CS)

#if PHP_API_VERSION < 20100412
static inline void
object_properties_init(zend_object *object, zend_class_entry *class_type)
{
	zval *tmp = NULL;
	zend_hash_copy(object->properties, &class_type->default_properties,
	               (copy_ctor_func_t)zval_add_ref, (void *)&tmp, sizeof(zval *));
}
#endif

#endif /* PHP_MECAB_COMPAT_H */
