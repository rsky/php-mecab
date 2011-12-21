<?php
/**
 * php-mecab/examples
 * show dictionary information (OO-API)
 * charset=utf-8
 */

require_once dirname(__FILE__) . '/common.inc.php';

$mecab = new MeCab_Tagger($arg);

border();

writefln('MeCab Version: %s', MeCab::VERSION);

border();

writeln('Dictionary Information:');
print_r($mecab->dictionaryInfo());

border();
