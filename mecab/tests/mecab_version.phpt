--TEST--
mecab_version() function
--SKIPIF--
<?php
if (PHP_VERSION_ID >= 70000) {
    die('skip this feature is not available in PHP 7');
}
?>
--FILE--
<?php
echo MeCab\version();
?>
--EXPECTREGEX--
[0-9]\.[0-9]+
