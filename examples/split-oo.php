<?php 
/**
 * php_mecab/examples
 * split string into an array of part-of-speech (OO-API)
 * charset=utf-8
 */

require_once dirname(__FILE__) . '/common.inc.php';

/**
 * Determine whether the part-of-speech is a noun.
 *
 * Annotate with comment.
 * This method takes "int $posid" instead of "array $node_info".
 *
 * @param   int $posid
 * @return  bool
 * @mecab_node_attribute posid
 */
function mecab_ipadic_is_noun($posid)
{
    return $posid >= 37 && $posid <= 66;
}

class MeCab_IPADic
{
    /**
     * Determine whether the part-of-speech is a noun.
     *
     * Annotate with comment.
     * This method takes "int $posid" instead of "array $node_info".
     *
     * @param   int $posid
     * @return  bool
     * @access  public
     * @static
     * @mecab_node_attribute posid
     */
    public static function isNoun($posid)
    {
        return $posid >= 37 && $posid <= 66;
    }
}

border();

print_r(MeCab::split($str));

border();

print_r(MeCab::split($str, null, null, 'mecab_ipadic_is_noun'));
print_r(MeCab::split($str, null, null, array('MeCab_IPADic', 'isNoun')));

border();
