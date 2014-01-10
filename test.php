<?php
error_reporting(E_ALL);
echo "version:".MPL_VERSION."\n";
echo(microtime(true)."\n");
$result = Mpl::getLocation('13366677888');
var_dump($result);
//echo $result['area_code'];
echo(microtime(true)."\n");
