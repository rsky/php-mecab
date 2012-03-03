<?php
/**
 * php-mecab/examples
 * parse string, wakati output format
 * charset=utf-8
 */

require_once dirname(__FILE__) . '/common.inc.php';

$mecab = mecab_new($arg_format);

border();

$node = mecab_sparse_tonode($mecab, $str_long);
while ($node) {
    echo mecab_format_node($mecab, $node);
    $node = mecab_node_next($node);
}

border();

$node = mecab_sparse_tonode($mecab, $str_long);
while ($node) {
    echo mecab_node_tostring($node);
    $node = mecab_node_next($node);
}

border();
