<?php
error_reporting(E_ALL);
echo "version:".MPL_VERSION."\n";
echo(microtime(true)."\n");
var_dump( Mpl::getLocation('888888888888'));
print_r( Mpl::getLocation('13681188888'));
echo(microtime(true)."\n");
