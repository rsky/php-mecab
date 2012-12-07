<?php
/**
 * php-mecab/examples
 * parse string, wakati output format
 * charset=utf-8
 */

require_once dirname(__FILE__) . '/common.inc.php';

$mecab = mecab_new($arg_wakati);

border();

echo mecab_sparse_tostr($mecab, $str_long);

border();

print_r(mecab_split($str));

border();

mecab_destroy($mecab);
