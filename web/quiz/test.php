<?
$a = "post_processed_string"; 
$b = array("post_", "_");
$c = array("", " ");
$d = ucwords(str_replace($b,$c,$a));

var_dump($d);
?>