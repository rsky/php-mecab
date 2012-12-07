<?php
/**
 * php-mecab/examples
 * parse string (OO-API)
 * charset=utf-8
 */

require_once dirname(__FILE__) . '/common.inc.php';

$mecab = new MeCab_Tagger();

border();

echo $mecab->parse($str_long);

border();
