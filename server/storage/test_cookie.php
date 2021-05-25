<?php
if (isset($_COOKIE['Mortal'])) $cnt = $_COOKIE['Mortal'] + 1;
else $cnt = 1;

setcookie("Mortal",$cnt,0x6FFFFFFF);
echo "NUM: [".@$_COOKIE['Mortal']."]";
?>
