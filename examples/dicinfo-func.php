<?php
/**
 * php-mecab/examples
 * show dictionary information
 * charset=utf-8
 */

require_once dirname(__FILE__) . '/common.inc.php';

$mecab = mecab_new($arg);

border();

writefln('MeCab Version: %s', MECAB_VERSION);

border();

writeln('Dictionary Information:');
print_r(mecab_dictionary_info($mecab));

border();

mecab_destroy($mecab);
