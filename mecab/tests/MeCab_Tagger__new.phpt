--TEST--
instantiate MeCab\Tagger
--FILE--
<?php
$mecab = new MeCab\Tagger();
echo get_class($mecab);
?>
--EXPECT--
MeCab\Tagger
