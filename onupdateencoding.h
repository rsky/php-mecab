/*
   +----------------------------------------------------------------------+
   | Zend Engine                                                          |
   +----------------------------------------------------------------------+
   | Copyright (c) 1998-2008 Zend Technologies Ltd. (http://www.zend.com) |
   +----------------------------------------------------------------------+
   | This source file is subject to version 2.00 of the Zend license,     |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.zend.com/license/2_00.txt.                                |
   | If you did not receive a copy of the Zend license and are unable to  |
   | obtain it through the world-wide-web, please send a note to          |
   | license@zend.com so we can mail you a copy immediately.              |
   +----------------------------------------------------------------------+
   | Authors: Andi Gutmans <andi@zend.com>                                |
   |          Zeev Suraski <zeev@zend.com>                                |
   +----------------------------------------------------------------------+
*/

static ZEND_INI_MH(PmOnUpdateEncoding);
static void pm_set_converter_error_mode(UConverter *conv, zend_conv_direction direction, uint16_t error_mode);
static void pm_set_converter_subst_char(UConverter *conv, UChar *subst_char);
static int pm_set_converter_encoding(UConverter **converter, const char *encoding);

/* {{{ ZEND_INI_MH(PmOnUpdateEncoding)
   this is a copy of OnUpdateEncoding in zend.c */
static ZEND_INI_MH(PmOnUpdateEncoding)
{
	UConverter **converter;
#ifndef ZTS
	char *base = (char *) mh_arg2;
#else
	char *base;

	base = (char *) ts_resource(*((int *) mh_arg2));
#endif

	converter = (UConverter **) (base+(size_t) mh_arg1);

	if (!new_value && converter == &UG(fallback_encoding_conv)) {
		new_value = "UTF-8";
	}

	if (new_value) {
		if (pm_set_converter_encoding(converter, new_value) == FAILURE) {
			zend_error(E_CORE_ERROR, "Unrecognized encoding '%s' used for %s", new_value ? new_value : "null", entry->name);
			return FAILURE;
		}
	} else {
		if (*converter) {
			ucnv_close(*converter);
		}
		*converter = NULL;
	}
	if (*converter) {
		pm_set_converter_error_mode(*converter, ZEND_FROM_UNICODE, UG(from_error_mode));
		pm_set_converter_error_mode(*converter, ZEND_TO_UNICODE, UG(to_error_mode));
		pm_set_converter_subst_char(*converter, UG(from_subst_char));
	}

	return SUCCESS;
}
/* }}} */

/* {{{ pm_set_converter_error_mode
   this is a copy of zend_set_converter_error_mode in zend_unicode.c */
static void pm_set_converter_error_mode(UConverter *conv, zend_conv_direction direction, uint16_t error_mode)
{
	UErrorCode status = U_ZERO_ERROR;

	switch (error_mode & 0xff) {
		case ZEND_CONV_ERROR_STOP:
			if (direction == ZEND_FROM_UNICODE)
				ucnv_setFromUCallBack(conv, UCNV_FROM_U_CALLBACK_STOP, NULL, NULL, NULL, &status);
			else
				ucnv_setToUCallBack(conv, UCNV_TO_U_CALLBACK_STOP, NULL, NULL, NULL, &status);
			break;

		case ZEND_CONV_ERROR_SKIP:
			if (direction == ZEND_FROM_UNICODE)
				ucnv_setFromUCallBack(conv, UCNV_FROM_U_CALLBACK_SKIP, UCNV_SKIP_STOP_ON_ILLEGAL, NULL, NULL, &status);
			else
				ucnv_setToUCallBack(conv, UCNV_TO_U_CALLBACK_SKIP, UCNV_SKIP_STOP_ON_ILLEGAL, NULL, NULL, &status);
			break;

		case ZEND_CONV_ERROR_SUBST:
			if (direction == ZEND_FROM_UNICODE)
				ucnv_setFromUCallBack(conv, UCNV_FROM_U_CALLBACK_SUBSTITUTE, UCNV_SUB_STOP_ON_ILLEGAL, NULL, NULL, &status);
			else
				ucnv_setToUCallBack(conv, UCNV_TO_U_CALLBACK_SUBSTITUTE, UCNV_SUB_STOP_ON_ILLEGAL, NULL, NULL, &status);
			break;

		case ZEND_CONV_ERROR_ESCAPE_UNICODE:
			if (direction == ZEND_FROM_UNICODE)
				ucnv_setFromUCallBack(conv, UCNV_FROM_U_CALLBACK_ESCAPE, UCNV_ESCAPE_UNICODE, NULL, NULL, &status);
			else
				ucnv_setToUCallBack(conv, UCNV_TO_U_CALLBACK_ESCAPE, UCNV_ESCAPE_UNICODE, NULL, NULL, &status);
			break;

		case ZEND_CONV_ERROR_ESCAPE_ICU:
			if (direction == ZEND_FROM_UNICODE)
				ucnv_setFromUCallBack(conv, UCNV_FROM_U_CALLBACK_ESCAPE, UCNV_ESCAPE_ICU, NULL, NULL, &status);
			else
				ucnv_setToUCallBack(conv, UCNV_TO_U_CALLBACK_ESCAPE, UCNV_ESCAPE_ICU, NULL, NULL, &status);
			break;

		case ZEND_CONV_ERROR_ESCAPE_JAVA:
			if (direction == ZEND_FROM_UNICODE)
				ucnv_setFromUCallBack(conv, UCNV_FROM_U_CALLBACK_ESCAPE, UCNV_ESCAPE_JAVA, NULL, NULL, &status);
			else
				/*
				 * use C escape, even though JAVA is requested, so that we don't
				 * have to expose another constant
				 */
				ucnv_setToUCallBack(conv, UCNV_TO_U_CALLBACK_ESCAPE, UCNV_ESCAPE_C, NULL, NULL, &status);
			break;

		case ZEND_CONV_ERROR_ESCAPE_XML_DEC:
			if (direction == ZEND_FROM_UNICODE)
				ucnv_setFromUCallBack(conv, UCNV_FROM_U_CALLBACK_ESCAPE, UCNV_ESCAPE_XML_DEC, NULL, NULL, &status);
			else
				ucnv_setToUCallBack(conv, UCNV_TO_U_CALLBACK_ESCAPE, UCNV_ESCAPE_XML_DEC, NULL, NULL, &status);
			break;

		case ZEND_CONV_ERROR_ESCAPE_XML_HEX:
			if (direction == ZEND_FROM_UNICODE)
				ucnv_setFromUCallBack(conv, UCNV_FROM_U_CALLBACK_ESCAPE, UCNV_ESCAPE_XML_HEX, NULL, NULL, &status);
			else
				ucnv_setToUCallBack(conv, UCNV_TO_U_CALLBACK_ESCAPE, UCNV_ESCAPE_XML_HEX, NULL, NULL, &status);
			break;

		default:
			assert(0);
			break;
	}
}
/* }}} */

