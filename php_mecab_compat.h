/*
 * macros for compatibility
 */
#ifndef PHP_SENNA_COMPAT_H
#define PHP_SENNA_COMPAT_H

#ifndef getThis
#define getThis() NULL
#endif

#ifdef ZEND_ENGINE_2
#include "php_mecab_ze2.h"
#else
#include "php_mecab_ze1.h"
#endif

#define PHP_MECAB_FROM_PARAMETER()	PHP_MECAB_RSRC_FROM_PARAMETER()
#define PHP_MECAB_NODE_FROM_PARAMETER()	PHP_MECAB_RSRC_FROM_PARAMETER2(node)
#define PHP_MECAB_PATH_FROM_PARAMETER()	PHP_MECAB_RSRC_FROM_PARAMETER2(path)

#define PHP_MECAB_NODE_PARSE_PARAMETERS(fmt, ...)	PHP_MECAB_PARSE_PARAMETERS2(node, fmt, __VA_ARGS__)
#define PHP_MECAB_PATH_PARSE_PARAMETERS(fmt, ...)	PHP_MECAB_PARSE_PARAMETERS2(path, fmt, __VA_ARGS__)

#define PHP_MECAB_NODE_RETURN_PROPERTY(type, ...) PHP_MECAB_RETURN_PROPERTY(node, type, __VA_ARGS__)
#define PHP_MECAB_PATH_RETURN_PROPERTY(type, ...) PHP_MECAB_RETURN_PROPERTY(path, type, __VA_ARGS__)

#endif /* PHP_SENNA_COMPAT_H */
