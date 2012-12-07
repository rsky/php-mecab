<?php
/**
 * php-mecab/examples
 * parse string, wakati output format (OO-API)
 * charset=utf-8
 */

require_once dirname(__FILE__) . '/common.inc.php';

$mecab = new MeCab_Tagger($arg_wakati);

border();

echo $mecab->parse($str_long);

border();

print_r(MeCab::split($str));

border();
