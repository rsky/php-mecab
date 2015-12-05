/**
 * The MeCab PHP extension
 *
 * Copyright (c) 2006-2015 Ryusuke SEKIYAMA. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * @package     php-mecab
 * @author      Ryusuke SEKIYAMA <rsky0711@gmail.com>
 * @copyright   2006-2015 Ryusuke SEKIYAMA
 * @license     http://www.opensource.org/licenses/mit-license.php  MIT License
 * @version     $Id$
 */

#ifndef PHP_MECAB_H
#define PHP_MECAB_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <php.h>

#include <php_ini.h>
#include <SAPI.h>
#include <ext/standard/info.h>
#include <Zend/zend_extensions.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#ifdef __cplusplus
} /* extern "C" */
#endif

#include <mecab.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

#define PHP_MECAB_MODULE_VERSION "0.6.0"

#ifndef PHP_MECAB_VERSION_NUMBER
#define PHP_MECAB_VERSION_NUMBER 0
#endif
#ifndef PHP_MECAB_VERSION_STRING
#define PHP_MECAB_VERSION_STRING "unknown"
#endif

#define FREE_RESOURCE(resource) zend_list_delete(Z_RESVAL_P(resource))

/* {{{ module globals */

ZEND_BEGIN_MODULE_GLOBALS(mecab)
	char *default_rcfile;
	char *default_dicdir;
	char *default_userdic;
ZEND_END_MODULE_GLOBALS(mecab)

#ifdef ZTS
#define MECAB_G(v) TSRMG(mecab_globals_id, zend_mecab_globals *, v)
#else
#define MECAB_G(v) (mecab_globals.v)
#endif

/* }}} */

/* {{{ type definitions */

typedef enum _php_mecab_node_attribute php_mecab_node_attribute;
typedef enum _php_mecab_node_rel php_mecab_node_rel;
typedef enum _php_mecab_path_rel php_mecab_path_rel;
typedef struct _php_mecab php_mecab;
typedef struct _php_mecab_node php_mecab_node;
typedef struct _php_mecab_path php_mecab_path;

enum _php_mecab_node_attribute {
	ATTR_ALL,
	ATTR_SURFACE,
	ATTR_FEATURE,
	ATTR_ID,
	ATTR_LENGTH,
	ATTR_RLENGTH,
	ATTR_RCATTR,
	ATTR_LCATTR,
	ATTR_POSID,
	ATTR_CHAR_TYPE,
	ATTR_STAT,
	ATTR_ISBEST,
	ATTR_ALPHA,
	ATTR_BETA,
	ATTR_PROB,
	ATTR_WCOST,
	ATTR_COST
};

enum _php_mecab_node_rel {
	NODE_PREV,
	NODE_NEXT,
	NODE_ENEXT,
	NODE_BNEXT,
	NODE_RPATH,
	NODE_LPATH
};

enum _php_mecab_path_rel {
	PATH_RNODE,
	PATH_RNEXT,
	PATH_LNODE,
	PATH_LNEXT
};

struct _php_mecab {
	mecab_t *ptr;
#if PHP_VERSION_ID >= 70000
	zend_string *str;
#else
	char *str;
	int len;
#endif
	int ref;
};

struct _php_mecab_node {
	php_mecab *tagger;
	const mecab_node_t *ptr;
};

struct _php_mecab_path {
	php_mecab *tagger;
	const mecab_path_t *ptr;
};

typedef enum _php_mecab_traverse_mode php_mecab_traverse_mode;
typedef struct _php_mecab_object php_mecab_object;
typedef struct _php_mecab_node_object php_mecab_node_object;
typedef struct _php_mecab_path_object php_mecab_path_object;

enum _php_mecab_traverse_mode {
	TRAVERSE_NEXT,
	TRAVERSE_ENEXT,
	TRAVERSE_BNEXT
};

struct _php_mecab_object {
	zend_object std;
	php_mecab *ptr;
};

struct _php_mecab_node_object {
	zend_object std;
	php_mecab_node *ptr;
	const mecab_node_t *root;
	php_mecab_traverse_mode mode;
};

struct _php_mecab_path_object {
	zend_object std;
	php_mecab_path *ptr;
};

/* }}} */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* PHP_MECAB_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
