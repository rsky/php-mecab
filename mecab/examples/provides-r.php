<?php
/**
 * php-mecab/examples
 * show module dependencies, ini entries, constants, functions
 * and methods provided by mecab extension (use ReflectionExtension)
 * charset=utf-8
 */

require_once dirname(__FILE__) . '/common.inc.php';

$linebreak = PHP_EOL . PHP_EOL;

$reflector = new ReflectionExtension('mecab');
$mapper = create_function('$m', 'return $m->getName();');

border();

echo 'Module dependencies:', $linebreak;
print_r($reflector->getDependencies());

border();

echo 'INI entries:', $linebreak;
print_r($reflector->getINIEntries());

border();

echo 'Constants:', $linebreak;
print_r($reflector->getConstants());

border();

echo 'Functions:', $linebreak;
print_r(array_keys($reflector->getFunctions()));

border();

echo 'Classes:', $linebreak;
$classes = array();
foreach ($reflector->getClasses() as $className => $class) {
    $classes[$className] = array(
        'interfaces'    => null,
        'constants'     => $class->getConstants(),
        'properties'    => $class->getProperties(),
        'methods'       => array_map($mapper, $class->getMethods()),
    );
    if (method_exists($class, 'getInterfaceNames')) {
        $classes[$className]['interfaces'] = $class->getInterfaceNames();
    } else {
        $classes[$className]['interfaces'] = array_keys($class->getInterfaces());
    }
}
print_r($classes);

border();
