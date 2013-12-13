/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2013 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: taogogo love@taogogo.info                                    |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_mpl.h"

/* If you declare any globals in php_mpl.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(mpl)
*/

/* True global resources - no need for thread safety here */
static int le_mpl;

/* {{{ mpl_methods[]
 */
const zend_function_entry mpl_methods[] = {
	PHP_ME(Mpl, getLocation, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END	/* Must be the last line in mpl_methods[] */
};
/* }}} */

/* {{{ mpl_module_entry
 */
zend_module_entry mpl_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"Mpl",
	mpl_methods,
	PHP_MINIT(mpl),
	PHP_MSHUTDOWN(mpl),
	PHP_RINIT(mpl),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(mpl),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(mpl),
#if ZEND_MODULE_API_NO >= 20010901
	"0.1", /* Replace with version number for your extension */
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_MPL
ZEND_GET_MODULE(mpl)
#endif

zend_class_entry *Mpl_ce;

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(mpl)
{
	REGISTER_STRING_CONSTANT("MPL_VERSION", "0.1", CONST_CS | CONST_PERSISTENT);
    //REGISTER_INI_ENTRIES();
    zend_class_entry Mpl_entry;
    INIT_CLASS_ENTRY(Mpl_entry, "Mpl", mpl_methods);
    Mpl_ce = zend_register_internal_class_ex(&Mpl_entry, NULL, NULL TSRMLS_CC);//注册类
   
   

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(mpl)
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
PHP_RINIT_FUNCTION(mpl)
{
	return SUCCESS;
}

/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(mpl)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(mpl)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "mpl(mobile phone location extension) support", "enabled");
	//读取常量
	zval mpl_version; 
    if(zend_get_constant("MPL_VERSION", sizeof("MPL_VERSION")-1, &mpl_version TSRMLS_DC)){
    	php_info_print_table_row(2, "version", Z_STRVAL(mpl_version));
    }
	php_info_print_table_end();
}
/* }}} */


/* {{{ Mpl::getLocation
 */
PHP_METHOD(Mpl, getLocation) {

    char *arg = NULL;
	int arg_len;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	FILE *fp;
	char str[8];
	char result[100];
	int has_result = 0;
	int pre_len = 7;
	char phone_pre[8];
	if(arg_len<7){
		php_error_docref(NULL TSRMLS_CC, E_NOTICE, "Argument length should be 7 or more");
		return;
	}
	
	strncpy(phone_pre, arg, 7); 
 
    zval *cfg_value;
    char *cfg_name="mpl_data_path";
    cfg_value = cfg_get_entry(cfg_name, strlen(cfg_name) + 1);
    if(!cfg_value){
		php_error_docref(NULL TSRMLS_CC, E_NOTICE, "mpl_data_path should be set in php.ini");
		return;
	}
	//zend_printf("path:%s\n",Z_STRVAL_P(cfg_value));
	if((fp=fopen(Z_STRVAL_P(cfg_value),"r"))==NULL) {
		php_error_docref(NULL TSRMLS_CC, E_NOTICE, "Cannot open mbl data file");
		return;
	}else{
		while (fgets(str,pre_len+1,fp)!=NULL) {
			if(strcmp(str,phone_pre)==0){
				fseek(fp,-pre_len,SEEK_CUR);
				fgets(result,100,fp);
				has_result = 1;
				break;
			}
		}
		fclose(fp);
	}

	if(has_result == 0){
		//php_error_docref(NULL TSRMLS_CC, E_NOTICE, "Cannot find this mobile phone number in data file");
		return;
	}else{
		array_init(return_value);
		char *delim = " ";
		char *slice_value;
		char value_keys[5][9] = {
			"province",
			"city",
			"type",
			"area_code",
			"post_code",
		};
		if(strstr(strtok(result, delim),phone_pre)){
			for(int i=0;i<5;i++){
				slice_value = strtok(NULL, delim);
				if(slice_value){
					add_assoc_string(return_value,value_keys[i],slice_value,1);
				}
			}
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
