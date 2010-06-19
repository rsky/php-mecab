<?php 
/**
 * php-mecab/examples
 * split string into an array of part-of-speech (persistent)
 * charset=utf-8
 */

require_once dirname(__FILE__) . '/common.inc.php';

function noun_filter($node_info)
{
    //var_dump($node_info);
    return $node_info['posid'] >= 37 && $node_info['posid'] <= 66;
}

border();

print_r(mecab_split($str));

border();

print_r(mecab_split($str, null, null, 'noun_filter', true));

border();
