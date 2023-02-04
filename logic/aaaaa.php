<?php
header("Refresh:3"); // refresca la pagina web cada 3 segundos
include "../conexion.php";
$url = "https://api.thingspeak.com/channels/2014575/feeds.xml?results=1&quot;metadata=true&quot"; 
$channel1 = simplexml_load_file($url); 
$channel_name[] = (string)$channel1->name;
//echo $channel->feeds->feed[0]->field1;
//echo $channel1->field1.":<br>";

//date_default_timezone_set('America/Bogota'); // esta l�nea es importante cuando el servidor es REMOTO y est� ubicado en otros pa�ses como USA o Europa. Fija la hora de Colombia para que grabe correctamente el dato de fecha y hora con CURDATE y CURTIME, en la base de datos.

//$fecha = date("Y-m-d H:i:s");
//$hora = date("h:i:s");

$channel_metadata = (string)$channel1->metadata;
echo $channel_metadata."<br>"."<br>";

$i = 0;
foreach ($channel1->feeds->feed as $nodo) {
    // Saco la fecha del xml
    $fechaNo = $nodo->{'created-at'};
    $my_array1 = str_split($fechaNo);
    
    
    // Elimino la parte de la fechya que no se nececita
    $fecha1 = array_slice($my_array1, 0, 10);
    $fecha11 = implode($fecha1);
    $fecha2 = array_slice($my_array1, 11, -1);
    $fecha21 = implode($fecha2);

    $fecha3 = $fecha11." ".$fecha21;
    $fecha = date("Y-m-d H:i:s", strtotime( $fecha3));
    
    // resto 5 horas para pasar la hora a la actual del territorio
    $fecha = strtotime ( '-5 hour' , strtotime ($fecha) ) ; 
    $fecha = date ( 'Y-m-d H:i:s' , $fecha); 
    
    //Se implimen datos
    echo "Fecha: ".$fecha."<br>";
	echo $channel1->field1.": ".$nodo->field1."<br>";
    echo $channel1->field2.": ".$nodo->field2."<br>";
    $dates[$i]=$fecha;
    $vibrates[$i]=$nodo->field1;
    $rfids[$i]=$nodo->field2;
    $alarms[$i]=$nodo->field4;
    $i++;
	}

$mysqli = new mysqli($host, $user, $pw, $db);
$sql = "SELECT fecha FROM alarma ORDER by id DESC LIMIT 1";
$result1 = $mysqli->query($sql);
$row = $result1->fetch_array(MYSQLI_NUM);
echo "<br>";

$dateOld = $row[0];
echo "old: ".$dateOld."<br>";
echo "presente: ".($dates[0])."<br>";
 
$comp = "0000-00-00 00:00:00";
$myarray3 = str_split($dates[0]);
$myarray3 = implode($myarray3);
//echo $myarray3."<br>";

$nombre = "PUERTA PRINCIPAL";
if((trim($dates[0]) != trim($dateOld)) && ($myarray3 != $comp)){
    $dateOld = $dates[0];
     // Aqu� se hace la conexi�n a la base de datos.

    $sql1 = "INSERT into alarma (nombre,vibracion,rfid,alarma,fecha) VALUES ('$nombre','$vibrates[0]', '$rfids[0]', '$alarms[0]', '$dates[0]')"; // Aqu� se ingresa el valor recibido a la base de datos.
    echo "sql1...".$sql1; // Se imprime la cadena sql enviada a la base de datos, se utiliza para depurar el programa php, en caso de alg�n error.
    $result1 = $mysqli->query($sql1);
}else{
    echo "El dato es el mismo aterior";
}
?>