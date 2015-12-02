<?php
/**
 * php-mecab/examples
 * dump all nodes (with SPL and Overloading)
 * charset=utf-8
 */

require_once dirname(__FILE__) . '/common.inc.php';

$mecab = new MeCab\Tagger($arg);

function call_format($node)
{
    return format($node->surface, $node->feature, $node->id, $node->stat);
}

if ($iter = $mecab->parseToNode($str)) {
    border();
    foreach ($iter as $node) {
        $ar = array(
            'node' => $node->toArray(),
            'prev' => '-',
            'next' => '-',
            'enext' => '-',
            'bnext' => '-',
            'rpath' => '-',
            'lpath' => '-',
        );
        if ($node->prev) {
            $ar['prev'] = call_format($node->prev);
        }
        if ($node->next) {
            $ar['next'] = call_format($node->next);
        }
        if ($node->enext) {
            $ar['enext'] = call_format($node->enext);
        }
        if ($node->bnext) {
            $ar['bnext'] = call_format($node->bnext);
        }
        if ($rpath = $node->rpath) {
            $ar['rpath'] = array(
                'prob' => $rpath->prob,
                'cost' => $rpath->cost,
                'rnode' => '-',
                'lnode' => '-',
            );
            if ($rpath->rnode) {
                $ar['rpath']['rnode'] = call_format($rpath->rnode);
            }
            if ($rpath->lnode) {
                $ar['rpath']['lnode'] = call_format($rpath->lnode);
            }
        }
        if ($lpath = $node->lpath) {
            $ar['lpath'] = array(
                'prob' => $lpath->prob,
                'cost' => $lpath->cost,
                'rnode' => '-',
                'lnode' => '-',
            );
            if ($lpath->rnode) {
                $ar['lpath']['rnode'] = call_format($lpath->rnode);
            }
            if ($lpath->lnode) {
                $ar['lpath']['lnode'] = call_format($lpath->lnode);
            }
        }
        print_r($ar);
        border();
    }
}
