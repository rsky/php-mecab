<?php
/**
 * php-mecab/examples
 * get begen/end node list (OO-API with SPL and Overloading)
 * charset=utf-8
 */

require_once dirname(__FILE__) . '/common.inc.php';

$mecab = new MeCab_Tagger($arg);

if ($node = $mecab->parseToNode($str)) {
    border();
    $len = $node->getSentenceLength();
    for ($i = 0; $i <= $len; $i++) {
        if ($bn = $node->getBeginNodeList($i)) {
            $bn->setTraverse(MeCab_Node::TRAVERSE_BNEXT);
            foreach ($bn as $b) {
                writefln("B[%d] %s\t%s", $i, $b->surface, $b->feature);
            }
        }
        if ($en = $node->getEndNodeList($i)) {
            $en->setTraverse(MeCab_Node::TRAVERSE_BNEXT);
            foreach ($en as $e) {
                writefln("E[%d] %s\t%s", $i, $e->surface, $e->feature);
            }
        }
    }
}
