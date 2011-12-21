<?php
/**
 * php-mecab/examples
 * show ini entries, constants, functions and methods provided by mecab extension
 * charset=utf-8
 */

require_once dirname(__FILE__) . '/common.inc.php';

$linebreak = PHP_EOL . PHP_EOL;

border();

echo 'INI entries:', $linebreak;
$entries = ini_get_all('mecab');
print_r($entries);

border();

echo 'Constants:', $linebreak;
if (substr(phpversion(), 0, 1) == '4') {
    $constants = array();
    $filter = create_function('$c', 'return preg_match("/^MECAB_/", $c);');
    foreach (array_filter(array_keys(get_defined_constants()), $filter) as $c) {
        $constants[$c] = constant($c);
    }
    print_r($constants);
} else {
    $constants = get_defined_constants(true);
    print_r($constants['mecab']);
}

border();

echo 'Functions:', $linebreak;
$functions = get_extension_funcs('mecab');
print_r($functions);

border();

if (class_exists('MeCab')) {
    echo 'Methods:', $linebreak;
    $classes = array('MeCab', 'MeCab_Tagger', 'MeCab_Node', 'MeCab_NodeIterator', 'MeCab_Path');
    $methods = array();
    foreach ($classes as $class) {
        $methods[$class] = get_class_methods($class);
    }
    print_r($methods);
    border();
}
