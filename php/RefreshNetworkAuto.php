<?php
	echo "before\n";
	$dbname='localhost';
	$dbuser='gmre';
	$dbpass='gmre';
	$conn=mysql_connect($dbname,$dbuser,$dbpass);
	mysql_select_db('gmre');
	$rez1=mysql_query("SELECT * FROM Aux");
	while($rows=mysql_fetch_array($rez1))
	{
		if ($rows['param']==0)
		{
			mysql_query("UPDATE Aux SET param=1;");
			$rez=mysql_query("SELECT * FROM Id_statii ORDER BY statii ASC;");
			$i=0;
			$statii=array();
			
			while ($row=mysql_fetch_array($rez))
			{
				$statii[$i++]=$row['statii'];
			}
			
			$j=0;
			while ($j<count($statii))
			{
				$output="";
				$output2="";
				$aux="";
				$aux2="";
				exec("/home/adrusu/Training/Php/Versiunea2/Build $statii[$j] | grep '-'",$output);
				foreach ($output as $row)
				{
					$aux=$aux.$row;
				}
			
				$aux = str_replace(" ", "<br />", $aux);
				exec("/home/adrusu/Training/Php/Versiunea2/Patches $statii[$j]",$output2);
				
				foreach ($output2 as $row2)
				{
					$aux2=$aux2.$row2.',';
				}
		
				$aux2 = str_replace(",", "<br />", $aux2);

		
				$var="UPDATE Id_statii SET build=\"".$aux."\",patches=\"".$aux2."\" WHERE statii=$statii[$j];";
				mysql_query($var);
				$j=$j+1;
			}
			mysql_query("UPDATE Aux SET param=0;");
		}
	}
	echo "after\n";

?>