/* {{{ pm_set_converter_subst_char
   this is a copy of zend_set_converter_subst_char in zend_unicode.c */
static void pm_set_converter_subst_char(UConverter *conv, UChar *subst_char)
{
	char dest[8], *dest_ptr;
	int8_t dest_len = 8;
	UErrorCode status = U_ZERO_ERROR;
	UErrorCode temp = U_ZERO_ERROR;
	const void *old_context;
	UConverterFromUCallback old_cb;
	int32_t subst_char_len = u_strlen(subst_char);

	if (!subst_char_len)
		return;

	ucnv_setFromUCallBack(conv, UCNV_FROM_U_CALLBACK_STOP, NULL, &old_cb, &old_context, &temp);
	dest_len = ucnv_fromUChars(conv, dest, dest_len, subst_char, subst_char_len, &status);
	ucnv_setFromUCallBack(conv, old_cb, old_context, NULL, NULL, &temp);
	if (U_FAILURE(status)) {
		zend_error(E_WARNING, "Could not set substitution character for the converter");
		return;
	}

	/* skip BOM for UTF-16/32 converters */
	switch (ucnv_getType(conv)) {
		case UCNV_UTF16:
			dest_ptr = dest + 2;
			dest_len -= 2;
			break;

		case UCNV_UTF32:
			dest_ptr = dest + 4;
			dest_len -= 4;
			break;

		default:
			dest_ptr = dest;
			break;
	}

	ucnv_setSubstChars(conv, dest_ptr, dest_len, &status);
	if (status == U_ILLEGAL_ARGUMENT_ERROR) {
		zend_error(E_WARNING, "Substitution character byte sequence is too short or long for this converter");
		return;
	}
}
/* }}} */

/* {{{ pm_set_converter_encoding
   this is a copy of zend_set_converter_encoding in zend_unicode.c */
static int pm_set_converter_encoding(UConverter **converter, const char *encoding)
{
	UErrorCode status = U_ZERO_ERROR;
	UConverter *new_converter = NULL;

	if (!converter) {
		return FAILURE;
	}

	/*
	 * The specified encoding might be the same as converter's existing one,
	 * which results in a no-op.
	 */
	if (*converter && encoding && encoding[0]) {
		const char *current = ucnv_getName(*converter, &status);
		status = U_ZERO_ERROR; /* reset error */
		if (!ucnv_compareNames(current, encoding)) {
			return SUCCESS;
		}
	}

	/*
	 * If encoding is NULL, ucnv_open() will return a converter based on
	 * the default platform encoding as determined by ucnv_getDefaultName().
	 */
	new_converter = ucnv_open(encoding, &status);
	if (U_FAILURE(status)) {
		return FAILURE;
	}

	if (*converter) {
		ucnv_close(*converter);
	}
	*converter = new_converter;

	return SUCCESS;
}
/* }}} */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * indent-tabs-mode: t
 * End:
 */
