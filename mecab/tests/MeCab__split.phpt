--TEST--
MeCab\split() member function
--FILE--
<?php
echo implode('/', MeCab\split('The quick brown fox jumps over the lazy dog.'));
?>
--EXPECT--
The/quick/brown/fox/jumps/over/the/lazy/dog/.
