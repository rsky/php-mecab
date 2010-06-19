<?php 
/**
 * php-mecab/examples
 * test like official bindings examples (OO-API)
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

writeln(MeCab::VERSION);

$t = new MeCab_Tagger($options);

writeln($t->parse($sentence));

foreach ($t->parseToNode($sentence) as $m) {
    writeln($m->surface . "\t" . $m->feature);
}
writeln('EOS');

$n = $t->parseToNode($sentence);
$len = $n->sentence_length;
for ($i = 0; $i <= $len; $i++) {
    $b = $n->getBeginNodeList($i);
    $e = $n->getEndNodeList($i);
    while ($b) {
        writefln("B[%d] %s\t%s", $i, $b->surface, $b->feature);
        $b = $b->bnext;
    }
    while ($e) {
        writefln("E[%d] %s\t%s", $i, $e->surface, $e->feature);
        $e = $e->bnext;
    }
}
writeln('EOS');

$di = $t->dictionaryInfo();
foreach ($di as $d) {
    writefln('filename: %s', $d['filename']);
    writefln('charset: %s', $d['charset']);
    writefln('size: %d', $d['size']);
    writefln('type: %d', $d['type']);
    writefln('lsize: %d', $d['lsize']);
    writefln('rsize: %d', $d['rsize']);
    writefln('version: %d', $d['version']);
}
