<?php
/**
 * php-mecab/examples
 * dump all nodes
 * charset=utf-8
 */

require_once dirname(__FILE__) . '/common.inc.php';

$mecab = new MeCab\Tagger($arg);

function call_format($node)
{
    return format($node->getSurface(), $node->getFeature(), $node->getId(), $node->getStat());
}

if ($node = $mecab->parseToNode($str)) {
    border();
    while ($node) {
        $ar = array(
            'node' => $node->toArray(),
            'prev' => '-',
            'next' => '-',
            'enext' => '-',
            'bnext' => '-',
            'rpath' => '-',
            'lpath' => '-',
        );
        if ($prev = $node->getPrev()) {
            $ar['prev'] = call_format($prev);
        }
        if ($next = $node->getNext()) {
            $ar['next'] = call_format($next);
        }
        if ($enext = $node->getENext()) {
            $ar['enext'] = call_format($enext);
        }
        if ($bnext = $node->getBNext()) {
            $ar['bnext'] = call_format($bnext);
        }
        if ($rpath = $node->getRPath()) {
            $ar['rpath'] = array(
                'prob' => $rpath->getProb(),
                'cost' => $rpath->getCost(),
                'rnode' => '-',
                'lnode' => '-',
            );
            if ($rpath_rnode = $rpath->getRNode()) {
                $ar['rpath']['rnode'] = call_format($rpath_rnode);
            }
            if ($rpath_lnode = $rpath->getLNode()) {
                $ar['rpath']['lnode'] = call_format($rpath_lnode);
            }
        }
        if ($lpath = $node->getLPath()) {
            $ar['lpath'] = array(
                'prob' => $lpath->getProb(),
                'cost' => $lpath->getCost(),
                'rnode' => '-',
                'lnode' => '-',
            );
            if ($lpath_rnode = $lpath->getRNode()) {
                $ar['lpath']['rnode'] = call_format($lpath_rnode);
            }
            if ($lpath_lnode = $lpath->getLNode()) {
                $ar['lpath']['lnode'] = call_format($lpath_lnode);
            }
        }
        print_r($ar);
        border();
        $node = $node->getNext();
    }
}
