<?php
/**
 * php-mecab/examples
 * parse N-Best
 * charset=utf-8
 */

require_once dirname(__FILE__) . '/common.inc.php';

$mecab = mecab_new($arg);

if (mecab_nbest_init($mecab, $str_long)) {
   border();
    for ($i = 0; ($i < NBEST_MAX_RESULT && ($next = mecab_nbest_next_tostr($mecab))); $i++) {
        echo $next;
        border();
    }
}

mecab_destroy($mecab);
