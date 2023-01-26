<?php
$url = "https://api.thingspeak.com/channels/2014575/feeds.xml?results=1"; 
$channel1 = simplexml_load_file($url); 
$channel_name[] = (string)$channel1->name;
//echo $channel->feeds->feed[0]->field1;
//echo $channel1->field1.":<br>";

date_default_timezone_set('America/Bogota'); // esta l�nea es importante cuando el servidor es REMOTO y est� ubicado en otros pa�ses como USA o Europa. Fija la hora de Colombia para que grabe correctamente el dato de fecha y hora con CURDATE y CURTIME, en la base de datos.

$fecha = date("Y-m-d H:i:s");
$hora = date("h:i:s");

$i = 0;
foreach ($channel1->feeds->feed as $nodo) {
    //$fecha = $nodo->{'created-at'};
    echo "Fecha: ".$fecha."<br>";
	echo $channel1->field1.": ".$nodo->field1."<br>";
    echo $channel1->field2.": ".$nodo->field2."<br>";
    $dates[$i]=$nodo->$fecha;
    $vibrates[$i]=$nodo->field1;
    $rfids[$i]=$nodo->field2;
    $i++;
	}

//include "conexion.php";  // Conexi�n tiene la informaci�n sobre la conexi�n de la base de datos.

//$hum = $_GET["humedad"]; // el dato de humedad que se recibe aqu� con GET denominado humedad, es enviado como parametro en la solicitud que realiza la tarjeta microcontrolada
//$temp = $_GET["temperatura"]; // el dato de temperatura que se recibe aqu� con GET denominado temperatura, es enviado como parametro en la solicitud que realiza la tarjeta microcontrolada

//$ID_TARJ = $_GET["ID_TARJ"];

//$mysqli = new mysqli($host, $user, $pw, $db); // Aqu� se hace la conexi�n a la base de datos.

//$sql1 = "INSERT into datos_medidos (ID_TARJ, temperatura, humedad, fecha, hora) VALUES ('$ID_TARJ', '$temp', '$hum', '$fecha', '$hora')"; // Aqu� se ingresa el valor recibido a la base de datos.
//echo "sql1...".$sql1; // Se imprime la cadena sql enviada a la base de datos, se utiliza para depurar el programa php, en caso de alg�n error.
//$result1 = $mysqli->query($sql1);
?>