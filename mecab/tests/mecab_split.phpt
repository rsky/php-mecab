--TEST--
mecab_split() function
--SKIPIF--
<?php
if (PHP_VERSION_ID >= 70000) {
    die('skip this feature is not available in PHP 7');
}
?>
--FILE--
<?php
echo implode('/', mecab_split('The quick brown fox jumps over the lazy dog.'));
?>
--EXPECT--
The/quick/brown/fox/jumps/over/the/lazy/dog/.
