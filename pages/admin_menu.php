<?php
    header("Refresh:5"); // refresca la pagina web cada 3 segundos
    include "../conexion.php";
    include "../logic/admin_securityLogic.php";

    // Inicio o reanudacion de una sesion
    $nombre_admin   = $_SESSION['NOM_USUARIO'];
    $id_admin       = $_SESSION['ID_USUARIO'];
    $tipo_usuario   = $_SESSION['TIPO_USUARIO'];

?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="preconnect" href="https://fonts.googleapis.com">
    <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
    <link rel="preconnect" href="https://fonts.gstatic.com">
    <link href="https://fonts.googleapis.com/css2?family=Kanit:ital,wght@0,400;1,400;1,500;1,900&family=Lobster&display=swap" rel="stylesheet">
    <script src="https://kit.fontawesome.com/b50f20f4b1.js" crossorigin="anonymous"></script>
    <link rel="icon" href="../images/icon.png">
    <link rel="stylesheet" href="../css/style.css">
    <link rel="stylesheet" href="../css/style_admin.css">
    <link rel="stylesheet" href="../css/style_collapsed_menu.css">
    <title>Admin</title>
</head>
<body>

<div id="particles-js"></div>
<!-- CABECERA DE TRABAJO -->
<header>

    <div class="contenedor_principal">
        <div class="contenedor_logo">
            <a href="../index.php"><img id="imagen_logo" src="../images/logo.png" alt="Error al cargar la imagen"></a>
        </div>
        <div class="contenedor_nombre_adm">
            <span> BIENVENIDO </span>
            <span>
                <?php
                    echo $nombre_admin;
                ?>

            </span>
        </div>
        <div class="contenedor_admin">
            Nombre de usuario:
            <span class="info_admin">
                <?php
                    echo " $nombre_admin";
                ?>
            </span><br>
            <span>
                ID usuario:
            </span>
            <span class="info_admin">
                <?php
                    echo " $id_admin";
                ?>
            </span><br>
                Tipo de usuario:
            <span>
                <?php
                    echo $tipo_usuario;
                ?>
            </span>



           <div class="contenedor_cerrar_sesion" >
                <a href="../logic/cerrar_sesion.php"><button class="btn-cierre-sesion">Cerrar Sesion</button></a>
           </div>
    </div>
</header>

<!-- INICIO DE SLIDE MENU -->

<div class = "contenedor_pr_menu">
    <div id="slide-menu" class="menu-collapsed">

        <!-- HEADER -->
        <div id="header">

            <div id="menu-btn">
                <div class="btn-logo"></div>
                <div class="btn-logo"></div>
                <div class="btn-logo"></div>
            </div>
            <div id="title"><span>PERFIL</span></div>

        </div>

        <!-- PROFILE -->
        <div id="profile">
            <div id="photo"><img src="../images/profile2.png" alt=""></div>
            <div id="name"><span>Nombre: <?php echo $nombre_admin ?></span></div>
            <div id="name"><span>Id: <?php echo $id_admin ?></span></div>
        </div>

        <!-- ITEMS -->
         <!--
        <div id="menu-items">

        
            <div class="item">
                <a href="../index.php">
                    <div class="icon"><img src="../images/home.png" alt=""></div>
                    <div class="title"><span>Menu Principal</span></div>

                </a>
            </div>

             
                <div class="item separator">
                </div>

            <div class="item">
                <a href="admin_estadisticas.php">
                    <div class="icon"><img src="../images/stadistics.png" alt=""></div>
                    <div class="title"><span>Estadisticas</span></div>

                </a>
            </div>

                
                <div class="item separator">
                </div>

            <div class="item">
                <a href="#">
                    <div class="icon"><img src="../images/users_admin.png" alt=""></div>
                    <div class="title"><span>Gestion de usuarios</span></div>

                </a>
            </div>
               
                <div class="item separator">
                </div>

            <div class="item">
                <a href="admin_edition_client.php">
                    <div class="icon"><img src="../images/edit_user.png" alt=""></div>
                    <div class="title"><span>Editar usuario</span></div>

                </a>
            </div>

               
                 <div class="item separator">
                </div>

            <div class="item">
                <a href="admin_delete_user.php">
                    <div class="icon"><img src="../images/delete_user.png" alt=""></div>
                    <div class="title"><span>Eliminar usuario</span></div>

                </a>
            </div>

        
                 <div class="item separator">
                </div>

            <div class="item">
                <a href="admin_create_user.php">
                    <div class="icon"><img src="../images/add-admin.png" alt=""></div>
                    <div class="title"><span>Creación de usuarios</span></div>

                </a>
            </div>

        


        </div>
        -->

        <!--
            =================================
            BOTON DE CARGA SUPERIOR
            =================================
        -->
        <div class="footer">
            <a href="#">
                <div class="btn_carga"><img src="../images/pages_up.png" alt=""></div>
            </a>
        </div>
    </div>
