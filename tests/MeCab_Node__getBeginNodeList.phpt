--TEST--
MeCab_Node::getBeginNodeList() member function
--SKIPIF--
<?php
if (!extension_loaded('mecab')) {
    die('skip mecab extension is not loaded');
}
if (strncmp(mecab_version(), '0.99', 4) === 0) {
    die('skip this function is not available with mecab 0.99');
}
die('skip test is not implemented');
?>
--FILE--
<?php
echo 'OK'; // no test case for this function yet
?>
--EXPECT--
OK