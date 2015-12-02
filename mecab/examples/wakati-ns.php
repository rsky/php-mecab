<?php
/**
 * php-mecab/examples
 * parse string, wakati output format
 * charset=utf-8
 */

require_once dirname(__FILE__) . '/common.inc.php';

$mecab = new MeCab\Tagger($arg_wakati);

border();

echo $mecab->parse($str_long);

border();

print_r(MeCab\split($str));

border();
