<!-- Author: Cian Bourke  --> 
<!-- Date: 20/11/2025  --> 
<!-- Programme: This php page will allow users to log in to User account  --> 
<!DOCTYPE html>

<?php

session_start();

include 'Header.php';

// Connect to the database on phpadmin
$mysqli = new mysqli("localhost", "root", "", "assignmentproject");

if ($mysqli->connect_error) //check if it connects to the database
{
    die("Connection failed: " . $mysqli->connect_error);//if it doesnt stop and display message
}

$errors = [];// Array stores errors messages in the array

if ($_SERVER['REQUEST_METHOD'] === 'POST') //run the database code if the user has submitted details
{
    //This makes sure username and password have no space issues or the string will be empty
    $username = trim($_POST['username'] ?? '');
    $password = $_POST['password'] ?? '';

    if ($username === '' || $password === '') //If the password or username are empty dsiplays error message
    {
        $errors[] = "Username and password are required Please enter both.";
    } 

    else 
    {
        $stmt = $mysqli->prepare("SELECT Password FROM users WHERE Username = ?");

        $stmt->bind_param("s", $username);

        $stmt->execute();

        $stmt->bind_result($stored_password);

        // check if a matching username can be found in database
        if ($stmt->fetch()) 
        {
            if ($password === $stored_password)
            {
                $_SESSION['username'] = $username;//if correct session stores username
                header("Location: search.php");
                exit();
            } 
            else 
            {
                $errors[] = "Incorrect password.";//if incorrect session display error message
            }
        } 
        else //If no username is found display error message
        {
            $errors[] = "Username not found.";
        }
        $stmt->close();
    }
}

?>
<html>
    <head>
        <title>Login</title>
    </head>
<style>


        .box /* This centers and styles the button boxes*/
        {
            border: 1px solid black;
            padding: 10px 20px;
            display: inline-block;
            color: black;
            
        }
        .content /* This centerrs and styles box buttons are in*/
        {
            background-color: white;
            padding: 26px 26px;
            border-radius: 12px;
            text-align: center;
        }

        body /* This css cody is for the background image of Login */
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
        

        
    </style>
<body>
        <div class="content">
    
    <h2>Login</h2>
<?php 
foreach ($errors as $e): echo "<p style='color:red;'>$e</p>"; endforeach; 
?>

<form method="post">
  Username: <input name="username" class="box" autocomplete = "off" required><br>
  Password: <input type="password" class="box" name="password" required><br>
  <button type="submit">Login</button>
  <a href="Register.php">if you don't have an account? Register here</a>
</form>
</body>
</html>

<?php include 'Footer.php'; ?>