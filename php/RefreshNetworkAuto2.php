#!/local/dev/bin/php -q
<?php
echo "before\n";
exec("/usr/bin/which which",$output);
exec('env',$output);
shell_exec('env > /home/dsipos/t.txt');
echo "after\n";
?>
