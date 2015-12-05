--TEST--
mecab_new() function
--SKIPIF--
<?php
if (PHP_VERSION_ID >= 70000) {
    die('skip this feature is not available in PHP 7');
}
?>
--FILE--
<?php
$mecab = mecab_new();
if (is_resource($mecab)) {
    echo get_resource_type($mecab);
}
?>
--EXPECT--
mecab
