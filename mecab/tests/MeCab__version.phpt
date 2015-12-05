--TEST--
MeCab\version() function
--FILE--
<?php
echo MeCab\version();
?>
--EXPECTREGEX--
[0-9]\.[0-9]+
