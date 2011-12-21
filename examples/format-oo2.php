<?php
/**
 * php-mecab/examples
 * parse string, wakati output format (OO-API with SPL and autocast)
 * charset=utf-8
 */

require_once dirname(__FILE__) . '/common.inc.php';

$mecab = new MeCab_Tagger($arg_format);

border();

foreach ($mecab->parseToNode($str_long) as $node) {
    echo $mecab->formatNode($node);
}

border();

foreach ($mecab->parseToNode($str_long) as $node) {
    echo $node;
}

border();
