<?php
/**
 * php-mecab/examples
 * get begen/end node list
 * charset=utf-8
 */

require_once dirname(__FILE__) . '/common.inc.php';

$mecab = mecab_new($arg);

if ($node = mecab_sparse_tonode($mecab, $str)) {
    border();
    $len = mecab_node_sentence_length($node);
    for ($i = 0; $i <= $len; $i++) {
        if ($b = mecab_node_begin_node_list($node, $i)) {
            while ($b) {
                writefln("B[%d] %s\t%s", $i, mecab_node_surface($b), mecab_node_feature($b));
                $b = mecab_node_bnext($b);
            }
        }
        if ($e = mecab_node_end_node_list($node, $i)) {
            while ($e) {
                writefln("E[%d] %s\t%s", $i, mecab_node_surface($e), mecab_node_feature($e));
                $e = mecab_node_bnext($e);
            }
        }
    }
}

mecab_destroy($mecab);
