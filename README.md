mpl
=====
##introduce

mpl is a php extension for getting mobile phone number location.
mpl是一个通过手机号码获取号码归属地的php扩展。
现在是简单的顺序查找，同样的逻辑，查询速度比php快5~9倍。
将来有空了我会用hashmap或其他数据结构来优化。

##install:
```shell
phpize
./configure 
make
make install
echo "extension=mpl.so" >> /etc/php.ini
echo "mpl_data_path=/var/www/phone.data" >> /etc/php.ini
```
##eg:
```php
<?php
print_r( Mpl::getLocation('133444'));
?>
```
##output:
```php
Array
(
    [province] => 北京
    [city] => 北京
    [type] => 移动神州行卡
    [area_codepost_code] => 010
    [post_code] => 100000

)
```

##contact
e-mail: love(a)taogogo.info