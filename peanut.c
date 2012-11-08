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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_peanut.h"

/* If you declare any globals in php_peanut.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(peanut)
*/

/* True global resources - no need for thread safety here */
static int le_peanut;

/* {{{ peanut_functions[]
 *
 * Every user visible function must have an entry in peanut_functions[].
 */
const zend_function_entry peanut_functions[] = {
	PHP_FE(peanut_multiple_array,	NULL)		/* For testing, remove later. */
	PHP_FE_END	/* Must be the last line in peanut_functions[] */
};
/* }}} */

/* {{{ peanut_module_entry
 */
zend_module_entry peanut_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"peanut",
	peanut_functions,
	PHP_MINIT(peanut),
	PHP_MSHUTDOWN(peanut),
	PHP_RINIT(peanut),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(peanut),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(peanut),
#if ZEND_MODULE_API_NO >= 20010901
	"0.1", /* Replace with version number for your extension */
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_PEANUT
ZEND_GET_MODULE(peanut)
#endif

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("peanut.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_peanut_globals, peanut_globals)
    STD_PHP_INI_ENTRY("peanut.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_peanut_globals, peanut_globals)
PHP_INI_END()
*/
/* }}} */

/* {{{ php_peanut_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_peanut_init_globals(zend_peanut_globals *peanut_globals)
{
	peanut_globals->global_value = 0;
	peanut_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(peanut)
{
	/* If you have INI entries, uncomment these lines 
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(peanut)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(peanut)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(peanut)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(peanut)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "Name", "SB结构数据");
  	php_info_print_table_row(2, "Desc", "解决工作中遇到的一些SB结构的数据");
  	php_info_print_table_row(2, "Author", "花生");
  	php_info_print_table_row(2, "Email", "wenjun1055@gmail.com");
  	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */


/* Remove the following function when you have succesfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_peanut_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(peanut_multiple_array)
{
  zval *sb_array, **data, **temp_data, *temp;
  HashTable *arr_hash, *temp_hash;
  HashPosition pointer, temp_pointer;
  array_init(return_value);

  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &sb_array) == FAILURE) 
  {
    RETURN_NULL();
  }

  //将接收到的数组转换成hash表
  arr_hash = Z_ARRVAL_P(sb_array);
  //重置hash指针
  zend_hash_internal_pointer_reset_ex(arr_hash, &pointer);
  //获取hash指针当前指向的值
  while (zend_hash_get_current_data_ex(arr_hash, (void**)&data, &pointer) == SUCCESS)
  {
    //将指针往后移
    zend_hash_move_forward_ex(arr_hash, &pointer);

    temp_hash = Z_ARRVAL_P(*data);
    zend_hash_internal_pointer_reset_ex(temp_hash, &temp_pointer);
    while (zend_hash_get_current_data_ex(temp_hash, (void**)&temp_data, &temp_pointer) == SUCCESS)
    {
      //初始化temp
      MAKE_STD_ZVAL(temp);
      *temp = **temp_data;
      //copytemp
      zval_copy_ctor(temp);

      zend_hash_move_forward_ex(temp_hash, &temp_pointer);
      //将temp所指向的值传入return_value数组中
      add_next_index_zval(return_value, temp);
    }
  }
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and 
   unfold functions in source code. See the corresponding marks just before 
   function definition, where the functions purpose is also documented. Please 
   follow this convention for the convenience of others editing your code.
*/


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
