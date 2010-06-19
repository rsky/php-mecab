<?php 
/**
 * php-mecab/examples
 * test like official bindings examples
 * charset=utf-8
 */

require_once dirname(__FILE__) . '/common.inc.php';

$sentence = '太郎はこの本を二郎を見た女性に渡した。';

if (isset($_SERVER['argv'])) {
    $options = $_SERVER['argv'];
    array_shift($options);
} else {
    $options = array();
}
writeln(MECAB_VERSION);

$t = mecab_new($options);

writeln(mecab_sparse_tostr($t, $sentence));

$m = mecab_sparse_tonode($t, $sentence);
while ($m) {
    writeln(mecab_node_surface($m) . "\t" . mecab_node_feature($m));
    $m = mecab_node_next($m);
}
writeln('EOS');

$n = mecab_sparse_tonode($t, $sentence);
$len = mecab_node_sentence_length($n);
for ($i = 0; $i <= $len; $i++) {
    $b = mecab_node_begin_node_list($n, $i);
    $e = mecab_node_end_node_list($n, $i);
    while ($b) {
        writefln("B[%d] %s\t%s", $i, mecab_node_surface($b), mecab_node_feature($b));
        $b = mecab_node_bnext($b);
    }
    while ($e) {
        writefln("E[%d] %s\t%s", $i, mecab_node_surface($e), mecab_node_feature($e));
        $e = mecab_node_bnext($e);
    }
}
writeln('EOS');

$di = mecab_dictionary_info($t);
foreach ($di as $d) {
    writefln('filename: %s', $d['filename']);
    writefln('charset: %s', $d['charset']);
    writefln('size: %d', $d['size']);
    writefln('type: %d', $d['type']);
    writefln('lsize: %d', $d['lsize']);
    writefln('rsize: %d', $d['rsize']);
    writefln('version: %d', $d['version']);
}
