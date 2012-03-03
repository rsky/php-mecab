--TEST--
mecab_version() function
--SKIPIF--
<?php
if (!extension_loaded('mecab')) {
    die('skip mecab extension is not loaded');
}
?>
--FILE--
<?php
if (preg_match('/^0\\.[1-9][0-9]+$/', mecab_version())) {
    echo 'OK';
} else {
    echo 'Unexpected MeCab Version';
}
?>
--EXPECT--
OK
