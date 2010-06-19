<?php 
/**
 * php_mecab/examples
 * parse string (OO-API, persistent)
 * charset=utf-8
 */

require_once dirname(__FILE__) . '/common.inc.php';

$mecab = new MeCab_Tagger(null, true);

border();

echo $mecab->parse($str_long);

border();
