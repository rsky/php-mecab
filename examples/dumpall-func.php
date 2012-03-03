<?php
/**
 * php-mecab/examples
 * dump all nodes
 * charset=utf-8
 */

require_once dirname(__FILE__) . '/common.inc.php';

$mecab = mecab_new($arg);

function call_format($node)
{
    return format(mecab_node_surface($node), mecab_node_feature($node),
                    mecab_node_id($node), mecab_node_stat($node));
}

if ($node = mecab_sparse_tonode($mecab, $str)) {
    border();
    while ($node) {
        $ar = array(
            'node' => mecab_node_toarray($node),
            'prev' => '-',
            'next' => '-',
            'enext' => '-',
            'bnext' => '-',
            'rpath' => '-',
            'lpath' => '-',
        );
        if ($prev = mecab_node_prev($node)) {
            $ar['prev'] = call_format($prev);
        }
        if ($next = mecab_node_next($node)) {
            $ar['next'] = call_format($next);
        }
        if ($enext = mecab_node_enext($node)) {
            $ar['enext'] = call_format($enext);
        }
        if ($bnext = mecab_node_bnext($node)) {
            $ar['bnext'] = call_format($bnext);
        }
        if ($rpath = mecab_node_rpath($node)) {
            $ar['rpath'] = array(
                'prob' => mecab_path_prob($rpath),
                'cost' => mecab_path_cost($rpath),
                'rnode' => '-',
                'lnode' => '-',
            );
            if ($rpath_rnode = mecab_path_rnode($rpath)) {
                $ar['rpath']['rnode'] = call_format($rpath_rnode);
            }
            if ($rpath_lnode = mecab_path_lnode($rpath)) {
                $ar['rpath']['lnode'] = call_format($rpath_lnode);
            }
        }
        if ($lpath = mecab_node_lpath($node)) {
            $ar['lpath'] = array(
                'prob' => mecab_path_prob($lpath),
                'cost' => mecab_path_cost($lpath),
                'rnode' => '-',
                'lnode' => '-',
            );
            if ($lpath_rnode = mecab_path_rnode($lpath)) {
                $ar['lpath']['rnode'] = call_format($lpath_rnode);
            }
            if ($lpath_lnode = mecab_path_lnode($lpath)) {
                $ar['lpath']['lnode'] = call_format($lpath_lnode);
            }
        }
        print_r($ar);
        border();
        $node = mecab_node_next($node);
    }
}

mecab_destroy($mecab);
