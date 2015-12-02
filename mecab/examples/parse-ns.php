<?php
/**
 * php-mecab/examples
 * parse string
 * charset=utf-8
 */

require_once dirname(__FILE__) . '/common.inc.php';

$mecab = new MeCab\Tagger();

border();

echo $mecab->parse($str_long);

border();
