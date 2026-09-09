<!-- Author: Cian Bourke  --> 
<!-- Date: 20/11/2025  --> 
<!-- Programme: This php page will serve as the index for Book Database  --> 
<!DOCTYPE html>
<?php 
session_start(); 

include 'Header.php';

?>

<html>
<head>
    <title>Cian's library book reservation</title>

    <style>

        html,body /* This css cody is for the background image of index */
         {
            margin: 0; 
            padding: 0;
            width: 100%;
            height: 100vh;
            background-image: url("bookImage.webp");
            background-size: cover;
            background-repeat: no-repeat;
            background-position: center center;
            background-attachment: fixed;
            display: flex;
            justify-content: center;
            align-items: center;
        }

        .content /* This centerrs and styles box buttons are in*/
        {
            background-color: white;
            padding: 26px 26px;
            border-radius: 12px;
            text-align: center;
        }

        .box /* This centers and styles the button boxes*/
        {
            border: 2px solid black;
            padding: 10px 20px;
            display: inline-block;
            color: black;
        }

        
    </style>
</head>
<body>
    <div class="content">
        <h1>Welcome to the Library</h1>
        <p>Select login to continue or register to create an account</p>

        <?php if (isset($_SESSION['username'])): ?><!-- If user isnt signed in btton takes to Login page -->

        <a href="Search.php" class="box">Login</a>
        <?php else: ?>
        <a href="Login.php" class="box">Login</a> <!-- If user isnt logged in itll take to Login page -->            
        <?php endif; ?>

        <a href="Register.php" class="box">Register</a>
    </div>
</body>
</html>
<?php include 'Footer.php'; ?>