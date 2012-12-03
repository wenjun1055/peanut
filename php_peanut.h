/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2012 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id: header 321634 2012-01-01 13:15:04Z felipe $ */

#ifndef PHP_PEANUT_H
#define PHP_PEANUT_H

extern zend_module_entry peanut_module_entry;
#define phpext_peanut_ptr &peanut_module_entry

#ifdef PHP_WIN32
#	define PHP_PEANUT_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_PEANUT_API __attribute__ ((visibility("default")))
#else
#	define PHP_PEANUT_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

PHP_MINIT_FUNCTION(peanut);
PHP_MSHUTDOWN_FUNCTION(peanut);
PHP_RINIT_FUNCTION(peanut);
PHP_RSHUTDOWN_FUNCTION(peanut);
PHP_MINFO_FUNCTION(peanut);

/* 将一个二维数组变成一维数组  */
PHP_FUNCTION(peanut_multiple_array);

/* 从一个字符串中找出所有的数字 */
PHP_FUNCTION(peanut_get_number_from_string);

/* 
  	Declare any global variables you may need between the BEGIN
	and END macros here:     

ZEND_BEGIN_MODULE_GLOBALS(peanut)
	long  global_value;
	char *global_string;
ZEND_END_MODULE_GLOBALS(peanut)
*/

/* In every utility function you add that needs to use variables 
   in php_peanut_globals, call TSRMLS_FETCH(); after declaring other 
   variables used by that function, or better yet, pass in TSRMLS_CC
   after the last function argument and declare your utility function
   with TSRMLS_DC after the last declared argument.  Always refer to
   the globals in your function as PEANUT_G(variable).  You are 
   encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/

#ifdef ZTS
#define PEANUT_G(v) TSRMG(peanut_globals_id, zend_peanut_globals *, v)
#else
#define PEANUT_G(v) (peanut_globals.v)
#endif

#endif	/* PHP_PEANUT_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