</div>




<!-- BARRA DE NAVEGACION -->
<div class="contenedor_menu">

    <div class="contenedor_listas">
        <ul>
            <a href="admin_menu.php"><li class="btn-inicio-go_home">Menu Principal</li></a>
            <!--
            <a href="../index.php"><li class="btn-inicio-go_home">Menu Principal</li></a>
            
            <a href="suscription.php"><li>Suscripciones<i class="fa fa-angle-down"></i></a>
                <ul>
                    <a href="compras.php?suscp=Prem"><li> Premiun</li></a>
                    <a href="compras.php?suscp=Basic"><li> Basico</li></a>
                </ul>
            </li>
            <a href="quienes_somos.php"><li class="btn-inicio-go_catalogo">¿Quienes somos?</li></a>
            Suscripciones-->
        </ul>
    </div>
</div>


<!-- CONTENEDOR CON TABLA DE USUARIOS -->
<div class="contenedor_tabla">
<table class="users_table">
    <tr>
        <!-- 
        <th>NUMERO DE REGISTRO</th>
        <th>ID</th>
        <th>NOMBRE</th>
        <th>FECHA</th>
        <th>TIPO ID</th>
        <th>DIRECCION</th>
        <th>DEPARTAMENTO</th>
        <th>MUNICIPIO</th>
        <th>CELULAR</th>
        <th>TIPO DE USUARIO</th>
        -->
        <th>ID</th>
        <th>FECHA</th>
        <th>HORA</th>
        <th>VIBRACIÓN</th>
        <th>RFID</th>
        <th>ALARMA</th>


    </tr>
    <?php
        $mysqli = new mysqli($host, $user, $pw, $db);
        $sqli = "SELECT * FROM alarma ORDER BY id DESC LIMIT 10";
        //$result = mysqli_query($conectar, $sqli);
        //while($mostrar = mysqli_fetch_array($result)){
        $result = $mysqli->query($sqli);
        while($mostrar = $result->fetch_array(MYSQLI_NUM)){
    ?>
    <tr>
          
        <td> <?php  // id
        echo $mostrar[0]?> 
        </td>
        <td><?php // fecha
        $my_array = str_split($mostrar[4]);
        $fecha = array_slice($my_array, 0, 10);
        $fecha1 = implode($fecha);
        echo $fecha1?>
        </td>
        <td><?php // fecha
        $my_array2 = str_split($mostrar[4]);
        $fecha2 = array_slice($my_array2, 11);
        $fecha21 = implode($fecha2);
        echo $fecha21?>
        </td>
        <td><?php  // vibracion
        if($mostrar[1]<1000){?>
            <img src="../images/verde.png" width='60' height='60'/><?php 
        }else if(($mostrar[1]>= 1000) && ($mostrar[1]< 3500)){?> 
            <img src="../images/amarillo.png" width='92' height='60'/><?php 
        }else{?> 
            <img src="../images/rojo.png" width='85' height='85'/><?php 
        }?>
        </td>
        <td><?php  // rfid
        if($mostrar[2]==1){?>
            <img src="../images/ok.png" width='60' height='60'/><?php 
        }else if($mostrar[2]==0){?> 
            <img src="../images/nook.png" width='60' height='60'/><?php 
        }else{?> 
            <img src="../images/anonimo.png" width='60' height='60'/><?php 
        }?>
        </td>
        <td><?php  // alarma
        if($mostrar[3]==1){?>
            <img src="../images/alerta.png" width='60' height='60'/><?php 
        }else{?> 
            <img src="../images/noalerta.png" width='60' height='60'/><?php 
        }?>
        </td>
        
    </tr>
    <?php
        }
    ?>
    </table>
</div>


<!-- SCRIPT DE PARTICULAS -->
<script src="https://cdn.jsdelivr.net/npm/particles.js@2.0.0/particles.min.js"></script>
<script src="../js/app.js"></script>


<!-- SCRIPT MENU LATERAL-->
<script>
    const btn = document.querySelector('#menu-btn');
    const menu = document.querySelector('#slide-menu');


    btn.addEventListener('click', e => {
        menu.classList.toggle("menu-expanded");
        window.scrollTo(150,150);
        menu.classList.toggle("menu-collapsed");
    });

</script>


</body>
</html>