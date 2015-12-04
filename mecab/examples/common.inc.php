<?php
/**
 * php-mecab/examples
 * common configuration file
 * charset=utf-8
 */

if (!extension_loaded('mecab')) {
    $_module_suffix = (PHP_SHLIB_SUFFIX == 'dylib') ? 'so' : PHP_SHLIB_SUFFIX;
    dl('mecab.' . $_module_suffix) || die('skip');
}

/**
 * N-Best 解を表示するときの上限
 */
define('NBEST_MAX_RESULT', 3);

/**
 * 改行文字
 */
defined('PHP_EOL') || define('PHP_EOL', strncasecmp(PHP_OS, 'WIN', 3) ? "\n" : "\r\n");

/**
 * 辞書のパス
 * 設定ファイル・辞書・ユーザ辞書のパスは、それぞれ php.ini の
 * mecab.default_rcfile, mecab.default_dicdir, mecab.default_userdic で設定できる。
 */
$dic = '/opt/local/lib/mecab/dic/ipadic-utf8';
$_dl = __LINE__ - 1;
if (!empty($dic)) {
    if (!file_exists($dic)) {
        printf('%s is not exists.%s', $dic, PHP_EOL);
        printf('please edit line %d in %s.%s', $_dl, __FILE__, PHP_EOL);
        exit(1);
    }
    ini_set('mecab.default_dicdir', $dic);
}

/**
 * 解析オプションは配列で指定する。
 * 値をとるオプションは、$options = array('-d', '/usr/local/lib/mecab/dic/ipadic')
 * のようにオプション名の次に値を入れる。
 * ('オプション名' => '値' の連想配列でも良い)
 * また、パスを指定するオプション (-r, -d, -u) は safe_mode と open_basedir の
 * 影響を受け、一部のオプション (-o, -v, -h) は利用できない。
 */
$arg = array();
$arg['-N'] = NBEST_MAX_RESULT;
$arg['-l'] = 1;

$arg_all_morphs = $arg;
$arg_all_morphs[] = '-a';

$arg_format = array();
$arg_format['--node-format'] = 'Node (%pi): %m' . PHP_EOL;
$arg_format['--bos-format'] = 'BOS (%pi)' . PHP_EOL;
$arg_format['--eos-format'] = 'EOS (%pi)' . PHP_EOL;
$arg_format['--unk-format'] = 'Unknown (%pi): %m' . PHP_EOL;

$arg_wakati = array('-O' => 'wakati');

// 解析用文字列
$str = '太郎は次郎が持っている本を花子に渡した。';
$str_long = <<<EOS
MeCab は 京都大学情報学研究科−日本電信電話株式会社コミュニケーション科学基礎研究所
共同研究ユニットプロジェクトの一環として開発されたオープンソース形態素解析エンジンです.
言語, 辞書, コーパスに依存しない汎用的な設計を基本方針としています.
EOS;

function border()
{
    static $border = NULL;
    if ($border === NULL) {
        $border = PHP_EOL . str_repeat('-', 72) . PHP_EOL . PHP_EOL;
    }
    echo $border;
}

function writeln($str)
{
    echo $str, PHP_EOL;
}

function writefln($fmt)
{
    $args = func_get_args();
    array_shift($args);
    vprintf($fmt, $args);
    echo PHP_EOL;
}

if (defined('MECAB_BOS_NODE')) {
    function format($surface, $feature, $id, $stat)
    {
        switch ($stat) {
            case MECAB_BOS_NODE:
                $str = 'BOS';
                break;
            case MECAB_EOS_NODE:
                $str = 'EOS';
                break;
            default:
                $str = $surface;
        }
        return sprintf('%d: %s [%s]', $id, $str, $feature);
    }
} else {
    function format($surface, $feature, $id, $stat)
    {
        switch ($stat) {
            case MeCab\BOS_NODE:
                $str = 'BOS';
                break;
            case MeCab\EOS_NODE:
                $str = 'EOS';
                break;
            default:
                $str = $surface;
        }
        return sprintf('%d: %s [%s]', $id, $str, $feature);
    }
}

function catcher($errno, $errstr, $errfile, $errline, $errcontext)
{
    border();
    writefln('%s:%d:[%d] %s', $errfile, $errline, $errno, $errstr);
    //print_r($errcontext);
    if ($errno !== E_DEPRECATED) {
        die($errno);
    }
}

set_error_handler('catcher');
