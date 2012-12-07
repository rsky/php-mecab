<?php
/**
 * php-mecab/examples
 * parse N-Best (OO-API)
 * charset=utf-8
 */

require_once dirname(__FILE__) . '/common.inc.php';

$mecab = new MeCab_Tagger($arg);

if ($mecab->parseNBestInit($str_long)) {
   border();
    for ($i = 0; ($i < NBEST_MAX_RESULT && ($next = $mecab->next())); $i++) {
        echo $next;
        border();
    }
}
