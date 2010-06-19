<?php 
/**
 * php-mecab/examples
 * get begen/end node list (OO-API)
 * charset=utf-8
 */

require_once dirname(__FILE__) . '/common.inc.php';

$mecab = new MeCab_Tagger($arg);

if ($node = $mecab->parseToNode($str)) {
    border();
    $len = $node->getSentenceLength();
    for ($i = 0; $i <= $len; $i++) {
        if ($b = $node->getBeginNodeList($i)) {
            while ($b) {
                writefln("B[%d] %s\t%s", $i, $b->getSurface(), $b->getFeature());
                $b = $b->getBNext();
            }
        }
        if ($e = $node->getEndNodeList($i)) {
            while ($e) {
                writefln("E[%d] %s\t%s", $i, $e->getSurface(), $e->getFeature());
                $e = $e->getBNext();
            }
        }
    }
}
