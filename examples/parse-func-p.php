<?php 
/**
 * php-mecab/examples
 * parse string (persistent)
 * charset=utf-8
 */

require_once dirname(__FILE__) . '/common.inc.php';

$mecab = mecab_new(null, true);

border();

echo mecab_sparse_tostr($mecab, $str_long);

border();

mecab_destroy($mecab);
