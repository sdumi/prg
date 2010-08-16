<?
include 'objMysql.php';

        if ($_GET['text']){
                $sql = new objSQL;
                
                $sql->MySqlConnect();
                $sql->MySqlInsert($_GET['text']);
                $sql->MysqlClose();
        }
?>
<html>
<body>
        <form action="sqlUpdate.php" method="get">
                <input type="text" name="text">
                <input type="submit" value="OK">
        </form>
</body>
</html>
