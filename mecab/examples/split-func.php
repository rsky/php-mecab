<?php
/**
 * php-mecab/examples
 * split string into an array of part-of-speech
 * charset=utf-8
 */

require_once dirname(__FILE__) . '/common.inc.php';

print_r(mecab_split($str));
