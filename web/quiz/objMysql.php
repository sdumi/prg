<?
class objSQL{
        var $MySqlServer='rotims00000';
        var $MySqlUser='coco';
        var $MySqlPassword='coco83';
        var $MySqlDB='coco';
        var $MySqlTable='test_razvan';
        var $dbo;
        
        var $id;
        var $text;
        
        
        function MySqlConnect(){
           $this->dbo=mysql_connect($this->MySqlServer.':/tmp/mysql.sock',$this->MySqlUser,$this->MySqlPassword) or die('Connection to server fail '.mysql_error());
           $db_selected = mysql_select_db($this->MySqlDB, $this->dbo) or die('DB select fail '. mysql_error());     
        }

        function MySqlInsert($text){
//                $this->id=$id;
                $this->text=$text;
                
                $mysql_querry="insert into $this->MySqlTable (text) values ('$this->text')";
                mysql_query($mysql_querry,$this->dbo) or die ('MySqlInsert query fail '.mysql_connect());
                 
        }
        
        function MysqlClose(){
                mysql_close($this->dbo);
        }
}

?>
