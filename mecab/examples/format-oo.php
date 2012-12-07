<?php
/**
 * php-mecab/examples
 * parse string, wakati output format (OO-API)
 * charset=utf-8
 */

require_once dirname(__FILE__) . '/common.inc.php';

$mecab = new MeCab_Tagger($arg_format);

border();

$node = $mecab->parseToNode($str_long);
while ($node) {
    echo $mecab->formatNode($node);
    $node = $node->getNext();
}

border();

$node = $mecab->parseToNode($str_long);
while ($node) {
    echo $node->toString();
    $node = $node->getNext();
}

border();
