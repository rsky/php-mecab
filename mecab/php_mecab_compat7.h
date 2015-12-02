/*
 * macros for compatibility
 */
#ifndef PHP_MECAB_COMPAT_H
#define PHP_MECAB_COMPAT_H

#define PHP_MECAB_INTERNAL_RSRC_FROM_PARAMETER() { \
	zmecab = object; \
	if (ZEND_NUM_ARGS() != 0) { \
		WRONG_PARAM_COUNT; \
	} else { \
		php_mecab_object *intern = php_mecab_object_fetch_object(Z_OBJ_P(object)); \
		xmecab = intern->ptr; \
	} \
}

#define PHP_MECAB_RSRC_FROM_PARAMETER() \
	PHP_MECAB_INTERNAL_RSRC_FROM_PARAMETER() \
	mecab = xmecab->ptr; \

#define PHP_MECAB_INTERNAL_RSRC_FROM_PARAMETER2(name) { \
	z##name = object; \
	if (ZEND_NUM_ARGS() != 0) { \
		WRONG_PARAM_COUNT; \
	} else { \
		php_mecab_##name##_object *intern = php_mecab_##name##_object_fetch_object(Z_OBJ_P(object)); \
		x##name = intern->ptr; \
	} \
}

#define PHP_MECAB_RSRC_FROM_PARAMETER2(name) \
	PHP_MECAB_INTERNAL_RSRC_FROM_PARAMETER2(name) \
	name = x##name->ptr;

#define PHP_MECAB_PARSE_PARAMETERS(fmt, ...) { \
	zmecab = object; \
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, fmt, __VA_ARGS__) == FAILURE) { \
		return; \
	} else { \
		php_mecab_object *intern = php_mecab_object_fetch_object(Z_OBJ_P(object)); \
		xmecab = intern->ptr; \
	} \
	mecab = xmecab->ptr; \
}

#define PHP_MECAB_PARSE_PARAMETERS2(name, fmt, ...) { \
	z##name = object; \
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, fmt, __VA_ARGS__) == FAILURE) { \
		return; \
	} else { \
		php_mecab_##name##_object *intern = php_mecab_##name##_object_fetch_object(Z_OBJ_P(object)); \
		x##name = intern->ptr; \
	} \
}

#define PHP_MECAB_RETURN_PROPERTY(name, type, ...) { \
	zval *object = getThis(); \
	php_mecab_##name *x##name = NULL; \
	const mecab_##name##_t *name = NULL; \
	if (ZEND_NUM_ARGS() != 0) { \
		WRONG_PARAM_COUNT; \
	} else { \
		php_mecab_##name##_object *intern; \
		intern = (php_mecab_##name##_object *)Z_OBJ_P(object); \
		x##name = intern->ptr; \
	} \
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
