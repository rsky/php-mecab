--TEST--
mecab_new() function
--SKIPIF--
<?php
if (!extension_loaded('mecab')) {
    die('skip mecab extension is not loaded');
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
